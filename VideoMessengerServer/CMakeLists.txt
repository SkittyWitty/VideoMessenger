# CMakeList.txt : CMake project for VideoMessenger, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_subdirectory(Communications)
add_subdirectory(ImageHandling)

# Add source to this project's executable.
add_executable (VideoMessengerServer "VideoMessenger.cpp" "VideoMessenger.h")

target_link_libraries(VideoMessengerServer COMMS_LIB IMAGE_HANDLING)

# TODO: Add tests and install targets if needed.
