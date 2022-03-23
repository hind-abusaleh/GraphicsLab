#define _USE_MATH_DEFINES
#include <cmath>
#include <imgui/imgui.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <nfd.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Renderer.h"
#include "Scene.h"
#include "Utils.h"
#include "Light.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

/**
 * Fields
 */
bool show_demo_window = false;
bool show_another_window = false;
bool local_frame_trans = false;
bool world_frame_trans = false;
bool scaling = false;
bool translation = false;
bool rotation = false;
bool A_X = false;
bool A_Y = false;
bool A_Z = false;
bool show_transformations_window = false;
bool cam_translation = false;
bool cam_rotation = false;
bool cam_A_X = false;
bool cam_A_Y = false;
bool cam_A_Z = false;
bool local_cam_frame_trans = false;
bool world_cam_frame_trans = false;
bool orthographic_projection = true;
bool perspective_projection = false;
bool show_light_window = false;

static float w_s_arry[3] = { 1.0f, 1.0f, 1.0f };
static float w_t_arry[3] = { 0.0f, 0.0f, 0.0f };
static float l_s_arry[3] = { 1.0f, 1.0f, 1.0f };
static float l_t_arry[3] = { 0.0f, 0.0f, 0.0f };
static float angle_x_w = 0.0f;
static float angle_y_w = 0.0f;
static float angle_z_w = 0.0f;
static float angle_x_l = 0.0f;
static float angle_y_l = 0.0f;
static float angle_z_l = 0.0f;
static float last_angle_x_w = 0.0f;
static float last_angle_y_w = 0.0f;
static float last_angle_z_w = 0.0f;
static float last_angle_x_l = 0.0f;
static float last_angle_y_l = 0.0f;
static float last_angle_z_l = 0.0f;
static float w_last_s_arry[3] = { 2.0f, 2.0f, 2.0f };
static float w_last_t_arry[3] = { 2.0f, 2.0f, 2.0f };
static float l_last_s_arry[3] = { 2.0f, 2.0f, 2.0f };
static float l_last_t_arry[3] = { 2.0f, 2.0f, 2.0f };
static int c = 0;
static int reset = 0;
static int bb = 0;
static int light_mode_flag = 0;
static int versNF = 0;
static int faceNF = 0;
static int cc = 0;
static int pro = 0;
static int reset_c = 0;
static float w_cam_t_arry[3] = { 0, 0, 0 };
static float l_cam_t_arry[3] = { 0, 0, 0 };
static float w_last_cam_t_arry[3] = { 0.0f, 0.0f, 0.0f };
static float l_last_cam_t_arry[3] = { 0.0f, 0.0f, 0.0f };
static float cam_angle_x_w = 0.0f;
static float cam_angle_z_w = 0.0f;
static float cam_angle_x_l = 0.0f;
static float cam_angle_y_l = 0.0f;
static float cam_angle_z_l = 0.0f;
static float cam_angle_y_w = 0.0f;

static float last_cam_angle_x_w = 0.0f;
static float last_cam_angle_y_w = 0.0f;
static float last_cam_angle_z_w = 0.0f;
static float last_cam_angle_x_l = 0.0f;
static float last_cam_angle_y_l = 0.0f;
static float last_cam_angle_z_l = 0.0f;

static float eye_arry[3] = { 0.0f, 0.0f, 2.0f };
static float at_arry[3] = { 0.0f, 0.0f, 0.0f };
static float up_arry[3] = { 0.0f, 1.0f, 0.0f };

static float orth_width = 0.5;
static float fov =10;

static float orth_width_beet = 20;
static float orth_width_dol = 1000;
static float dol_fov = 270;
static float bunny_fov = 60;
static int draw_flag = 0;


static float ambient_model_color[3] = {1.0f, 1.0f, 1.0f };
static float diffuse_model_color[3] = { 1.0f, 1.0f, 1.0f };
static float specular_model_color[3] = { 1.0f, 1.0f, 1.0f };

//lights =>
bool control_model_color = false;
bool control_shading_type = false;
bool control_active_light_color = false;
bool control_light_direction = false;
static float ambient_color[3] = { 1.0f, 1.0f, 1.0f};
static float diffuse_color[3] = { 1.0f, 1.0f, 1.0f};
static float specular_color[3] = { 1.0f, 1.0f, 1.0f};
static float active_ambient_color[3] = { 1.0f, 1.0f, 1.0f };
static float active_diffuse_color[3] = { 1.0f, 1.0f, 1.0f };
static float active_specular_color[3] = { 1.0f, 1.0f, 1.0f };
int lights_counter = 0;
static int c_light = 0;
bool translation_light = false;
bool rotation_light = false;
bool A_X_light = false;
bool A_Y_light = false;
bool A_Z_light = false;
bool local_frame_trans_light = false;
bool world_frame_trans_light = false;
static float w_t_arry_light[3] = { 0.0f, 0.0f, 0.0f };
static float l_t_arry_light[3] = { 0.0f, 0.0f, 0.0f };
static float angle_x_w_light = 0.0f;
static float angle_y_w_light = 0.0f;
static float angle_z_w_light = 0.0f;
static float angle_x_l_light = 0.0f;
static float angle_y_l_light = 0.0f;
static float angle_z_l_light = 0.0f;
static float last_angle_x_w_light = 0.0f;
static float last_angle_y_w_light = 0.0f;
static float last_angle_z_w_light = 0.0f;
static float last_angle_x_l_light = 0.0f;
static float last_angle_y_l_light = 0.0f;
static float last_angle_z_l_light = 0.0f;
static float w_last_t_arry_light[3] = { 2.0f, 2.0f, 2.0f };
static float l_last_t_arry_light[3] = { 2.0f, 2.0f, 2.0f };
static bool control_light = false;
static float diriction_array[3] = { 0.0f, 0.1f, 0.0f };
static float Fog = 0.0f;
bool show_all = false;

glm::vec4 clear_color = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);


/**
 * Function declarations
 */
static void GlfwErrorCallback(int error, const char* description);
GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name);
ImGuiIO& SetupDearImgui(GLFWwindow* window);
void StartFrame();
void RenderFrame(GLFWwindow* window, std::shared_ptr<Scene>& scene, Renderer& renderer, ImGuiIO& io);
void Cleanup(GLFWwindow* window);
void DrawImguiMenus(ImGuiIO& io, std::shared_ptr<Scene>& scene);

/**
 * Function implementation
 */
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
	// TODO: Handle mouse scroll here
}

int main(int argc, char **argv)
{
	int windowWidth = 1920, windowHeight = 1080;

	GLFWwindow* window = SetupGlfwWindow(windowWidth, windowHeight, "Mesh Viewer");
	if (!window)
		return 1;

    int frameBufferWidth, frameBufferHeight;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

	Renderer renderer = Renderer(frameBufferWidth, frameBufferHeight);
	renderer.LoadShaders();//////////////////////////////////////////////////////////////////////
	renderer.LoadTextures();
	//Scene scene = Scene();
	std::shared_ptr<Scene>& scene = std::make_shared<Scene>();
	
	

	ImGuiIO& io = SetupDearImgui(window);
	glfwSetScrollCallback(window, ScrollCallback);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
		StartFrame();
		DrawImguiMenus(io, scene);
		glEnable(GL_DEPTH_TEST);
		glClearColor(1.f,1.f,1.f,1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RenderFrame(window,  scene, renderer, io);
    }

	Cleanup(window);
    return 0;
}

static void GlfwErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name)
{
	glfwSetErrorCallback(GlfwErrorCallback);
	if (!glfwInit())
		return NULL;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	#if __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
	
	GLFWwindow* window = glfwCreateWindow(w, h, window_name, NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
						 // very importent!! initialization of glad
						 // https://stackoverflow.com/questions/48582444/imgui-with-the-glad-opengl-loader-throws-segmentation-fault-core-dumped

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	return window;
}

ImGuiIO& SetupDearImgui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	return io;
}

void StartFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void RenderFrame(GLFWwindow* window, std::shared_ptr<Scene>& scene, Renderer& renderer, ImGuiIO& io)
{
	ImGui::Render();
	int frameBufferWidth, frameBufferHeight;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	

	if (frameBufferWidth != renderer.GetViewportWidth() || frameBufferHeight != renderer.GetViewportHeight())
	{
		glfwSetWindowAspectRatio(window, renderer.GetViewportWidth(), renderer.GetViewportHeight());
		// TODO: Set new aspect ratio
	}

	if (!io.WantCaptureKeyboard)
	{
		// TODO: Handle keyboard events here
		if (io.KeysDown[65])
		{
			// A key is down
			// Use the ASCII table for more key codes (https://www.asciitable.com/)
		}
	}

	if (!io.WantCaptureMouse)
	{
		// TODO: Handle mouse events here
		if (io.MouseDown[0])
		{
			// Left mouse button is down
		}
	}

	//renderer.ClearColorBuffer(clear_color);
	renderer.Render(scene);
	//renderer.SwapBuffers();
	//renderer.ClearZBuffer();

	//renderer.Set_ZBuffertoMax();/&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwMakeContextCurrent(window);
	glfwSwapBuffers(window);
}

void Cleanup(GLFWwindow* window)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void DrawImguiMenus(ImGuiIO& io, std::shared_ptr<Scene>& scene)
{
	/**
	 * MeshViewer menu
	 */
	ImGui::Begin("MeshViewer Menu");

	// Menu Bar
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open", "CTRL+O"))
			{
				nfdchar_t* outPath = NULL;
				nfdresult_t result = NFD_OpenDialog("obj;", NULL, &outPath);
				if (result == NFD_OKAY)
				{
					scene->AddModel(Utils::LoadMeshModel(outPath));
					scene->AddCamera(std::make_shared<Camera>());
					//scene.AddLight(std::make_shared<Light>());///@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@///

					free(outPath);
				}
				else if (result == NFD_CANCEL)
				{
				}
				else
				{
				}

			}
			ImGui::EndMenu();
		}

		// TODO: Add more menubar items (if you want to)
		ImGui::EndMainMenuBar();
	}

	// Controls
	ImGui::ColorEdit3("Clear Color", (float*)&clear_color);
	// TODO: Add more controls as needed

	ImGui::End();

	/**
	 * Imgui demo - you can remove it once you are familiar with imgui
	 */

	 // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;


		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		if (scene->GetModelCount()) {
			ImGui::Checkbox("Transformations Window", &show_transformations_window);
			ImGui::Checkbox("Light Window", &show_light_window);
		}
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

	if (show_transformations_window) {
		ImGui::Begin("Transformations Window", &show_transformations_window);
		/********************************/

		if (scene->GetModelCount()) {
			if (ImGui::Button("show bounding box"))
				bb++;
			if (bb % 2 == 0) {
				scene->GetActiveModel()->set_show_box_flag(0);
			}
			else scene->GetActiveModel()->set_show_box_flag(1);

			if (ImGui::Button("show face Normals"))
				faceNF++;
			if (faceNF % 2 == 0) {
				scene->GetActiveModel()->set_facenorm_flag(0);
			}
			else scene->GetActiveModel()->set_facenorm_flag(1);

			if (ImGui::Button("show verticses Normals"))
				versNF++;
			if (versNF % 2 == 0) {
				scene->GetActiveModel()->set_vernorm_flag(0);
			}
			else scene->GetActiveModel()->set_vernorm_flag(1);


			if (ImGui::Button("Reset"))
				reset = 1;
			if (ImGui::Button("change frame")) {
				c++;
				scaling = 0;
				translation = 0;
				rotation = 0;
				A_X = 0;
				A_Y = 0;
				A_Z = 0;
			}
			if (c % 2 == 0) {
				world_frame_trans = 1;
				local_frame_trans = 0;
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1, 0, 1, 1), "world frame");
			}
			else {
				local_frame_trans = 1;
				world_frame_trans = 0;
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1, 0, 1, 1), "local frame");
			}

			if (reset == 1) {
				reset = 0;
				scene->GetActiveModel()->set_Transform_Mat(1);
				local_frame_trans = 0;
				world_frame_trans = 0;
				scaling = 0;
				translation = 0;
				rotation = 0;
				A_X = 0;
				A_Y = 0;
				A_Z = 0;
				w_s_arry[0] = 1;
				w_s_arry[1] = 1;
				w_s_arry[2] = 1;
				w_t_arry[0] = 0;
				w_t_arry[1] = 0;
				w_t_arry[2] = 0;

				l_s_arry[0] = 1;
				l_s_arry[1] = 1;
				l_s_arry[2] = 1;
				l_t_arry[0] = 0;
				l_t_arry[1] = 0;
				l_t_arry[2] = 0;
				angle_x_w = 0.0f;
				angle_z_w = 0.0f;
				angle_x_l = 0.0f;
				angle_y_l = 0.0f;
				angle_z_l = 0.0f;
				c = 0;
				bb = 0;
				versNF = 0;
				faceNF = 0;

			}
			if (local_frame_trans || world_frame_trans) {
				ImGui::TextColored(ImVec4(0, 1, 1, 1), "choose a transformation:");
				ImGui::Checkbox("Scaling", &scaling);
				ImGui::Checkbox("Rotation", &rotation);
				ImGui::Checkbox("Translation", &translation);


				if (scaling) {
					if (world_frame_trans) {
						ImGui::InputFloat("X", &w_s_arry[0]);
						ImGui::InputFloat("Y", &w_s_arry[1]);
						ImGui::InputFloat("Z", &w_s_arry[2]);
					}
					else {
						ImGui::InputFloat("X", &l_s_arry[0]);
						ImGui::InputFloat("Y", &l_s_arry[1]);
						ImGui::InputFloat("Z", &l_s_arry[2]);
					}
					if (world_frame_trans) {
						if (w_s_arry[0] != w_last_s_arry[0])
							w_last_s_arry[0] = w_s_arry[0];
						if (w_s_arry[1] != w_last_s_arry[1])
							w_last_s_arry[1] = w_s_arry[1];
						if (w_s_arry[2] != w_last_s_arry[2])
							w_last_s_arry[2] = w_s_arry[2];
						scene->GetActiveModel()->set_scaling_w(w_s_arry[0], w_s_arry[1], w_s_arry[2]);

					}

					else {
						if (l_s_arry[0] != l_last_s_arry[0])
							l_last_s_arry[0] = l_s_arry[0];
						if (l_s_arry[1] != l_last_s_arry[1])
							l_last_s_arry[1] = l_s_arry[1];
						if (l_s_arry[2] != l_last_s_arry[2])
							l_last_s_arry[2] = l_s_arry[2];
						scene->GetActiveModel()->set_scaling_L(l_s_arry[0], l_s_arry[1], l_s_arry[2]);
					}
				}


				if (translation) {
					if (world_frame_trans) {
						ImGui::InputFloat("X", &w_t_arry[0]);
						ImGui::InputFloat("Y", &w_t_arry[1]);
						ImGui::InputFloat("Z", &w_t_arry[2]);
					}
					else {
						ImGui::InputFloat("X", &l_t_arry[0]);
						ImGui::InputFloat("Y", &l_t_arry[1]);
						ImGui::InputFloat("Z", &l_t_arry[2]);
					}
					if (world_frame_trans) {
						if (w_t_arry[0] != w_last_t_arry[0])
							w_last_t_arry[0] = w_t_arry[0];
						if (w_t_arry[1] != w_last_t_arry[1])
							w_last_t_arry[1] = w_t_arry[1];
						if (w_t_arry[2] != w_last_t_arry[2])
							w_last_t_arry[2] = w_t_arry[2];
						scene->GetActiveModel()->set_translation_w(w_t_arry[0], w_t_arry[1], w_t_arry[2]);



					}
					else {
						if (l_t_arry[0] != l_last_t_arry[0])
							l_last_t_arry[0] = l_t_arry[0];
						if (l_t_arry[1] != l_last_t_arry[1])
							l_last_t_arry[1] = l_t_arry[1];
						if (l_t_arry[2] != l_last_t_arry[2])
							l_last_t_arry[2] = l_t_arry[2];
						scene->GetActiveModel()->set_translation_L(l_t_arry[0], l_t_arry[1], l_t_arry[2]);



					}
				}

				if (rotation) {
					ImGui::TextColored(ImVec4(1, 1, 0, 1), "choose a axis of rotation:");
					ImGui::Checkbox("axis X", &A_X);
					ImGui::Checkbox("axis Y", &A_Y);
					ImGui::Checkbox("axis Z", &A_Z);

					if (A_X == 1) {
						if (world_frame_trans) {
							ImGui::SliderFloat("angle_x", &angle_x_w, -360.0f, 360.0f);
							if (angle_x_w != last_angle_x_w) {
								last_angle_x_w = angle_x_w;
								scene->GetActiveModel()->set_rotation_w(glm::radians(angle_x_w), 1, 0, 0);
							}
						}
						else {
							ImGui::SliderFloat("angle_x", &angle_x_l, -360.0f, 360.0f);
							if (angle_x_l != last_angle_x_l) {
								last_angle_x_l = angle_x_l;
								scene->GetActiveModel()->set_rotation_L(glm::radians(angle_x_l), 1, 0, 0);
							}
						}
					}
					if (A_Y == 1) {
						if (world_frame_trans) {
							ImGui::SliderFloat("angle_y", &angle_y_w, -360.0f, 360.0f);
							if (angle_y_w != last_angle_y_w) {
								last_angle_y_w = angle_y_w;
								scene->GetActiveModel()->set_rotation_w(glm::radians(angle_y_w), 0, 1, 0);
							}
						}
						else {
							ImGui::SliderFloat("angle_y", &angle_y_l, -360.0f, 360.0f);
							if (angle_y_l != last_angle_y_l) {
								last_angle_y_l = angle_y_l;
								scene->GetActiveModel()->set_rotation_L(glm::radians(angle_y_l), 0, 1, 0);
							}
						}
					}
					if (A_Z == 1) {
						if (world_frame_trans) {
							ImGui::SliderFloat("angle_z", &angle_z_w, -360.0f, 360.0f);
							if (angle_z_w != last_angle_z_w) {
								last_angle_z_w = angle_z_w;
								scene->GetActiveModel()->set_rotation_w(glm::radians(angle_z_w), 0, 0, 1);
							}
						}
						else {
							ImGui::SliderFloat("angle_z", &angle_z_l, -360.0f, 360.0f);
							if (angle_z_l != last_angle_z_l) {
								last_angle_z_l = angle_z_l;
								scene->GetActiveModel()->set_rotation_L(glm::radians(angle_z_l), 0, 0, 1);
							}
						}
					}
				}

			}
		}

		/********************************/
		if (ImGui::Button("Close Me"))
			show_transformations_window = false;
		ImGui::End();
	}


	//Camera Transformation Window
	if (scene->GetModelCount()) {

		ImGui::Begin("Camera Transformation Window");

		/********************************/
		if (ImGui::Button("change projection"))
			pro++;

		if (pro % 2 == 0) {
			orthographic_projection = 1;
			perspective_projection = 0;
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 0, 1, 1), "Orthographic Projection");
			//ImGui::SliderFloat("Orthographic Projection width", &orth_width, 0,1);
			//scene.GetActiveCamera().set_orth_flag(orthographic_projection);
			// scene.GetActiveCamera().set_orth(orth_width);
			if (scene->GetActiveModel()->GetModelName() == "banana.obj") {//1
				ImGui::SliderFloat("Orthographic Projection width", &orth_width, 0.1, 1);
			}

			if (scene->GetActiveModel()->GetModelName() == "beethoven.obj") {//2//////////////////////////////////////
				ImGui::SliderFloat("Orthographic Projection width", &orth_width_beet, 0.1f, 100.0f);
				orth_width = orth_width_beet;
			}

			if (scene->GetActiveModel()->GetModelName() == "bishop.obj") {//3
				ImGui::SliderFloat("Orthographic Projection width", &orth_width, 0.1, 1);
			}

			if (scene->GetActiveModel()->GetModelName() == "blob.obj") {//4////////////////////////////////////////////
				ImGui::SliderFloat("Orthographic Projection width", &orth_width_beet, 0.1, 200);
				orth_width = orth_width_beet;
			}

			if (scene->GetActiveModel()->GetModelName() == "bunny.obj") {//5
				ImGui::SliderFloat("Orthographic Projection width", &orth_width_beet, 0.1, 20);
				orth_width = orth_width_beet;
			}

			if (scene->GetActiveModel()->GetModelName() == "camera.obj") {//6
				ImGui::SliderFloat("Orthographic Projection width", &orth_width_beet, 0.1, 50);
				orth_width = orth_width_beet;
			}

			if (scene->GetActiveModel()->GetModelName() == "chain.obj") {//7
				ImGui::SliderFloat("Orthographic Projection width", &orth_width_beet, 0.1, 40);
				orth_width = orth_width_beet;
			}

			if (scene->GetActiveModel()->GetModelName() == "cow.obj") {//8
				ImGui::SliderFloat("Orthographic projection width", &orth_width_beet, 0.1, 50);
				orth_width = orth_width_beet;
			}

			if (scene->GetActiveModel()->GetModelName() == "demo.obj") {//9
				ImGui::SliderFloat("Orthographic projection width", &orth_width_beet, 0.1, 50);
				orth_width = orth_width_beet;
			}

			if (scene->GetActiveModel()->GetModelName() == "dolphin.obj") {//10
				ImGui::SliderFloat("Orthographic projection width", &orth_width_dol, 0.1, 2500);
				orth_width = orth_width_dol;
			}

			if (scene->GetActiveModel()->GetModelName() == "feline.obj") {//11///////////////////////////////////
				ImGui::SliderFloat("Orthographic projection width", &orth_width_beet, 0.1, 2500);
				orth_width = orth_width_beet;
			}

			if (scene->GetActiveModel()->GetModelName() == "pawn.obj") {//12
				ImGui::SliderFloat("Orthographic projection width", &orth_width, 0.1, 1);
			}

			if (scene->GetActiveModel()->GetModelName() == "teapot.obj") {//13
				ImGui::SliderFloat("Orthographic projection width", &orth_width_beet, 0.1, 50);
				orth_width = orth_width_beet;
			}
			scene->GetActiveCamera().set_orth_flag(orthographic_projection);
			scene->GetActiveCamera().set_orth(orth_width);
		}
		else {
			orthographic_projection = 0;
			perspective_projection = 1;
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 0, 1, 1), "Perspective Projection");
			if (scene->GetActiveModel()->GetModelName() == "bunny.obj") {//5
				ImGui::SliderFloat("perspective projection fovy", &bunny_fov, 0.1, 360);
				fov = bunny_fov;
			}

			else if (scene->GetActiveModel()->GetModelName() == "dolphin.obj") {//10
				ImGui::SliderFloat("perspective projection fovy", &dol_fov, 0.1, 360);
				fov = dol_fov;
			}
			else
				ImGui::SliderFloat("perspective projection fovy", &fov, 0.1, 360);

			scene->GetActiveCamera().set_orth_flag(orthographic_projection);
			scene->GetActiveCamera().set_perspective(glm::radians(fov));
		}

		if (ImGui::Button("change color")) {
			draw_flag++;
		}
		if (draw_flag % 2 == 0) {
			scene->GetActiveCamera().set_draw_color(0);
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 0, 1, 1), "gray scale");
		}
		else {
			scene->GetActiveCamera().set_draw_color(1);
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 0, 1, 1), "random colors");
		}


		if (ImGui::Button("change frame")) {
			cc++;
			cam_translation = 0;
			cam_rotation = 0;
			cam_A_X = 0;
			cam_A_Y = 0;
			cam_A_Z = 0;

		}
		if (cc % 2 == 0) {
			world_cam_frame_trans = 1;
			local_cam_frame_trans = 0;
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 0, 1, 1), "world frame");
		}
		else {
			local_frame_trans = 1;
			world_frame_trans = 0;
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1, 0, 1, 1), "local frame");
		}

		if (ImGui::Button("Reset"))
			reset_c = 1;
		if (reset_c == 1) {
			reset_c = 0;
			scene->GetActiveCamera().set_invTransform_Mat(1);
			local_cam_frame_trans = 0;
			world_cam_frame_trans = 0;
			cam_translation = 0;
			cam_rotation = 0;
			cam_A_X = 0;
			cam_A_Y = 0;
			cam_A_Z = 0;
			w_cam_t_arry[0] = 0.0f;
			w_cam_t_arry[1] = 0.0f;
			w_cam_t_arry[2] = 0.0f;
			l_cam_t_arry[0] = 0.0f;
			l_cam_t_arry[1] = 0.0f;
			l_cam_t_arry[2] = 0.0f;

			cam_angle_x_w = 0.0f;
			cam_angle_z_w = 0.0f;
			cam_angle_y_w = 0.0f;
			cam_angle_x_l = 0.0f;
			cam_angle_y_l = 0.0f;
			cam_angle_z_l = 0.0f;
			cc = 0;
			eye_arry[0] = 0;
			eye_arry[1] = 0;
			eye_arry[2] = 2;
			at_arry[0] = 0;
			at_arry[1] = 0;
			at_arry[2] = 0;
			up_arry[0] = 0;
			up_arry[1] = 1;
			up_arry[2] = 0;

		}
		if (local_cam_frame_trans || world_cam_frame_trans) {
			ImGui::TextColored(ImVec4(0, 1, 1, 1), "choose a transformation:");
			ImGui::Checkbox("Rotation", &cam_rotation);
			ImGui::Checkbox("Translation", &cam_translation);


			if (cam_translation) {
				if (world_cam_frame_trans) {
					ImGui::InputFloat("X", &w_cam_t_arry[0]);
					ImGui::InputFloat("Y", &w_cam_t_arry[1]);
					ImGui::InputFloat("Z", &w_cam_t_arry[2]);

					if (w_cam_t_arry[0] != w_last_cam_t_arry[0])
						w_last_cam_t_arry[0] = w_cam_t_arry[0];
					if (w_cam_t_arry[1] != w_last_cam_t_arry[1])
						w_last_cam_t_arry[1] = w_cam_t_arry[1];
					if (w_cam_t_arry[2] != w_last_cam_t_arry[2])
						w_last_cam_t_arry[2] = w_cam_t_arry[2];
					scene->GetActiveCamera().set_translation_w(w_cam_t_arry[0], w_cam_t_arry[1], w_cam_t_arry[2]);
				}
				else if (local_cam_frame_trans) {

					ImGui::InputFloat("X", &l_cam_t_arry[0]);
					ImGui::InputFloat("Y", &l_cam_t_arry[1]);
					ImGui::InputFloat("Z", &l_cam_t_arry[2]);

					if (l_cam_t_arry[0] != l_last_cam_t_arry[0])
						l_last_cam_t_arry[0] = l_cam_t_arry[0];
					if (l_cam_t_arry[1] != l_last_cam_t_arry[1])
						l_last_cam_t_arry[1] = l_cam_t_arry[1];
					if (l_cam_t_arry[2] != l_last_cam_t_arry[2])
						l_last_cam_t_arry[2] = l_cam_t_arry[2];
					scene->GetActiveCamera().set_translation_L(l_cam_t_arry[0], l_cam_t_arry[1], l_cam_t_arry[2]);
				}
			}

			if (cam_rotation) {
				ImGui::TextColored(ImVec4(1, 1, 0, 1), "choose a axis of rotation:");
				ImGui::Checkbox("axis X", &cam_A_X);
				ImGui::Checkbox("axis Y", &cam_A_Y);
				ImGui::Checkbox("axis Z", &cam_A_Z);

				if (cam_A_X) {
					if (world_cam_frame_trans) {
						ImGui::SliderFloat("angle_x", &cam_angle_x_w, -360.0f, 360.0f);
						if (cam_angle_x_w != last_cam_angle_x_w) {
							last_cam_angle_x_w = cam_angle_x_w;
							scene->GetActiveCamera().set_rotation_w(glm::radians(cam_angle_x_w), 1, 0, 0);
						}
					}
					else {
						ImGui::SliderFloat("angle_x", &cam_angle_x_l, -360.0f, 360.0f);
						if (cam_angle_x_l != last_cam_angle_x_l) {
							last_cam_angle_x_l = cam_angle_x_l;
							scene->GetActiveCamera().set_rotation_L(glm::radians(cam_angle_x_l), 1, 0, 0);
						}
					}
				}
				if (cam_A_Y) {
					if (world_cam_frame_trans) {
						ImGui::SliderFloat("angle_y", &cam_angle_y_w, -360.0f, 360.0f);
						if (cam_angle_y_w != last_cam_angle_y_w) {
							last_cam_angle_y_w = cam_angle_y_w;
							scene->GetActiveCamera().set_rotation_w(glm::radians(cam_angle_y_w), 0, 1, 0);
						}
					}
					else {
						ImGui::SliderFloat("angle_y", &cam_angle_y_l, -360.0f, 360.0f);
						if (cam_angle_y_l != last_cam_angle_y_l) {
							last_cam_angle_y_l = cam_angle_y_l;
							scene->GetActiveCamera().set_rotation_L(glm::radians(cam_angle_y_l), 0, 1, 0);
						}
					}
				}
				if (cam_A_Z) {
					if (world_cam_frame_trans) {
						ImGui::SliderFloat("angle_z", &cam_angle_z_w, -360.0f, 360.0f);
						if (cam_angle_z_w != last_cam_angle_z_w) {
							last_cam_angle_z_w = cam_angle_z_w;
							scene->GetActiveCamera().set_rotation_w(glm::radians(cam_angle_z_w), 0, 0, 1);
						}
					}
					else {
						ImGui::SliderFloat("angle_z", &cam_angle_z_l, -360.0f, 360.0f);
						if (cam_angle_z_l != last_cam_angle_z_l) {
							last_cam_angle_z_l = cam_angle_z_l;
							scene->GetActiveCamera().set_rotation_L(glm::radians(cam_angle_z_l), 0, 0, 1);
						}
					}
				}



			}
		}
		ImGui::TextColored(ImVec4(0, 1, 1, 1), "Look At:");

		ImGui::TextColored(ImVec4(0, 1, 0, 1), "eye:");
		ImGui::InputFloat("X_eye", &eye_arry[0]);
		ImGui::InputFloat("Y_eye", &eye_arry[1]);
		ImGui::InputFloat("Z_eye", &eye_arry[2]);


		ImGui::TextColored(ImVec4(0, 1, 0, 1), "at:");
		ImGui::InputFloat("X_at", &at_arry[0]);
		ImGui::InputFloat("Y_at", &at_arry[1]);
		ImGui::InputFloat("Z_at", &at_arry[2]);


		ImGui::TextColored(ImVec4(0, 1, 0, 1), "up:");
		ImGui::InputFloat("X_up", &up_arry[0]);
		ImGui::InputFloat("Y_up", &up_arry[1]);
		ImGui::InputFloat("Z_up", &up_arry[2]);

		scene->GetActiveCamera().SetCameraLookAt(glm::vec3(eye_arry[0], eye_arry[1], eye_arry[2]), glm::vec3(at_arry[0], at_arry[1], at_arry[2]),
			glm::vec3(up_arry[0], up_arry[1], up_arry[2]));

		/********************************/
		ImGui::End();

	}

	//Light window:
static int add_light_B = 0;
static int F_B = 0;
static int Lightmode = 0;
static int shadingType = 0;
bool  show_adding_window = false;
static std::vector <bool> lights;
static int last_activ_light_index = 0;
static float alpha = 5;

if (show_light_window) {
	ImGui::Begin("Light Window", &show_light_window);


	if (ImGui::Button("Fog Button")) { F_B++; }
	if (F_B % 2 == 1) { 
		ImGui::SliderFloat("Fog Density", &Fog, 0.0f, 360.0f);
		scene->set_Fog(Fog);
		scene->set_Fog_flag(1);
	}
	else { scene->set_Fog_flag(0); }
	


	/*ImGui::Checkbox("Control Shading Type", &control_shading_type);
	if (control_shading_type) {
		if (ImGui::RadioButton("Flat", &shadingType, 0)) {
			scene->set_shading(1);
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Gouraud", &shadingType, 1)) {
			scene->set_shading(2);
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Phong", &shadingType, 2)) {
			scene->set_shading(0);
		}

	}*/

	ImGui::Checkbox("Control Shading Type", &control_shading_type);
	if (control_shading_type) {
		if (ImGui::RadioButton("Phong", &shadingType, 0)) {
			scene->set_shading(1);
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Texture_planar", &shadingType, 1)) {
			scene->set_shading(2);
		}
		/*ImGui::SameLine();
		if (ImGui::RadioButton("Phong", &shadingType, 2)) {
			scene->set_shading(0);
		}*/

	}


	if (ImGui::Button("Add a new light")) { add_light_B++; }
	if (add_light_B % 2 == 1) { show_adding_window = true; }
	ImGui::TextColored(ImVec4(1, 0, 1, 1), "control a specific light");

	if (ImGui::ListBoxHeader("##", lights_counter, 3))
	{
		for (int n = 0; n < lights_counter; n++)
		{
			char label[32];  sprintf(label, "light %d", n);

			if (ImGui::Selectable(label, lights[n]))
			{
				lights[n] = 1;
				scene->SetActiveLightIndex(n);
				control_light = true;
			}
		}
		for (int n = 0; n < lights_counter; n++)
		{
			if (!(scene->GetActiveLightIndex() == n)) {
				lights[n] = 0;
			}
		}
		ImGui::ListBoxFooter();
	}
	if (control_light) {

		active_ambient_color[0] = scene->GetActiveLight().get_ambient_color().x;
		active_ambient_color[1] = scene->GetActiveLight().get_ambient_color().y;
		active_ambient_color[2] = scene->GetActiveLight().get_ambient_color().z;

		active_diffuse_color[0] = scene->GetActiveLight().get_diffuse_color().x;
		active_diffuse_color[1] = scene->GetActiveLight().get_diffuse_color().y;
		active_diffuse_color[2] = scene->GetActiveLight().get_diffuse_color().z;

		active_specular_color[0] = scene->GetActiveLight().get_specular_color().x;
		active_specular_color[1] = scene->GetActiveLight().get_specular_color().y;
		active_specular_color[2] = scene->GetActiveLight().get_specular_color().z;


		if (scene->GetActiveLightIndex() != last_activ_light_index) {
			if (!(scene->GetActiveLight().get_changes_flag())) {
				scene->GetActiveLight().set_Transform_Mat(1);
			}
			last_activ_light_index = scene->GetActiveLightIndex();
			local_frame_trans_light = 0;
			world_frame_trans_light = 0;
			translation_light = 0;
			rotation_light = 0;
			A_X_light = 0;
			A_Y_light = 0;
			A_Z_light = 0;
			w_t_arry_light[0] = 0;
			w_t_arry_light[1] = 0;
			w_t_arry_light[2] = 0;
			l_t_arry_light[0] = 0;
			l_t_arry_light[1] = 0;
			l_t_arry_light[2] = 0;
			angle_x_w_light = 0.0f;
			angle_z_w_light = 0.0f;
			angle_x_l_light = 0.0f;
			angle_y_l_light = 0.0f;
			angle_y_w_light = 0.0f;
			angle_z_l_light = 0.0f;
			

		}
		
		ImGui::Checkbox("change active light colors:", &control_active_light_color);
		if (control_active_light_color) {

			ImGui::ColorEdit3("active ambient color", active_ambient_color);
			ImGui::ColorEdit3("active diffuse color", active_diffuse_color);
			ImGui::ColorEdit3("active specular color", active_specular_color);

			scene->GetActiveLight().set_ambient_color(active_ambient_color[0], active_ambient_color[1], active_ambient_color[2]);
			scene->GetActiveLight().set_diffuse_color(active_diffuse_color[0], active_diffuse_color[1], active_diffuse_color[2]);
			scene->GetActiveLight().set_specular_color(active_specular_color[0], active_specular_color[1], active_specular_color[2]);

		}

		if (scene->GetActiveLight().get_mode() != 0) {//only for parallel
			ImGui::Checkbox("light direction:", &control_light_direction);
			if (control_light_direction) {
				ImGui::InputFloat("X_direction", &diriction_array[0]);
				ImGui::InputFloat("Y_direction", &diriction_array[1]);
				ImGui::InputFloat("Z_direction", &diriction_array[2]);
				scene->GetActiveLight().set_direction(glm::vec3(diriction_array[0], diriction_array[1], diriction_array[2]));
			}
		}
		if (scene->get_shading() == 0) {
			ImGui::TextColored(ImVec4(1, 1, 1, 1), "control alpha:");
			ImGui::InputFloat("Alpha", &alpha);
			scene->GetActiveLight().set_alpha(alpha);
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////

		if (scene->GetActiveLight().get_mode() == 0) { // if the light is parallel, then no transformations for it
			ImGui::TextColored(ImVec4(1, 1, 1, 1), "transformations:");
			if (ImGui::Button("change frame")) {
				c_light++;
				translation_light = 0;
				rotation_light = 0;
				A_X_light = 0;
				A_Y_light = 0;
				A_Z_light = 0;
			}
			if (c_light % 2 == 0) {
				world_frame_trans_light = 1;
				local_frame_trans_light = 0;
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1, 0, 1, 1), "world frame");
			}
			else {
				local_frame_trans_light = 1;
				world_frame_trans_light = 0;
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1, 0, 1, 1), "local frame");
			}

			if (local_frame_trans_light || world_frame_trans_light) {
				ImGui::TextColored(ImVec4(0, 1, 1, 1), "choose a transformation:");
				ImGui::Checkbox("Rotation", &rotation_light);
				ImGui::Checkbox("Translation", &translation_light);


				if (translation_light) {
					if (world_frame_trans_light) {
						ImGui::InputFloat("X", &w_t_arry_light[0]);
						ImGui::InputFloat("Y", &w_t_arry_light[1]);
						ImGui::InputFloat("Z", &w_t_arry_light[2]);
					}
					else {
						ImGui::InputFloat("X", &l_t_arry_light[0]);
						ImGui::InputFloat("Y", &l_t_arry_light[1]);
						ImGui::InputFloat("Z", &l_t_arry_light[2]);
					}
					if (world_frame_trans_light) {
						if (w_t_arry_light[0] != w_last_t_arry_light[0])
							w_last_t_arry_light[0] = w_t_arry_light[0];
						if (w_t_arry_light[1] != w_last_t_arry_light[1])
							w_last_t_arry_light[1] = w_t_arry_light[1];
						if (w_t_arry_light[2] != w_last_t_arry_light[2])
							w_last_t_arry_light[2] = w_t_arry_light[2];
						scene->GetActiveLight().set_translation_w(w_t_arry_light[0], w_t_arry_light[1], w_t_arry_light[2]);



					}
					else {
						if (l_t_arry_light[0] != l_last_t_arry_light[0])
							l_last_t_arry_light[0] = l_t_arry_light[0];
						if (l_t_arry_light[1] != l_last_t_arry_light[1])
							l_last_t_arry_light[1] = l_t_arry_light[1];
						if (l_t_arry_light[2] != l_last_t_arry_light[2])
							l_last_t_arry_light[2] = l_t_arry_light[2];
						scene->GetActiveLight().set_translation_L(l_t_arry_light[0], l_t_arry_light[1], l_t_arry_light[2]);



					}
				}

				if (rotation_light) {
					ImGui::TextColored(ImVec4(1, 1, 0, 1), "choose a axis of rotation:");
					ImGui::Checkbox("axis X", &A_X_light);
					ImGui::Checkbox("axis Y", &A_Y_light);
					ImGui::Checkbox("axis Z", &A_Z_light);

					if (A_X_light == 1) {
						if (world_frame_trans_light) {
							ImGui::SliderFloat("angle_x", &angle_x_w_light, -360.0f, 360.0f);
							if (angle_x_w_light != last_angle_x_w_light) {
								last_angle_x_w_light = angle_x_w_light;
								scene->GetActiveLight().set_rotation_w(glm::radians(angle_x_w_light), 1, 0, 0);
							}
						}
						else {
							ImGui::SliderFloat("angle_x", &angle_x_l_light, -360.0f, 360.0f);
							if (angle_x_l_light != last_angle_x_l_light) {
								last_angle_x_l_light = angle_x_l_light;
								scene->GetActiveLight().set_rotation_L(glm::radians(angle_x_l_light), 1, 0, 0);
							}
						}
					}
					if (A_Y_light == 1) {
						if (world_frame_trans_light) {
							ImGui::SliderFloat("angle_y", &angle_y_w_light, -360.0f, 360.0f);
							if (angle_y_w_light != last_angle_y_w_light) {
								last_angle_y_w_light = angle_y_w_light;
								scene->GetActiveLight().set_rotation_w(glm::radians(angle_y_w_light), 0, 1, 0);
							}
						}
						else {
							ImGui::SliderFloat("angle_y", &angle_y_l_light, -360.0f, 360.0f);
							if (angle_y_l_light != last_angle_y_l_light) {
								last_angle_y_l_light = angle_y_l_light;
								scene->GetActiveLight().set_rotation_L(glm::radians(angle_y_l_light), 0, 1, 0);
							}
						}
					}
					if (A_Z_light == 1) {
						if (world_frame_trans_light) {
							ImGui::SliderFloat("angle_z", &angle_z_w_light, -360.0f, 360.0f);
							if (angle_z_w_light != last_angle_z_w_light) {
								last_angle_z_w_light = angle_z_w_light;
								scene->GetActiveLight().set_rotation_w(glm::radians(angle_z_w_light), 0, 0, 1);
							}
						}
						else {
							ImGui::SliderFloat("angle_z", &angle_z_l_light, -360.0f, 360.0f);
							if (angle_z_l_light != last_angle_z_l_light) {
								last_angle_z_l_light = angle_z_l_light;
								scene->GetActiveLight().set_rotation_L(glm::radians(angle_z_l_light), 0, 0, 1);
							}
						}
					}
				}
			}
		}

		
	}

	//ImGui::Checkbox("Control Model material", &control_model_color);
	//if (control_model_color) {
		
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "choose model colors:");
		ImGui::ColorEdit3("Ambient Color", ambient_model_color);
		ImGui::ColorEdit3("Diffuse Color", diffuse_model_color);
		ImGui::ColorEdit3("Specular Color", specular_model_color);

		scene->GetActiveModel()->set_ambient_color(ambient_model_color[0], ambient_model_color[1], ambient_model_color[2]);
		scene->GetActiveModel()->set_diffuse_color(diffuse_model_color[0], diffuse_model_color[1], diffuse_model_color[2]);
		scene->GetActiveModel()->set_specular_color(specular_model_color[0], specular_model_color[1], specular_model_color[2]);
		//scene.GetActiveCamera().set_draw_color(-1);
	//}
		ImGui::Checkbox("Show_all_lights", &show_all);
		if (show_all) {
			scene->set_showAllLghts(1);
		}
		else { scene->set_showAllLghts(0); }


	ImGui::End();
}



if (show_adding_window) {
		ImGui::Begin("Add light window", &show_adding_window);
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "choose mode:");
		ImGui::RadioButton("Point", &Lightmode, 0);
		ImGui::SameLine();
		ImGui::RadioButton("Parallel", &Lightmode, 1);
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "choose light colors:");
		ImGui::ColorEdit3("Ambient Color", ambient_color);
		ImGui::ColorEdit3("Diffuse Color", diffuse_color);
		ImGui::ColorEdit3("Specular Color", specular_color);

		if (ImGui::Button("ADD"))
		{
			//scene.GetActiveCamera().set_draw_color(-1);
			scene->set_shade_flag(1);
			lights_counter++;
			std::shared_ptr<Light>& new_light = std::make_shared<Light>(scene->GetActiveModel()->get_Uvec4(), Lightmode, scene->GetActiveModel()->get_Uvec4());
			(*new_light).set_ambient_color(ambient_color[0], ambient_color[1], ambient_color[2]);
			(*new_light).set_diffuse_color(diffuse_color[0], diffuse_color[1], diffuse_color[2]);
			(*new_light).set_specular_color(specular_color[0], specular_color[1], specular_color[2]);
			if (Lightmode == 0) {
				(*new_light).set_mode(0);//point
				(*new_light).set_position(scene->GetActiveModel()->get_Uvec1());
			}
			else {
				(*new_light).set_mode(1);
				(*new_light).set_position(scene->GetActiveModel()->get_Uvec4());
				//(*new_light).set_direction(scene.GetActiveModel().get_Dvec1());
				//(*new_light).set_direction(glm::vec3(1,1,1));
			}
			(*new_light).set_m(lights_counter);
			scene->AddLight(new_light);
			lights.push_back(0);
		}

		ImGui::End();
	}

		
}


