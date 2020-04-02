#include <pybind11/pybind11.h>
#include <string>

namespace py = pybind11;

void init_bar( py::module& m ) {
  m.def("text",[](){ return std::string("bar");});
}
