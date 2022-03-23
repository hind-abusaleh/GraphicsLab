#pragma once
#include <glm/glm.hpp>
#include <string>
#include "Face.h"
#include <glad/glad.h>
#include <memory>
#include "MeshModel.h"


struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoords;
	
};

class MeshModel
{
public:
	MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name , glm:: mat4x4 M, float x_max , float y_max,float z_max,float x_min, float y_min,float z_min, std::vector<glm::vec2> textureCoords);
	virtual ~MeshModel();
	const Face& GetFace(int index) const;
	int GetFacesCount() const;
	const std::string& GetModelName() const;
	const glm::vec3 GetVer(int index) const;
	const glm::mat4x4 GetM() const;
	void print_faces();
	void print_vers();
	void set_translation_w(float x, float y, float z);
	void set_rotation_w(float a, float x, float y, float z);
	void set_scaling_w(float x, float y, float z);
	void set_translation_L(float x, float y, float z);
	void set_rotation_L(float a, float x, float y, float z);
	void set_scaling_L(float x, float y, float z);
	const glm::mat4x4 get_Transform_Mat() const;
	void set_Transform_Mat(int flag);
    glm::vec4 get_Uvec1() const;
	glm::vec4 get_Uvec2() const;
	glm::vec4 get_Uvec3() const;
	glm::vec4 get_Uvec4() const;
	glm::vec4 get_Dvec1() const;
	glm::vec4 get_Dvec2() const;
	glm::vec4 get_Dvec3() const;
	glm::vec4 get_Dvec4() const;
	void set_show_box_flag(int f);
	int get_show_box_flag();
	const glm::mat4x4 Get_rotation_W() const;
	const glm::mat4x4 Get_rotation_L() const;
	const glm::vec3 GetNorms(int index) const;
	void set_facenorm_flag(int f);
	int get_facenorm_flag();
	void set_vernorm_flag(int f);
	int get_vernorm_flag();

	//colors methods
	void set_ambient_color(float R, float G, float B);
	 glm::vec3 get_ambient_color() ;
	void set_diffuse_color(float R, float G, float B);
	 glm::vec3 get_diffuse_color() ;
	void set_specular_color(float R, float G, float B);
	 glm::vec3 get_specular_color() ;


	 GLuint GetVAO() const;
	 const std::vector<Vertex>& GetModelVertices();





protected:
	

	std::vector<Vertex> modelVertices;
	glm::vec3 color;

	GLuint vbo;
	GLuint vao;



private:
	std::vector<Face> faces_;
	std::vector<glm::vec3> vertices_;
	std::vector<glm::vec3> normals_;
	std::string model_name_;
	glm::mat4x4 Mmat;
	glm::mat4x4 translation_Mat_W;
	glm::mat4x4 rotation_Mat_W;
	glm::mat4x4 scaling_Mat_W;
	glm::mat4x4 translation_Mat_L;
	glm::mat4x4 rotation_Mat_L;
	glm::mat4x4 scaling_Mat_L;
	glm::mat4x4 Transform_Mat;
	glm::mat4x4 R_X_W;
	glm::mat4x4 R_Y_W;
	glm::mat4x4 R_Z_W;
	glm::mat4x4 R_X_L;
	glm::mat4x4 R_Y_L;
	glm::mat4x4 R_Z_L;
	float max_x;
	float max_y;
	float max_z;
	float min_x;
	float min_y;
	float min_z;
	int show_box_flag;
	int verNorm_flag;
	int faceNorm_flag;

	float R_ambient;
	float G_ambient;
	float B_ambient;
	float R_diffuse;
	float G_diffuse;
	float B_diffuse;
	float R_specular;
	float G_specular;
	float B_specular;

	
};


