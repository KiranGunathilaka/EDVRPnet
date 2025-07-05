
enum EDVRPMessageType
{
    HELLO = 1;
    ROUTING_UPDATE = 2;
}

//
// Base message for EDVRP protocol
//
packet EDVRPMessage
{
    int messageType @enum(EDVRPMessageType);
    int routerId;
    simtime_t timestamp;
    string authToken = "";
}

//
// Hello message for neighbor discovery
//
packet EDVRPHelloMessage extends EDVRPMessage
{
    messageType = HELLO;
}

//
// Route entry for routing updates
//
struct RouteEntry
{
    int destinationId;
    double cost;
    int sequenceNumber;
}

//
// Routing update message
//
packet EDVRPRoutingUpdateMessage extends EDVRPMessage
{
    messageType = ROUTING_UPDATE;
    int destinationCount;
    RouteEntry routes[];
}