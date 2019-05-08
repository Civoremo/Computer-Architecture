#include "cpu.h"
#include "dispatch.h"
#include <stdio.h>
#include <stdlib.h>

void inst_LDI(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] = opB;
}

void inst_PRN(struct cpu *cpu, unsigned char opA)
{
  printf("%d\n", cpu->registers[opA]);
}

void alu_Push(struct cpu *cpu, unsigned char opA)
{
  cpu->registers[SP]--;
  int val = cpu->registers[opA];
  cpu->ram[cpu->registers[SP]] = val;
}

void alu_Pop(struct cpu *cpu, unsigned char opA)
{
  int val = cpu->ram[cpu->registers[SP]];
  cpu->registers[opA] = val;
  cpu->registers[SP]++;
}

void alu_Mult(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] *= cpu->registers[opB];
}

void alu_Div(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] = cpu->registers[opA] / cpu->registers[opB];
}

void alu_Add(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] += cpu->registers[opB];
}

void alu_Sub(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] -= cpu->registers[opB];
}