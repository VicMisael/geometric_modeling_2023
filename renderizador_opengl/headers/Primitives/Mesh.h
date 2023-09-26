#pragma once
#ifndef MESH_H
#define MESH_H

//glm
#include<glm/gtc/matrix_transform.hpp>
#include<glm/mat4x4.hpp>
//primitivas
#include<vector>
#include<iostream>
#include<Primitives/Vertex.h>
#include<Primitives/Shader.h>
#include<Primitives/Texture.h>
#include<Primitives/primform.h>

class Mesh
{
    private:
        //std::vector<Vertex> vertices;
        Vertex* vertices;
        unsigned verticesQnt;
        //std::vector<int> indices;
        unsigned int* indices;
        unsigned indicesQnt;
        //buffers
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EAB; 
        //como os vertices serao desenhados
        GLenum drawMode;
        //transformacao
        glm::mat4 transform;
        //funcao de inicializacao
        void initBuffers(){
            //crio os buffers e mando os dados
            glCreateVertexArrays(1, &this->VAO);
		    glBindVertexArray(this->VAO);
            //Vertex buffer
            glGenBuffers(1, &this->VBO);
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
            glBufferData(GL_ARRAY_BUFFER, this->verticesQnt * sizeof(Vertex), this->vertices, GL_STATIC_DRAW);
            //Indices buffer
            glGenBuffers(1, &this->EAB);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EAB);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indicesQnt * sizeof(unsigned int), this->indices, GL_STATIC_DRAW);
            //envio os dados para a placa
            //posicoes
            glVertexAttribPointer(0, 
                                  3,
                                  GL_FLOAT,
                                  false, 
                                  8*sizeof(float), 
                                  (void*)(0*sizeof(float)));
            glEnableVertexAttribArray(0);
            //normais
            glVertexAttribPointer(1, 
                                  3,
                                  GL_FLOAT,
                                  false, 
                                  8*sizeof(float), 
                                  (void*)(3*sizeof(float)));
            glEnableVertexAttribArray(1);
            //coordenadas de textura
            glVertexAttribPointer(2, 
                                  2,
                                  GL_FLOAT,
                                  false, 
                                  8*sizeof(float), 
                                  (void*)(6*sizeof(float)));
            glEnableVertexAttribArray(2);
            glBindVertexArray(0);
    }   



    public:
    void updateTransform(glm::mat4 transform){
        this->transform = transform;
    }

    Mesh(Vertex* vertices, const unsigned & qntVertices, unsigned int* indices, const unsigned& qntIndices){
        this->verticesQnt = qntVertices;
        this->indicesQnt = qntIndices;
        glm::mat4 transform = glm::mat4(1, 0, 0,  0, 0, 1, 0,  0,0, 0, 1, 0, 0, 0, 0,  1);
        this->transform = transform;
        //alocando memoria
        this->vertices = new Vertex[this->verticesQnt];
        for (int i = 0; i < this->verticesQnt; i++)
        {
            this->vertices[i] = vertices[i];
        }
        
        this->indices  = new unsigned int[this->indicesQnt];
        for (int i = 0; i < this->indicesQnt; i++)
        {
            this->indices[i] = indices[i];
        }
        this->initBuffers();
    }
    Mesh(Vertex* vertices, const unsigned & qntVertices, unsigned int* indices, const unsigned& qntIndices, glm::mat4 transform){
        this->verticesQnt = qntVertices;
        this->indicesQnt = qntIndices;
        this->transform = transform;
        this->vertices = new Vertex[this->verticesQnt];
        this->indices  = new unsigned int[this->indicesQnt];

        for (int i = 0; i < this->verticesQnt; i++)
        {
            this->vertices[i] = vertices[i];
        }

        for (int i = 0; i < this->indicesQnt; i++)
        {
            this->indices[i] = indices[i];
        }
         this->initBuffers();
    }


    Mesh(Primitiva* primitiva){
        this->verticesQnt = primitiva->getVertivesQnt();
        this->indicesQnt = primitiva->getIndicesQnt();
        glm::mat4 transform = glm::mat4(1, 0, 0,  0, 0, 1, 0,  0, 0, 0, 1, 0, 0, 0, 0,  1);
        this->transform = transform;
        
        this->vertices = new Vertex[this->verticesQnt];
        this->indices  = new unsigned int[this->indicesQnt];
        for (int i = 0; i < this->verticesQnt; i++)
        {
            this->vertices[i] = primitiva->getVertices()[i];
        }

        for (int i = 0; i < this->indicesQnt; i++)
        {
            this->indices[i] = primitiva->getIndices()[i];
        }
        this->initBuffers();
    }
    
    Mesh(Primitiva* primitiva, glm::mat4 transform){
        this->verticesQnt = primitiva->getVertivesQnt();
        this->indicesQnt = primitiva->getIndicesQnt();
        this->transform = transform;

        this->vertices = new Vertex[this->verticesQnt];
        this->indices  = new unsigned int[this->indicesQnt];
        for (int i = 0; i < this->verticesQnt; i++)
        {
            this->vertices[i] = primitiva->getVertices()[i];
        }

        for (int i = 0; i < this->indicesQnt; i++)
        {
            this->indices[i] = primitiva->getIndices()[i];
        }
        this->initBuffers();
    }


  
    ~Mesh(){
        glDeleteBuffers(1, &this->VAO);
        glDeleteBuffers(1, &this->VBO);
        glDeleteBuffers(1, &this->EAB);
        delete[] this->indices;
        delete[] this->vertices;
    }

    glm::mat4 getTransf(){return this->transform;}

    
    void Render(Shader *shader, unsigned int textI){
        glBindVertexArray(this->VAO);
        //ativa shader
        shader->use();
        //shader->setMat4("transform", this->transform);
        //shader->setInt("texture_1", textI);
        //shader->setFloat("uPixelSize", 5.0f);
        //shader->set2dVec("uTextureSize", (float)256, (float)256);
        //renderiza
        //std::cout << this->indicesQnt << "\n";
        //RENDER
		if (this->indicesQnt == 0)
			glDrawArrays(GL_TRIANGLES, 0, this->verticesQnt);
		else
			glDrawElements(GL_TRIANGLES, this->indicesQnt, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Render(Shader *shader, unsigned int textI, glm::mat4 transformacao){
        glBindVertexArray(this->VAO);
        //ativa shader
        this->updateTransform(transformacao);
        shader->use();
       /* shader->setMat4("transform", this->transform);
        shader->setInt("texture_1", textI);
        shader->setFloat("uPixelSize", 5.0f);
        shader->set2dVec("uTextureSize", (float)256, (float)256);*/
        //renderiza
        //std::cout << this->indicesQnt << "\n";
        //RENDER
		if (this->indicesQnt == 0)
			glDrawArrays(GL_TRIANGLES, 0, this->verticesQnt);
		else
			glDrawElements(GL_TRIANGLES, this->indicesQnt, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};





#endif