#include <pybind11/pybind11.h>

namespace py = pybind11;

int add( int i, int j ) {
  return i+j;
}

PYBIND11_MODULE(free_function,m) {
  m.doc() = "Example of using simple free function";
  m.def("add", &add, "Adds two integers");
}
