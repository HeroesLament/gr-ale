# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT ale_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT ale_sources)

########################################################################
# Check for pygccxml
########################################################################
GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND ale_python_files
    decode_ff_python.cc
    python_bindings.cc)

GR_PYBIND_MAKE_OOT(ale
   ../../..
   gr::ale
   "${ale_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(TARGET ale_python POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ale_python>
    ${PROJECT_BINARY_DIR}/test_modules/gnuradio/ale/
)

install(TARGETS ale_python DESTINATION ${GR_PYTHON_DIR}/gnuradio/ale COMPONENT pythonapi)
