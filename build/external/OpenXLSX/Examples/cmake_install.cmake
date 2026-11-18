# Install script for directory: /Users/egorasoskov/Desktop/search-engine/external/OpenXLSX/Examples

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/OpenXLSX/examples" TYPE FILE RENAME "CMakeLists.txt" FILES "/Users/egorasoskov/Desktop/search-engine/external/OpenXLSX/Examples/templates/CMakeLists.txt.examples")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/OpenXLSX/examples" TYPE FILE RENAME "Makefile" FILES "/Users/egorasoskov/Desktop/search-engine/build/external/OpenXLSX/Examples/Makefile.examples")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/OpenXLSX/examples" TYPE FILE FILES
    "/Users/egorasoskov/Desktop/search-engine/external/OpenXLSX/Examples/Demo1.cpp"
    "/Users/egorasoskov/Desktop/search-engine/external/OpenXLSX/Examples/Demo1A.cpp"
    "/Users/egorasoskov/Desktop/search-engine/external/OpenXLSX/Examples/Demo2.cpp"
    "/Users/egorasoskov/Desktop/search-engine/external/OpenXLSX/Examples/Demo3.cpp"
    "/Users/egorasoskov/Desktop/search-engine/external/OpenXLSX/Examples/Demo4.cpp"
    "/Users/egorasoskov/Desktop/search-engine/external/OpenXLSX/Examples/Demo5.cpp"
    "/Users/egorasoskov/Desktop/search-engine/external/OpenXLSX/Examples/Demo6.cpp"
    "/Users/egorasoskov/Desktop/search-engine/external/OpenXLSX/Examples/Demo7.cpp"
    "/Users/egorasoskov/Desktop/search-engine/external/OpenXLSX/Examples/Demo8.cpp"
    "/Users/egorasoskov/Desktop/search-engine/external/OpenXLSX/Examples/Demo9.cpp"
    "/Users/egorasoskov/Desktop/search-engine/external/OpenXLSX/Examples/Demo10.cpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/OpenXLSX/examples/cmake" TYPE FILE FILES "/Users/egorasoskov/Desktop/search-engine/external/OpenXLSX/Examples/cmake/FindLIBZIP.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/OpenXLSX/examples/external/CustomZip" TYPE FILE FILES "/Users/egorasoskov/Desktop/search-engine/external/OpenXLSX/Examples/external/CustomZip/CustomZip.hpp")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/Users/egorasoskov/Desktop/search-engine/build/external/OpenXLSX/Examples/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
