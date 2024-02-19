cmake_minimum_required(VERSION 3.15)

project(
    "project-name"
    VERSION 0.1.0
    LANGUAGES CUDA CXX C
)

# Include testing framework
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

# option(BUILD_TESTING) supported by cmake.

# CUDA 
include(CheckLanguage)
check_language(CUDA)
find_package(CUDAToolkit 11.0 REQUIRED)

# Hardware requirement : GPU compute capability 7.0 or higher.
include(FindCUDA/select_compute_arch)
CUDA_DETECT_INSTALLED_GPUS(INSTALLED_GPU_CCS_1)
string(STRIP "${INSTALLED_GPU_CCS_1}" INSTALLED_GPU_CCS_2)
string(REPLACE " " ";" INSTALLED_GPU_CCS_3 "${INSTALLED_GPU_CCS_2}")
string(REPLACE "." "" CUDA_ARCH_LIST "${INSTALLED_GPU_CCS_3}")
if(CUDA_ARCH_LIST STRLESS "72")
  message(FATAL_ERROR "Mostalgia requires compute capability 7.2 or higher" )
else()
  set(CMAKE_CUDA_ARCHITECTURES ${CUDA_ARCH_LIST} CACHE STRING "CUDA architectures" FORCE)
endif()

# OpenMP
find_package(OpenMP REQUIRED)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

# Enforce Cpp Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# Set initial output directory
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})

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
# target_compile_options(${LIBRARY_NAME} PUBLIC 
#   $<$<COMPILE_LANGUAGE:CUDA>:
#   -Xcompiler=-fopenmp
#     -Wall
#     -Wextra
#     -Wnon-virtual-dtor
#     -Wcast-align
#     -Woverloaded-virtual
#     -Wconversion
#     -Wnull-dereference
#     -Wdouble-promotion
#     -Wmisleading-indentation
#     -Wduplicated-cond
#     -Wduplicated-branches
#     -Wlogical-op
#     -Wno-address-of-packed-member
#     -Wno-class-memaccess
#     >
#   ) 

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
include(GNUInstallDirs)

install(
  TARGETS 
    # Listing up all excutables that you want to install
    # ${LIBRARY_NAME}
    # ${EXECUTABLE_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION include
  PUBLIC_HEADER DESTINATION include
)

install(
  EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Install the `include` directory
install(
  DIRECTORY
  include/${PROJECT_NAME}
  DESTINATION
  include
)

#########################
# CMAKE Configure files #
#########################
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${PROJECT_NAME}ConfigVersion.cmake
  VERSION
  ${PROJECT_VERSION}
  COMPATIBILITY
  SameMajorVersion
)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION
  ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION
  ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)