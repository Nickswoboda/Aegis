#include "Texture.h"

#include "Renderer.h"
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>
namespace Aegis {

    Texture::~Texture()
    {
        //glDeleteTextures(1, &ID_);
    }

    Texture::Texture(const std::string& path)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &ID_);

        int width, height, channels;
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        size_ = Vec2(width, height);

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
        :size_(width, height)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &ID_);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureStorage2D(ID_, 1, GL_RGBA8, width, height);
        glTextureSubImage2D(ID_, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }

    //used for static text caching. combines all glyph textures into one big texture
    std::shared_ptr<Texture> Texture::TextureFromText(const std::string& text, std::shared_ptr<Font> font)
    {
        //get atlas_pixel_data
		auto atlas = font->atlas_;
        unsigned char* atlas_pixel_data = new unsigned char[(size_t)(atlas->size_.x * atlas->size_.y * 4)]();
        glBindTexture(GL_TEXTURE_2D, atlas->ID_);
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, atlas_pixel_data);

		Vec2 tex_size = font->GetStringPixelSize(text);
        unsigned char* new_tex_pixel_data = new unsigned char[(size_t)( tex_size.x * tex_size.y * 4)]();
		int pen_x = 0;
        for (const auto& c : text) {
			auto glyph = font->glyphs_[c];
            for (int row = 0; row < glyph.size.y; ++row) {
				for (int col = 0; col < glyph.size.x * 4; ++col){
                    int x = pen_x + col + glyph.bearing.x * 4;;
                    int y = font->tallest_glyph_height_ + row - glyph.bearing.y;
                    new_tex_pixel_data[y * (int)tex_size.x * 4 + x] = atlas_pixel_data[ (int)(row + glyph.atlas_pos.y) * (int)atlas->size_.x * 4 + (col + (int)glyph.atlas_pos.x * 4)];
				}
			}
			pen_x += glyph.advance * 4;
		}
		//return std::make_shared<Texture>(atlas_pixel_data, atlas->size_.x, atlas->size_.y);
		return std::make_shared<Texture>(new_tex_pixel_data, tex_size.x, tex_size.y);
    }

    void Texture::Bind()
    {
        glBindTextureUnit(0, ID_);
    }

    SubTexture::SubTexture(const std::shared_ptr<Texture>& texture, Vec2 pos, Vec2 size)
        :texture_(texture), size_(size)
    {
        tex_coords_ = { pos.x / texture->size_.x, pos.y / texture->size_.y, (pos.x + size.x) / texture->size_.x, (pos.y + size.y) / texture_->size_.y };
    }
}

