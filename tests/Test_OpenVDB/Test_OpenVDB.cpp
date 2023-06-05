#include "gtest/gtest.h"

#include "Framework/TestLogger.h"
#include "MQTT/Mocks/Mosquitto.h"
#include "PrinterNetworkFramework/Mocks/PNFRunner.h"

#include "Mocks/MyMessage.h"

#include <boost/optional/optional.hpp>
#include <chrono>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <thread>

using namespace std;
using namespace std::chrono;

struct Test_OpenVDB : public virtual ::testing::Test
{
   framework::Azul3DLogger logger;

   Test_OpenVDB() 
   {
      logger.start();
   }
   virtual~Test_OpenVDB() {}

   void SetUp() {}
   void TearDown() {}
};

namespace Test_OpenVDB_Namespace 
{


} // Test_OpenVDB_Namespace

using namespace Test_OpenVDB_Namespace;

TEST_F(Test_OpenVDB, instantiate)
{
   logger.mute();

   // SETUP

   // EXERCISE

   // VERIFY

}
