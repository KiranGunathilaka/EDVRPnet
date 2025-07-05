# How to Run

1. Download/clone the folder/repository as a zip file and extract it inside a new directory named EDVRP in /omnetpp-6.1/samples directory.
So the content will be availble in  /omnetpp-6.1/samples/EDVRP

2. Open the project inside the Omnet++ project explorer.

3. then open a terminal inside /EDVRP and run "make clean" to clear the existing build files. The omnet++ was installed inside a linux environment. So if you are running on windows machine this is needed to clear the existing binary files before building the .exe files. make sure to have the same CMAKE version installed.

4. then run "make MODE=release" to build the binaries.

5. After EDVRP binary/executable appear on the directory, go to the omnetpp GUI IDE and inside EDVRP/simulations/ right click on the omnet.ini file and select "Run As" and then "Omnet simulation". Omnet simulation window will appear and select infile test configurations needed and run the simulation.
