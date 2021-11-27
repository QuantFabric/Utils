#include <unistd.h>
#include "HPPackServer.h"
#include "Logger.h"

int main()
{
    // init Logger
    Utils::gLogger = Utils::Singleton<Utils::Logger>::GetInstance();
    HPPackServer server("0.0.0.0", 6000);
    server.Start();
    while (true)
    {
        sleep(1);
    }
    
    return 0;
}

// g++ --std=c++17 HPPackServer.cpp HPPackServerTest.cpp Logger.cpp -o server -pthread -lhpsocket4c -lspdlog  -I/home/xxx/QuantFabric/XAPI/HP-Socket/5.8.2/include -L/home/xxx/QuantFabric/XAPI/HP-Socket/5.8.2/lib -I/home/xxx/QuantFabric/XAPI/SPDLog/include -L/home/xxx/QuantFabric/XAPI/SPDLog/lib/ -I/home/xxx/QuantFabric/XAPI/ConcurrentQueue/