#include "Cpu.hpp"
#include "Bus.hpp"

#include <bitset>

namespace DedOs
{
    Cpu::Cpu()
    {
        halted = false;
        running = true;

        regs.pc = 0x100;
        regs.a = 0x01;
#pragma region InstructionSet
        // Todo: Tout l'instruction set
        lookup.resize(0x100);
        lookup[0x00] = {"NOP ", procNop, A_IMP};

        lookup[0x01] = {"LD  ", procLd, A_R_D16, R_BC};
        lookup[0x02] = {"LD  ", procLd, A_MR_R, R_BC, R_A};
        lookup[0x03] = {"INC ", procInc, A_R, R_BC};
        lookup[0x04] = {"INC ", procInc, A_R, R_B};
        lookup[0x05] = {"DEC ", procDec, A_R, R_B};
        lookup[0x06] = {"LD  ", procLd, A_R_D8, R_B};
        lookup[0x08] = {"LD  ", procLd, A_A16_R, R_NONE, R_SP};
        lookup[0x0A] = {"LD  ", procLd, A_R_MR, R_A, R_BC};
        lookup[0x0E] = {"LD  ", procLd, A_R_D8, R_C};

        lookup[0x11] = {"LD  ", procLd, A_R_D16, R_DE};
        lookup[0x12] = {"LD  ", procLd, A_MR_R, R_DE, R_A};
        lookup[0x13] = {"INC ", procInc, A_R, R_DE};
        lookup[0x14] = {"INC ", procInc, A_R, R_D};
        lookup[0x15] = {"DEC ", procDec, A_R, R_D};
        lookup[0x16] = {"LD  ", procLd, A_R_D8, R_D};
        lookup[0x1A] = {"LD  ", procLd, A_R_MR, R_A, R_DE};
        lookup[0x1E] = {"LD  ", procLd, A_R_D8, R_E};

        lookup[0x21] = {"LD  ", procLd, A_R_D16, R_HL};
        lookup[0x22] = {"LD  ", procLd, A_HLI_R, R_HL, R_A};
        lookup[0x23] = {"INC ", procInc, A_R, R_HL};
        lookup[0x24] = {"INC ", procInc, A_R, R_H};
        lookup[0x25] = {"DEC ", procDec, A_R, R_H};
        lookup[0x26] = {"LD  ", procLd, A_R_D8, R_H};
        lookup[0x2A] = {"LD  ", procLd, A_R_HLI, R_A, R_HL};
        lookup[0x2E] = {"LD  ", procLd, A_R_D8, R_L};

        lookup[0x31] = {"LD  ", procLd, A_R_D16, R_SP};
        lookup[0x32] = {"LD  ", procLd, A_HLD_R, R_HL, R_A};
        lookup[0x33] = {"INC ", procInc, A_R, R_SP};
        lookup[0x34] = {"INC ", procInc, A_MR, R_HL}; // A VERIF
        lookup[0x35] = {"DEC ", procDec, A_MR, R_HL}; // A VERIF
        lookup[0x36] = {"LD  ", procLd, A_MR_D8, R_HL};
        lookup[0x3A] = {"LD  ", procLd, A_R_HLD, R_A, R_HL};
        lookup[0x3E] = {"LD  ", procLd, A_R_D8, R_A};

        lookup[0x40] = {"LD  ", procLd, A_R_R, R_B, R_B};
        lookup[0x41] = {"LD  ", procLd, A_R_R, R_B, R_C};
        lookup[0x42] = {"LD  ", procLd, A_R_R, R_B, R_D};
        lookup[0x43] = {"LD  ", procLd, A_R_R, R_B, R_E};
        lookup[0x44] = {"LD  ", procLd, A_R_R, R_B, R_H};
        lookup[0x45] = {"LD  ", procLd, A_R_R, R_B, R_L};
        lookup[0x46] = {"LD  ", procLd, A_R_MR, R_B, R_HL};
        lookup[0x47] = {"LD  ", procLd, A_R_R, R_B, R_A};
        lookup[0x48] = {"LD  ", procLd, A_R_R, R_C, R_B};
        lookup[0x49] = {"LD  ", procLd, A_R_R, R_C, R_C};
        lookup[0x4A] = {"LD  ", procLd, A_R_R, R_C, R_D};
        lookup[0x4B] = {"LD  ", procLd, A_R_R, R_C, R_E};
        lookup[0x4C] = {"LD  ", procLd, A_R_R, R_C, R_H};
        lookup[0x4D] = {"LD  ", procLd, A_R_R, R_C, R_L};
        lookup[0x4E] = {"LD  ", procLd, A_R_MR, R_C, R_HL};
        lookup[0x4F] = {"LD  ", procLd, A_R_R, R_C, R_A};

        lookup[0x50] = {"LD  ", procLd, A_R_R, R_D, R_B};
        lookup[0x51] = {"LD  ", procLd, A_R_R, R_D, R_C};
        lookup[0x52] = {"LD  ", procLd, A_R_R, R_D, R_D};
        lookup[0x53] = {"LD  ", procLd, A_R_R, R_D, R_E};
        lookup[0x54] = {"LD  ", procLd, A_R_R, R_D, R_H};
        lookup[0x55] = {"LD  ", procLd, A_R_R, R_D, R_L};
        lookup[0x56] = {"LD  ", procLd, A_R_MR, R_D, R_HL}; // A VERIF
        lookup[0x57] = {"LD  ", procLd, A_R_R, R_D, R_A};
        lookup[0x58] = {"LD  ", procLd, A_R_R, R_E, R_B};
        lookup[0x59] = {"LD  ", procLd, A_R_R, R_E, R_C};
        lookup[0x5A] = {"LD  ", procLd, A_R_R, R_E, R_D};
        lookup[0x5B] = {"LD  ", procLd, A_R_R, R_E, R_E};
        lookup[0x5C] = {"LD  ", procLd, A_R_R, R_E, R_H};
        lookup[0x5D] = {"LD  ", procLd, A_R_R, R_E, R_L};
        lookup[0x5E] = {"LD  ", procLd, A_R_MR, R_E, R_HL};
        lookup[0x5F] = {"LD  ", procLd, A_R_R, R_E, R_A};

        lookup[0x60] = {"LD  ", procLd, A_R_R, R_H, R_B};
        lookup[0x61] = {"LD  ", procLd, A_R_R, R_H, R_C};
        lookup[0x62] = {"LD  ", procLd, A_R_R, R_H, R_D};
        lookup[0x63] = {"LD  ", procLd, A_R_R, R_H, R_E};
        lookup[0x64] = {"LD  ", procLd, A_R_R, R_H, R_H};
        lookup[0x65] = {"LD  ", procLd, A_R_R, R_H, R_L};
        lookup[0x66] = {"LD  ", procLd, A_R_MR, R_H, R_HL};
        lookup[0x67] = {"LD  ", procLd, A_R_R, R_H, R_A};
        lookup[0x68] = {"LD  ", procLd, A_R_R, R_L, R_B};
        lookup[0x69] = {"LD  ", procLd, A_R_R, R_L, R_C};
        lookup[0x6A] = {"LD  ", procLd, A_R_R, R_L, R_D};
        lookup[0x6B] = {"LD  ", procLd, A_R_R, R_L, R_E};
        lookup[0x6C] = {"LD  ", procLd, A_R_R, R_L, R_H};
        lookup[0x6D] = {"LD  ", procLd, A_R_R, R_L, R_L};
        lookup[0x6E] = {"LD  ", procLd, A_R_MR, R_L, R_HL};
        lookup[0x6F] = {"LD  ", procLd, A_R_R, R_L, R_A};

        lookup[0x70] = {"LD  ", procLd, A_MR_R, R_HL, R_B};
        lookup[0x71] = {"LD  ", procLd, A_MR_R, R_HL, R_C};
        lookup[0x72] = {"LD  ", procLd, A_MR_R, R_HL, R_D};
        lookup[0x73] = {"LD  ", procLd, A_MR_R, R_HL, R_E};
        lookup[0x74] = {"LD  ", procLd, A_MR_R, R_HL, R_H};
        lookup[0x75] = {"LD  ", procLd, A_MR_R, R_HL, R_L};
        lookup[0x76] = {"HALT", procHalt}; // A VERIF
        lookup[0x77] = {"LD  ", procLd, A_R_R, R_HL, R_A};
        lookup[0x78] = {"LD  ", procLd, A_R_R, R_A, R_B};
        lookup[0x79] = {"LD  ", procLd, A_R_R, R_A, R_C};
        lookup[0x7A] = {"LD  ", procLd, A_R_R, R_A, R_D};
        lookup[0x7B] = {"LD  ", procLd, A_R_R, R_A, R_E};
        lookup[0x7C] = {"LD  ", procLd, A_R_R, R_A, R_H};
        lookup[0x7D] = {"LD  ", procLd, A_R_R, R_A, R_L};
        lookup[0x7E] = {"LD  ", procLd, A_R_MR, R_A, R_HL};
        lookup[0x7F] = {"LD  ", procLd, A_R_R, R_A, R_A};

#pragma region XOR
        lookup[0xA8] = {"XOR ", procXor, A_R, R_B};
        lookup[0xA9] = {"XOR ", procXor, A_R, R_C};
        lookup[0xAA] = {"XOR ", procXor, A_R, R_D};
        lookup[0xAB] = {"XOR ", procXor, A_R, R_E};
        lookup[0xAC] = {"XOR ", procXor, A_R, R_H};
        lookup[0xAD] = {"XOR ", procXor, A_R, R_L};
        lookup[0xAE] = {"XOR ", procXor, A_R, R_HL}; //
        lookup[0xAF] = {"XOR ", procXor, A_R, R_A};
#pragma endregion XOR
        lookup[0xC3] = {"JP  ", procJp, A_D16};

        lookup[0xE0] = {"LDH ", procLdh, A_A8_R, R_NONE, R_A};
        lookup[0xE2] = {"LD  ", procLd, A_MR_R, R_C, R_A};
        lookup[0xEA] = {"LD  ", procLd, A_A16_R, R_NONE, R_A};

        lookup[0xF0] = {"LDH ", procLdh, A_R_A8, R_A};
        lookup[0xF2] = {"LD  ", procLd, A_R_MR, R_A, R_C};
        lookup[0xF3] = {"DI  ", procDi, A_IMP};
        lookup[0xFA] = {"LD  ", procLd, A_R_A16, R_A};
#pragma endregion InstructionSet
    }
    Cpu::~Cpu()
    {
    }

    void Cpu::fetch()
    {
        // OpCode
        cOpcode = bus->busRead(regs.pc++);
        // Instruction
        curInst = lookup[cOpcode];
        memDest = 0;
        isMem = false;

        // Address Mode
        switch (curInst.aMode)
        {
        case A_IMP:
            return;
        case A_R:
            fetchData = readReg(curInst.reg1);
            return;
        case A_R_R:
            fetchData = readReg(curInst.reg2);
            return;

        case A_R_D8:
        case A_R_A8:
        case A_HL_SPR:
        case A_D8:
            fetchData = bus->busRead(regs.pc);
            emuCycle(1);
            regs.pc++;
            return;

        case A_A8_R:
            memDest = bus->busRead(regs.pc) | 0xFF00;
            isMem = true;
            emuCycle(1);
            regs.pc++;
            return;
        case A_R_D16: // Same
        case A_D16:
        {
            uint16_t lo = bus->busRead(regs.pc);
            emuCycle(1);

            uint16_t hi = bus->busRead(regs.pc + 1);
            emuCycle(1);

            fetchData = lo | (hi << 8);
            regs.pc += 2;
        }
            return;

        case A_MR:
            memDest = readReg(curInst.reg1);
            isMem = true;
            fetchData = bus->busRead(curInst.reg1);
            emuCycle(1);
            return;
        case A_MR_R:
            fetchData = readReg(curInst.reg2);
            memDest = readReg(curInst.reg1);
            isMem = true;

            if (curInst.reg1 == R_C)
            { // C case
                memDest |= 0xFF00;
            }
            return;

        case A_MR_D8:
            fetchData = bus->busRead(regs.pc);
            emuCycle(1);
            regs.pc++;
            memDest = readReg(curInst.reg1);
            isMem = true;

            return;
        case A_R_MR:
        {
            uint16_t addr = readReg(curInst.reg2);
            if (curInst.reg2 == R_C)
            { // C case
                memDest |= 0xFF00;
            }

            fetchData = bus->busRead(addr);
            emuCycle(1);
        }
            return;

        case A_R_HLI:
            fetchData = bus->busRead(curInst.reg2);
            emuCycle(1);
            setReg(R_HL, readReg(R_HL) + 1);
            return;
        case A_R_HLD:
            fetchData = bus->busRead(curInst.reg2);
            emuCycle(1);
            setReg(R_HL, readReg(R_HL) - 1);
            return;

        case A_HLI_R:
            fetchData = readReg(curInst.reg2);
            memDest = readReg(curInst.reg1);
            isMem = true;
            setReg(R_HL, readReg(R_HL) + 1);
            return;
        case A_HLD_R:
            fetchData = readReg(curInst.reg2);
            memDest = readReg(curInst.reg1);
            isMem = true;
            setReg(R_HL, readReg(R_HL) - 1);
            return;

        case A_A16_R:
        case A_D16_R:
        {
            uint16_t lo = bus->busRead(regs.pc);
            emuCycle(1);

            uint16_t hi = bus->busRead(regs.pc + 1);
            emuCycle(1);

            memDest = lo | (hi << 8);
            isMem = true;
            regs.pc += 2;
            fetchData = readReg(curInst.reg2);
        }
            return;

        case A_R_A16:
        {
            uint16_t lo = bus->busRead(regs.pc);
            emuCycle(1);

            uint16_t hi = bus->busRead(regs.pc + 1);
            emuCycle(1);

            uint16_t addr = lo | (hi << 8);
            isMem = true;
            regs.pc += 2;
            fetchData = bus->busRead(addr);
        }
            return;

        default:
            std::cout << std::hex << "Unknown Add Mode : " << curInst.aMode << "(" << (int)cOpcode << ")" << std::endl;
            std::exit(0);
            return;
        }
    }

    void Cpu::execute()
    {
        if (curInst.operate == nullptr)
        {
            std::cout << "Not implemented" << std::endl;
            std::exit(0);
        }
        (this->*curInst.operate)();
    }

    bool Cpu::step()
    {
        if (!halted)
        {
            uint16_t dPc = regs.pc; // Debug pc before fetching
            fetch();
            std::bitset<8> w(regs.f);
            std::cout << "PC: " << dPc << " Instruction : " << curInst.name << " Op: " << (int)cOpcode << " A:" << (int)regs.a << " B:" << (int)regs.b << " C:" << (int)regs.c << " D:" << (int)regs.d << " E:" << (int)regs.e << " H:" << (int)regs.h << " L:" << (int)regs.l << " F:" << w << std::endl;
            execute();
        }

        return true;
    }

    void Cpu::emuCycle(int nb)
    {
        // Wait
    }

    uint16_t reverse(uint16_t n)
    {
        return ((n & 0xFF00) >> 8) | ((n & 0x00FF) << 8);
    }

    uint16_t Cpu::readReg(RegType r)
    {
        switch (r)
        {
        case R_NONE:
            return 0;
        case R_A:
            return regs.a;
        case R_F:
            return regs.f;
        case R_B:
            return regs.b;
        case R_C:
            return regs.c;
        case R_D:
            return regs.d;
        case R_E:
            return regs.e;
        case R_H:
            return regs.h;
        case R_L:
            return regs.l;
        //
        case R_AF:
            return reverse((uint16_t)regs.a);
        case R_BC:
            return reverse((uint16_t)regs.b);
        case R_DE:
            return reverse((uint16_t)regs.d);
        case R_HL:
            return reverse((uint16_t)regs.h);
        case R_SP:
            return regs.sp;
        case R_PC:
            return regs.pc;
        }
        return 0;
    };

    void Cpu::setReg(RegType r, uint16_t val)
    {
        switch (r)
        {
        case R_A:
            regs.a = val & 0xFF;
            break;
        case R_F:
            regs.f = val & 0xFF;
            break;
        case R_B:
            regs.b = val & 0xFF;
            break;
        case R_C:
        {
            regs.c = val & 0xFF;
        }
        break;
        case R_D:
            regs.d = val & 0xFF;
            break;
        case R_E:
            regs.e = val & 0xFF;
            break;
        case R_H:
            regs.h = val & 0xFF;
            break;
        case R_L:
            regs.l = val & 0xFF;
            break;

        case R_AF:
            *((uint16_t *)&regs.a) = reverse(val);
            break;
        case R_BC:
            *((uint16_t *)&regs.b) = reverse(val);
            break;
        case R_DE:
            *((uint16_t *)&regs.d) = reverse(val);
            break;
        case R_HL:
        {
            *((uint16_t *)&regs.h) = reverse(val);
            break;
        }

        case R_PC:
            regs.pc = val;
            break;
        case R_SP:
            regs.sp = val;
            break;
        case R_NONE:
            break;
        }
    }

    void Cpu::push(uint8_t value){
        regs.sp--;
        bus->busWrite(regs.sp, value);
    }
    void Cpu::push16(uint16_t value){
        //à tester avec busWrite16
        push((value >> 8) & 0xFF);
        push(value & 0xFF);
    }
    uint8_t Cpu::pop(){
        return bus->busRead(regs.sp++);
    }
    uint16_t Cpu::pop16(){
        uint16_t lo = pop();
        uint16_t hi = pop();

        return lo | (hi << 8);
    }

    uint8_t Cpu::readRegIE()
    {
        return ieRegister;
    }
    void Cpu::setRegIE(uint8_t val)
    {
        ieRegister = val;
    }

    bool Cpu::checkCondition()
    {
        bool z = CPU_FLAG_Z;
        bool c = CPU_FLAG_C;

        switch (curInst.cond)
        {
        case CT_NONE:
            return true;
        case CT_C:
            return c;
        case CT_Z:
            return z;
        case CT_NZ:
            return !z;
        case CT_NC:
            return !c;
        default:
            break;
        }
        return false;
    }

    void Cpu::setFlags(uint8_t z, uint8_t n, uint8_t h, uint8_t c)
    {
        if (z != -1)
        {
            BIT_SET(regs.f, 7, z);
        }
        if (n != -1)
        {
            BIT_SET(regs.f, 6, n);
        }
        if (h != -1)
        {
            BIT_SET(regs.f, 5, h);
        }
        if (c != -1)
        {
            BIT_SET(regs.f, 4, c);
        }
    }

    void Cpu::procNone()
    {
        std::cout << "INSTRUCTION INVALIDE" << std::endl;
        std::exit(0);
    }

    void Cpu::procNop()
    {
        // std::cout << "Nop" << std::endl;
    }
    void Cpu::procLd()
    {
        if (isMem)
        {
            if (curInst.reg2 >= R_AF)
            { // If reg2 16bits
                emuCycle(1);
                bus->busWrite16(memDest, fetchData);
            }
            else
            {
                bus->busWrite(memDest, fetchData);
            }
            return;
        }

        if (curInst.aMode == A_HL_SPR)
        {
            uint8_t hFlag = ((readReg(curInst.reg2) & 0xF) + (fetchData & 0xF)) >= 0x10;
            uint8_t cFlag = ((readReg(curInst.reg2) & 0xFF) + (fetchData & 0xFF)) >= 0x100;

            setFlags(0, 0, hFlag, cFlag);
            setReg(curInst.reg1, readReg(curInst.reg2) + (char)fetchData);

            return;
        }

        setReg(curInst.reg1, fetchData);
    }

    void Cpu::procLdh()
    {
        if (curInst.reg1 == R_A)
        {
            setReg(curInst.reg1, bus->busRead(0xFF00 | fetchData));
        }
        else
        {
            bus->busWrite(0xFF00 | fetchData, regs.a);
        }

        emuCycle(1);
    }
    void Cpu::procJp()
    {
        if (checkCondition())
        {
            regs.pc = fetchData;
            // std::cout << "Jp to " << (int)regs.pc << std::endl;
            emuCycle(1);
        }
    }

    void Cpu::procDi() // Disable Interupt
    {
        IME = false;
    }
    void Cpu::procXor()
    {
        regs.a ^= fetchData & 0xFF;
        setFlags(regs.a == 0, 0, 0, 0);
    }

    void Cpu::procInc()
    {
        // TODO ....
    }
    void Cpu::procDec()
    {
        // TODO ...
    }

    void Cpu::procHalt()
    {
        // TODO ...
    }
}