cmake_minimum_required(VERSION 3.15)

project(
    "project-name"
    VERSION 0.1.0
    LANGUAGES CXX
)

# Include testing framework
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

# option(BUILD_TESTING) supported by cmake.

# Enforce Cpp Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

# ROS2
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

###################
# Library example #
###################
# add_library(${LIBRARY_NAME} [INTERFACE]
#  Listing up your sources if not interface library
# )
# target_include_directories(${LIBRARY_NAME} [PUBLIC or INTERFACE]
#     $<INSTALL_INTERFACE:include>
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
# )
# add_library(${PROJECT_NAME}::${LIBRARY_NAME} ALIAS ${LIBRARY_NAME})
# ament_target_dependencies(${LIBRARY_NAME}
#   rclcpp
# )

######################
# Executable example #
######################
# add_executable(${EXECUTABLE_NAME}
#   Listing up your sources
# )
# target_include_directories(${EXECUTABLE_NAME} PUBLIC
#     $<INSTALL_INTERFACE:include>
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#     PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/src
# )
# add_executable(${PROJECT_NAME}::${EXECUTABLE_NAME} ALIAS ${EXECUTABLE_NAME})

###################
##### Testing #####
###################
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  add_subdirectory(test)
endif()

# Set common compiler warnings
include(cmake/CompilerWarnings.cmake)

####################
# Install settings #
####################
ament_export_targets(${PROJECT_NAME}Targets HAS_LIBRARY_TARGET)

install(DIRECTORY include/"project-name" DESTINATION include)
# install(DIRECTORY ros2/include/"project-name" DESTINATION include)
# install(DIRECTORY ros2/launch DESTINATION share/${PROJECT_NAME})
# install(DIRECTORY ros2/rviz DESTINATION share/${PROJECT_NAME})

# install(
#   TARGETS 
#     ${PROJECT_NAME}
#   EXPORT ${PROJECT_NAME}Targets
#   LIBRARY DESTINATION lib/${PROJECT_NAME}
#   ARCHIVE DESTINATION lib/${PROJECT_NAME}
#   RUNTIME DESTINATION lib/${PROJECT_NAME}
#   INCLUDES DESTINATION include
# )

ament_package()
