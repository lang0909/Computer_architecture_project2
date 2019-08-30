/***************************************************************/
/*                                                             */
/*   MIPS-32 Instruction Level Simulator                       */
/*                                                             */
/*   SCE212 Ajou University                                    */
/*   run.c                                                     */
/*   Adapted from CS311@KAIST                                  */
/*                                                             */
/***************************************************************/

#include <stdio.h>

#include "util.h"
#include "run.h"

/***************************************************************/
/*                                                             */
/* Procedure: get_inst_info                                    */
/*                                                             */
/* Purpose: Read insturction information                       */
/*                                                             */
/***************************************************************/
instruction* get_inst_info(uint32_t pc)
{
    return &INST_INFO[(pc - MEM_TEXT_START) >> 2];
}

/***************************************************************/
/*                                                             */
/* Procedure: process_instruction                              */
/*                                                             */
/* Purpose: Process one instrction                             */
/*                                                             */
/***************************************************************/
void process_instruction()
{
	/** Implement this function */
    if(INST_INFO[INSTRUCTION_COUNT].value!=1)
    {
        RUN_BIT = 0;
        return;
    }
    switch(INST_INFO[INSTRUCTION_COUNT].opcode)
    {
        case 0:
            if(INST_INFO[INSTRUCTION_COUNT].func_code==33)
            {
                CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.r.rd] 
                = CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rs] + CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rt];
                CURRENT_STATE.PC = MEM_TEXT_START + INSTRUCTION_COUNT*4+4;
                break;
            }
            if(INST_INFO[INSTRUCTION_COUNT].func_code==36)
            {
                CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.r.rd] 
                = CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rs] & CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rt];
                CURRENT_STATE.PC = MEM_TEXT_START + INSTRUCTION_COUNT*4+4;
                break;
            }
            if(INST_INFO[INSTRUCTION_COUNT].func_code==39)
            {
                CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.r.rd] 
                = ~(CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rs] | CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rt]);
                CURRENT_STATE.PC = MEM_TEXT_START + INSTRUCTION_COUNT*4+4;
                break;                
            }
            if(INST_INFO[INSTRUCTION_COUNT].func_code==37)
            {
                CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.r.rd] 
                = (CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rs] | CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rt]);
                CURRENT_STATE.PC = MEM_TEXT_START + INSTRUCTION_COUNT*4+4;
                break;   
            }
            if(INST_INFO[INSTRUCTION_COUNT].func_code==43)
            {
                if(CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rs]<CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rt])
                {
                    CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.r.rd]=1;
                }
                else
                {
                    CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.r.rd]=0;
                }
                CURRENT_STATE.PC = MEM_TEXT_START + INSTRUCTION_COUNT*4+4;
                break;
            }
            if(INST_INFO[INSTRUCTION_COUNT].func_code==0)
            {
                CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.r.rd]
                = CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rt] << INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.r.shamt;
                CURRENT_STATE.PC = MEM_TEXT_START + INSTRUCTION_COUNT*4+4;
                break;
            }
            if(INST_INFO[INSTRUCTION_COUNT].func_code==2)
            {
                CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.r.rd]
                = CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rt] >> INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.r.shamt;
                CURRENT_STATE.PC = MEM_TEXT_START + INSTRUCTION_COUNT*4+4;
                break;
            }
            if(INST_INFO[INSTRUCTION_COUNT].func_code==35)
            {
                CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.r.rd] 
                = CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rs] - CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rt];
                CURRENT_STATE.PC = MEM_TEXT_START + INSTRUCTION_COUNT*4+4;
                break;
            }
            if(INST_INFO[INSTRUCTION_COUNT].func_code==8) //need change
            {
                INSTRUCTION_COUNT 
                = (CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rs]-MEM_TEXT_START-4)/4;
                CURRENT_STATE.PC = MEM_TEXT_START + INSTRUCTION_COUNT*4+4;
                break;
            }

        case 9:
            CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rt]
            = CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rs] + INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.imm;
            CURRENT_STATE.PC = MEM_TEXT_START + INSTRUCTION_COUNT*4+4;
            break;

        case 12:
            CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rt]
            = CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rs] & INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.imm;
            CURRENT_STATE.PC = MEM_TEXT_START + INSTRUCTION_COUNT*4+4;
            break;

        case 15:
            CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rt]
            = INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.imm<<16;
            CURRENT_STATE.PC = MEM_TEXT_START + INSTRUCTION_COUNT*4+4;
            break;

        case 13:
            CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rt]
            = CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rs] | INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.imm;
            CURRENT_STATE.PC = MEM_TEXT_START + INSTRUCTION_COUNT*4+4;
            break;

        case 11:
            if(CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rs]<INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.imm)
            {
                CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rt]=1;
            }
            else
            {
                CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rt]=0;
            }
            CURRENT_STATE.PC = MEM_TEXT_START + INSTRUCTION_COUNT*4+4;
            break;

        case 35:
            CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rt]
            = mem_read_32(CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rs]+INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.imm);
            CURRENT_STATE.PC = MEM_TEXT_START + INSTRUCTION_COUNT*4+4;
            break;

        case 43:
            mem_write_32(CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rs]
            +INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.imm,CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rt]);
            CURRENT_STATE.PC = MEM_TEXT_START + INSTRUCTION_COUNT*4+4;
            break;

        case 4:
            if(CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rs]==CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rt])
            {
                INSTRUCTION_COUNT = INSTRUCTION_COUNT + INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.imm;
                CURRENT_STATE.PC = CURRENT_STATE.PC + INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.imm*4;
            }
            else
            {
                CURRENT_STATE.PC = MEM_TEXT_START + INSTRUCTION_COUNT*4+4;
            }
            break;

        case 5:
            if(CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rs]!=CURRENT_STATE.REGS[INST_INFO[INSTRUCTION_COUNT].r_t.r_i.rt])
            {
                INSTRUCTION_COUNT = INSTRUCTION_COUNT + INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.imm;
                CURRENT_STATE.PC = CURRENT_STATE.PC + INST_INFO[INSTRUCTION_COUNT].r_t.r_i.r_i.imm*4;    
            }
            else
            {
                CURRENT_STATE.PC = MEM_TEXT_START + INSTRUCTION_COUNT*4+4;
            }
            break;

        case 2:
            CURRENT_STATE.PC = INST_INFO[INSTRUCTION_COUNT].r_t.target + 4;
            INSTRUCTION_COUNT = (INST_INFO[INSTRUCTION_COUNT].r_t.target*4 - MEM_TEXT_START)/4;
            break;

        case 3:
            CURRENT_STATE.REGS[31] = (MEM_TEXT_START + INSTRUCTION_COUNT*4+8);
            CURRENT_STATE.PC = MEM_TEXT_START + INSTRUCTION_COUNT*4;
            INSTRUCTION_COUNT = (INST_INFO[INSTRUCTION_COUNT].r_t.target*4 - MEM_TEXT_START)/4-1;
            break;
    }
}
