# Import catch2
Include(FetchContent)

set(CATCH_INSTALL_DOCS OFF CACHE INTERNAL "")
set(CATCH_INSTALL_EXTRAS OFF CACHE INTERNAL "")

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)

# Macro for testing targets
function (build_test fn)
    add_executable(test_${fn}
        ${fn}.cpp
    )
    target_link_libraries(test_${fn} PRIVATE
        ${PROJECT_NAME}
        Catch2::Catch2WithMain
    )
    target_compile_options(${PROJECT_NAME} PUBLIC 
        $<$<COMPILE_LANGUAGE:CUDA>:-Wno-double-promotion>)
    catch_discover_tests(test_${fn})
endfunction()

build_test(test)