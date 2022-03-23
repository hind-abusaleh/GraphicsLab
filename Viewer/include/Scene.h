#pragma once

#include <vector>
#include <memory>

#include "Camera.h"
#include "MeshModel.h"
#include "Light.h"

class Scene {
public:
	Scene();

	void AddModel(const std::shared_ptr<MeshModel>& mesh_model);
	int GetModelCount() const;
	//MeshModel& GetModel(int index) const;
	//MeshModel& GetActiveModel() const;
	std::shared_ptr<MeshModel> GetModel(int index) const;
	std::shared_ptr<MeshModel> GetActiveModel() const;



	void AddCamera(const std::shared_ptr<Camera>& camera);
	int GetCameraCount() const;
	Camera& GetCamera(int index);
	Camera& GetActiveCamera()const;

	void SetActiveCameraIndex(int index);
	int GetActiveCameraIndex() const;

	void SetActiveModelIndex(int index);
	int GetActiveModelIndex() const;

	void AddLight(const std::shared_ptr<Light>& light);
	int GetLightCount() const;
	std::shared_ptr<Light> GetLight(int index) const;
	Light& GetActiveLight()const;

	int GetActiveLightIndex() const;
	void SetActiveLightIndex(int index);


	int get_shading()const;
	void set_shading(int flag);

	int get_shade_flag()const;
	void set_shade_flag(int flag);
	
	int get_Fog_flag()const;
	void set_Fog_flag(int p);

	float get_Fog()const;
	void set_Fog(int p);

	int get_showAllLights()const;
	void set_showAllLghts(int flag);
	

private:
	std::vector<std::shared_ptr<MeshModel>> mesh_models_;
	std::vector<std::shared_ptr<Camera>> cameras_;
    std::vector<std::shared_ptr<Light>> lights_;

	int active_camera_index_;
	int active_model_index_;
	int active_light_index_;


	int shade_flag = 0;
	int shading = 1 ; //0_phong, 1_flat, 2_gouraud
	int Fog_flag = 0;
	float Fog = 0;
	int show_all_lights=0;
	

};