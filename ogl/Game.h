#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<chrono>
#include<iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Primitives/Shader.h"
#include "States/State.h"
#include "Primitives/Camera.h"


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
    Shader *Main_shader;
    EstadoUm      *state;
    GlCamera* Camera;
public:
    void Update(float);
    void Render();
    void Loop();
    Game(int width, int heigth, const char* name);
    ~Game();
};

Game::Game(int width, int heigth, const char* name)
{
    //abrir a janela
    //gladLoadGL();
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

    // tell GLFW to capture our mouse
    glfwSetInputMode(janela, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //carregar funcoes opengl
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
    glViewport(0, 0, width, heigth);
    //glEnable(GL_DEPTH_TEST);

    this->Main_shader = new Shader("Shaders/mVtxShader.glsl","Shaders/mFragShader.glsl");
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), ((float)width/(float)heigth), 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    this->Main_shader->use();
    this->Main_shader->setMat4("projection", proj);
    this->Main_shader->setMat4("view", view);

    this->state       = new EstadoUm();
    this->Camera    = new GlCamera(glm::vec3(0.0f, 0.0f, 3.0f));
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
    this->state->Render(this->Main_shader);

}
void Game::Update(float deltaTime){
    this->state->Update(deltaTime, this->janela, this->Camera, this->Main_shader);
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
                std::string frm = "FPS: " + std::to_string(frames);
                glfwSetWindowTitle(this->janela, frm.c_str());
                //std::cout << "FPS: " << frames << std::endl;
                frames = 0;
                lastTime += 1.0;
            }

            glfwSwapBuffers(janela);
            glfwPollEvents();
        }
    }
}
