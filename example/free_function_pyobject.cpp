#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>

namespace py = pybind11;


py::object add( py::object x,  py::object y ) {
  return x+y;
}

PYBIND11_MODULE(free_function_pyobject,m) {
  m.doc() = "Example of using simple free function with PyObjects";
  m.def("add", &add, "Adds two Python Objects");
}
