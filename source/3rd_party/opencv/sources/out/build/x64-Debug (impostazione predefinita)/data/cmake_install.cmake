# Install script for directory: D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data

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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibsx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/OpenCV/haarcascades" TYPE FILE FILES
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_eye.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_frontalcatface.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_frontalcatface_extended.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_frontalface_alt2.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_frontalface_alt_tree.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_frontalface_default.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_fullbody.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_lefteye_2splits.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_licence_plate_rus_16stages.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_lowerbody.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_mcs_eyepair_big.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_mcs_eyepair_small.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_mcs_leftear.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_mcs_lefteye.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_mcs_mouth.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_mcs_nose.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_mcs_rightear.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_mcs_righteye.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_mcs_upperbody.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_profileface.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_righteye_2splits.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_russian_plate_number.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_smile.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/haarcascades/haarcascade_upperbody.xml"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibsx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/OpenCV/lbpcascades" TYPE FILE FILES
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/lbpcascades/lbpcascade_frontalcatface.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/lbpcascades/lbpcascade_frontalface.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/lbpcascades/lbpcascade_profileface.xml"
    "D:/Documenti/SparkEngine_Desktop - Copia/source/3rd_party/opencv/sources/data/lbpcascades/lbpcascade_silverware.xml"
    )
endif()

