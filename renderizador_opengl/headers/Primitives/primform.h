#pragma once


#include<vector>
#include<new>
#include"vertex.h"

using std::nothrow;


class Primitiva
{
private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
public:
    Primitiva(/* args */){}
    ~Primitiva(){}

    void set(const Vertex* vertices, const unsigned qntVertices, const unsigned int* indices, const unsigned qntIndices){
        for (int i = 0; i < qntVertices; i++)
        {
            this->vertices.push_back(vertices[i]);
        }

        for (int i = 0; i < qntIndices; i++)
        {
            this->indices.push_back(indices[i]);
        }
        
        
    }

    Vertex* getVertices(){return this->vertices.data(); }

    unsigned int* getIndices(){return this->indices.data();}

    const unsigned getVertivesQnt(){return this->vertices.size();}

    const unsigned getIndicesQnt(){return this->indices.size();}
};


class Cube :  public Primitiva {
    public:
        Cube() : Primitiva(){
            Vertex verticesTri[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f, 1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f, 1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f, 0.0f, 0.0f,1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,1.0f, 0.0f, 0.0f,
            
            -0.5f, -0.5f,  0.5f, 0.0f,0.0f,-1.0f, 0.0f, 0.0f,
            0.5f, -0.5f,  0.5f, 0.0f,0.0f,-1.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f, 0.0f,0.0f,-1.0f, 1.0f, 1.0f,
            0.5f,  0.5f,  0.5f, 0.0f,0.0f,-1.0f, 1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f, 0.0f,0.0f,-1.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, 0.0f,0.0f,-1.0f, 0.0f, 0.0f,
            
            -0.5f,  0.5f,  0.5f, -1.0f,0.0f,0.0f, 1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,0.0f,0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,0.0f,0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,0.0f,0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,0.0f,0.0f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,0.0f,0.0f, 1.0f, 0.0f,
        
            0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f, 1.0f, 0.0f,
            0.5f,  0.5f, -0.5f, 1.0f,0.0f,0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f,0.0f,0.0f, 0.0f, 1.0f,
            0.5f, -0.5f,  0.5f, 1.0f,0.0f,0.0f, 0.0f, 0.0f,
            0.5f,  0.5f,  0.5f, 1.0f,0.0f,0.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f,-1.0f,0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f,-1.0f,0.0f, 1.0f, 1.0f,
            0.5f, -0.5f,  0.5f, 0.0f,-1.0f,0.0f, 1.0f, 0.0f,
            0.5f, -0.5f,  0.5f, 0.0f,-1.0f,0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f, 0.0f,-1.0f,0.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f,-1.0f,0.0f, 0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f, 0.0f,1.0f,0.0f, 0.0f, 1.0f,
            0.5f,  0.5f, -0.5f, 0.0f,1.0f,0.0f, 1.0f, 1.0f,
            0.5f,  0.5f,  0.5f, 0.0f,1.0f,0.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f, 0.0f,1.0f,0.0f, 1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, 0.0f,1.0f,0.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, 0.0f,1.0f,0.0f, 0.0f, 1.0f
            
            };
            unsigned int verticesInd[] = {
                0,1,2,
                3,4,5,
                6,7,8,
                9,10,11,
                12,13,14,
                15,16,17,
                18,19,20,
                21,22,23,
                24,25,26,
                27,28,29,
                30,31,32,
                33,34,35
            };
            unsigned nrOfVertices = sizeof(verticesTri) / sizeof(Vertex);
            unsigned nrOfIndices = sizeof(verticesInd) / sizeof(unsigned int);
            this->set(verticesTri, nrOfVertices, verticesInd, nrOfIndices);
        }
};

class Quad :  public Primitiva {
    public:
        Quad() : Primitiva(){
            Vertex verticesTri[] = {
                -1.0f,  1.0f, -1.0f, 0.0f,1.0f,0.0f, 0.0f, 1.0f,
                1.0f,  1.0f, -1.0f, 0.0f,1.0f,0.0f, 1.0f, 1.0f,
                1.0f,  1.0f,  1.0f, 0.0f,1.0f,0.0f, 1.0f, 0.0f,
                1.0f,  1.0f,  1.0f, 0.0f,1.0f,0.0f, 1.0f, 0.0f,
                -1.0f,  1.0f,  1.0f, 0.0f,1.0f,0.0f, 0.0f, 0.0f,
                -1.0f,  1.0f, -1.0f, 0.0f,1.0f,0.0f, 0.0f, 1.0f
            };
            unsigned int verticesInd[] = {
                0,1,2,
                3,4,5
            };
            unsigned nrOfVertices = sizeof(verticesTri) / sizeof(Vertex);
            unsigned nrOfIndices = sizeof(verticesInd) / sizeof(unsigned int);
            this->set(verticesTri, nrOfVertices, verticesInd, nrOfIndices);
        }
};
