#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

namespace py = pybind11;

template<typename T>
py::array_t<T> add( py::array_t<T> x, 
                    py::array_t<T> y ) {

  // Read input arrays to buffer info
  py::buffer_info x_buf = x.request(),
                  y_buf = y.request();
  
  // Allocate the output buffer
  py::array_t<T> result = py::array_t<T>(x_buf.size);
  py::buffer_info r_buf = result.request();

  T* x_ptr = (T*) x_buf.ptr;
  T* y_ptr = (T*) y_buf.ptr;
  T* r_ptr = (T*) r_buf.ptr;

  for( size_t i=0; i<x_buf.shape[0]; ++i )
    r_ptr[i] = x_ptr[i] + y_ptr[i];

  return result;
}

PYBIND11_MODULE(numpy_array,m) {
  m.doc() = "Example of adding two numpy arrays";
  m.def("add", &add<int>, "Adds two numpy arrays of integers");
  m.def("add", &add<double>, "Adds two numpy arrays of doubles");
}
