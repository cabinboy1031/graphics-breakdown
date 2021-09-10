#include "Violet/Platform/OpenGL/OpenGLTexture.hpp"

#include "glad/glad.h"
#include "Violet/Log.hpp"
#include "stb/stb_image.h"

using namespace Violet;

OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
  :m_Path(path), m_RendererID(0){

  VGE_CORE_TRACE("Loading texture: {}", path);
  int width, height, channels;
  stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
  VGE_CORE_ASSERT(data, "Failed to load image!");

  m_Width = width;
  m_Height = height;


  VGE_CORE_TRACE("Done(w:{0},h{1},c:{2}). Creating a texture buffer.", m_Width, m_Height,channels);
  glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
  glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);

  glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  VGE_CORE_TRACE("Done. Registering it to OpenGL.");
  glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);

  stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D(){
  glDeleteTextures(1, &m_RendererID);
}

void OpenGLTexture2D::bind(uint32_t slot) const {
  glBindTextureUnit(slot, m_RendererID);
}
