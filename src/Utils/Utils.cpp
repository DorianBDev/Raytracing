#include "Utils.h"

Endian endianness()
{
    std::uint16_t i = 0x1;
    auto* ptr = (std::uint8_t*)&i; // NOLINT

    Endian res;
    if (ptr[0] == 1)
        res = Endian::LITTLE;
    else
        res = Endian::BIG;

    return res;
}