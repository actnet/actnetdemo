# Install script for directory: /home/yecao/newsae/sae/saedb

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/yecao/newsae/sae/saedemo/backend/build/saedb/external/gflags/cmake_install.cmake")
  INCLUDE("/home/yecao/newsae/sae/saedemo/backend/build/saedb/external/google-glog/cmake_install.cmake")
  INCLUDE("/home/yecao/newsae/sae/saedemo/backend/build/saedb/testing/cmake_install.cmake")
  INCLUDE("/home/yecao/newsae/sae/saedemo/backend/build/saedb/indexing/cmake_install.cmake")
  INCLUDE("/home/yecao/newsae/sae/saedemo/backend/build/saedb/storage/cmake_install.cmake")
  INCLUDE("/home/yecao/newsae/sae/saedemo/backend/build/saedb/serialization/cmake_install.cmake")
  INCLUDE("/home/yecao/newsae/sae/saedemo/backend/build/saedb/zrpc/cmake_install.cmake")
  INCLUDE("/home/yecao/newsae/sae/saedemo/backend/build/saedb/computing/cmake_install.cmake")
  INCLUDE("/home/yecao/newsae/sae/saedemo/backend/build/saedb/toolkit/activity/cmake_install.cmake")
  INCLUDE("/home/yecao/newsae/sae/saedemo/backend/build/saedb/toolkit/influence/cmake_install.cmake")
  INCLUDE("/home/yecao/newsae/sae/saedemo/backend/build/saedb/toolkit/RStarTree/cmake_install.cmake")
  INCLUDE("/home/yecao/newsae/sae/saedemo/backend/build/saedb/toolkit/LDA/cmake_install.cmake")
  INCLUDE("/home/yecao/newsae/sae/saedemo/backend/build/saedb/toolkit/pagerank/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

