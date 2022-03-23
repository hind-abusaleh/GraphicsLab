#include "MeshModel.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <string>
#include "Utils.h"
#include <fstream>
#include <sstream>
#include <random>


MeshModel::MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name, glm::mat4x4 M, float x_max, float y_max, float z_max, float x_min, float y_min, float z_min, std::vector<glm::vec2> textureCoords) :
	faces_(faces),
	vertices_(vertices),
	normals_(normals),
	model_name_ ( model_name),
	Mmat(M),
	translation_Mat_W(glm::mat4x4(1.0f)),
	rotation_Mat_W(glm::mat4x4(1.0f)),
	scaling_Mat_W(glm::mat4x4(1.0f)),
	translation_Mat_L(glm::mat4x4(1.0f)),
	rotation_Mat_L(glm::mat4x4(1.0f)),
	scaling_Mat_L(glm::mat4x4(1.0f)),
	Transform_Mat(glm::mat4x4(1.0f)),
	R_X_W(glm::mat4x4(1.0f)),
	R_Y_W(glm::mat4x4(1.0f)),
	R_Z_W(glm::mat4x4(1.0f)),
	R_X_L(glm::mat4x4(1.0f)),
	R_Y_L(glm::mat4x4(1.0f)),
	R_Z_L(glm::mat4x4(1.0f)),
	max_x(x_max),
	max_y(y_max),
	max_z(z_max),
	min_x(x_min),
	min_y(y_min),
	min_z(z_min)
{

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(0, 1);
	color = glm::vec3(dist(mt), dist(mt), dist(mt));

	R_ambient = dist(mt);
	G_ambient = dist(mt);
	B_ambient = dist(mt);
	R_diffuse = dist(mt);
	G_diffuse = dist(mt);
	B_diffuse = dist(mt);
	R_specular = dist(mt);
	G_specular = dist(mt);
	B_specular = dist(mt);


	modelVertices.reserve(3 * faces.size());
	for (int i = 0; i < faces.size(); i++)
	{
		Face currentFace = faces.at(i);
		for (int j = 0; j < 3; j++)
		{
			int vertexIndex = currentFace.GetVertexIndex(j) - 1;
			int normalIndex = currentFace.GetNormalIndex(j) - 1;

			Vertex vertex;
			vertex.position = vertices[vertexIndex];
			if (normals.size())
				vertex.normal = normals[normalIndex];

			if (textureCoords.size() > 0)
			{
				int textureCoordsIndex = currentFace.GetTextureIndex(j) - 1;
				vertex.textureCoords = textureCoords[textureCoordsIndex];
			}

			modelVertices.push_back(vertex);
		}
	}
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, modelVertices.size() * sizeof(Vertex), &modelVertices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Vertex Texture Coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// unbind to make sure other code does not change it somewhere else
	glBindVertexArray(0);
}

MeshModel::~MeshModel()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

const Face& MeshModel::GetFace(int index) const
{
	return faces_[index];
}

int MeshModel::GetFacesCount() const
{
	return faces_.size();
}

const std::string& MeshModel::GetModelName() const
{
	return model_name_;
}


const glm::vec3 MeshModel::GetVer(int index) const
{
	return vertices_[index - 1];
}

const glm::mat4x4 MeshModel::GetM() const
{
	return Mmat;
}

void MeshModel::print_faces() {
	int index;
	for (int i = 0; i < faces_.size(); i++){
			index = faces_[i].GetVertexIndex(0);
			std::cout << '[' << vertices_[index - 1].x << ',' << vertices_[index - 1].y << ',' << vertices_[index - 1].z << ']';
			index = faces_[i].GetVertexIndex(1);
			std::cout << '[' << vertices_[index - 1].x << ',' << vertices_[index - 1].y << ',' << vertices_[index - 1].z << ']';
			index = faces_[i].GetVertexIndex(2);
			std::cout << '[' << vertices_[index - 1].x << ',' << vertices_[index - 1].y << ',' << vertices_[index - 1].z << ']';
			std::cout << "\n";

		}
}

void MeshModel::print_vers() {
	std::cout << "all the  vertices:";
	for (int i = 1; i < vertices_.size(); i++)
	{
		std::cout << '[' << vertices_[i - 1].x << ',' << vertices_[i - 1].y << ',' << vertices_[i - 1].z << ']';
		std::cout << "\n";

	}
}

void MeshModel::set_translation_w(float x, float y, float z) {
	translation_Mat_W = glm::translate(glm::vec3(x, y, z));
	set_Transform_Mat(0);
}

void MeshModel::set_rotation_w(float a, float x, float y, float z) {
	rotation_Mat_W = glm::rotate(a, glm::vec3(x, y, z));
	if (x == 1) {
		R_X_W = rotation_Mat_W;
	}
	if (y == 1) {
		R_Y_W = rotation_Mat_W;
	}
	if (z == 1) {
		R_Z_W = rotation_Mat_W;
	}
	set_Transform_Mat(0);
}

void MeshModel::set_scaling_w(float x, float y, float z) {
	scaling_Mat_W = glm::scale(glm::vec3( x,  y, z));
	set_Transform_Mat(0);
}

void MeshModel::set_translation_L(float x, float y, float z) {
	translation_Mat_L = glm::translate(glm::vec3(x, y, z));
	set_Transform_Mat(0);
}

void MeshModel::set_rotation_L(float a, float x, float y, float z) {
	rotation_Mat_L = glm::rotate(a, glm::vec3(x, y, z));
	if (x == 1) {
		R_X_L = rotation_Mat_L;
	}
	if (y == 1) {
		R_Y_L = rotation_Mat_L;
	}
	if (z == 1) {
		R_Z_L = rotation_Mat_L;
	}
	set_Transform_Mat(0);
}

void MeshModel::set_scaling_L(float x, float y, float z) {
	scaling_Mat_L = glm::scale(glm::vec3(x, y, z));
	set_Transform_Mat(0);
}

 const glm::mat4x4 MeshModel::get_Transform_Mat() const {
	return Transform_Mat;
}


 void MeshModel::set_Transform_Mat(int flag) {
	 if (flag == 0)
		 Transform_Mat = scaling_Mat_W * R_Z_W * R_Y_W * R_X_W * translation_Mat_W * scaling_Mat_L * R_Z_L * R_Y_L * R_X_L * translation_Mat_L;
	 else {
		 Transform_Mat = glm::mat4x4(1.0f);
		 translation_Mat_W = glm::mat4x4(1.0f);
		 rotation_Mat_W = glm::mat4x4(1.0f);
		 scaling_Mat_W = glm::mat4x4(1.0f);
		 translation_Mat_L = glm::mat4x4(1.0f);
		 rotation_Mat_L = glm::mat4x4(1.0f);
		 scaling_Mat_L = glm::mat4x4(1.0f);
		 R_X_W = glm::mat4x4(1.0f);
		 R_Y_W = glm::mat4x4(1.0f);
		 R_Z_W = glm::mat4x4(1.0f);
		 R_X_L = glm::mat4x4(1.0f);
		 R_Y_L = glm::mat4x4(1.0f);
		 R_Z_L = glm::mat4x4(1.0f);
	 }
 }

 glm::vec4 MeshModel::get_Uvec1() const {
	 glm::mat4x4 mymat;
	// mymat = Transform_Mat * Mmat;
	 return (Transform_Mat * glm::vec4(max_x, max_y, max_z, 1));
 }

 glm::vec4 MeshModel::get_Uvec2() const {
	 glm::mat4x4 mymat;
	// mymat = Transform_Mat * Mmat;
	 return (Transform_Mat * glm::vec4(max_x, max_y, min_z, 1));
 }

 glm::vec4 MeshModel::get_Uvec3() const {
	 glm::mat4x4 mymat;
	// mymat = Transform_Mat * Mmat;
	 return (Transform_Mat * glm::vec4(min_x, max_y, max_z, 1));
 }

 glm::vec4 MeshModel::get_Uvec4() const {
	 glm::mat4x4 mymat;
	// mymat = Transform_Mat * Mmat;
	 return (Transform_Mat * glm::vec4(min_x, max_y, min_z, 1));
 }

 glm::vec4 MeshModel::get_Dvec1() const {
	 glm::mat4x4 mymat;
	// mymat = Transform_Mat * Mmat;
	 return (Transform_Mat * glm::vec4(max_x, min_y, max_z, 1));
 }

 glm::vec4 MeshModel::get_Dvec2() const {
	 glm::mat4x4 mymat;
	 //mymat = Transform_Mat * Mmat;
	 return (Transform_Mat * glm::vec4(max_x, min_y, min_z, 1));
 }

 glm::vec4 MeshModel::get_Dvec3() const {
	 glm::mat4x4 mymat;
	// mymat = Transform_Mat * Mmat;
	 return (Transform_Mat * glm::vec4(min_x, min_y, max_z, 1));
 }

 glm::vec4 MeshModel::get_Dvec4() const {
	 glm::mat4x4 mymat;
	// mymat = Transform_Mat * Mmat;
	 return (Transform_Mat * glm::vec4(min_x, min_y, min_z, 1));
 }

 void MeshModel::set_show_box_flag(int f) {
	 show_box_flag = f;
 }
 int MeshModel::get_show_box_flag() {
	 return show_box_flag;
 }

 const glm::mat4x4 MeshModel::Get_rotation_W() const {
	 return rotation_Mat_W;
 }
 const glm::mat4x4 MeshModel::Get_rotation_L() const {
	 return rotation_Mat_L;
 }


 const glm::vec3 MeshModel::GetNorms(int index) const {
	 return normals_[index - 1];
 }

 void MeshModel::set_facenorm_flag(int f) {
	 faceNorm_flag = f;
 }
 int MeshModel::get_facenorm_flag() {
	 return faceNorm_flag;
 }

 void MeshModel::set_vernorm_flag(int f) {
	 verNorm_flag = f;
 }
 int MeshModel::get_vernorm_flag() {
	 return verNorm_flag;
 }

 // color 

 void MeshModel::set_ambient_color(float R, float G, float B) {
	 R_ambient = R;
	 G_ambient = G;
	 B_ambient = B;
 }

  glm::vec3 MeshModel::get_ambient_color()  {
	 return glm::vec3(R_ambient, G_ambient, B_ambient);
 }

 void MeshModel::set_diffuse_color(float R, float G, float B) {
	 R_diffuse = R;
	 G_diffuse = G;
	 B_diffuse = B;
 }

  glm::vec3 MeshModel::get_diffuse_color()  {
	 return glm::vec3(R_diffuse, G_diffuse, B_diffuse);
 }

 void MeshModel::set_specular_color(float R, float G, float B) {
	 R_specular = R;
	 G_specular = G;
	 B_specular = B;
 }

  glm::vec3 MeshModel::get_specular_color()  {
	 return glm::vec3(R_specular, G_specular, B_specular);
 }



  GLuint MeshModel::GetVAO() const
  {
	  return vao;
  }

  const std::vector<Vertex>& MeshModel::GetModelVertices()
  {
	  return modelVertices;
  }