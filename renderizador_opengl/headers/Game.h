#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<States/State.h>
#include<chrono>
#include<iostream>
#include<Primitives/Shader.h>
#include<Primitives/Imagem.h>
#include<Primitives/Mesh.h>



enum GameStates{
    Start,
    Estado_Um,
    Estado_Dois
};


class Game
{
private:
    /* data */
    GLFWwindow* janela;
    GameStates state = Start;
    Shader *Main_shader;
    State         *estadoVazio;
    EstadoUm      *estadoUm;
    EstadoDois   *estadoDois;
public:
    Game(int width, int heigth, const char* name);
    ~Game();
    void Update(float);
    void Render();
    void Loop();
};

Game::Game(int width, int heigth, const char* name)
{
    
    //abrir a janela
    if(!glfwInit()){ return; }
    janela = glfwCreateWindow(width, heigth,  name, NULL, NULL);
    if (!janela)
    {
        glfwTerminate();
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    glfwMakeContextCurrent(janela);
    //carregar funcoes opengl
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }   
    glViewport(0, 0, width, heigth);
    this->Main_shader = new Shader("Shaders/mVtxShader.glsl","Shaders/mFragShader.glsl");
    this->estadoVazio = new State();
    this->estadoUm    = new EstadoUm();
    this->estadoDois  = new EstadoDois();
}  

Game::~Game()
{
    glfwDestroyWindow(janela);
    glfwTerminate();
    //fechar a janela
}

void Game::Render(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
   if(this->state == Start){
        this->estadoVazio->Render(this->Main_shader);
    }else if(this->state == Estado_Um){
        this->estadoUm->Render(this->Main_shader);
    }else if(this->state == Estado_Dois){
        this->estadoDois->Render(this->Main_shader);
    }
  
}
void Game::Update(float deltaTime){
   if(this->state == Start){
        this->estadoVazio->Update(deltaTime);
        //std::cout << "ESTADO START" << std::endl;
   }else if(this->state == Estado_Um){
        this->estadoUm->Update(deltaTime);
        //std::cout << "ESTADO WILD" << std::endl;
   }else if(this->state == Estado_Dois){
        this->estadoDois->Update(deltaTime);
        //std::cout << "ESTADO TRAINER" << std::endl;
   }


    //processamento de input
   if(glfwGetKey(janela, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(janela, true);
    }
    else if(glfwGetKey(janela, GLFW_KEY_1) == GLFW_PRESS){
        this->state = Start;
    }else if(glfwGetKey(janela, GLFW_KEY_2) == GLFW_PRESS){
        this->state = Estado_Um;
    }else if(glfwGetKey(janela, GLFW_KEY_3) == GLFW_PRESS){
        this->state = Estado_Dois;
    }
}

void Game::Loop(){
    int frames = 0;
    double lastTime = glfwGetTime();

    const int FPS = 60;
    const double frameDuration = 1.0 / FPS;
    double last_frame = glfwGetTime();
    while(!glfwWindowShouldClose(janela)){
        double now = glfwGetTime();
        double deltaTime = now - last_frame;
        if(deltaTime >= frameDuration){
            last_frame = now;

            this->Update(deltaTime);
            this->Render();

            frames++;
            if (now - lastTime >= 1.0) {
                std::cout << "FPS: " << frames << std::endl;
                frames = 0;
                lastTime += 1.0;
            }
            
            glfwSwapBuffers(janela);
            glfwPollEvents();
        }
    }
}
