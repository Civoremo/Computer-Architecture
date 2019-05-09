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
  if (cpu->registers[opB] != 0) {
    // alu_Div(cpu, opA, opB);
    cpu->registers[opA] = cpu->registers[opA] / cpu->registers[opB];
  } else {
    fprintf(stderr, "DIV: can't divide by 0\n");
    exit(1);
  }
}

void alu_Add(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] += cpu->registers[opB];
}

void alu_Sub(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] -= cpu->registers[opB];
}

void alu_And(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] = cpu->registers[opA] & cpu->registers[opB];
}

void alu_Inc(struct cpu *cpu, unsigned char opA)
{
  cpu->registers[opA] += 1;
}

void alu_Dec(struct cpu *cpu, unsigned char opA)
{
  cpu->registers[opA] -= 1;
}

void alu_Xor(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] = cpu->registers[opA] ^ cpu->registers[opB];
}

void alu_Or(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] = cpu->registers[opA] | cpu->registers[opB];
}

void alu_Mod(struct cpu *cpu, unsigned char opA, unsigned char opB)
{
  cpu->registers[opA] = cpu->registers[opA] % cpu->registers[opB];
}

void alu_Not(struct cpu *cpu, unsigned char opA)
{
  cpu->registers[opA] = ~cpu->registers[opA];
}