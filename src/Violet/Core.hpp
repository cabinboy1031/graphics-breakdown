#ifndef __VIOLET_CORE_HPP_
#define __VIOLET_CORE_HPP_

#ifdef VGE_PLATFORM_LINUX
#define VIOLET_API __attribute__((visibility("default")))

#elif VGE_PLATFORM_WINDOWS
#error Application doesnt support windows at the moment! Try linux.

#else
#error Application only supports Linux builds right now!

#endif //VGE_PLATFORM
#endif // __VIOLET_CORE_HPP_
