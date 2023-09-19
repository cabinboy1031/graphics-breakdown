#ifndef VIOLET_OPENGL_TEXTURE_H_
#define VIOLET_OPENGL_TEXTURE_H_
#include "Violet/Renderer/Texture.hpp"
#include <glad/glad.h>

namespace Violet {
  class OpenGLTexture2D: public Texture2D{
    public:
      OpenGLTexture2D(const std::string& path);
      OpenGLTexture2D(const Violet::TextureSpecification& specification);
      virtual ~OpenGLTexture2D() override;

      virtual uint32_t getWidth() const override { return m_Width; };
      virtual uint32_t getHeight() const override { return m_Height; };

      virtual void setData(void* data, uint32_t size) override;
      virtual void bind(uint32_t slot) const override;

      private:
      TextureSpecification m_Specification;

      std::string m_Path;
      uint32_t m_Width, m_Height;
      uint32_t m_RendererID;
      GLenum m_InternalFormat, m_DataFormat;
  };
}


#endif // VIOLET_OPENGL_TEXTURE_H_
