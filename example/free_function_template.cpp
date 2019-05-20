#include <pybind11/pybind11.h>
#include <string>

namespace py = pybind11;

template<typename T>
T add( T i, T j ) {
  return i+j;
}

PYBIND11_MODULE(free_function_template,m) {
  m.doc() = "Example of using simple free function";
  m.def("add", &add<int>, "Add two integers");
  m.def("add", &add<double>, "Add two doubles");
  m.def("add", &add<std::string>, "Concatenate two strings");
}
