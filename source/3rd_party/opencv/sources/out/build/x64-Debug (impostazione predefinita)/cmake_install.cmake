# Install script for directory: D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/out/install/x64-Debug (impostazione predefinita)")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2" TYPE FILE FILES "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/out/build/x64-Debug (impostazione predefinita)/opencv2/opencv_modules.hpp")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/out/build/x64-Debug (impostazione predefinita)/win-install/OpenCVConfig.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OpenCVModules.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OpenCVModules.cmake"
         "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/out/build/x64-Debug (impostazione predefinita)/CMakeFiles/Export/lib/OpenCVModules.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OpenCVModules-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/OpenCVModules.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/out/build/x64-Debug (impostazione predefinita)/CMakeFiles/Export/lib/OpenCVModules.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/out/build/x64-Debug (impostazione predefinita)/CMakeFiles/Export/lib/OpenCVModules-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/out/build/x64-Debug (impostazione predefinita)/win-install/OpenCVConfig-version.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xdevx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/cmake/OpenCVConfig.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibsx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE PERMISSIONS OWNER_READ GROUP_READ WORLD_READ FILES "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/LICENSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/out/build/x64-Debug (impostazione predefinita)/3rdparty/zlib/cmake_install.cmake")
  include("D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/out/build/x64-Debug (impostazione predefinita)/3rdparty/libtiff/cmake_install.cmake")
  include("D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/out/build/x64-Debug (impostazione predefinita)/3rdparty/libjpeg/cmake_install.cmake")
  include("D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/out/build/x64-Debug (impostazione predefinita)/3rdparty/libjasper/cmake_install.cmake")
  include("D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/out/build/x64-Debug (impostazione predefinita)/3rdparty/libpng/cmake_install.cmake")
  include("D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/out/build/x64-Debug (impostazione predefinita)/3rdparty/openexr/cmake_install.cmake")
  include("D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/out/build/x64-Debug (impostazione predefinita)/include/cmake_install.cmake")
  include("D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/out/build/x64-Debug (impostazione predefinita)/modules/cmake_install.cmake")
  include("D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/out/build/x64-Debug (impostazione predefinita)/doc/cmake_install.cmake")
  include("D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/out/build/x64-Debug (impostazione predefinita)/data/cmake_install.cmake")
  include("D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/out/build/x64-Debug (impostazione predefinita)/apps/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/out/build/x64-Debug (impostazione predefinita)/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
