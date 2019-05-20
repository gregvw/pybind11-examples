#include <pybind11/pybind11.h>
#include <string>

namespace py = pybind11;


PYBIND11_MODULE(lambda_function,m) {
  m.doc() = "Example of using a lambda function";
  m.def("add",[](int a,int b){ return a+b; }, "Adds two integers");
  m.def("add",[](double a,double b){ return a+b; }, "Adds two doubles");
  m.def("add",[](std::string a, std::string b){ return a+b; }, 
        "Concatenates two strings");
}
