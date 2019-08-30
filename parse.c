/***************************************************************/
/*                                                             */
/*   MIPS-32 Instruction Level Simulator                       */
/*                                                             */
/*   SCE212 Ajou University                                    */
/*   parse.c                                                   */
/*   Adapted from CS311@KAIST                                  */
/*                                                             */
/***************************************************************/

#include <stdio.h>

#include "util.h"
#include "parse.h"

int text_size;
int data_size;

instruction parsing_instr(const char *buffer, const int index)
{
    instruction instr;
	/** Implement this function */
    char str1[7]={0,};
    char str2[6]={0,};
    char str3[17]={0,};
    char str4[27]={0,};
    char str5[33]={0,};
    int a;
    int b;
    for(int i=0;i<32;i++)
    {
        str5[i]=buffer[i];
    }
    b=fromBinary(str5);
    mem_write_32(MEM_TEXT_START+index,b);
    for(int i=0;i<6;i++)
    {
        str1[i]=str5[i];
    }
    a=fromBinary(str1);
    switch(a)
    {
        case 9:
        case 12:
        case 15:
        case 13:
        case 11:
        case 35:
        case 43:
        case 4:
        case 5:
            instr.opcode = a;
            for(int i=6;i<11;i++)
            {
                str2[i-6]=str5[i];
            }
            instr.r_t.r_i.rs = fromBinary(str2);
            for(int i=11;i<16;i++)
            {
                str2[i-11]=str5[i];
            }
            instr.r_t.r_i.rt = fromBinary(str2);
            for(int i=16;i<32;i++)
            {
                str3[i-16]=str5[i];
            }
            instr.r_t.r_i.r_i.imm = fromBinary(str3);
            instr.value = 1;
            break;
        
        case 0:
            instr.opcode = a;
            for(int i=6;i<11;i++)
            {
                str2[i-6]=str5[i];
            }
            instr.r_t.r_i.rs = fromBinary(str2);
            for(int i=11;i<16;i++)
            {
                str2[i-11]=str5[i];
            }
            instr.r_t.r_i.rt = fromBinary(str2);
            for(int i=16;i<21;i++)
            {
                str2[i-16]=str5[i];
            }
            instr.r_t.r_i.r_i.r.rd = fromBinary(str2);
            for(int i=21;i<26;i++)
            {
                str2[i-21]=str5[i];
            }
            instr.r_t.r_i.r_i.r.shamt = fromBinary(str2);
            for(int i=26;i<32;i++)
            {
                str1[i-26]=str5[i];
            }
            instr.func_code = fromBinary(str1);
            instr.value = 1;
            break;

        case 2:
        case 3:
            instr.opcode = a;
            for(int i=6;i<32;i++)
            {
                str4[i-6]=str5[i];
            }
            instr.r_t.target = fromBinary(str4);
            instr.value = 1;
            break;
            
            
    }
    return instr;
}

void parsing_data(const char *buffer, const int index)
{
	/** Implement this function */
    char str[32]={0,};
    for(int i=0;i<32;i++)
    {
        str[i]=buffer[i];
    }
    int fb = fromBinary(str);
    mem_write_32(MEM_DATA_START+index,fb);
}

void print_parse_result()
{
    int i;
    printf("Instruction Information\n");

    for(i = 0; i < text_size/4; i++)
    {
        printf("INST_INFO[%d].value : %x\n",i, INST_INFO[i].value);
        printf("INST_INFO[%d].opcode : %d\n",i, INST_INFO[i].opcode);

	    switch(INST_INFO[i].opcode)
        {
            //Type I
            case 0x9:		//(0x001001)ADDIU
            case 0xc:		//(0x001100)ANDI
            case 0xf:		//(0x001111)LUI	
            case 0xd:		//(0x001101)ORI
            case 0xb:		//(0x001011)SLTIU
            case 0x23:		//(0x100011)LW
            case 0x2b:		//(0x101011)SW
            case 0x4:		//(0x000100)BEQ
            case 0x5:		//(0x000101)BNE
                printf("INST_INFO[%d].rs : %d\n",i, INST_INFO[i].r_t.r_i.rs);
                printf("INST_INFO[%d].rt : %d\n",i, INST_INFO[i].r_t.r_i.rt);
                printf("INST_INFO[%d].imm : %d\n",i, INST_INFO[i].r_t.r_i.r_i.imm);
                break;

            //TYPE R
            case 0x0:		//(0x000000)ADDU, AND, NOR, OR, SLTU, SLL, SRL, SUBU  if JR
                printf("INST_INFO[%d].func_code : %d\n",i, INST_INFO[i].func_code);
                printf("INST_INFO[%d].rs : %d\n",i, INST_INFO[i].r_t.r_i.rs);
                printf("INST_INFO[%d].rt : %d\n",i, INST_INFO[i].r_t.r_i.rt);
                printf("INST_INFO[%d].rd : %d\n",i, INST_INFO[i].r_t.r_i.r_i.r.rd);
                printf("INST_INFO[%d].shamt : %d\n",i, INST_INFO[i].r_t.r_i.r_i.r.shamt);
                break;

            //TYPE J
            case 0x2:		//(0x000010)J
            case 0x3:		//(0x000011)JAL
                printf("INST_INFO[%d].target : %d\n",i, INST_INFO[i].r_t.target);
                break;

            default:
                printf("Not available instruction\n");
                assert(0);
        }
    }

    printf("Memory Dump - Text Segment\n");
    for(i = 0; i < text_size; i+=4)
        printf("text_seg[%d] : %x\n", i, mem_read_32(MEM_TEXT_START + i));
    for(i = 0; i < data_size; i+=4)
        printf("data_seg[%d] : %x\n", i, mem_read_32(MEM_DATA_START + i));
    printf("Current PC: %x\n", CURRENT_STATE.PC);
}
