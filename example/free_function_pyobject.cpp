#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>

namespace py = pybind11;


py::list concatenate( py::list x,  py::list y ) {
  return x+y;
}

PYBIND11_MODULE(free_function_pyobject,m) {
  m.doc() = "Example of using simple free function with PyObjects";
  m.def("concatenate", &concatenate, "Concatenate two Python lists");
}
