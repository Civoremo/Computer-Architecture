
#ifndef _DISPATCH_H_
#define _DISPATCH_H_

void inst_LDI(struct cpu *cpu, unsigned char opA, unsigned char opB);
void inst_PRN(struct cpu *cpu, unsigned char opA);
void alu_Mult(struct cpu *cpu, unsigned char opA, unsigned char opB);
void alu_Div(struct cpu *cpu, unsigned char opA, unsigned char opB);
void alu_Add(struct cpu *cpu, unsigned char opA, unsigned char opB);
void alu_Sub(struct cpu *cpu, unsigned char opA, unsigned char opB);

#endif