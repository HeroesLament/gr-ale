# Find the Google Test framework
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Define your test source
set(TEST_SOURCE test_modem.cpp)

# Add executable for your test
add_executable(runUnitTests ${TEST_SOURCE})

# Link against GTest and your library
target_link_libraries(runUnitTests GTest::GTest GTest::Main my_block_lib)

# Add test to CMake test system
add_test(NAME MyBlockUnitTests COMMAND runUnitTests)
