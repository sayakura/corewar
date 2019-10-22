
#include "core.h"


void        p_context_switch(bool op, t_process *p)
{
    if (op)
        memcpy(&CPU_STATE, &p->state, sizeof(t_cpu));
    else
        memcpy(&p->state, &CPU_STATE, sizeof(t_cpu));
}

void        p_process_loop()
{
    t_process *p;

    p = CORE.process;
    while (p)
    {
        p_context_switch(PUSH, p);
        i_instruction_cycle();
        p_context_switch(POP, p);
        p = p->next;
    }    
}

void        p_fork(uint32_t pc, int32_t id, bool before)
{
    t_process *p;
    t_process *tmp;

    p = malloc(sizeof(t_process));
    bzero(p, sizeof(t_process));
    p->state.registers[1] = id;
    p->state.pc = pc;
    p->champ_id = id;
    p->next = NULL;
    CORE.nprocess++;
    if (before)
    {
        p->next = CORE.process;
        CORE.process = p;
    }
    else 
    {
        tmp = CORE.process;
        if (!tmp)
            CORE.process = p;
        else
        {
            while (tmp->next)
                tmp = tmp->next;
            tmp->next = p;
        }
    }
}
