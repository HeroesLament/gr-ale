find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_ALE gnuradio-ale)

FIND_PATH(
    GR_ALE_INCLUDE_DIRS
    NAMES gnuradio/ale/api.h
    HINTS $ENV{ALE_DIR}/include
        ${PC_ALE_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_ALE_LIBRARIES
    NAMES gnuradio-ale
    HINTS $ENV{ALE_DIR}/lib
        ${PC_ALE_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-aleTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_ALE DEFAULT_MSG GR_ALE_LIBRARIES GR_ALE_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_ALE_LIBRARIES GR_ALE_INCLUDE_DIRS)
