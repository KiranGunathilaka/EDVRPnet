//EDVRPRouter.ned
package edvrp.simulations;

import edvrp.*;


network EDVRPTestNetwork
{
    parameters:
        @display("bgb=800,600");
        
    submodules:
        router1: EDVRPRouter {
            parameters:
                routerId = 1;
                linkBandwidth = 100Mbps;
                linkLatency = 1ms;
                @display("p=150,200;i=abstract/router;t=R1");
        }
        
        router2: EDVRPRouter {
            parameters:
                routerId = 2;
                linkBandwidth = 100Mbps;
                linkLatency = 1ms;
                @display("p=300,200;i=abstract/router;t=R2");
        }
        
        router3: EDVRPRouter {
            parameters:
                routerId = 3;
                linkBandwidth = 100Mbps;
                linkLatency = 1ms;
                @display("p=450,200;i=abstract/router;t=R3");
        }
        
        router4: EDVRPRouter {
            parameters:
                routerId = 4;
                linkBandwidth = 100Mbps;
                linkLatency = 1ms;
                @display("p=600,200;i=abstract/router;t=R4");
        }
        
        // Additional routers for scalability testing
        router5: EDVRPRouter {
            parameters:
                routerId = 5;
                linkBandwidth = 10Mbps;  // Slower link
                linkLatency = 5ms;       // Higher latency
                @display("p=300,350;i=abstract/router;t=R5");
        }
        
        router6: EDVRPRouter {
            parameters:
                routerId = 6;
                linkBandwidth = 1000Mbps; // Faster link
                linkLatency = 0.1ms;      // Lower latency
                @display("p=450,350;i=abstract/router;t=R6");
        }
        
    connections:
        // Linear topology: R1 -- R2 -- R3 -- R4
        router1.port++ <--> { delay = 1ms; datarate = 100Mbps; } <--> router2.port++;
        router2.port++ <--> { delay = 1ms; datarate = 100Mbps; } <--> router3.port++;
        router3.port++ <--> { delay = 1ms; datarate = 100Mbps; } <--> router4.port++;
        
        // Additional connections for testing composite metrics
        router2.port++ <--> { delay = 5ms; datarate = 10Mbps; } <--> router5.port++;
        router3.port++ <--> { delay = 0.1ms; datarate = 1000Mbps; } <--> router6.port++;
        router5.port++ <--> { delay = 2ms; datarate = 50Mbps; } <--> router6.port++;
}


network EDVRPScalabilityNetwork
{
    parameters:
        @display("bgb=1000,800");
        int numRouters = default(10);
        
    submodules:
        router[numRouters]: EDVRPRouter {
            parameters:
                routerId = index + 1;
                linkBandwidth = uniform(10, 100) * 1Mbps;
                linkLatency = uniform(1, 10) * 1ms;
                @display("i=abstract/router");
        }
        
    connections:
        // Create a linear topology
        for i=0..numRouters-2 {
            router[i].port++ <--> { 
                delay = uniform(1, 5) * 1ms; 
                datarate = uniform(10, 100) * 1Mbps; 
            } <--> router[i+1].port++;
        }
        
        
        for i=0..numRouters-3, if numRouters >= 6 && i < 3 {
            router[i].port++ <--> { 
                delay = uniform(2, 8) * 1ms; 
                datarate = uniform(50, 200) * 1Mbps; 
            } <--> router[i+3].port++;
        }
}

network RIPComparisonNetwork
{
    parameters:
        @display("bgb=800,600");
        
    submodules:
        router1: EDVRPRouter {
            parameters:
                routerId = 1;
                linkBandwidth = 100Mbps;
                linkLatency = 1ms;
                // Simulate RIP behavior with longer timers and different metrics
                helloInterval = 30s;     // RIP updates every 30s
                holdTimeout = 180s;      // RIP timeout
                routeTimeout = 180s;     // Route expiry
                alpha = 0;               // Disable bandwidth consideration (RIP uses hop count)
                beta = 0;                // Disable latency consideration
                @display("p=150,200;i=abstract/router;t=R1");
        }
        
        router2: EDVRPRouter {
            parameters:
                routerId = 2;
                linkBandwidth = 100Mbps;
                linkLatency = 1ms;
                helloInterval = 30s;
                holdTimeout = 180s;
                routeTimeout = 180s;
                alpha = 0;
                beta = 0;
                @display("p=300,200;i=abstract/router;t=R2");
        }
        
        router3: EDVRPRouter {
            parameters:
                routerId = 3;
                linkBandwidth = 100Mbps;
                linkLatency = 1ms;
                helloInterval = 30s;
                holdTimeout = 180s;
                routeTimeout = 180s;
                alpha = 0;
                beta = 0;
                @display("p=450,200;i=abstract/router;t=R3");
        }
        
        router4: EDVRPRouter {
            parameters:
                routerId = 4;
                linkBandwidth = 100Mbps;
                linkLatency = 1ms;
                helloInterval = 30s;
                holdTimeout = 180s;
                routeTimeout = 180s;
                alpha = 0;
                beta = 0;
                @display("p=600,200;i=abstract/router;t=R4");
        }
        
        router5: EDVRPRouter {
            parameters:
                routerId = 5;
                linkBandwidth = 10Mbps;
                linkLatency = 5ms;
                helloInterval = 30s;
                holdTimeout = 180s;
                routeTimeout = 180s;
                alpha = 0;
                beta = 0;
                @display("p=300,350;i=abstract/router;t=R5");
        }
        
        router6: EDVRPRouter {
            parameters:
                routerId = 6;
                linkBandwidth = 1000Mbps;
                linkLatency = 0.1ms;
                helloInterval = 30s;
                holdTimeout = 180s;
                routeTimeout = 180s;
                alpha = 0;
                beta = 0;
                @display("p=450,350;i=abstract/router;t=R6");
        }
        
    connections:
        // Same topology as EDVRPTestNetwork
        router1.port++ <--> { delay = 1ms; datarate = 100Mbps; } <--> router2.port++;
        router2.port++ <--> { delay = 1ms; datarate = 100Mbps; } <--> router3.port++;
        router3.port++ <--> { delay = 1ms; datarate = 100Mbps; } <--> router4.port++;
        router2.port++ <--> { delay = 5ms; datarate = 10Mbps; } <--> router5.port++;
        router3.port++ <--> { delay = 0.1ms; datarate = 1000Mbps; } <--> router6.port++;
        router5.port++ <--> { delay = 2ms; datarate = 50Mbps; } <--> router6.port++;
}