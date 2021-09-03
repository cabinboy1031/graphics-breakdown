#ifndef VIOLET_BUFFER_H
#define VIOLET_BUFFER_H
#include "Violet/Log.hpp"

#include <cstdint>
#include <vector>
#include <string>

namespace Violet{
    enum class ShaderDataType{ None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool};

    static uint32_t shaderDataTypeSize(ShaderDataType type){
        switch(type){
            case(ShaderDataType::Float):  return 4;
            case(ShaderDataType::Float2): return 4 * 2;
            case(ShaderDataType::Float3): return 4 * 3;
            case(ShaderDataType::Float4): return 4 * 4;
            case(ShaderDataType::Mat3):   return 4 * 3 * 3;
            case(ShaderDataType::Mat4):   return 4 * 4 * 4;
            case(ShaderDataType::Int):    return 4;
            case(ShaderDataType::Int2):   return 4 * 2;
            case(ShaderDataType::Int3):   return 4 * 3;
            case(ShaderDataType::Int4):   return 4 * 4;
            case(ShaderDataType::Bool):   return 1;
            case(ShaderDataType::None):   return 0;
        }
        VGE_CORE_ASSERT(false, "Unknown data type!")
            return 0;
    }
    struct BufferElement {
        std::string name;
        ShaderDataType type;
        uint32_t offset;
        uint32_t size;
        bool normalized;

        BufferElement(ShaderDataType Type, const std::string& Name, bool normalized = false)
            :name(Name), type(Type),  offset(0), size(shaderDataTypeSize(type)), normalized(normalized)
        {}

        uint32_t getComponentCount() const{
            switch (type){
                case(ShaderDataType::Float):  return 1;
                case(ShaderDataType::Float2): return 2;
                case(ShaderDataType::Float3): return 3;
                case(ShaderDataType::Float4): return 4;
                case(ShaderDataType::Mat3):   return 3 * 3;
                case(ShaderDataType::Mat4):   return 4 * 4;
                case(ShaderDataType::Int):    return 1;
                case(ShaderDataType::Int2):   return 2;
                case(ShaderDataType::Int3):   return 3;
                case(ShaderDataType::Int4):   return 4;
                case(ShaderDataType::Bool):   return 1;
                case(ShaderDataType::None):   return 0;
            }
        VGE_CORE_ASSERT(false, "Unknown data type!")
            return 0;
        }
    };

    class BufferLayout{
        public:
            BufferLayout(const std::initializer_list<BufferElement>& elements)
                :m_Elements(elements){
                calculateOffsetsAndStride();
            }

            inline const std::vector<BufferElement>& getElements() const {return m_Elements;}

            inline uint32_t getStride() const {return m_Stride; }
 
            std::vector<BufferElement>::iterator begin() {return m_Elements.begin();}
            std::vector<BufferElement>::iterator end()   {return m_Elements.end();}
        private:
            std::vector<BufferElement> m_Elements;
            uint32_t m_Stride = 0;
            void calculateOffsetsAndStride(){
                uint32_t offset = 0;
                m_Stride = 0;
                for(auto& element: m_Elements){
                    element.offset = offset;
                    offset += element.size;
                    m_Stride += element.size;
                }
            }
    };

    class VertexBuffer {
        public:
            virtual ~VertexBuffer() {}

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual BufferLayout& getLayout() = 0;
            virtual void setLayout(const BufferLayout& layout) = 0;

            virtual uint32_t getCount() const = 0;

            static VertexBuffer* create(float* vertices, uint32_t size);
    };

    class IndexBuffer {
        public:
            virtual ~IndexBuffer() {}

            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual uint32_t getCount() const = 0;

            static IndexBuffer* create(uint32_t* vertices, uint32_t size);
    };
}


#endif // VIOLET_BUFFER_H
