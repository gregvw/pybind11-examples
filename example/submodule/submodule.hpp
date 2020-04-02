#pragma once
#ifndef SUBMODULE_HPP
#define SUBMODULE_HPP

#include <pybind11/pybind11.h>

namespace py = pybind11;

void init_foo( py::module& );
void init_bar( py::module& );


#endif //SUBMODULE_HPP

