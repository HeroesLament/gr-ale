#pragma once

#include <pybind11/pybind11.h>
#include <gnuradio/ale/decode_ff.h>

// Macro for documentation utility, if used elsewhere, ensure it doesn't conflict
#ifndef D
#define D(...) DOC(gr, ale, __VA_ARGS__)
#endif

// Declaration of the binding function for decode_ff
void bind_decode_ff(pybind11::module &m);
