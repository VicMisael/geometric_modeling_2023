#pragma once
#include<iostream>
#include<Entities/Pokemon.h>
#include<Primitives/Shader.h>
#include<Primitives/Texture.h>
#include<string>

using std::string;

class State
{
private:
    string estado = "Base";
public:
    State(/* args */){}
    virtual void Render(Shader* s){  }

    virtual void Update(float delta){ }

    virtual string getEstado(){return this->estado;}
};


//battle State
class WildBattle : public State
{
private:
    string estado = "Batalha Wild";
    unsigned int VBO;
    unsigned int VAO;
    Texture *text;
public:
    WildBattle(/* args */){
        float vertices[] = {//r  g     b       tx   ty
        -1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         1.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         1.0f,-1.0f, 0.0f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
         -1.0f,-1.0f,0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f
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
                              8 * sizeof(float),
                             (void*)0);
        glEnableVertexAttribArray(0);  

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);  

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
        glEnableVertexAttribArray(2);  

        std::cout << "mandou os dados\n";
        this->text = new Texture("resource/background.png", PNG, GL_TEXTURE_2D);
        if(this->text != nullptr){
            std::cout << "carregado textura\n";
            this->text->bind(GL_TEXTURE0, GL_TEXTURE_2D);
        }
    }
    void Render(Shader* s){ 
        s->setBool("isText", true);
        s->use();
        glBindVertexArray(this->VAO);
        glDrawArrays(GL_QUADS, 0, 4);
    }
    void Update(float delta){ }
    string getEstado(){return this->estado;}
};


//battle State
class TrainerBattle : public State
{
private:
    string estado = "Batalha Trainer";
    unsigned int VBO;
    unsigned int VAO;
public:
    TrainerBattle(/* args */){
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
    }
    void Update(float delta){  }
    string getEstado(){return this->estado;}
};