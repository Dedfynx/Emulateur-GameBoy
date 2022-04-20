#include "Ram.hpp"

#include <iostream>

namespace DedOs
{
    Ram::Ram()
    {
    }
    Ram::~Ram()
    {
    }

    uint8_t Ram::wram_read(uint16_t address)
    {
        address -= 0xC000;
        if (address >= 0x2000)
        {
            std::cout << "Invalid WRAM addr " << address << std::endl;
        }
        return wram[address];
    }
    void Ram::wram_write(uint16_t address, uint8_t value)
    {
        address -= 0xC000;
        wram[address] = value;
    }

    uint8_t Ram::hram_read(uint16_t address)
    {
        address -= 0xFF80;
        return hram[address];
    }
    void Ram::hram_write(uint16_t address, uint8_t value)
    {
        address -= 0xFF80;
        hram[address] = value;
    }
}