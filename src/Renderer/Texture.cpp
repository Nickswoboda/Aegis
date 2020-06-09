#include "Texture.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>
namespace Aegis {
    Texture::Texture()
    {
        width_ = 1;
        height_ = 1;
        glCreateTextures(GL_TEXTURE_2D, 1, &ID_);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        uint32_t data = 0xffffffff;
        glTextureStorage2D(ID_, 1, GL_RGBA8, 1, 1);
        glTextureSubImage2D(ID_, 0, 0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &data);
    }

    Texture::~Texture()
    {
        //glDeleteTextures(1, &ID_);
    }

    Texture::Texture(const std::string& path)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &ID_);
    
        int width, height, channels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    
        width_ = width;
        height_ = height;
    
        GLint internal_format = 0, format = 0;
        if (channels == 3) {
            internal_format = GL_RGB8;
            format = GL_RGB;
        }
        else if (channels == 4) {
            internal_format = GL_RGBA8;
            format = GL_RGBA;
        }
        else {
            std::cout << "Texture format not supported, unable to create texture.";
        }
    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
        glTextureStorage2D(ID_, 1, internal_format, width, height);
        glTextureSubImage2D(ID_, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
    
        stbi_image_free(data);
    }

    Texture::Texture(unsigned char* data, int width, int height)
        :width_(width), height_(height)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &ID_);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureStorage2D(ID_, 1, GL_RGBA8, width, height);
        glTextureSubImage2D(ID_, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }

    void Texture::Bind()
    {
        glBindTextureUnit(0, ID_);
    }
}