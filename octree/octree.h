//
// Created by Misael on 08/09/2023.
//

#ifndef OCTREE_MODEL_OCTREE_H
#define OCTREE_MODEL_OCTREE_H


#include <memory>
#include <string>
#include <glm/vec3.hpp>
#include <utility>

#include "../primitives/Primitive.h"

namespace octree
{
	const auto standardBoundingBox = BoundingBox::GenerateCubeByCenterAndSideLength(glm::vec3(0, 0, 0), 30);

	class Node : std::enable_shared_from_this<Node>
	{
	public:
		NodeType nodeType;
		BoundingBox boundingBox;
		bool isLeaf = true;
		std::shared_ptr<Node> children[8];
		bool isRoot = false;

		void makeTree(const std::shared_ptr<Primitive>& _primitive, int _depth);

		void makeTreeInit(const std::shared_ptr<Primitive>& _primitive, int _depth);

		int depth();

		float volume();

		std::string parse();

		void translate(glm::vec3 vec3);

		void scale(float size);

		glm::vec3 getCenter()
		{
			return boundingBox.center();
		}

		static std::shared_ptr<Node> intersection(const std::shared_ptr<Node>& a, const std::shared_ptr<Node>& b);

		explicit Node(BoundingBox box) : boundingBox(std::move(box))
		{
		};

		static std::shared_ptr<Node> standardize(const std::shared_ptr<Node>& node);

	private:
		static void copyTree(std::shared_ptr<Node> dest, std::shared_ptr<Node> src);

		void subdivide();

		static void intersectionHelper(const std::shared_ptr<Node>& result, const std::shared_ptr<Node>& a,
		                               const std::shared_ptr<Node>& b);
	};

	class Octree
	{
	private:


	public:
		std::shared_ptr<Node> rootNode;

		explicit Octree(std::shared_ptr<Node> root);
		explicit Octree(const std::shared_ptr<Primitive>& primitive, int depth);

		std::string parse();

		float volume();

		int depth();

		void scale(float size);

		void translate(glm::vec3 point);

		Octree octreeUnion(const Octree other);

		std::shared_ptr<Octree> octreeIntersection(const std::shared_ptr<octree::Octree>& other);
	};
}

#endif //OCTREE_MODEL_OCTREE_H
