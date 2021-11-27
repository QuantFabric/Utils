#include "Logger.h"

int main(int argc, char* argv[])
{
    Utils::gLogger = Utils::Singleton<Utils::Logger>::GetInstance();
    Utils::gLogger->setDebugLevel();
    Utils::gLogger->Log->info("hello world!");
    Utils::gLogger->Log->debug("hello world!");
    Utils::gLogger->Console->info("hello world!");
    Utils::gLogger->Console->debug("hello world!");
    spdlog::drop_all();
    return 0;
}