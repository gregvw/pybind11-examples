pybind11_add_module( free_function          free_function.cpp          )
pybind11_add_module( free_function_defargs  free_function_defargs.cpp  )
pybind11_add_module( free_function_overload free_function_overload.cpp )
pybind11_add_module( free_function_template free_function_template.cpp )
pybind11_add_module( lambda_function        lambda_function.cpp        )
pybind11_add_module( numpy_array            numpy_array.cpp            )
pybind11_add_module( vector                 vector.cpp                 )
add_subdirectory(submodule)
