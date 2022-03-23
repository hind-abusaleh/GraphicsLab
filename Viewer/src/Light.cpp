#include "Light.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <string>



Light::Light(glm::vec4 p, int type, glm::vec4 p2)
{


	R_ambient = 1;
	G_ambient = 1;
	B_ambient = 1;
	R_diffuse = 1;
	G_diffuse = 1;
	B_diffuse = 1;
	R_specular = 1;
	G_specular = 1;
	B_specular = 1;
	
	//light_direction = glm::vec3(0, 0, -1);
	light_direction = glm::vec3(-0.009f, -0.005f, 0.0f);
	//light_position = glm::vec4(p,1);
	mode_flag = type;
	if (mode_flag == 0) //point
	{
		light_position = p;
		pointlightVertices.reserve(3);
		glm::vec3 p1 = glm::vec3(p.x, p.y,p.z);
		glm::vec3 p2 = glm::vec3(p.x-0.002, p.y-0.002, p.z);
		glm::vec3 p3 = glm::vec3(p.x+0.002, p.y-0.002, p.z);

		pointlightVertices.push_back(p1);
		pointlightVertices.push_back(p2);
		pointlightVertices.push_back(p3);


		glGenVertexArrays(1, &Vao_l);
		glGenBuffers(1, &Vbo_l);

		glBindVertexArray(Vao_l);
		glBindBuffer(GL_ARRAY_BUFFER, Vbo_l);
		glBufferData(GL_ARRAY_BUFFER, pointlightVertices.size() * sizeof(glm::vec3), &pointlightVertices[0], GL_STATIC_DRAW);


		// Vertex Positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		
		
		// unbind to make sure other code does not change it somewhere else
		glBindVertexArray(0);
		//glGenVertexArrays(1, &Vao_l);

	}
	else //paralell
	{
		light_position = p2;
		glm::vec4 direction = normalize(glm::vec4(light_direction,1));
		direction = glm::scale(glm::vec3(10, 5, 5)) * direction + p2;


		paralightVertices.reserve(3);
		glm::vec3 p1 = glm::vec3(direction.x, direction.y, direction.z);
		glm::vec3 p2 = glm::vec3(direction.x - 0.002, direction.y - 0.002, direction.z);
		glm::vec3 p3 = glm::vec3(direction.x + 0.002, direction.y - 0.002, direction.z);

		paralightVertices.push_back(p1);
		paralightVertices.push_back(p2);
		paralightVertices.push_back(p3);

		glGenVertexArrays(1, &Vao_l);
		glGenBuffers(1, &Vbo_l);

		
		glBindVertexArray(Vao_l);
		glBindBuffer(GL_ARRAY_BUFFER, Vbo_l);
		glBufferData(GL_ARRAY_BUFFER, paralightVertices.size() * sizeof(glm::vec3), &paralightVertices[0], GL_STATIC_DRAW);

		// Vertex Positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// unbind to make sure other code does not change it somewhere else
		glBindVertexArray(0);
	}
}

Light::~Light()
{
	glDeleteVertexArrays(1, &Vao_l);
	glDeleteBuffers(1, &Vbo_l);
}

//transformation methods

void Light::set_translation_w(float x, float y, float z) {
	translation_Mat_W = glm::translate(glm::vec3(x, y, z));
	set_Transform_Mat(0);
}

void Light::set_rotation_w(float a, float x, float y, float z) {
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

void Light::set_translation_L(float x, float y, float z) {
	translation_Mat_L = glm::translate(glm::vec3(x, y, z));
	set_Transform_Mat(0);
}

void Light::set_rotation_L(float a, float x, float y, float z) {
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

const glm::mat4x4 Light::get_Transform_Mat() const {
	return Transform_Mat;
}

void Light::set_Transform_Mat(int flag) {
	if (flag == 0) {
		Transform_Mat = R_Z_W * R_Y_W * R_X_W * translation_Mat_W * R_Z_L * R_Y_L * R_X_L * translation_Mat_L;
		changes_flag = true;
	}
	else {
		Transform_Mat = glm::mat4x4(1.0f);
		translation_Mat_W = glm::mat4x4(1.0f);
		rotation_Mat_W = glm::mat4x4(1.0f);
		translation_Mat_L = glm::mat4x4(1.0f);
		rotation_Mat_L = glm::mat4x4(1.0f);
		R_X_W = glm::mat4x4(1.0f);
		R_Y_W = glm::mat4x4(1.0f);
		R_Z_W = glm::mat4x4(1.0f);
		R_X_L = glm::mat4x4(1.0f);
		R_Y_L = glm::mat4x4(1.0f);
		R_Z_L = glm::mat4x4(1.0f);
	}
}

//colors methods

void Light::set_ambient_color(float R, float G, float B) {
	R_ambient = R;
	G_ambient = G;
	B_ambient = B;
	changes_flag = true;
}

 glm::vec3 Light::get_ambient_color()  {
	return glm::vec3(R_ambient, G_ambient, B_ambient);
}

void Light::set_diffuse_color(float R, float G, float B) {
	R_diffuse = R;
	G_diffuse = G;
	B_diffuse = B;
	changes_flag = true;
}

 glm::vec3 Light::get_diffuse_color()  {
	return glm::vec3(R_diffuse, G_diffuse, B_diffuse);
}

void Light::set_specular_color(float R, float G, float B) {
	R_specular = R;
	G_specular = G;
	B_specular = B;
	changes_flag = true;
}

 glm::vec3 Light::get_specular_color()  {
	return glm::vec3(R_specular, G_specular, B_specular);
}

//direction, position and mode methods

void Light::set_direction(glm::vec3 direction) {
	light_direction = direction;
	changes_flag = true;
}

const glm::vec3 Light::get_direction() const {
	return light_direction;
}
void Light::set_position(glm::vec4 position) {
	light_position = position;
	changes_flag = true;
}

 glm::vec4 Light::get_position()  {
	return light_position;
}
void Light::set_mode(int mode) {
	mode_flag = mode;
	changes_flag = true;
}
const int Light::get_mode() const {
	return mode_flag;
}

//changes_flag

void Light::set_chandes_flag(bool b) {
	changes_flag = b;
}

const int Light::get_changes_flag() const {
	return changes_flag;
}

//alpha
void Light::set_alpha(int a) {
	alpha = a;
}
const int Light::get_alpha() const {
	return alpha;
}

//m
void Light::set_m(int a) {
	m = a;
}
const int Light::get_m() const {
	return m;
}

GLuint Light::GetVAO() const
{
	return Vao_l;
}
glm::vec3 Light::Get_parallel() const
{
	return parallel;
}

const std::vector<glm::vec3>& Light::GetpointlightVertices()
{
	return pointlightVertices;
}

const std::vector<glm::vec3>& Light::GetparalightVertices()
{
	return paralightVertices;
}