#ifndef STDINTDEF_HPP_
#define STDINTDEF_HPP_

#ifdef USE_ARM_GCC
#include "/opt/gcc-arm-none-eabi/arm-none-eabi/include/sys/_stdint.h"
#endif

#ifndef USE_ARM_GCC
#include <cstdint>
#endif

#endif