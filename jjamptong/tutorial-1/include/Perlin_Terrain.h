#pragma once
#include <GLDemo.h>
#include <mesh.hpp>
#include <input.hpp>

class Perlin_Terrain : public GLDemo
{
public:
	Perlin_Terrain():terrain(nullptr),camera(nullptr) {};
	~Perlin_Terrain() override {};

	void init() override;
	void update(double delta_time) override;
	void draw() override;
	void cleanup() override;
private:

	Mesh* terrain;
	Camera* camera;

	float frequency = 0.1f;
};