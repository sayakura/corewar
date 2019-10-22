
#include "core.h"

void    i_fetch()
{
    uint8_t icode;
    uint8_t acb;

    icode = MEM[PC];
    acb = MEM[PC + 1];
}

void    i_decode()
{

}

void    i_excute()
{

}

void    i_instruction_cycle()
{
    uint32_t    val_p;
    
    val_p = 0;
    if (CPU_STATE.write_back)
        WRITE_BACK(R1, 123);
    PC_UPDATE(PC, val_p);
}