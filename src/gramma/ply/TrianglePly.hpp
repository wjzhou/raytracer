#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <tr1/functional>
//#include <boost/container/vector.hpp>
#include <vector>
//using namespace boost::container;
using namespace std;
#include "ply_parser.hpp"

using namespace std::tr1::placeholders;
template <typename TMVertex, typename TMFace>
class Ply
{
public:
  Ply(const string& istream_filename);
  bool parse();
  vector<TMVertex>& getVertexs(){return vertexs;}
  vector<TMFace>& getFaces(){return faces;}

private:
  void info_callback(const std::string& filename, std::size_t line_number, const std::string& message);
  void warning_callback(const std::string& filename, std::size_t line_number, const std::string& message);
  void error_callback(const std::string& filename, std::size_t line_number, const std::string& message);
  std::tr1::tuple<std::tr1::function<void()>, std::tr1::function<void()> > element_definition_callback(const std::string& element_name, std::size_t count);
  template <typename ScalarType> std::tr1::function<void (ScalarType)> scalar_property_definition_callback(const std::string& element_name, const std::string& property_name);
  template <typename SizeType, typename ScalarType> std::tr1::tuple<std::tr1::function<void (SizeType)>, std::tr1::function<void (ScalarType)>, std::tr1::function<void ()> > list_property_definition_callback(const std::string& element_name, const std::string& property_name);
  void vertex_begin();
  void vertex_x(ply::float32 x);
  void vertex_y(ply::float32 y);
  void vertex_z(ply::float32 z);
  void vertex_end();
  void face_begin();
  void face_vertex_indices_begin(ply::uint8 size);
  void face_vertex_indices_element(ply::int32 vertex_index);
  void face_vertex_indices_end();
  void face_end();
  float vertex_x_, vertex_y_, vertex_z_;
  std::size_t face_vertex_indices_element_index_, face_vertex_indices_first_element_, face_vertex_indices_previous_element_;
  vector<TMVertex> vertexs;
  vector<TMFace> faces;
  std::string istream_filename;
};

template <typename TMVertex, typename TMFace>
Ply<TMVertex,TMFace>::Ply(const string& istream_filename)
  :istream_filename(istream_filename)
{
}

template <typename TMVertex, typename TMFace>
void Ply<TMVertex,TMFace>::info_callback(const std::string& filename, std::size_t line_number, const std::string& message)
{
  std::cerr << filename << ":" << line_number << ": " << "info: " << message << std::endl;
}
template <typename TMVertex, typename TMFace>
void Ply<TMVertex,TMFace>::warning_callback(const std::string& filename, std::size_t line_number, const std::string& message)
{
  std::cerr << filename << ":" << line_number << ": " << "warning: " << message << std::endl;
}

template <typename TMVertex, typename TMFace>
void Ply<TMVertex,TMFace>::error_callback(const std::string& filename, std::size_t line_number, const std::string& message)
{
  std::cerr << filename << ":" << line_number << ": " << "error: " << message << std::endl;
}

template <typename TMVertex, typename TMFace>
std::tr1::tuple<std::tr1::function<void()>, std::tr1::function<void()> > Ply<TMVertex,TMFace>::element_definition_callback(const std::string& element_name, std::size_t count)
{
  if (element_name == "vertex") {
    vertexs.reserve(count);
    return std::tr1::tuple<std::tr1::function<void()>, std::tr1::function<void()> >(
      std::tr1::bind(&Ply::vertex_begin, this),
      std::tr1::bind(&Ply::vertex_end, this)
    );
  }
  else if (element_name == "face") {
    faces.reserve(count);
    return std::tr1::tuple<std::tr1::function<void()>, std::tr1::function<void()> >(
      std::tr1::bind(&Ply::face_begin, this),
      std::tr1::bind(&Ply::face_end, this)
    );
  }
  else {
    return std::tr1::tuple<std::tr1::function<void()>, std::tr1::function<void()> >(0, 0);
  }
}

template <typename TMVertex, typename TMFace>
template <typename ScalarType>
std::tr1::function<void (ScalarType)> Ply<TMVertex,TMFace>::scalar_property_definition_callback(const std::string& element_name, const std::string& property_name)
{
  if (element_name == "vertex") {
    if (property_name == "x") {
      return std::tr1::bind(&Ply::vertex_x, this, _1);
    }
    else if (property_name == "y") {
      return std::tr1::bind(&Ply::vertex_y, this, _1);
    }
    else if (property_name == "z") {
      return std::tr1::bind(&Ply::vertex_z, this, _1);
    }
    else {
      return 0;
    }
  }
  else {
    return 0;
  }
}

template <typename TMVertex, typename TMFace>
template <class SizeType, class ScalarType>
std::tr1::tuple<std::tr1::function<void (SizeType)>, std::tr1::function<void (ScalarType)>, std::tr1::function<void ()> > Ply<TMVertex,TMFace>::list_property_definition_callback(const std::string& element_name, const std::string& property_name)
{
  if ((element_name == "face") && (property_name == "vertex_indices")) {
    return std::tr1::tuple<std::tr1::function<void (ply::uint8)>, std::tr1::function<void (ply::int32)>, std::tr1::function<void ()> >(
      std::tr1::bind(&Ply::face_vertex_indices_begin, this, _1),
      std::tr1::bind(&Ply::face_vertex_indices_element, this, _1),
      std::tr1::bind(&Ply::face_vertex_indices_end, this)
    );
  }
  else {
    return std::tr1::tuple<std::tr1::function<void (ply::uint8)>, std::tr1::function<void (ply::int32)>, std::tr1::function<void ()> >(0, 0, 0);
  }
}

template <typename TMVertex, typename TMFace>
void Ply<TMVertex,TMFace>::vertex_begin()
{
}

template <typename TMVertex, typename TMFace>
void Ply<TMVertex,TMFace>::vertex_x(ply::float32 x)
{
  vertex_x_ = x;
}

template <typename TMVertex, typename TMFace>
void Ply<TMVertex,TMFace>::vertex_y(ply::float32 y)
{
  vertex_y_ = y;
}

template <typename TMVertex, typename TMFace>
void Ply<TMVertex,TMFace>::vertex_z(ply::float32 z)
{
  vertex_z_ = z;
}

template <typename TMVertex, typename TMFace>
void Ply<TMVertex,TMFace>::vertex_end()
{
  vertexs.emplace_back(vertex_x_,vertex_y_,vertex_z_);
}

template <typename TMVertex, typename TMFace>
void Ply<TMVertex,TMFace>::face_begin()
{

}

template <typename TMVertex, typename TMFace>
void Ply<TMVertex,TMFace>::face_vertex_indices_begin(ply::uint8 size)
{
  face_vertex_indices_element_index_ = 0;
}

template <typename TMVertex, typename TMFace>
void Ply<TMVertex,TMFace>::face_vertex_indices_element(ply::int32 vertex_index)
{
  if (face_vertex_indices_element_index_ == 0) {
    face_vertex_indices_first_element_ = vertex_index;
  }
  else if (face_vertex_indices_element_index_ == 1) {
    face_vertex_indices_previous_element_ = vertex_index;
  }
  else {
    faces.emplace_back(vertexs[face_vertex_indices_first_element_].position,vertexs[face_vertex_indices_previous_element_].position,vertexs[vertex_index].position);
    face_vertex_indices_previous_element_ = vertex_index;
  }
  ++face_vertex_indices_element_index_; 
}

template <typename TMVertex, typename TMFace>
void Ply<TMVertex,TMFace>::face_vertex_indices_end()
{

}

template <typename TMVertex, typename TMFace>
void Ply<TMVertex,TMFace>::face_end()
{
}

template <typename TMVertex, typename TMFace>
bool Ply<TMVertex,TMFace>::parse()
{
  std::ifstream ifstream;
  ifstream.open(istream_filename.c_str(),std::ifstream::in);
  if (!ifstream.is_open()) {
    std::cerr << "can not open fly file" << istream_filename << ": " << "no such file or directory" << "\n";
    exit(EXIT_FAILURE);
  }
  ply::ply_parser ply_parser;

  ply_parser.info_callback(std::tr1::bind(&(Ply<TMVertex,TMFace>::info_callback), this, std::tr1::ref(istream_filename), _1, _2));
  ply_parser.warning_callback(std::tr1::bind(&Ply<TMVertex,TMFace>::warning_callback, this, std::tr1::ref(istream_filename), _1, _2));
  ply_parser.error_callback(std::tr1::bind(&Ply<TMVertex,TMFace>::error_callback, this, std::tr1::ref(istream_filename), _1, _2)); 

  ply_parser.element_definition_callback(std::tr1::bind(&Ply<TMVertex,TMFace>::element_definition_callback, this, _1, _2));

  ply::ply_parser::scalar_property_definition_callbacks_type scalar_property_definition_callbacks;
  scalar_property_definition_callbacks.get<ply::float32>() = std::tr1::bind(&Ply<TMVertex,TMFace>::scalar_property_definition_callback<ply::float32>, this, _1, _2);
  ply_parser.scalar_property_definition_callbacks(scalar_property_definition_callbacks);

  ply::ply_parser::list_property_definition_callbacks_type list_property_definition_callbacks;
  list_property_definition_callbacks.get<ply::uint8, ply::int32>() = std::tr1::bind(&Ply<TMVertex,TMFace>::list_property_definition_callback<ply::uint8, ply::int32>, this, _1, _2);
  ply_parser.list_property_definition_callbacks(list_property_definition_callbacks);

  return ply_parser.parse(ifstream);
}
