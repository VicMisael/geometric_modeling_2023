#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<string>
#include<vector>
#include<new>
#include "../../octree/octree.h"
#include "Mesh.h"
#include "primform.h"
#include "Shader.h"

using std::vector;

class Model
{
private:
    octree::Octree* oct;
    int prim = 0;
    unsigned int drawM = 0;
    vector<Mesh*> meshes;
    void PercorreArvore(octree::Node* node){
            if(node->nodeType == octree::GRAY){
                //percorre os filhos
                for(int i = 0; i < 8; i++){
                    PercorreArvore(node->children[i].get());
                }
            }else{
                //tamanho
                float size =  glm::length(node->boundingBox.max - node->boundingBox.min);
                //centro
                glm::vec3 center = node->boundingBox.center();
                //cria o bloco
                glm::mat4 model = glm::mat4(1);
                model = glm::translate(model, center);
                model = glm::scale(model, glm::vec3(size, size, size));
                //
                Cube tempCube = Cube();
                auto mesh = new Mesh(&tempCube, model);
                if(node->nodeType == octree::BLACK){
                     this->meshes.push_back(mesh);
                     return;
                }else{
                    mesh->OnOff();
                    this->meshes.push_back(mesh);
                    return;
                }
            }
            return;
    }
public:
    Model(octree::Octree* oct);
    ~Model();

    void switchDrawMode(){
        if(this->drawM == 1){
            this->drawM--;
        }else{
            this->drawM++;
        }
    }

    void Render(Shader* shader){
        for(int i = 0; i < this->meshes.size(); i++){
            if(this->meshes[i]->isActive()){
                this->meshes[i]->Render(shader,this->drawM);
            }
        }
    }
};

Model::Model(octree::Octree* oct)
{
    this->oct = oct;
    PercorreArvore(oct->rootNode.get());
}

Model::~Model()
{
}
