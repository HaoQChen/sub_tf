cmake_minimum_required(VERSION 3.0.0)
project(sub_tf)

add_definitions(-std=c++11)



find_package(catkin REQUIRED COMPONENTS
  std_msgs
  roscpp
  rospy
  tf
  geometry_msgs
)


catkin_package(
)
## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)


add_executable(sub_tf src/sub_tf.cc)


target_link_libraries(sub_tf
  ${catkin_LIBRARIES}
)


#add_definitions(-DVECTORDATA_ENABLED)



