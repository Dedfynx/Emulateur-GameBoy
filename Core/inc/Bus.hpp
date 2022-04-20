#pragma once

#include <memory>

#include "Cartouche.hpp"
#include "Cpu.hpp"
#include "Common.hpp"
#include "Ram.hpp"

namespace DedOs
{
    class Bus
    {
    public:
        Bus();
        ~Bus();

        void loadCartouche(const std::shared_ptr<Cartouche>& c);

        uint8_t busRead(uint16_t address);
        void busWrite(uint16_t address, uint8_t value);

        uint8_t busRead16(uint16_t address);
        void busWrite16(uint16_t address, uint16_t value);

        Cpu cpu;

    private:
        std::shared_ptr<Cartouche> cartouche;
        Ram ram;
    };
}
