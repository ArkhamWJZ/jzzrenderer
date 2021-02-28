cmake_minimum_required(VERSION 3.2)
project(Jzzrenderer)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CLANG_CXX_FLAGS "-std=c++11 -m64 -O3 -funroll-loops")
  set(CLANG_CXX_FLAGS "${CLANG_CXX_FLAGS} -Wno-deprecated-declarations")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CLANG_CXX_FLAGS}")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdiagnostics-color=always")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always")
endif ()

add_subdirectory(ext ext_build)

include_directories(
        # Portable filesystem API
        SYSTEM ${FILESYSTEM_INCLUDE_DIR}
        # PugiXML parser
        ${PUGIXML_INCLUDE_DIR}
        # Eigen linear algebra library
        SYSTEM ${EIGEN_INCLUDE_DIR}
        # GLFW library for OpenGL context creation
        SYSTEM ${GLFW_INCLUDE_DIR}
        # GLEW library for accessing OpenGL functions
        SYSTEM ${GLEW_INCLUDE_DIR}
        # NanoVG drawing library
        SYSTEM ${NANOVG_INCLUDE_DIR}
        # NanoGUI user interface library
        SYSTEM ${NANOGUI_INCLUDE_DIR}
        SYSTEM ${NANOGUI_EXTRA_INCS}
)

add_executable(plasticine


 # Source code files
 src/main.cpp

)