# simpletron
The Simpletron, software-based simulation of a primitive computer. 

## Description
The simpletron equipped with 100 words of memory. Words can be referenced by their location number 00 .. 99.
Word is a signed 4 digit decimal as +0001, +3364, -1293.
Word can be data or instruction. Instruction always positive; data can be positive or negative. First, two digits of the word are operation second operands. 

Simpletron CPU contains an accumulator and can handle basic arithmetic operations, memory and console IO operations, basic program branching. 

### Supported commands

* READ  
  ```C
	#define READ 10 	// Read a word from the terminal into 
						//a specific location in memory
  ```
   format +1050 - 10 operation code 50 operand - memory address 

* WRITE
  ```C
	#define WRITE 11	//Write a word from specific location
						//in memory to the terminal
  ```
  format +1150 - 11 operation code 50 operand - memory address 

## App Setup

### Prerequisites

* Installed [clang](https://clang.llvm.org/)
* Installed [gnu make](https://www.gnu.org/software/make/)

### Build and run 

```bash
make simpletron
./simpletron
```

