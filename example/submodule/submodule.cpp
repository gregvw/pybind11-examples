#include "submodule.hpp"

PYBIND11_MODULE(submodule,m) {

  py::module foo = m.def_submodule("foo","Submodule foo");
  init_foo(foo);

  py::module bar = m.def_submodule("bar","Submodule bar");
  init_bar(bar);

}
