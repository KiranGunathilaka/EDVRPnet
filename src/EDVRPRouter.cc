
//EDVRPRouter.cc
#include "EDVRPRouter.h"

using namespace omnetpp;
using namespace edvrp;

// Register the module without namespace qualification
Define_Module(EDVRPRouter);

namespace edvrp {

void EDVRPRouter::initialize()
{
    // Read parameters
    routerId = par("routerId");
    helloInterval = par("helloInterval");
    holdTimeout = par("holdTimeout");
    routeTimeout = par("routeTimeout");
    updateInterval = par("updateInterval");
    linkBandwidth = par("linkBandwidth").doubleValue();
    linkLatency = par("linkLatency").doubleValue();
    alpha = par("alpha");
    beta = par("beta");

    // Initialize state
    routingTableChanged = false;


    convergenceTimeSignal = registerSignal("convergenceTime");
    routingTableSizeSignal = registerSignal("routingTableSize");
    messageCountSignal = registerSignal("messageCount");


    EV << "Router " << routerId << " registered signals: "
       << "convergenceTime=" << convergenceTimeSignal << ", "
       << "routingTableSize=" << routingTableSizeSignal << ", "
       << "messageCount=" << messageCountSignal << endl;

    // Initialize timers
    helloTimer = new cMessage("helloTimer");
    neighborAgingTimer = new cMessage("neighborAgingTimer");
    routeAgingTimer = new cMessage("routeAgingTimer");
    updateTimer = new cMessage("updateTimer");

    // Add self to routing table
    routingTable[routerId] = RoutingTableEntry(routerId, -1, 0.0, 0, simTime() + routeTimeout);
    sequenceCounters[routerId] = 1;

    // Schedule initial timers
    scheduleAt(simTime() + uniform(0, 1), helloTimer);
    scheduleAt(simTime() + 1.0, neighborAgingTimer);
    scheduleAt(simTime() + 1.0, routeAgingTimer);

    EV << "EDVRP Router " << routerId << " initialized with " << gateSize("port") << " ports" << endl;

    // Emit initial statistics - TESTING
    EV << "Router " << routerId << " emitting initial routing table size: " << routingTable.size() << endl;
    emit(routingTableSizeSignal, (long)routingTable.size());

    // Emit test convergence time
    emit(convergenceTimeSignal, 0.0);

    printRoutingTable();
}

void EDVRPRouter::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        if (msg == helloTimer) {
            sendHelloMessage();
            scheduleAt(simTime() + helloInterval, helloTimer);
        }
        else if (msg == neighborAgingTimer) {
            ageNeighbors();
            scheduleAt(simTime() + 1.0, neighborAgingTimer);
        }
        else if (msg == routeAgingTimer) {
            ageRoutes();
            scheduleAt(simTime() + 1.0, routeAgingTimer);
        }
        else if (msg == updateTimer) {
            sendRoutingUpdate();
        }
    }
    else {
        // Handle received messages
        EDVRPMessage *edvrpMsg = dynamic_cast<EDVRPMessage*>(msg);
        if (edvrpMsg) {
            emit(messageCountSignal, 1);

            int gateIndex = msg->getArrivalGate()->getIndex();

            if (edvrpMsg->getMessageType() == HELLO) {
                EDVRPHelloMessage *helloMsg = check_and_cast<EDVRPHelloMessage*>(edvrpMsg);
                processHelloMessage(helloMsg, gateIndex);
            }
            else if (edvrpMsg->getMessageType() == ROUTING_UPDATE) {
                EDVRPRoutingUpdateMessage *updateMsg = check_and_cast<EDVRPRoutingUpdateMessage*>(edvrpMsg);
                processRoutingUpdate(updateMsg, gateIndex);
            }
        }
        delete msg;
    }
}

void EDVRPRouter::sendHelloMessage()
{
    EV << "Router " << routerId << " sending HELLO messages" << endl;

    int messagesSent = 0;
    for (int i = 0; i < gateSize("port"); i++) {
        if (gate("port$o", i)->isConnected()) {
            EDVRPHelloMessage *helloMsg = new EDVRPHelloMessage("HELLO");
            helloMsg->setRouterId(routerId);
            helloMsg->setTimestamp(simTime());
            helloMsg->setAuthToken("auth123");

            send(helloMsg, "port$o", i);
            messagesSent++;

            // Emit message count statistics
            emit(messageCountSignal, 1);
        }
    }

    // Also record as scalar for debugging
    if (messagesSent > 0) {
        recordScalar("helloMessagesSent", messagesSent);
    }
}

void EDVRPRouter::processHelloMessage(EDVRPHelloMessage *msg, int gateIndex)
{
    int senderId = msg->getRouterId();
    simtime_t timestamp = msg->getTimestamp();

    EV << "Router " << routerId << " received HELLO from router " << senderId
       << " on gate " << gateIndex << endl;

    // Calculate link cost
    double linkCost = calculateLinkCost();

    // Check if this is a new neighbor
    auto it = neighborTable.find(senderId);
    bool isNewNeighbor = (it == neighborTable.end());

    if (isNewNeighbor) {
        // New neighbor discovered
        addNeighbor(senderId, gateIndex, linkCost);
        EV << "New neighbor " << senderId << " discovered with cost " << linkCost << endl;

        // Add direct route to neighbor
        updateRoutingTable(senderId, gateIndex, linkCost, 0, simTime() + routeTimeout);
        scheduleUpdate();

        // Emit convergence time for new neighbor discovery
        emit(convergenceTimeSignal, simTime().dbl());
    }
    else {
        // Update existing neighbor
        it->second.lastSeen = simTime();
        it->second.linkCost = linkCost;
        it->second.isActive = true;
    }
}

void EDVRPRouter::sendRoutingUpdate()
{
    EV << "Router " << routerId << " sending routing updates" << endl;

    std::vector<RouteEntry> routes = getChangedRoutes();

    if (routes.empty() && !routingTableChanged) {
        EV << "No changes to advertise" << endl;
        return;
    }

    // Include all routes if table changed significantly
    if (routingTableChanged) {
        routes.clear();
        for (const auto& entry : routingTable) {
            if (entry.second.isValid && entry.first != routerId) {
                RouteEntry route;
                route.destinationId = entry.first;
                route.cost = entry.second.cost;
                route.sequenceNumber = entry.second.sequenceNumber;
                routes.push_back(route);
            }
        }
    }

    // Send to all active neighbors
    for (const auto& neighbor : neighborTable) {
        if (neighbor.second.isActive) {
            EDVRPRoutingUpdateMessage *updateMsg = new EDVRPRoutingUpdateMessage("ROUTING_UPDATE");
            updateMsg->setRouterId(routerId);
            updateMsg->setTimestamp(simTime());
            updateMsg->setDestinationCount(routes.size());
            updateMsg->setRoutesArraySize(routes.size());

            for (size_t i = 0; i < routes.size(); i++) {
                // Split horizon: don't advertise routes learned from this neighbor
                if (routingTable[routes[i].destinationId].nextHopGate != neighbor.second.gateIndex) {
                    updateMsg->setRoutes(i, routes[i]);
                } else {
                    RouteEntry poisonRoute = routes[i];
                    poisonRoute.cost = INFINITY; // Poison reverse
                    updateMsg->setRoutes(i, poisonRoute);
                }
            }

            send(updateMsg, "port$o", neighbor.second.gateIndex);

            // Emit message count statistics
            emit(messageCountSignal, 1);
        }
    }

    routingTableChanged = false;
    changedDestinations.clear();
}

void EDVRPRouter::processRoutingUpdate(EDVRPRoutingUpdateMessage *msg, int gateIndex)
{
    int senderId = msg->getRouterId();
    int routeCount = msg->getDestinationCount();

    EV << "Router " << routerId << " received routing update from router " << senderId
       << " with " << routeCount << " routes" << endl;

    bool tableUpdated = false;
    simtime_t updateStartTime = simTime();

    for (int i = 0; i < routeCount; i++) {
        RouteEntry route = msg->getRoutes(i);
        int destination = route.destinationId;
        double advertisedCost = route.cost;
        int sequenceNumber = route.sequenceNumber;

        // Skip self routes
        if (destination == routerId) continue;

        // Calculate total cost via this neighbor
        double totalCost = advertisedCost;
        if (advertisedCost != INFINITY) {
            auto neighborIt = neighborTable.find(senderId);
            if (neighborIt != neighborTable.end()) {
                totalCost += neighborIt->second.linkCost;
            }
        }

        // Check if we should update the route
        auto existingIt = routingTable.find(destination);
        bool shouldUpdate = false;

        if (existingIt == routingTable.end()) {
            // New destination
            if (advertisedCost != INFINITY) {
                shouldUpdate = true;
            }
        } else {
            RoutingTableEntry& existing = existingIt->second;

            // Update if sequence number is newer, or same sequence with better cost
            if (sequenceNumber > existing.sequenceNumber ||
                (sequenceNumber == existing.sequenceNumber && totalCost < existing.cost)) {
                shouldUpdate = true;
            }
        }

        if (shouldUpdate) {
            updateRoutingTable(destination, gateIndex, totalCost,
                             sequenceNumber, simTime() + routeTimeout);
            tableUpdated = true;
            EV << "Updated route to " << destination << " via " << senderId
               << " cost=" << totalCost << " seq=" << sequenceNumber << endl;
        }
    }

    if (tableUpdated) {
        scheduleUpdate();
        printRoutingTable();

        // Emit convergence time
        emit(convergenceTimeSignal, (simTime() - updateStartTime).dbl());
    }
}

void EDVRPRouter::updateRoutingTable(int destination, int nextHopGate, double cost,
                                   int sequenceNumber, simtime_t validityTime)
{
    routingTable[destination] = RoutingTableEntry(destination, nextHopGate, cost,
                                                 sequenceNumber, validityTime);
    changedDestinations.insert(destination);
    routingTableChanged = true;

    // Emit statistics
    emit(routingTableSizeSignal, (long)routingTable.size());

    // Also record as scalar
    recordScalar("routingTableUpdates", 1);
    recordScalar("currentTableSize", (long)routingTable.size());
}

void EDVRPRouter::addNeighbor(int neighborId, int gateIndex, double linkCost)
{
    neighborTable[neighborId] = NeighborTableEntry(neighborId, gateIndex,
                                                  simTime(), linkCost);
}

void EDVRPRouter::removeNeighbor(int neighborId)
{
    auto it = neighborTable.find(neighborId);
    if (it != neighborTable.end()) {
        // Mark routes via this neighbor as invalid
        for (auto& route : routingTable) {
            if (route.second.nextHopGate == it->second.gateIndex) {
                route.second.isValid = false;
                route.second.cost = INFINITY;
                incrementSequenceNumber(route.first);
                changedDestinations.insert(route.first);
            }
        }
        neighborTable.erase(it);
        routingTableChanged = true;
        scheduleUpdate();
    }
}

double EDVRPRouter::calculateLinkCost()
{
    // link_cost = α * (1/bandwidth_bps) + β * latency_ms
    double bandwidthBps = linkBandwidth * 1000000; // Convert Mbps to bps
    double latencyMs = linkLatency * 1000; // Convert seconds to ms

    return alpha * (1.0 / bandwidthBps) + beta * latencyMs;
}

void EDVRPRouter::ageNeighbors()
{
    std::vector<int> deadNeighbors;

    for (auto& neighbor : neighborTable) {
        if (simTime() - neighbor.second.lastSeen > holdTimeout) {
            deadNeighbors.push_back(neighbor.first);
        }
    }

    for (int deadNeighbor : deadNeighbors) {
        EV << "Neighbor " << deadNeighbor << " timed out" << endl;
        removeNeighbor(deadNeighbor);
    }
}

void EDVRPRouter::ageRoutes()
{
    std::vector<int> expiredRoutes;

    for (auto& route : routingTable) {
        if (route.first != routerId && route.second.isValid &&
            simTime() > route.second.validityTimer) {
            expiredRoutes.push_back(route.first);
        }
    }

    for (int expiredRoute : expiredRoutes) {
        EV << "Route to " << expiredRoute << " expired" << endl;
        routingTable[expiredRoute].isValid = false;
        routingTable[expiredRoute].cost = INFINITY;
        incrementSequenceNumber(expiredRoute);
        changedDestinations.insert(expiredRoute);
        routingTableChanged = true;
    }

    if (!expiredRoutes.empty()) {
        scheduleUpdate();
    }
}

void EDVRPRouter::scheduleUpdate()
{
    if (!updateTimer->isScheduled()) {
        scheduleAt(simTime() + uniform(0.1, 0.5), updateTimer);
    }
}

std::vector<RouteEntry> EDVRPRouter::getChangedRoutes()
{
    std::vector<RouteEntry> routes;

    for (int destination : changedDestinations) {
        auto it = routingTable.find(destination);
        if (it != routingTable.end()) {
            RouteEntry route;
            route.destinationId = destination;
            route.cost = it->second.cost;
            route.sequenceNumber = it->second.sequenceNumber;
            routes.push_back(route);
        }
    }

    return routes;
}

void EDVRPRouter::incrementSequenceNumber(int destinationId)
{
    sequenceCounters[destinationId]++;
    if (routingTable.find(destinationId) != routingTable.end()) {
        routingTable[destinationId].sequenceNumber = sequenceCounters[destinationId];
    }
}

void EDVRPRouter::printRoutingTable()
{
    EV << "=== Routing Table for Router " << routerId << " ===" << endl;
    EV << "Dest\tNext\tCost\tSeq\tValid" << endl;

    for (const auto& entry : routingTable) {
        EV << entry.first << "\t" << entry.second.nextHopGate << "\t"
           << entry.second.cost << "\t" << entry.second.sequenceNumber << "\t"
           << (entry.second.isValid ? "Y" : "N") << endl;
    }
    EV << "=================================" << endl;
}

void EDVRPRouter::printNeighborTable()
{
    EV << "=== Neighbor Table for Router " << routerId << " ===" << endl;
    EV << "Neighbor\tGate\tCost\tLast Seen\tActive" << endl;

    for (const auto& entry : neighborTable) {
        EV << entry.first << "\t\t" << entry.second.gateIndex << "\t"
           << entry.second.linkCost << "\t" << entry.second.lastSeen << "\t"
           << (entry.second.isActive ? "Y" : "N") << endl;
    }
    EV << "===================================" << endl;
}

void EDVRPRouter::finish()
{
    // Cancel all timers
    cancelAndDelete(helloTimer);
    cancelAndDelete(neighborAgingTimer);
    cancelAndDelete(routeAgingTimer);
    cancelAndDelete(updateTimer);

    // Print final statistics
    EV << "Router " << routerId << " final routing table size: "
       << routingTable.size() << endl;

    // Emit final statistics
    EV << "Router " << routerId << " emitting final statistics..." << endl;
    emit(routingTableSizeSignal, (long)routingTable.size());
    emit(convergenceTimeSignal, simTime().dbl());  // Total simulation time as convergence measure

    // Emit some test values to ensure signals work
    recordScalar("finalTableSize", (long)routingTable.size());
    recordScalar("finalSimTime", simTime().dbl());
    recordScalar("routerId", routerId);

    printRoutingTable();
}

} // namespace edvrp
