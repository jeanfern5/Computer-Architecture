# Computer Architecture

## Project

* [Implement the LS-8 Emulator](ls8/)

## Task List: add this to the first comment of your Pull Request

### Day 1: Get `print8.ls8` running
- [ ] Inventory what is here
- [ ] Implement `struct cpu` in `cpu.h`
- [ ] Add RAM functions `cpu_ram_read` and `cpu_ram_write`
- [ ] Implement `cpu_init()`
- [ ] Implement the core of `cpu_run()`
- [ ] Implement the `HLT` instruction handler
- [ ] Add the `LDI` instruction
- [ ] Add the `PRN` instruction

### Day 2: Add the ability to load files dynamically, get `mult.ls8`
- [ ] Un-hardcode the machine code
- [ ] Implement the `cpu_load` function to load an `.ls8` file given the filename passed in as an argument
- [ ] Implement a Multiply instruction and Print the result (run `mult8.ls8`)

### Day 3: Get `stack.ls8` running
- [ ] Implement the System Stack and be able to run the `stack.ls8` program

### Day 4: Get `call.ls8` running
- [ ] Implement the CALL and RET instructions
- [ ] Implement Subroutine Calls and be able to run the `call.ls8` program

### Stretch
- [ ] Add the timer interrupt to the LS-8 emulator
- [ ] Add the keyboard interrupt to the LS-8 emulator

## Sprint Challenge: Minimum Viable Product

Your finished project must include all of the following requirements:

- [ ] Add the `CMP` instruction and `equal` flag to your LS-8.

- [ ] Add the `JMP` instruction.

- [ ] Add the `JEQ` and `JNE` instructions.

## Stretch Problems

After finishing your required elements, you can push your work further. These
goals may or may not be things you have learned in this module but they build on
the material you just studied. Time allowing, stretch your limits and see if you
can deliver on the following optional goals:

- [ ] Add the ALU operations: `AND` `OR` `XOR` `NOT` `SHL` `SHR` `MOD`
- [ ] Add an `ADDI` extension instruction to add an immediate value to a register
- [ ] Add timer interrupts
- [ ] Add keyboard interrupts
