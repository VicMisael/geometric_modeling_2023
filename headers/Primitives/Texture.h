#pragma once
#include<Primitives/Imagem.h>
#include<iostream>

class Texture
{
private:
    Imagem* img;
    unsigned int id;
public:
    Texture(string filename, IMG_FORMAT formato, GLenum tipo){
        this->img = new Imagem(filename, formato);
        if(this->img == nullptr){std::cout << "ERROR::CARREGAMENTO DE TEXTURA FALHOU\n"; return;}
        glGenTextures(1, &this->id);
        glBindTexture(tipo, this->id);
        if(img->getFormat() == PNG){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 
            0, GL_RGBA, GL_UNSIGNED_BYTE, img->getData());
        }else{
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->getWidth(), img->getHeight(), 
            0, GL_RGB, GL_UNSIGNED_BYTE, img->getData());
        }
        glTexParameteri(tipo, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(tipo, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(tipo, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(tipo, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    void Apagar(){
        this->img->~Imagem();
        glDeleteTextures(1, &this->id);
    }

    unsigned int getId() const{ return this->id; }

    void bind(GLint texture_unit, GLenum tipo){
        glActiveTexture(GL_TEXTURE0 + texture_unit);
        glBindTexture(tipo, this->id);
    }

    void unbind(GLenum tipo){
        glActiveTexture(0);
        glBindTexture(tipo, 0);
    }

};
