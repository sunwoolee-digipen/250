#pragma once
#include <glDemo.h>
#include <mesh.hpp>
#include <vector>
#include <input.hpp>

class Toon_Fog :public GLDemo
{
public:
	Toon_Fog() {};
	~Toon_Fog() {};

	void init() override;
	void update(double delta_time) override;
	void draw() override;
	void cleanup() override;
private:
	//std::vector<Mesh> meshes = { CreatePlane(10,10),
	//								CreateCube(10, 10),       /*  For torso, feet */
	//								CreateSphere(16, 16),   /*  For head */
	//								CreateCylinder(1, 8),   /*  For arms, legs */
	//								CreateCone(16, 8),      /*  For hat */
	//								CreateTorus(16, 32, 0, TWO_PI)                      /*  For base */
	//};
	Mesh sphere;
	Camera* camera;
};