#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <memory>
#include "MeshModel.h"






class Light
{

public:
	Light(glm::vec4 p, int type, glm::vec4 p2);
	virtual ~Light();

	//transformation methods
	void set_translation_w(float x, float y, float z);
	void set_rotation_w(float a, float x, float y, float z);
	void set_translation_L(float x, float y, float z);
	void set_rotation_L(float a, float x, float y, float z);
	const glm::mat4x4 get_Transform_Mat() const;
	void set_Transform_Mat(int flag);

	//colors methods
	void set_ambient_color(float R, float G, float B);
	 glm::vec3 get_ambient_color() ;
	void set_diffuse_color(float R, float G, float B);
	 glm::vec3 get_diffuse_color() ;
	void set_specular_color(float R, float G, float B);
	 glm::vec3 get_specular_color() ;

	//direction, position and mode methods
	void set_direction(glm::vec3 direction);
	const glm::vec3 get_direction() const;
	void set_position(glm::vec4 position);
	 glm::vec4 get_position() ;
	void set_mode(int mode);
	const int get_mode() const;

	//changes_flag
	void set_chandes_flag(bool b);
	const int get_changes_flag() const;

	//alpha
	void set_alpha(int a);
	const int get_alpha() const;

	//m
	void set_m(int a);
	const int get_m() const;


	GLuint GetVAO() const;
	glm::vec3 Get_parallel() const;
	const std::vector<glm::vec3>& GetpointlightVertices();
	const std::vector<glm::vec3>& GetparalightVertices();

private:

	int m=0;

	float R_ambient;
	float G_ambient;
	float B_ambient;
	float R_diffuse;
	float G_diffuse;
	float B_diffuse;
	float R_specular;
	float G_specular;
	float B_specular;
	int alpha = 5;

	int mode_flag = 0; // 0 for Point and 1 for Parallel and 2 for Ambient
	//glm::vec3 light_direction = glm::vec3(0.0f, 0.5f, 0.0f);
	glm::vec3 light_direction ;
	glm::vec4 light_position;

	glm::mat4x4 translation_Mat_W = glm::mat4(1.0f);
	glm::mat4x4 rotation_Mat_W = glm::mat4(1.0f);
	glm::mat4x4 translation_Mat_L = glm::mat4(1.0f);
	glm::mat4x4 rotation_Mat_L = glm::mat4(1.0f);
	glm::mat4x4 Transform_Mat = glm::mat4(1.0f);
	glm::mat4x4 R_X_W = glm::mat4(1.0f);
	glm::mat4x4 R_Y_W = glm::mat4(1.0f);
	glm::mat4x4 R_Z_W = glm::mat4(1.0f);
	glm::mat4x4 R_X_L = glm::mat4(1.0f);
	glm::mat4x4 R_Y_L = glm::mat4(1.0f);
	glm::mat4x4 R_Z_L = glm::mat4(1.0f);

	bool changes_flag = false;

	GLuint Vao_l;
	GLuint Vbo_l;
	glm::vec3 parallel = glm::vec3(0.07, 0.02, 0);
	std::vector<glm::vec3> pointlightVertices;
	std::vector<glm::vec3> paralightVertices;

};

