#include "Violet/Platform/OpenGL/OpenGLTexture.hpp"

#include "glad/glad.h"
#include "Violet/Log.hpp"
#include "stb/stb_image.h"

using namespace Violet;
namespace Violet::Utils {

		static GLenum VioletImageFormatToGLDataFormat(ImageFormat format)
		{
			switch (format)
			{
				case ImageFormat::RGB8:  return GL_RGB;
				case ImageFormat::RGBA8: return GL_RGBA;
        default: VGE_CORE_ASSERT(false, "");
			}

			VGE_CORE_ASSERT(false, "");
			return 0;
		}

		static GLenum VioletImageFormatToGLInternalFormat(ImageFormat format)
		{
			switch (format)
			{
        case ImageFormat::RGB8:  return GL_RGB8;
        case ImageFormat::RGBA8: return GL_RGBA8;
        default: VGE_CORE_ASSERT(false, "");
			}

      VGE_CORE_ASSERT(false, "");
			return 0;
		}
}


OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
  :m_Path(path), m_RendererID(0){

  VGE_CORE_TRACE("Loading texture: {}", path);
  int width, height, channels;
  stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
  VGE_CORE_ASSERT(data, "Failed to load image!");

  m_Width = width;
  m_Height = height;

  GLenum internalFormat = 0;
  GLenum dataFormat = 0;
  if(channels == 4){
    internalFormat = GL_RGBA8;
    dataFormat = GL_RGBA;
  } else if (channels == 3){
    internalFormat = GL_RGB8;
    dataFormat = GL_RGB;
  }

  VGE_CORE_ASSERT(internalFormat & dataFormat, "Format not supported.");

  VGE_CORE_TRACE("Done(w:{0},h{1},c:{2}). Creating a texture buffer.", m_Width, m_Height,channels);
  glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
  glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

  glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  VGE_CORE_TRACE("Done. Registering it to OpenGL.");
  glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

  stbi_image_free(data);
}

OpenGLTexture2D::OpenGLTexture2D(const Violet::TextureSpecification& specification)
  :m_Specification(specification),
  m_Width(m_Specification.width),
  m_Height(m_Specification.height){
  m_InternalFormat = Utils::VioletImageFormatToGLInternalFormat(m_Specification.format);
  m_DataFormat = Utils::VioletImageFormatToGLDataFormat(m_Specification.format);

  glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
  glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

  glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
}


OpenGLTexture2D::~OpenGLTexture2D(){
  glDeleteTextures(1, &m_RendererID);
}

void OpenGLTexture2D::bind(uint32_t slot) const {
  glBindTextureUnit(slot, m_RendererID);
}

void OpenGLTexture2D::setData(void* data, uint32_t size){
  uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
  VGE_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
  glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}
