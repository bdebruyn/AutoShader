#include "gtest/gtest.h"

// #include "Framework/TestLogger.h"

#include <algorithm> // for min()
#include <chrono>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <thread>

#include <openvdb/openvdb.h>
#include <cmath> // for exp()

using namespace std;
using namespace std::chrono;

struct Test_OpenVDB : public virtual ::testing::Test
{
   // framework::Azul3DLogger logger;

   Test_OpenVDB() 
   {
      // logger.start();
   }
   virtual~Test_OpenVDB() {}

   void SetUp() {}
   void TearDown() {}
};

namespace Test_OpenVDB_Namespace 
{

   int main() {
       openvdb::initialize();
   
       // Create a FloatGrid and accessor.
       openvdb::FloatGrid::Ptr grid = openvdb::FloatGrid::create(0.0);
       openvdb::FloatGrid::Accessor accessor = grid->getAccessor();
   
       // Define the initial light intensity and the light's penetration depth.
       double I0 = 100.0;
       double dp = 0.5;
   
       // Define the grid's dimensions.
       int width = 1;
       int height = 1;
       int depth = 15; // Number of layers in the z direction.
   
       // Calculate the light intensity at each layer and store it in the grid.
       for (int z = 0; z < depth; ++z) 
       {
           // Add light to the current layer.
           double I = I0 * std::exp(-z / dp);
   
           // Update all existing layers with the new light.
           for (int x = 0; x < width; ++x) 
           {
               for (int y = 0; y < height; ++y) 
               {
                   for (int existing_z = 0; existing_z <= z; ++existing_z) 
                   {
                       double existing_I = accessor.getValue(openvdb::Coord(x, y, existing_z));
                       accessor.setValue(openvdb::Coord(x, y, existing_z), static_cast<float>(existing_I + I));
                   }
               }
           }
       }
   
       // Print the light intensity at each layer.
       for (int z = 0; z < depth; ++z) 
       {
           openvdb::Coord xyz(0, 0, z);
           float I = accessor.getValue(xyz);
           std::cout << "The total light intensity at layer " << z << " is " << I << std::endl;
       }
   
       return 0;
   }


} // Test_OpenVDB_Namespace

using namespace Test_OpenVDB_Namespace;

TEST_F(Test_OpenVDB, instantiate)
{
   // logger.mute();

   // SETUP

   // EXERCISE

   main();

   // VERIFY

}
