#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <iostream>
Camera::Camera()
{

}

Camera::~Camera()
{
	
}

const glm::mat4x4& Camera::GetProjectionTransformation() const
{
	return projection_transformation_;
}

const glm::mat4x4& Camera::GetViewTransformation() const
{
	return view_transformation_;
}


void Camera::set_translation_w(float x, float y, float z) {
	translation_Mat_W = glm::translate(glm::vec3(x, y, z));
	set_invTransform_Mat(0);
}

void Camera::set_rotation_w(float a, float x, float y, float z) {
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
	set_invTransform_Mat(0);
}


void Camera::set_translation_L(float x, float y, float z) {
	translation_Mat_L = glm::translate(glm::vec3(x, y, z));
	set_invTransform_Mat(0);
}

void Camera::set_rotation_L(float a, float x, float y, float z) {
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
	set_invTransform_Mat(0);
}


const glm::mat4x4 Camera::get_invTransform_Mat() const {
	return invTransform_Mat;
}


void Camera::set_invTransform_Mat(int flag) {
	if (flag == 0) {
		invTransform_Mat = R_Z_W * R_Y_W * R_X_W * translation_Mat_W * R_Z_L * R_Y_L * R_X_L * translation_Mat_L;
		invTransform_Mat = glm::inverse(invTransform_Mat);
	}
	else if(flag == 1){
		invTransform_Mat = glm::mat4x4(1.0f);
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

void Camera::set_orth( float x) {
	w = x;
	h = w / aspectrat;
	left = -w / 2;
	right = w / 2;
	bottom = -h / 2;
	top = h / 2;
	projection_transformation_ = glm::ortho(left, right, bottom, top, pro_near, pro_far);
}

void Camera::set_perspective(float x) {
	fovy = x;
	projection_transformation_ = glm::perspective(fovy, aspectrat, pro_near, pro_far);

}

void Camera::set_orth_flag(int flag) {
	orth_flag = flag;
}

int Camera::get_orth_flag() const {
	return orth_flag;
}

void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up) {
	lookAt_mat = glm::lookAt(eye, at, up);
	eye_ = eye;
}

const glm::mat4x4 Camera::get_lookAt_mat() const {
	return lookAt_mat;
}

void Camera::set_draw_color(int flag) {//0_gray, 1_random, -1_user
	draw_flag = flag;
}

int Camera::get_draw_flag(){
	return draw_flag;
}


glm::vec3 Camera::get_eye() const {
	return normalize(eye_);
}