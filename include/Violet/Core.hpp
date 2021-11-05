#ifndef __VIOLET_CORE_HPP_
#define __VIOLET_CORE_HPP_

#ifdef VGE_PLATFORM_LINUX
    #define VIOLET_API gnu::visibility("default")
#elif VGE_PLATFORM_WINDOWS
    #ifdef VGE_BUILD_DLL
        #define VIOLET_API __declspec(dllexport)
    #else
        #define VIOLET_API __declspec(dllimport)
    #endif
#else
    #error Application only supports Linux builds right now!
#endif //VGE_PLATFORM

#define BIT(x) (1 << x)

#ifdef VGE_ENABLE_ASSERTS
    #define VGE_ASSERT(x, ...) { if(!(x)) { VGE_ERROR("Assertion failed: {0}", __VA_ARGS__); __builtin_trap();}}
    #define VGE_CORE_ASSERT(x, ...) { if(!(x)) { VGE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __builtin_trap();}}
#else
    #define VGE_ASSERT(x, ...)
    #define VGE_CORE_ASSERT(x, ...)
#endif

#define VGE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#include <memory>
namespace Violet{
    template<typename T>
    using Scoped = std::unique_ptr<T>;

    template<typename T>
    using Reference = std::shared_ptr<T>;

}

#endif // __VIOLET_CORE_HPP_
