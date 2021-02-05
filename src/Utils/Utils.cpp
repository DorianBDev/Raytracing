#include "Utils.h"

Endian endianness()
{
    std::uint16_t i = 0x1;
    std::uint8_t* ptr = (std::uint8_t*)&i;

    if (ptr[0] == 1)
        return Endian::LITTLE;
    else
        return Endian::BIG;
}