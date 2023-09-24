//
// Created by Misael on 19/09/2023.
//

#ifndef OCTREE_MODEL_PRIMITIVE_H
#define OCTREE_MODEL_PRIMITIVE_H
namespace octree {
    enum NodeType {
        BLACK,
        GRAY,
        WHITE
    };
}
class Primitive {
    virtual octree::NodeType classify() = 0;

public:
    virtual std::tuple<glm::vec3,glm::vec3> minMax()=0;
};


#endif //OCTREE_MODEL_PRIMITIVE_H
