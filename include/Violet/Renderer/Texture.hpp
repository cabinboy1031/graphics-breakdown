#ifndef VIOLET_TEXTURE_H_
#define VIOLET_TEXTURE_H_
#include <string>
#include "Violet/Core.hpp"

namespace Violet {
  enum class ImageFormat{
		None = 0,
		R8,
		RGB8,
		RGBA8,
		RGBA32F
	};

  struct TextureSpecification{
    uint32_t width = 1;
    uint32_t height = 1;
    ImageFormat format = ImageFormat::RGBA8;
    bool generateMips = true;
  };

  class Texture {
    public:
      virtual ~Texture() {}
      virtual uint32_t getWidth() const = 0;
      virtual uint32_t getHeight() const = 0;

      virtual void setData(void* data, uint32_t size) = 0;

      virtual void bind(uint32_t slot) const = 0;
  };

  class Texture2D: public Texture {
    public:
      virtual ~Texture2D() {}
      static Reference<Texture2D> create(const std::string& path);
      static Reference<Texture2D> create(const TextureSpecification& specification);
  };
}


#endif // VIOLET_TEXTURE_H_
