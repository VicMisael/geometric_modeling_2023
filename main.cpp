#include <iostream>
#include "octree/octree.h"
#include "primitives/Sphere.h"
#include "primitives/Box.h"
#include "strippedRayTracer/RayTracerRedone/tracer/objects/VirtualObject.h"
#include "strippedRayTracer/RayTracerRedone/tracer/scene/materials/Phong.h"
#include "strippedRayTracer/RayTracerRedone/RayTracerRedone.cpp"
#include "rt_interface/InterceptableOctree.h"

int main()
{
	auto sphere = std::make_shared<Sphere>(40 / 3.0f);
	auto octree = std::make_shared<octree::Octree>(sphere, 6);

	//std::cout << octree->parse() << std::endl;
	std::cout << octree->volume() << std::endl;
	auto box = std::make_shared<Box>(glm::vec3(0,0,0),glm::vec3(30,60,20));
	auto boxOct = std::make_shared<octree::Octree>(box, 6);
	//std::cout << boxOct->parse() << std::endl;
	std::cout << boxOct->volume() << std::endl;

	const auto intersectionResult = octree->octreeIntersection(boxOct);
	intersectionResult->scale(3);

	std::cout << intersectionResult->parse() << std::endl;


	std::shared_ptr<VirtualObject> object = std::make_shared<InterceptableOctree>(intersectionResult,
		std::make_shared<Phong>(
			ColorVec(0.5, 0.5, 0.5), 1, 1,
			25));

	Raytracer::render1(object, "plane", 600, 600);
	Raytracer::render2(object, "plane2", 300, 300);
	Raytracer::render3(object, "plane3", 600, 600);
	return 0;
}
