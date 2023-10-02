#pragma once
#include<iostream>
#include "glad/glad.h"
#include<GLFW/glfw3.h>


#include<string>
#include<vector>
#include<new>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "../Primitives/Shader.h"
#include "../Primitives/Camera.h"
#include "../../primitives/Sphere.h"
#include "../../octree/octree.h"
#include "../Primitives/Model.h"


using std::string;
using std::vector;

bool firstMouse = true;
float lastX = 1024 / 2.0f;
float lastY = 768 / 2.0f;

class State
{
private:
    string estado = "Base";
public:
    State(/* args */){}
    virtual void Render(Shader* s){  }

    virtual void Update(float deltaTime, GLFWwindow* janela, GlCamera* GlCamera, Shader* shader){ }

    virtual string getEstado(){return this->estado;}
};


//battle State
class EstadoUm : public State
{
private:
    string estado = "View";
    vector<Model*> models;
    
public:
    EstadoUm(){
       auto sphere = std::make_shared<Sphere>();
       auto octree = std::make_shared<octree::Octree>(sphere, 6);
       Model* model = new Model(octree.get());
       models.push_back(model);
    }
    
    void Render(Shader* shader){ 
        //shader->setBool("isText", false);
        for(int i = 0; i < this->models.size(); i++){
            this->models[i]->Render(shader);
        }
    }

    void Update(float deltaTime, GLFWwindow* janela, GlCamera* GlCamera, Shader* shader){
        if(this->estado == "View"){
            glfwSetInputMode(janela, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            //ativando o shader
            shader->use();
            //processamento de mouse
            double xposIn;
            double yposIn;
            glfwGetCursorPos(janela, &xposIn, &yposIn);
            float xpos = static_cast<float>(xposIn);
            float ypos = static_cast<float>(yposIn);

            if (firstMouse)
            {
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
            }
            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
            lastX = xpos;
            lastY = ypos;
            GlCamera->ProcessMouseMovement(xoffset, yoffset);

            //manda os valores da GlCamera para o shader
            glm::mat4 view = GlCamera->GetViewMatrix();
            shader->setMat4("view", view);

            //processamento de input
            if(glfwGetKey(janela, GLFW_KEY_ESCAPE) == GLFW_PRESS){
                    glfwSetWindowShouldClose(janela, true);
            }
            if(glfwGetKey(janela, GLFW_KEY_W) == GLFW_PRESS){
                    GlCamera->ProcessKeyboard(FORWARD, deltaTime);
            }else if(glfwGetKey(janela, GLFW_KEY_A) == GLFW_PRESS){
                    GlCamera->ProcessKeyboard(LEFT, deltaTime);
            }else if(glfwGetKey(janela, GLFW_KEY_S) == GLFW_PRESS){
                    GlCamera->ProcessKeyboard(BACKWARD, deltaTime);
            }else if(glfwGetKey(janela, GLFW_KEY_D) == GLFW_PRESS){
                    GlCamera->ProcessKeyboard(RIGHT, deltaTime);
            }else if(glfwGetKey(janela, GLFW_KEY_TAB) == GLFW_PRESS){
                    estado = "Console";
                    glfwSetInputMode(janela, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        }else{
            string esta;
            std::cout << "Digite{p - para voltar para o modo de view | w - para mudar para wired }: ";
            std::cin >> esta;
            if(esta == "p"){
                estado = "View";
                firstMouse = true;
                lastX = 1024 / 2.0f;
                lastY = 768 / 2.0f;
            }else if(esta == "w"){
                for(int i = 0; i < this->models.size(); i++){
                    this->models[i]->switchDrawMode();
                }
            }
        }
       
    }
    string getEstado(){return this->estado;}
};


//battle State
class EstadoDois : public State
{
private:
    string estado = "Estado 2";
    unsigned int VBO;
    unsigned int VAO;
public:
    EstadoDois(/* args */){
        float vertices[] = {//r  g     b
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,
        }; 
        glGenVertexArrays(1, &this->VAO);  
        glBindVertexArray(this->VAO);
        glGenBuffers(1, &this->VBO);  
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO); 
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              6 * sizeof(float),
                             (void*)0);
        glEnableVertexAttribArray(0);  

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);  
    }
    void Render(Shader* s){  
        s->setBool("isText", false);
        s->use();
        glBindVertexArray(this->VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }
    void Update(float delta){  }
    string getEstado(){return this->estado;}
};