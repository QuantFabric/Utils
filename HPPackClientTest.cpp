#include "HPPackClient.h"
#include "Logger.h"

int main(int argc, char *argv[])
{
    // init Logger
    Utils::gLogger = Utils::Singleton<Utils::Logger>::GetInstance();
    // start client
    HPPackClient client("127.0.0.1", 6000);
    client.Start();
    // send data
    for (size_t i = 0; i < 100; i++)
    {
        Message::Test test;
        sprintf(test.Account, "Test%03d", i);
        sprintf(test.Content, "Hello Server %03d", i);
        Message::PackMessage message;
        message.MessageType = Message::MessageType::TestMessage;
        memcpy(&message.TestData, &test, sizeof(test));
        client.SendData((const unsigned char*)(&message), sizeof(message));
        sleep(1);
    }
    
    return 0;
}

// g++ --std=c++17 HPPackClient.cpp HPPackClientTest.cpp Logger.cpp -o client -pthread -lhpsocket4c -lspdlog  -I/home/xxx/QuantFabric/XAPI/HP-Socket/5.8.2/include -L/home/xxx/QuantFabric/XAPI/HP-Socket/5.8.5/lib -I/home/xxx/QuantFabric/XAPI/SPDLog/include -L/home/xxx/QuantFabric/XAPI/SPDLog/lib/ -I/home/xxx/QuantFabric/XAPI/ConcurrentQueue/