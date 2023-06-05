#include "gtest/gtest.h"

// #include "Framework/TestLogger.h"

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

//    int simple()
//    {
//        // Initialize the OpenVDB library.  This must be called at least
//        // once per program and may safely be called multiple times.
//        openvdb::initialize();
//    
//        // Create an empty floating-point grid with background value 0.
//        openvdb::FloatGrid::Ptr grid = openvdb::FloatGrid::create();
//    
//        // Get an accessor for coordinate-based access to voxels.
//        openvdb::FloatGrid::Accessor accessor = grid->getAccessor();
//    
//        // Define a coordinate with three integer components.
//        openvdb::Coord xyz(5, 10, 15);
//    
//        // Set the voxel value at (5, 10, 15) to 1.
//        accessor.setValue(xyz, 1.0f);
//    
//        // Verify that the voxel value at (5, 10, 15) is now 1.
//        float check_value = accessor.getValue(xyz);
//        std::cout << "Value at (5, 10, 15): " << check_value << std::endl;
//    
//        // Reset the voxel value at (5, 10, 15) to the background value.
//        accessor.setValueOff(xyz);
//    
//        // Check that the voxel value at (5, 10, 15) is now 0 (the background value).
//        check_value = accessor.getValue(xyz);
//        std::cout << "Value at (5, 10, 15): " << check_value << std::endl;
//    
//        return 0;
//    }

   int main() 
   {
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
         double I = I0 * std::exp(-z / dp);
         
         for (int x = 0; x < width; ++x) 
         {
            for (int y = 0; y < height; ++y) 
            {
               accessor.setValue(openvdb::Coord(x, y, z), static_cast<float>(I));
            }
         }
      }
      
      // Print the light intensity at each layer.
      for (int z = 0; z < depth; ++z) 
      {
         openvdb::Coord xyz(0, 0, z);
         float I = accessor.getValue(xyz);
         std::cout << "The light intensity at layer " << z << " is " << I << std::endl;
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
