#include "Bus.hpp"

namespace dedOs
{
    // 0x0000 - 0x3FFF : ROM Bank 0
    // 0x4000 - 0x7FFF : ROM Bank 1 - Switchable
    // 0x8000 - 0x97FF : CHR RAM
    // 0x9800 - 0x9BFF : BG Map 1
    // 0x9C00 - 0x9FFF : BG Map 2
    // 0xA000 - 0xBFFF : Cartridge RAM
    // 0xC000 - 0xCFFF : RAM Bank 0
    // 0xD000 - 0xDFFF : RAM Bank 1-7 - switchable - Color only
    // 0xE000 - 0xFDFF : Reserved - Echo RAM
    // 0xFE00 - 0xFE9F : Object Attribute Memory
    // 0xFEA0 - 0xFEFF : Reserved - Unusable
    // 0xFF00 - 0xFF7F : I/O Registers
    // 0xFF80 - 0xFFFE : Zero Page

    Bus::Bus()
    {
        cpu.loadBus(this);
    }

    Bus::~Bus()
    {
    }

    void Bus::loadCartouche(const std::shared_ptr<Cartouche> &c)
    {
        cartouche = c;
    }

    uint8_t Bus::busRead(uint16_t address)
    {
        //gere que la rom

        if (address < 0x8000)
        {
            uint8_t ret = cartouche->read(address);
            return ret;
        }
        std::cout << "Pas implémenté" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    void Bus::busWrite(uint16_t address, uint8_t value)
    {
        //gere que la rom
        if (address < 0x8000)
        {
            cartouche->write(address, value);
            return;
        }
        std::cout << "Pas implémenté" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    //16 bit operations

    uint8_t Bus::busRead16(uint16_t address)
    {
        uint16_t lo = busRead(address);
        uint16_t hi = busRead(address + 1);

        return lo | (hi << 8);
    }
    void Bus::busWrite16(uint16_t address, uint16_t value)
    {
        busWrite(address + 1, (value >> 8) & 0xFF);
        busWrite(address, value & 0xFF);
    }
} // namespace dedOs
