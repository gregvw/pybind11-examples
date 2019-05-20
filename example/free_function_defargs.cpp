#include <pybind11/pybind11.h>

namespace py = pybind11;

int add( int i, int j ) {
  return i+j;
}

PYBIND11_MODULE(free_function_defargs,m) {
  m.doc() = "Example of using simple free function with default arguments";
  m.def("add", &add, "Adds two integers with default argument values of 1 and 2",
        py::arg("i")=1, py::arg("j")=2);

}
