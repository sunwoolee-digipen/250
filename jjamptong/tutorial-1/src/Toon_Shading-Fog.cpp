#include <Toon_Shading-Fog.h>
#include <IG.h>
#include <graphics.hpp>
/*                                                   objects with file scope
----------------------------------------------------------------------------- */
//static GLNew    g_glnew;

void Toon_Fog::init() {
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glViewport(0, 0, GLHelper::width, GLHelper::height);

	camera = new Camera();
	camera->Set_eye(3);

	std::vector<std::pair<GLenum, std::string>> shdr_files;
	shdr_files.push_back(std::make_pair(GL_VERTEX_SHADER, "../shaders/toon.vert"));
	shdr_files.push_back(std::make_pair(GL_FRAGMENT_SHADER, "../shaders/toon.frag"));

	// shd, color, position, scale, rot(?)
	Sphere = CreateSphere(16, 16);
	Sphere.init(shdr_files, Vec4(0.1f, 0.1f, 0.9f, 1.00f), { 0,0,0}, { 1,1,1 }, { 0,0,0 });
	Plane = CreatePlane(10, 10);
	Plane.init(shdr_files, Vec4(0.1f, 0.1f, 0.9f, 1.00f), {-0,0,7}, {30,30,1}, {0,0,0});


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

	Sphere.GetShdr_pgm().Use();
	glUniform3fv(Sphere.lightPosLoc, 1, ValuePtr(Sphere.lightPos));
	//glUniform3fv(Plane.lightPosLoc, 1, ValuePtr(Plane.lightPos));
	ImGui::SliderFloat3("LightPos", &Sphere.lightPos.x, -100.f, 100.f);
	ImGui::SliderFloat3("SpherePos", &Sphere.Get_position().x, -15.f, 15.f);
	Sphere.set_position(Sphere.Get_position());
	Sphere.GetShdr_pgm().UnUse();
	
	if (camera->eyeMoved || camera->resized)
	{
		Sphere.compute_matrix(static_cast<float>(delta_time), camera->Get_eye(), camera->Get_frustum());
		Plane.compute_matrix(static_cast<float>(delta_time), camera->Get_eye(), camera->Get_frustum());
	}

	camera->eyeMoved = false;
	camera->resized = false;
}

void Toon_Fog::draw() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Sphere.draw();
	Plane.draw();
}

void Toon_Fog::cleanup() {
	delete camera;
}


