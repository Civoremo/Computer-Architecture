#include "cpu.h"
#include <string.h>
#include <stdio.h>

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu)
{
  char data[DATA_LEN] = {
    // From print8.ls8
    0b10000010, // LDI R0,8
    0b00000000,
    0b00001000,
    0b01000111, // PRN R0
    0b00000000,
    0b00000001  // HLT
  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++) {
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
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
  switch (op) {
    case ALU_MUL:
      // TODO
      break;

    // TODO: implement more ALU ops
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
    // unsigned int test;
    // unsigned int operands2 = current_inst >> 7;
    // 10 000010 -> LDI
    //   |
    // operand = 2

    // trace(cpu);

    // printf("OPERAND: %d\n", operands);
    // printf("OPERAND2: %d\n", operands2);
    // printf("CurrentInst: %d\n", current_inst);
    
    switch (current_inst) {
      case HLT:
        // printf("HALT\n");
        running = 0;
        break;

      case LDI:
        // printf("LDI\n");
        cpu_ram_write(cpu, operandA, operandB);
        cpu->registers[operandA] = operandB;
        // test = cpu->PC;
        // cpu->registers[cpu_ram_read(cpu, (cpu->PC + 1))] = cpu->registers[cpu_ram_read(cpu, (cpu->PC + 2))];
        break;

      case PRN:
        // printf("PRINT\n");
        printf("%d\n", cpu->registers[operandA]);
        // printf("TESTL %d\n", cpu->ram[test]);
        // printf("%d\n", cpu->registers[cpu_ram_read(cpu, cpu->PC + 1)]);
        break;

      default:
        printf("DEFAULT\n");
        break;
    }

    cpu->PC = cpu->PC + operands + 1;
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  memset(cpu->registers, 0, sizeof(cpu->registers));
  cpu->registers[8] = 0xF4;
  cpu->PC = 0;
  memset(cpu->ram, 0, sizeof(cpu->ram));
}
