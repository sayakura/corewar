
#include "core.h"

void        p_process_loop()
{
    t_process *p;

    p = CORE.process;
    while (p)
    {
        p = p->next;
    }    
}

void        p_fork(uint8_t *pc, int32_t id, bool before)
{
    t_process *p;
    t_process *tmp;

    p = malloc(sizeof(t_process));
    bzero(&p->state, sizeof(t_cpu));
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
