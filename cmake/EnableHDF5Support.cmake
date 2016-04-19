# Configure the HDF5 options that will be required in this project. The 
# following variables will be set:
# 1.) HDF5 - stores the HDF5 cpp wrapper library and the HDF5 core library
MACRO(ENABLE_HDF5_SUPPORT)

  IF(DEFINED HDF5_PREFIX)
    SET(CMAKE_PREFIX_PATH ${HDF5_PREFIX} ${CMAKE_PREFIX_PATH})
  ENDIF()

  # Find the HDF5 package available on this system
  FIND_PACKAGE(HDF5 1.8 REQUIRED)
 
  # Any execs built off of HFD5 will need both libraries so they will both
  # be stored in a single variable
  SET(HDF5 ${HDF5_CXX_LIBRARIES} -ldl)
  
  # Set the include paths for HDF5
  INCLUDE_DIRECTORIES(${HDF5_INCLUDE_DIRS})
  
  # Set the link paths for HDF5
  LINK_DIRECTORIES(${HDF5_LIBRARY_DIRS})

  # Echo the HDF5 details if a verbose configure was requested
  IF(CMAKE_VERBOSE_CONFIGURE)
    MESSAGE("Found HDF5! Here are the details: ")
    MESSAGE(" HDF5_INCLUDE_DIRS = ${HDF5_INCLUDE_DIRS}")
    MESSAGE(" HDF5_LIBRARY_DIRS = ${HDF5_LIBRARY_DIRS}")
    MESSAGE(" HDF5_LIBRARY = ${HDF5}")
    MESSAGE("End of HDF5 details\n")
  ENDIF()

ENDMACRO(ENABLE_HDF5_SUPPORT)