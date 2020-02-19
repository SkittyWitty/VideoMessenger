# CMakeList.txt : CMake project for VideoMessenger, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_subdirectory(ClientCommunications)

# Add source to this project's executable.
add_executable (VideoMessengerClient "VideoMessengerClient.cpp" "VideoMessengerClient.h")

target_link_libraries(VideoMessengerClient COMMS_CLIENT_LIB)

# TODO: Add tests and install targets if needed.
