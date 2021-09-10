#ifndef VIOLET_TEXTURE_H_
#define VIOLET_TEXTURE_H_
#include <string>
#include "Violet/Core.hpp"

namespace Violet {
  class Texture {
    public:
      virtual ~Texture() {}
      virtual uint32_t getWidth() const = 0;
      virtual uint32_t getHeight() const = 0;

      virtual void bind(uint32_t slot) const = 0;
  };

  class Texture2D: public Texture {
    public:
      virtual ~Texture2D() {}
      static Reference<Texture2D> create(const std::string& path);
  };
}


#endif // VIOLET_TEXTURE_H_
