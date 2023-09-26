#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<States/State.h>
#include<chrono>
#include<iostream>
#include<Primitives/Shader.h>
#include<Primitives/Imagem.h>
#include<Primitives/Mesh.h>
#include<Primitives/Camera.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

bool firstMouse = true;
float lastX = 1024 / 2.0f;
float lastY = 768 / 2.0f;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
   
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


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
    Camera* camera;
public:
    void Update(float);
    void Render();
    void Loop();
    /*void set_mouse_callback(GLFWcursorposfun func){
        glfwSetCursorPosCallback(this->janela, func);
    }
    void set_scroll_callback(GLFWscrollfun func){
        glfwSetScrollCallback(this->janela, func);
    }
    */
    Game(int width, int heigth, const char* name);
    ~Game();
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

    this->estadoVazio = new State();
    this->estadoUm    = new EstadoUm();
    this->estadoDois  = new EstadoDois();
    this->camera      = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
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
   //if(this->state == Start){
     //   this->estadoVazio->Render(this->Main_shader);
    //}else if(this->state == Estado_Um){
    this->estadoUm->Render(this->Main_shader);
    //}else if(this->state == Estado_Dois){
      //  this->estadoDois->Render(this->Main_shader);
    //}
  
}
void Game::Update(float deltaTime){
   //if(this->state == Start){
     //   this->estadoVazio->Update(deltaTime);
        //std::cout << "ESTADO START" << std::endl;
   //}else if(this->state == Estado_Um){
        this->estadoUm->Update(deltaTime);
        //std::cout << "ESTADO WILD" << std::endl;
   //}else if(this->state == Estado_Dois){
     //   this->estadoDois->Update(deltaTime);
        //std::cout << "ESTADO TRAINER" << std::endl;
   //}
    //processamento de input
    if(glfwGetKey(janela, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(janela, true);
    }
    if(glfwGetKey(janela, GLFW_KEY_W) == GLFW_PRESS){
            this->camera->ProcessKeyboard(FORWARD, deltaTime);
    }else if(glfwGetKey(janela, GLFW_KEY_A) == GLFW_PRESS){
            this->camera->ProcessKeyboard(LEFT, deltaTime);
    }else if(glfwGetKey(janela, GLFW_KEY_S) == GLFW_PRESS){
            this->camera->ProcessKeyboard(BACKWARD, deltaTime);
    }else if(glfwGetKey(janela, GLFW_KEY_D) == GLFW_PRESS){
            this->camera->ProcessKeyboard(RIGHT, deltaTime);
    }

    //ativando o shader
    this->Main_shader->use();
    //processamento de mouse
    double xposIn;
    double yposIn;
    glfwGetCursorPos(this->janela, &xposIn, &yposIn);
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
    this->camera->ProcessMouseMovement(xoffset, yoffset);

    //manda os valores da camera para o shader
    glm::mat4 view = this->camera->GetViewMatrix();
    this->Main_shader->setMat4("view", view);
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
