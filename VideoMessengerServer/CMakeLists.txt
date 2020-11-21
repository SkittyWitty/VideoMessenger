# CMakeList.txt : CMake project for VideoMessenger, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_subdirectory(ServerCommunications)
add_subdirectory(ImageHandling)

# Add source to this project's executable.

#Video Server Executable
add_executable (VideoMessengerServer "VideoMessenger.cpp" "VideoMessenger.h")
target_link_libraries(VideoMessengerServer SERVER_COMMS_LIB IMAGE_HANDLING)


#Testing
add_executable (unit_tests "Test/test_main.cpp")

target_link_libraries(unit_tests
    GTest::GTest 
    GTest::Main
)

add_test(test_all unit_tests)
