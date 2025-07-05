

package edvrp;

simple EDVRPRouter
{
    parameters:
        int routerId;
        double helloInterval @unit(s) = default(5s);
        double holdTimeout @unit(s) = default(15s);
        double routeTimeout @unit(s) = default(30s);
        double updateInterval @unit(s) = default(10s);
        double linkBandwidth @unit(Mbps) = default(100Mbps);
        double linkLatency @unit(ms) = default(1ms);
        double alpha = default(1000000.0);  // Scaling factor for bandwidth
        double beta = default(1.0);         // Scaling factor for latency
        @display("i=abstract/router");
        @class(edvrp::EDVRPRouter);
        
    gates:
        inout port[];
}