cmake_minimum_required(VERSION 3.28)

project("RandNumGen")

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

include(FetchContent)
FetchContent_Declare(
	mhook
    GIT_REPOSITORY https://github.com/SToFU-Systems/mhook.git
    GIT_TAG        development
)
FetchContent_MakeAvailable(mhook)

add_executable(${PROJECT_NAME} "RandNumGen.cpp" "RandNumGen.h")
set_target_properties(${PROJECT_NAME} PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
)
if(NOT MSVC)
    target_link_options(${PROJECT_NAME} PRIVATE "-static" "-static-libgcc" "-static-libstdc++")
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE mhook::mhook)
