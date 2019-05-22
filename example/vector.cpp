#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <vector>
#include <sstream>
#include <iostream>

namespace py = pybind11;

template<typename T>
class Vector {
public:

  using value_type      = T; 
  using data_type       = std::vector<T>;
  using reference       = value_type&;
  using const_reference = const value_type&;

  Vector( int N ) : data(N) {}

  Vector operator+ ( const Vector& x ) const {
    Vector result(data.size());
    for(int i=0; i<data.size(); ++i)  result.data[i] = data[i] + x.data[i];
    return result;
  }

  Vector operator- ( const Vector& x ) const {
    Vector result(data.size());
    for(int i=0; i<data.size(); ++i)  result.data[i] = data[i] - x.data[i];
    return result;
  }

  inline int size() const { return static_cast<int>(data.size()); }
  inline const_reference operator[] ( int i ) const noexcept { return data[i]; }
  inline reference       operator[] ( int i )       noexcept { return data[i]; }

   std::string to_string() const { 
     std::stringstream s;
     s << "[ ";
     for( auto e: data ) { s << e << " "; }
     s << "]";
     return s.str();
   } 
 
   void apply_function( py::object func ) {
     for( auto& e : data ) {
       py::object result = func(e);
       e = result.cast<T>();
     }
   }

   void reduce( py::object r ) {
     py::float_ minus_one(-1.0), one(1.0), two(2.0), zero(0.0);
     py::float_ y = r(-one-one,-one);
     py::float_ x = r(zero,one);
     std::cout << x.cast<T>() << " " << y.cast<T>() << std::endl;
     
   }


private: 

  data_type data;

}; // class Vector

template<typename T>
py::class_<Vector<T>> pybind_class_Vector( py::module& m, const char* name ) {
  return 
  py::class_<Vector<T>>(m,name)
  .def(py::init<int>())
  .def("size",&Vector<T>::size,"Number of elements")
  .def("__setitem__", 
       [](Vector<T>& v, int index, T value) {
         if(index>v.size()) throw py::index_error();
         else v[index] = value;
       })
  .def("__getitem__",[](Vector<T>& v, int index) {
    if(index>v.size()) throw py::index_error();
    else return v[index];
  })
  .def("__len__",&Vector<T>::size)
  .def("__str__",&Vector<T>::to_string)
  .def("__repr__",&Vector<T>::to_string)
  .def("apply_function",[]( Vector<T>& v, py::object func ) {
    v.apply_function(func);
   })
  .def("reduce",[]( Vector<T>& v, py::object r ) { 
    v.reduce(r);
   })
  .def(py::self + py::self)
  .def(py::self - py::self);
}


PYBIND11_MODULE(vector,m) {
  pybind_class_Vector<float>(m,"FloatVector");
  pybind_class_Vector<double>(m,"DoubleVector");
}
