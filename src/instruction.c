
#include "core.h"

void    i_fetch(uint8_t *icode)
{
    uint8_t     offset;

    offset = 1;
    *icode = MEM[REG[PC]];
    if (LOOKUP[*icode].coding_byte)
    {
        ACB = MEM[REG[PC] + offset];
        offset++;
    }
    else
        ACB = 0;
    REG[VAL_P] = REG[PC] + offset;
}

void    i_decode(uint8_t    icode)
{
	static uint8_t	sizes[4] = {0, T_REG, 4, T_IND};
	uint8_t	acb;
    int32_t *ptr;
    uint8_t offset;

    acb = ACB;
    ptr = REG + RDI;
    bzero(ptr, sizeof(int32_t)  * 3);
	while (acb >>= 2)
	{   
        if (LOOKUP[icode].truncate && (acb & 0b11) == 0b10)
            offset = 2;
        else
            offset = sizes[acb & 0b11];
        memcpy(ptr, &MEM[REG[VAL_P]], offset); 
        REG[VAL_P] += offset;
        ptr++;
    }
}

void    i_excute(uint8_t icode)
{
    
}

void    i_instruction_cycle()
{
    uint8_t     icode;

    i_fetch(&icode);
    i_decode(icode);
    i_excute(icode);
    if (CPU_STATE.write_back)
        WRITE_BACK(R0, 123);
    PC_UPDATE(REG[PC], REG[VAL_P]);
}