#include "cpu.h"
#include "dispatch.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, int argCount, char *filename)
{
  // char data[DATA_LEN] = {
  //   // From print8.ls8
  //   0b10000010, // LDI R0,8
  //   0b00000000,
  //   0b00001000,
  //   0b01000111, // PRN R0
  //   0b00000000,
  //   0b00000001  // HLT
  // };

  // int address = 0;

  // for (int i = 0; i < DATA_LEN; i++) {
  //   cpu->ram[address++] = data[i];
  // }

  // TODO: Replace this with something less hard-coded
  FILE *fp;
  char line[1024];
  int address = 0;

  if (argCount != 2) {
    fprintf(stderr, "usage: ls8 filename\n");
  }

  fp = fopen(filename, "r");

  if (fp == NULL) {
    fprintf(stderr, "cpu: error opening file\n");
    exit(2);
  }

  while (fgets(line, 1024, fp) != NULL) {
    char *endptr;

    unsigned int val = strtoul(line, &endptr, 2);

    if (endptr == line) {
      continue;
    }

    cpu->ram[address] = val;
    address++;
  }
  fclose(fp);
}

// RAM read
unsigned char cpu_ram_read(struct cpu *cpu, unsigned char address) {
  return cpu->ram[address];
}

// RAM write
void cpu_ram_write(struct cpu *cpu, unsigned char address, unsigned char value) {
  cpu->ram[address] = value;
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  // printf("%d\n", op);
  switch (op) {
    case ALU_PUSH:
      alu_Push(cpu, regA);
      break;

    case ALU_POP:
    alu_Pop(cpu, regA);
      break;

    case ALU_MUL:
      alu_Mult(cpu, regA, regB);
      break;

    case ALU_DIV:
        alu_Div(cpu, regA, regB);
      break;

    case ALU_ADD:
      alu_Add(cpu, regA, regB);
      break;

    case ALU_SUB:
        alu_Sub(cpu, regA, regB);
      break;

    case ALU_AND:
      alu_And(cpu, regA, regB);
      break;

    case ALU_INC:
      alu_Inc(cpu, regA);
      break;

    case ALU_DEC:
      alu_Dec(cpu, regA);
      break;

    case ALU_XOR:
      alu_Xor(cpu, regA, regB);
      break;

    case ALU_OR:
      alu_Or(cpu, regA, regB);
      break;

    case ALU_MOD:
      alu_Mod(cpu, regA, regB);
      break;

    case ALU_NOT:
      alu_Not(cpu, regA);
      break;

    // TODO: implement more ALU ops
    default:
      printf("ALU default\n");
      break;
  }
}


void trace(struct cpu *cpu)
{
    printf("%02X | ", cpu->PC);

    printf("%02X %02X %02X |",
        cpu_ram_read(cpu, cpu->PC),
        cpu_ram_read(cpu, cpu->PC + 1),
        cpu_ram_read(cpu, cpu->PC + 2));

    for (int i = 0; i < 8; i++) {
        printf(" %02X", cpu->registers[i]);
    }

    printf("\n");
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    // 2. Figure out how many operands this next instruction requires
    // 3. Get the appropriate value(s) of the operands following this instruction
    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.

    unsigned int current_inst = cpu_ram_read(cpu, cpu->PC);
    unsigned char operandA = cpu_ram_read(cpu, (cpu->PC + 1));
    unsigned char operandB = cpu_ram_read(cpu, (cpu->PC + 2));
    unsigned int operands = current_inst >> 6;
    unsigned char return_addr;
    unsigned char call_addr;
    unsigned char reg_num;
    // 10 000010 -> LDI
    //   |
    // 00000010
    // operand = 2

    // trace(cpu);
    
    switch (current_inst) {
      case HLT:
        // printf("HALT\n");
        running = 0;
        break;

      case LDI:
        inst_LDI(cpu, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case PRN:
        inst_PRN(cpu, operandA);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case MUL:
        alu(cpu, ALU_MUL, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case PUSH:
        alu(cpu, ALU_PUSH, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case POP:
        alu(cpu, ALU_POP, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case ADD:
        alu(cpu, ALU_ADD, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case AND:
        alu(cpu, ALU_AND, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case CALL:
        return_addr = cpu->PC + 2;
        cpu->registers[SP]--;
        cpu->ram[cpu->registers[SP]] = return_addr;
        reg_num = cpu->ram[cpu->PC + 1];        
        call_addr = cpu->registers[reg_num];
        cpu->PC = call_addr;
        break;

      case CMP:
        break;

      case DEC:
        alu(cpu, ALU_DEC, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case DIV:
        alu(cpu, ALU_DIV, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case INC:
        alu(cpu, ALU_INC, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case IRET:
        break;

      case JEQ:
        break;

      case JGE:
        break;

      case JGT:
        break;

      case JLE:
        break;

      case JLT:
        break;

      case JMP:
        break;

      case JNE:
        break;

      case LD:
        break;

      case MOD:
        alu(cpu, ALU_MOD, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case NOP:
        break;

      case NOT:
        alu(cpu, ALU_NOT, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case OR:
        alu(cpu, ALU_OR, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case RET:
        return_addr = cpu->ram[cpu->registers[SP]];
        cpu->registers[SP]++;
        cpu->PC = return_addr;
        break;

      case SHL:
        break;

      case SHR:
        break;

      case ST:
        break;

      case SUB:
        alu(cpu, ALU_SUB, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      case XOR:
        alu(cpu, ALU_XOR, operandA, operandB);
        cpu->PC = cpu->PC + operands + 1;
        break;

      default:
        printf("DEFAULT\n");
        break;
    }

    // cpu->PC = cpu->PC + operands + 1;
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  memset(cpu->registers, 0, sizeof(cpu->registers));
  cpu->registers[SP] = 0xF4;
  cpu->PC = 0;
  memset(cpu->ram, 0, sizeof(cpu->ram));
}
