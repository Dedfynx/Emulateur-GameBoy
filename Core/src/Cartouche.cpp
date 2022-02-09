#include "Cartouche.hpp"

#include <iostream>

namespace dedOs
{
    Cartouche::Cartouche()
    {
    }
    Cartouche::~Cartouche()
    {
    }

    std::string Cartouche::nameLic()
    {

        //New lic code if lic_code == 0x33
        if (header->lic_code == 0x33)
        {
            //newliccode >> 4
            uint8_t newLicCode = ((header->new_lic_code >> 8) - 0x30) + 16 * ((header->new_lic_code & 0xff) - 0x30);
            return NEW_LIC_NAMES[newLicCode];
        }
        return LIC_NAMES[header->lic_code];
    }

    bool Cartouche::load(std::string filePath)
    {

        std::ifstream file(filePath, std::ios::binary);
        if (file.is_open())
        {
            file.seekg(0, file.end);
            size = file.tellg();

            data = new uint8_t[size];

            file.clear();
            file.seekg(0);
            file.read((char *)data, size);
            file.close();

            header = (romHeader *)(data + 0x100);
            header->title[15] = 0;

            std::cout << "Cartouche chargée " << std::endl;
            std::cout << "Titre      : " << header->title << std::endl;
            std::cout << "Type       : " << std::hex << (int)header->type << std::endl;
            std::cout << "ROM size   : " << std::hex << (int)header->rom_size << std::endl;
            std::cout << "RAM size   : " << std::hex << (int)header->ram_size << std::endl;
            std::cout << "LIC code   : " << std::hex << (int)header->lic_code << std::endl;
            std::cout << "LIC Name   : " << nameLic() << std::endl;
            std::cout << "ROM vers   : " << std::hex << (int)header->version << std::endl;

            uint16_t x = 0;
            for (uint16_t i = 0x0134; i <= 0x014C; i++)
            {
                x = x - data[i] - 1;
            };

            std::cout << "Checksum :" << std::hex << (int)header->checksum << " & " << (int)data[0x014D] << " = " << ((x & data[0x014D]) ? "PASSED" : "FAILED") << std::endl;

            return true;
        }
        return false;
    }

    uint8_t Cartouche::read(uint16_t address)
    {
        return data[address];
    }
    void Cartouche::write(uint16_t address, uint8_t value)
    {
        std::cout << "Pas implémenté" << std::endl;
        std::exit(EXIT_FAILURE);
    }
}