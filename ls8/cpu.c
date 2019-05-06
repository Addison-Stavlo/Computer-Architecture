#include "cpu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
      0b00000001 // HLT
  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++)
  {
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
}

unsigned int cpu_ram_read(struct cpu *cpu, unsigned int pc)
{
  return cpu->ram[pc];
}

void cpu_ram_write(struct cpu *cpu, unsigned int instruction, unsigned int pc)
{
  cpu->ram[pc] = instruction;
}
/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op)
  {
  case ALU_MUL:
    // TODO
    break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running)
  {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    int current_inst = cpu_ram_read(cpu, cpu->pc);
    // 2. Figure out how many operands this next instruction requires
    int reg_index;
    int val;
    // 3. Get the appropriate value(s) of the operands following this instruction
    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.

    switch (current_inst)
    {
    case LDI:
      //sets value of register to an int
      reg_index = cpu_ram_read(cpu, cpu->pc + 1);
      val = cpu_ram_read(cpu, cpu->pc + 2);
      cpu->reg[reg_index] = val;
      cpu->pc += 3; // move to next instruction
      break;

      // case PRINT_NUM:
      //   printf("%d\n", memory[pc + 1]);
      //   pc += 2;
      //   break;

      // case SAVE_REG:
      //   reg_num = memory[pc + 1];
      //   val = memory[pc + 2];
      //   reg[reg_num] = val;
      //   pc += 3; // next inst
      //   break;

      // case PRINT_REG:
      //   reg_num = memory[pc + 1];
      //   printf("%d\n", reg[reg_num]);
      //   pc += 2; // next inst
      //   break;

    case HLT:
      running = 0;
      break;

    default:
      printf("Unknown instruction at %d: %d\n", cpu->pc, current_inst);
      exit(1);
    }
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu = malloc(sizeof(struct cpu));
  cpu->pc = 0;
  memset(cpu->reg, 0, 8 * (sizeof(char)));
  memset(cpu->ram, 0, 128 * sizeof(char));
}
