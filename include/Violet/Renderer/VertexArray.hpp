#ifndef VIOLET_VERTEXARRAY_H_
#define VIOLET_VERTEXARRAY_H_
#include <cstdint>

namespace Violet{
    class VertexArray{
        public:
            virtual ~VertexArray(){}

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            static VertexArray* create();
    };
}



#endif // VIOLET_VERTEXARRAY_H_
