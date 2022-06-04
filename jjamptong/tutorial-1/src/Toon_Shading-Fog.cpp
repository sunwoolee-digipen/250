#include <Toon_Shading-Fog.h>
#include <IG.h>
#include <graphics.hpp>
/*                                                   objects with file scope
----------------------------------------------------------------------------- */
//static GLNew    g_glnew;

void Toon_Fog::init() {
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glViewport(0, 0, GLHelper::width, GLHelper::height);

	camera = new Camera();
	camera->Set_eye(3);

	std::vector<std::pair<GLenum, std::string>> shdr_files;
	shdr_files.push_back(std::make_pair(GL_VERTEX_SHADER, "../shaders/toon.vert"));
	shdr_files.push_back(std::make_pair(GL_FRAGMENT_SHADER, "../shaders/toon.frag"));

	// shd, color, position, scale, rot(?)
	//meshes[PLANE].init(shdr_files, Vec4(0.1f, 0.1f, 0.9f, 1.00f), { -4,1.5,-3 }, { 1,1,1 }, { 0,0,0 });

	//meshes[CUBE].init(shdr_files, Vec4(0.1f, 0.1f, 0.9f, 1.00f), { 0,1.5,-3 }, { 1,1,1 }, { 0,0,0 });

	//meshes[SPHERE].init(shdr_files, Vec4(0.3f, 0.3f, 0.7f, 1.00f), { 4,1.5,-3 }, { 1,1,1 }, { 0,0,0 });

	//meshes[TORUS].init(shdr_files, Vec4(0.1f, 0.1f, 0.9f, 1.00f), { -4,-1.5,-3 }, { 1,1,1 }, { 0,0,0 });

	//meshes[CYLINDER].init(shdr_files, Vec4(0.7f, 0.7f, 1.0f, 1.0f), { 0,-1.5,-3 }, { 1,1,1 }, { 0,0,0 });

	//meshes[CONE].init(shdr_files, Vec4(1.0f, 0.0f, 0.0f, 1.0f), { 4,-1.5,-3 }, { 1,1,1 }, { 0,0,0 });

	sphere = CreateSphere(16,16);
	sphere.init(shdr_files, Vec4(0.1f, 0.1f, 0.9f, 1.00f), { 0,0,0 }, { 1.,1.,1. }, { 0,0,0 });


	GLubyte const* str_ven = glGetString(GL_VENDOR);
	std::cout << "GPU Vendor: " << str_ven << std::endl;

	GLubyte const* str_ren = glGetString(GL_RENDERER);
	//std::cout << "GL Renderer: " << str_ren << std::endl;

	GLubyte const* str_ver = glGetString(GL_VERSION);
	std::cout << "GL Version: " << str_ver << std::endl;

	GLubyte const* sha_ver = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cout << "GL Shader Version: " << sha_ver << std::endl;
}

void Toon_Fog::update(double delta_time) {

	switch (static_cast<int>(GLHelper::currCameraMode))
	{
	case GLHelper::UP: camera->MoveUp(); GLHelper::currCameraMode = GLHelper::IDLE; break;
	case GLHelper::DOWN:camera->MoveDown(); GLHelper::currCameraMode = GLHelper::IDLE; break;
	case GLHelper::LEFT:camera->MoveLeft(); GLHelper::currCameraMode = GLHelper::IDLE; break;
	case GLHelper::RIGHT:camera->MoveRight(); GLHelper::currCameraMode = GLHelper::IDLE; break;
	case GLHelper::CLOSER:camera->MoveCloser(); GLHelper::currCameraMode = GLHelper::IDLE; break;
	case GLHelper::FARTHER:camera->MoveFarther(); GLHelper::currCameraMode = GLHelper::IDLE; break;
	}

	//for (auto& mesh : meshes)
	//{
	//	if (camera->eyeMoved || camera->resized)
	//	{
	//		mesh.compute_matrix(static_cast<float>(delta_time), camera->Get_eye(), camera->Get_frustum());
	//	}
	//}

	sphere.compute_matrix(static_cast<float>(delta_time), camera->Get_eye(), camera->Get_frustum());

	camera->eyeMoved = false;
	camera->resized = false;
}

void Toon_Fog::draw() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//for (auto& mesh : meshes)
	//{
	//	mesh.draw();
	//}
	sphere.draw();
}

void Toon_Fog::cleanup() {
	delete camera;
}

