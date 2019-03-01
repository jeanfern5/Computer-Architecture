#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_LEN 6

/**
 * Reads memory data (MDR) from memory address (MAR) - helper function
 */
unsigned char cpu_ram_read(struct cpu *cpu, unsigned char MAR)
{
  return cpu->ram[MAR];
}

/**
 * Writes memory data (MDR) to memory address (MAR) - helper function
 */
void cpu_ram_write(struct cpu *cpu, unsigned char MAR, unsigned char MDR)
{
  cpu->ram[MAR] = MDR;
}

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, char *filename)
{
  FILE *fp = fopen(filename, "r"); //opens file

  int address = 0;
  char line[8192];

  if (fp != NULL)
  {
    //read in its contents line by line, 
    while (fgets(line, sizeof(line), fp) != NULL)
    {
      char *endptr;
      unsigned char bistrValue = strtoul(line, &endptr, 2); // OR strtoul(line, NULL , 2);

      //ignore everything after a `#`, since that's a comment.
      if (endptr == line)
      {
        continue;
      }
      
      //save appropriate data into RAM
      cpu_ram_write(cpu, address++, bistrValue); //OR cpu->ram[address++] = bistrValue;
    }
  }
  else
  {
    fprintf(stderr, "%s filename was not found.\n", filename);
  }

  fclose(fp); //closes file
}

/**
 * ALU handles MUL instruction
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  unsigned char a = cpu->reg[regA];
  unsigned char b = cpu->reg[regB];

  switch (op) {
    case ALU_MUL:
      cpu->reg[regA] = a * b; //multiply the values in two registers together and store the result in registerA.
      break;

    case ALU_ADD:
    cpu->reg[regA] = a + b; //add the value in two registers and store the result in registerA.
    break;

    case ALU_CMP: //Compare the values in two registers. FL bits: 00000LGE
    if (a < b) //L Less-than: during a CMP, set to 1 if registerA is less than registerB, zero otherwise.
    {
      cpu->FL = 0b00000100;
    }
    else if (b > a) //G Greater-than: during a CMP, set to 1 if registerA is greater than registerB, zero otherwise.
    {
      cpu->FL = 0b00000010;
    }
    else //E Equal: during a CMP, set to 1 if registerA is equal to registerB, zero otherwise.
    {
      cpu->FL = cpu->FL| 0b00000001;
    }
    break;
  }
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
    unsigned char IR = cpu_ram_read(cpu, cpu->PC); // IR store results from memory address that's stored in register PC
    unsigned char SP = cpu->reg[7]; //R7 is reserved as the stack pointer (SP)

    // 2. Figure out how many operands this next instruction requires
      //Some instructions requires up to the next two bytes of data _after_ the `PC` in memory to perform operations on.
    // 3. Get the appropriate value(s) of the operands following this instruction
    unsigned operandA = cpu_ram_read(cpu, (cpu->PC + 1));
    unsigned operandB = cpu_ram_read(cpu, (cpu->PC + 2));



    printf("TRACE: %02X: %02X   %02X %02X\n", cpu->PC, IR, operandA, operandB);

    // 4. switch() over it to decide on a course of action.
    switch(IR)
    {
      // 5. Do whatever the instruction should do according to the spec.
      // 6. Move the PC to the next instruction.
      case LDI: //load "immediate", store a value in a register, or "set this register to this value".
      cpu->reg[operandA] = operandB; //Loads registerA with the value at the memory address stored in registerB.
      cpu->PC += 3; //moves PC down 3 lines
      break;

      case MUL: //This is an instruction handled by the ALU.
      alu(cpu, ALU_MUL, operandA, operandB);
      cpu->PC += 3; //moves PC down 3 lines
      break;

      case ADD: //This is an instruction handled by the ALU.
      alu(cpu, ALU_ADD, operandA, operandB); 
      cpu->PC += 3;
      break;
      
      case PUSH: //Push the value in the given register on the stack.
      SP--; // 1. Decrement the SP
      cpu_ram_write(cpu, SP, cpu->reg[operandA]); //2. Copy the value in the given register to the address pointed to by SP
      cpu->PC += 2; 
      break;

      case POP: //Pop the value at the top of the stack into the given register.
      cpu->reg[operandA] = cpu_ram_read(cpu, SP); //1. Copy the value from the address pointed to by SP to the given register.
      SP++; //2. Increment SP.
      cpu->PC += 2; 
      break;

      case CALL: //Calls a subroutine (function) at the address stored in the register.
      SP--; //from PUSH
      cpu_ram_write(cpu, SP, (cpu->PC + 2)); //1. The address of the instruction directly after CALL is pushed onto the stack. This allows us to return to where we left off when the subroutine finishes executing.
      cpu->PC = cpu->reg[operandA]; //2. The PC is set to the address stored in the given register. We jump to that location in RAM and execute the first instruction in the subroutine. The PC can move forward or backwards from its current location.
      break;

      case RET: //Return from subroutine.
      cpu->PC = cpu->ram[SP];//Pop the value from the top of the stack and store it in the PC.
      SP++; //from POP
      break;

      case CMP: //This is an instruction handled by the ALU.
      alu(cpu, ALU_CMP, operandA, operandB);
      cpu->PC += 3;
      break;

      case JMP: //Jump to the address stored in the given register.
      cpu->PC = cpu->reg[operandA]; //Set the PC to the address stored in the given register.
      break;

      case JEQ:
      if (cpu->FL == 0b00000001) //if equal flag is set (true), 
      {
        cpu->PC = cpu->reg[operandA]; //jump to the address stored in the given register.
      }
      cpu->PC +=2;//if it doesn't jump
      break;

      case JNE:
      if (cpu->FL == 0b00000000)//If E flag is clear (false, 0)
      {
        cpu->PC = cpu->reg[operandA]; //jump to the address stored in the given register.
      }
      cpu->PC += 2; //if it doesn't jump
      break;

      case PRN: //a pseudo-instruction that prints the numeric value stored in a register.
      printf("%d\n", cpu->reg[operandA]); 
      cpu->PC += 2; //moves PC down 2 lines
      break;

      case HLT: //halt the CPU and exit the emulator.
      running = 0;
      break;

      default:
      printf("unexpected instruction 0x%02X at 0x%02X\n", IR, cpu->PC);
      exit(1);
    }
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  cpu->PC = 0; //PC and FL registers are cleared to 0.
  cpu->FL = 0;
  memset(cpu->ram, 0, sizeof(cpu->reg)); //R0-R6 are cleared to 0
  memset(cpu->ram, 0, sizeof(cpu->ram)); //RAM is cleared to 0
  cpu->reg[7] = 0xF4; //R7 is set to 0xF4.
}
