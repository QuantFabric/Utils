#include <stdio.h>
#include "XPluginEngine.hpp"

class PluginTest
{
public:
    void print()
    {
        printf("PluginTest::print");
    }
};

CreateObjectFunc(PluginTest);

// g++ -fPIC shared XPluginTest.hpp -o libPluginTest.so