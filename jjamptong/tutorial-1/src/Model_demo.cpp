#include <Model_demo.h>
#include <IG.h>
#include <graphics.hpp>
/*                                                   objects with file scope
----------------------------------------------------------------------------- */
//static GLNew    g_glnew;

//ImVec4 clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

void Models::init() {
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glViewport(0, 0, GLHelper::width, GLHelper::height);

	camera = new Camera();
	camera->Set_eye(20);

	std::vector<std::pair<GLenum, std::string>> shdr_files;
	shdr_files.push_back(std::make_pair(GL_VERTEX_SHADER, "../shaders/model_shader.vert"));
	shdr_files.push_back(std::make_pair(GL_FRAGMENT_SHADER, "../shaders/model_shader.frag"));

	// shd, color, position, scale, rot(?)
	meshes[0].init(shdr_files, Vec4(0.1f, 0.1f, 0.9f, 1.00f), { -4,1.5,-3 }, { 1,1,1 }, { 0,0,0 });

	meshes[1].init(shdr_files, Vec4(0.1f, 0.1f, 0.9f, 1.00f), { 0,1.5,-3 }, { 1,1,1 }, { 0,0,0 });

	meshes[2].init(shdr_files, Vec4(0.3f, 0.3f, 0.7f, 1.00f), { 4,1.5,-3 }, { 1,1,1 }, { 0,0,0 });

	meshes[3].init(shdr_files, Vec4(0.1f, 0.1f, 0.9f, 1.00f), { -4,-1.5,-3 }, { 1,1,1 }, { 0,0,0 });

	meshes[4].init(shdr_files, Vec4(0.7f, 0.7f, 1.0f, 1.0f), { 0,-1.5,-3 }, { 1,1,1 }, { 0,0,0 });

	meshes[5].init(shdr_files, Vec4(1.0f, 0.0f, 0.0f, 1.0f), { 4,-1.5,-3 }, { 1,1,1 }, { 0,0,0 });
}

void Models::update(double delta_time) {

	switch (static_cast<int>(GLHelper::currCameraMode))
	{
	case static_cast<int>(GLHelper::CameraMode::UP): camera->MoveUp(); GLHelper::currCameraMode = GLHelper::CameraMode::IDLE; break;
	case static_cast<int>(GLHelper::CameraMode::DOWN):camera->MoveDown(); GLHelper::currCameraMode = GLHelper::CameraMode::IDLE; break;
	case static_cast<int>(GLHelper::CameraMode::LEFT):camera->MoveLeft(); GLHelper::currCameraMode = GLHelper::CameraMode::IDLE; break;
	case static_cast<int>(GLHelper::CameraMode::RIGHT):camera->MoveRight(); GLHelper::currCameraMode = GLHelper::CameraMode::IDLE; break;
	case static_cast<int>(GLHelper::CameraMode::CLOSER):camera->MoveCloser(); GLHelper::currCameraMode = GLHelper::CameraMode::IDLE; break;
	case static_cast<int>(GLHelper::CameraMode::FARTHER):camera->MoveFarther(); GLHelper::currCameraMode = GLHelper::CameraMode::IDLE; break;
	}

	for (auto& mesh : meshes)
	{
		if (camera->eyeMoved || camera->resized)
		{
			mesh.compute_matrix(static_cast<float>(delta_time), camera->Get_eye(), camera->Get_frustum());
		}
	}

	camera->eyeMoved = false;
	camera->resized = false;

	//mesh 각각 imgui 해서 포지션이나 로테이트 셋해서 메트릭스 업데이트 시키기
}

void Models::draw() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	for (auto& mesh : meshes)
	{
		mesh.draw();
	}
}

void Models::cleanup() {
	delete camera;
}


