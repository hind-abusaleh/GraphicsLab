#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	virtual ~Camera();

	void SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);
	const glm::mat4x4 get_lookAt_mat() const;
	const glm::mat4x4& GetProjectionTransformation() const;
	const glm::mat4x4& GetViewTransformation() const;

	void set_translation_w(float x, float y, float z);
	void set_rotation_w(float a, float x, float y, float z);
	void set_translation_L(float x, float y, float z);
	void set_rotation_L(float a, float x, float y, float z);
	const glm::mat4x4 get_invTransform_Mat() const;
	void set_invTransform_Mat(int flag);
	void set_orth(float x);
	void set_perspective(float x);
	void set_orth_flag(int flag);
    int get_orth_flag()const;
	void set_draw_color(int flag);
	int get_draw_flag();

	glm::vec3 get_eye()const;

private:
	float w = 1920;
	float h = 1080;
	float aspectrat = w / h;
	float fovy = 45;
	float ortho_val = 0.5;
	float left = (-w) / 2, right = w / 2;
	float  bottom = (-h) / 2, top = h / 2;
	float pro_near = 0.1;
	float pro_far = 200;
	int orth_flag=1;

	glm::mat4x4 view_transformation_ = glm::mat4x4(1.0f);
	glm::mat4x4 projection_transformation_ = glm::mat4x4(1.0f);

	glm::mat4x4 translation_Mat_W = glm::mat4x4(1.0f);
	glm::mat4x4 rotation_Mat_W = glm::mat4x4(1.0f);
	glm::mat4x4 translation_Mat_L = glm::mat4x4(1.0f);
	glm::mat4x4 rotation_Mat_L = glm::mat4x4(1.0f);
	glm::mat4x4 invTransform_Mat = glm::mat4x4(1.0f);
	glm::mat4x4 R_X_W = glm::mat4x4(1.0f);
	glm::mat4x4 R_Y_W = glm::mat4x4(1.0f);
	glm::mat4x4 R_Z_W = glm::mat4x4(1.0f);
	glm::mat4x4 R_X_L = glm::mat4x4(1.0f);
	glm::mat4x4 R_Y_L = glm::mat4x4(1.0f);
	glm::mat4x4 R_Z_L = glm::mat4x4(1.0f);
	glm::mat4x4 lookAt_mat = glm::mat4x4(1.0f);

	int draw_flag = 0;
	glm::vec3 eye_;
};
