/*
 * EDVRPRouter.h
 *
 *  Created on: Jul 4, 2025
 *      Author: kiran_gunathilaka
 */


#ifndef __EDVRP_EDVRPROUTER_H_
#define __EDVRP_EDVRPROUTER_H_

#include <omnetpp.h>
#include <map>
#include <vector>
#include <set>
#include "EDVRPMessage_m.h"

using namespace omnetpp;

namespace edvrp {

struct RoutingTableEntry {
    int destinationId;
    int nextHopGate;
    double cost;
    int sequenceNumber;
    simtime_t validityTimer;
    bool isValid;

    RoutingTableEntry() : destinationId(-1), nextHopGate(-1), cost(INFINITY),
                         sequenceNumber(0), validityTimer(0), isValid(false) {}

    RoutingTableEntry(int dest, int gate, double c, int seq, simtime_t timer) :
        destinationId(dest), nextHopGate(gate), cost(c), sequenceNumber(seq),
        validityTimer(timer), isValid(true) {}
};

struct NeighborTableEntry {
    int neighborId;
    int gateIndex;
    simtime_t lastSeen;
    double linkCost;
    bool isActive;

    NeighborTableEntry() : neighborId(-1), gateIndex(-1), lastSeen(0),
                          linkCost(1.0), isActive(false) {}

    NeighborTableEntry(int id, int gate, simtime_t time, double cost) :
        neighborId(id), gateIndex(gate), lastSeen(time), linkCost(cost), isActive(true) {}
};

class EDVRPRouter : public cSimpleModule
{
private:
    // Parameters
    int routerId;
    double helloInterval;
    double holdTimeout;
    double routeTimeout;
    double updateInterval;
    double linkBandwidth;
    double linkLatency;
    double alpha, beta;

    // Tables
    std::map<int, RoutingTableEntry> routingTable;
    std::map<int, NeighborTableEntry> neighborTable;
    std::map<int, int> sequenceCounters;

    // Timers
    cMessage *helloTimer;
    cMessage *neighborAgingTimer;
    cMessage *routeAgingTimer;
    cMessage *updateTimer;

    // Statistics
    simsignal_t convergenceTimeSignal;
    simsignal_t routingTableSizeSignal;
    simsignal_t messageCountSignal;

    // Internal state
    std::set<int> changedDestinations;
    bool routingTableChanged;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

private:
    // Protocol methods
    void sendHelloMessage();
    void processHelloMessage(EDVRPHelloMessage *msg, int gateIndex);
    void sendRoutingUpdate();
    void processRoutingUpdate(EDVRPRoutingUpdateMessage *msg, int gateIndex);

    // Table management
    void updateRoutingTable(int destination, int nextHopGate, double cost,
                           int sequenceNumber, simtime_t validityTime);
    void addNeighbor(int neighborId, int gateIndex, double linkCost);
    void removeNeighbor(int neighborId);
    bool isNeighborActive(int neighborId);

    // Utility methods
    double calculateLinkCost();
    void ageNeighbors();
    void ageRoutes();
    void printRoutingTable();
    void printNeighborTable();

    // Route computation
    void scheduleUpdate();
    std::vector<RouteEntry> getChangedRoutes();
    void incrementSequenceNumber(int destinationId);

public:
    // For visualization and debugging
    int getRouterId() const { return routerId; }
    const std::map<int, RoutingTableEntry>& getRoutingTable() const { return routingTable; }
    const std::map<int, NeighborTableEntry>& getNeighborTable() const { return neighborTable; }
};

} // namespace edvrp

#endif
