#pragma once
#include <glDemo.h>
#include <mesh.hpp>
#include <vector>
#include <input.hpp>


class Toon_Fog :public GLDemo
{
public:
	Toon_Fog():camera(nullptr) {};
	~Toon_Fog() {};

	void init() override;
	void update(double delta_time) override;
	void draw() override;
	void cleanup() override;


private:
	   /*  For head */
	
	Mesh Sphere  ;
	Mesh Plane;
	Camera* camera;


	
	
};