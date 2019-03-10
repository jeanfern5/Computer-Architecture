# Computer Architecture

## Project

* [Implement the LS-8 Emulator](ls8/)

## Task List: add this to the first comment of your Pull Request

### Day 1: Get `print8.ls8` running
- [x] Inventory what is here
- [x] Implement `struct cpu` in `cpu.h`
- [x] Add RAM functions `cpu_ram_read` and `cpu_ram_write`
- [x] Implement `cpu_init()`
- [x] Implement the core of `cpu_run()`
- [x] Implement the `HLT` instruction handler
- [x] Add the `LDI` instruction
- [x] Add the `PRN` instruction

### Day 2: Add the ability to load files dynamically, get `mult.ls8` running
- [x] Un-hardcode the machine code
- [x] Implement the `cpu_load` function to load an `.ls8` file given the filename passed in as an argument
- [x] Implement a Multiply instruction and Print the result (run `mult8.ls8`)

### Day 3: Get`stack.ls8` running
- [x] Implement the System Stack and be able to run the `stack.ls8` program

### Day 4: Get `call.ls8` running
- [x] Implement the CALL and RET instructions
- [x] Implement Subroutine Calls and be able to run the `call.ls8` program

## Sprint Challenge Minimum Viable Product

Your finished project must include all of the following requirements:

- [x] Add the `CMP` instruction and `equal` flag to your LS-8.
- [x] Add the `JMP` instruction.
- [x] Add the `JEQ` and `JNE` instructions.

### Stretch
- [ ] Add the ALU operations: `AND` `OR` `XOR` `NOT` `SHL` `SHR` `MOD`
- [ ] Add an `ADDI` extension instruction to add an immediate value to a register
- [ ] Add timer interrupts
- [ ] Add keyboard interrupts
