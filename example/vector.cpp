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

   T reduce( py::object r ) {

     // Deduce function type as min, max, plus, or multiplies
     py::float_ minus_one(-1.0), zero(0.0), one(1.0);

     py::float_ test_1 = r(minus_one,one);  T value_1 = test_1.cast<T>();
     py::float_ test_2 = r(minus_one,zero); T value_2 = test_2.cast<T>();
     T test_value = 3 + 2*value_1 + value_2;

     py::float_ result;

     if     ( test_value == T(0) ) result = py::float_(std::numeric_limits<T>::max());
     else if( test_value == T(5) ) result = py::float_(std::numeric_limits<T>::min());
     else if( test_value == T(2) ) result = zero;
     else if( test_value == T(1) ) result = one;
     else throw std::runtime_error("Binary function could not be identified");

     for( auto& e : data ) result = r(result,e);

     return result.cast<T>();       
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
    return v.reduce(r);
   })
  .def(py::self + py::self)
  .def(py::self - py::self);
}


PYBIND11_MODULE(vector,m) {
  pybind_class_Vector<float>(m,"FloatVector");
  pybind_class_Vector<double>(m,"DoubleVector");
}
