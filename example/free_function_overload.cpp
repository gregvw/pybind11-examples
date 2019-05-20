#include <pybind11/pybind11.h>

namespace py = pybind11;

int add( int i, int j ) {
  return i+j;
}

double add( double i, double j ) {
  return i+j;
}

PYBIND11_MODULE(free_function_overload,m) {
  m.doc() = "Example of using simple free function";
  m.def("add", (int(*)(int,int))&add, "Adds two integers");
  m.def("add", (double(*)(double,double))&add, "Adds two doubles");
  
}
