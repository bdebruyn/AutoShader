#===============================================================================
#
# old pnf ${source_path}/Test_Framework.cpp
# ??? Test_TaskQueue.cpp
#
#===============================================================================
set(tests
   Test_OpenVDB
)
set(libraries
   openvdb
   tbb
)
UnitTest_All("${tests}" "${libraries}")
