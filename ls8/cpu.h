#ifndef _CPU_H_
#define _CPU_H_

// Holds all information about the CPU
struct cpu {
  unsigned char PC; // Program Counter
  unsigned char FL; // Flag Register
  unsigned char reg[8]; // only has 8 wires availavle for addresses
  unsigned char ram[256]; // contains 256 bytes of memory, can only compute values up to 255
};

// ALU operations
enum alu_op { //enum often used for group of constants
	ALU_MUL,
	ALU_ADD, 
  ALU_CMP
};

// Instructions

// These use binary literals. If these aren't available with your compiler, 
// hex literals should be used.
// These instructions can be used in cpu_run().
#define LDI  0b10000010
#define MUL  0b10100010
#define ADD  0b10100000
#define PUSH 0b01000101 
#define POP  0b01000110
#define CALL 0b01010000
#define RET  0b00010001
#define JMP  0b01010100 
#define CMP  0b10100111
#define PRN  0b01000111
#define HLT  0b00000001


// Function declarations
extern void cpu_load(struct cpu *cpu, char *filename);
extern void cpu_init(struct cpu *cpu);
extern void cpu_run(struct cpu *cpu);

#endif
