# simpletron
The Simpletron, software-based simulation of a primitive computer. 

## Description
The simpletron equipped with 100 words of memory. Words can be referenced by their location number 00 .. 99.
Word is a signed 4 digit decimal as +0001, +3364, -1293.
Word can be data or instruction. Instruction always positive; data can be positive or negative. First, two digits of the word are operation second operands. 

Simpletron CPU contains an accumulator and can handle basic arithmetic operations, memory and console IO operations, basic program branching. 


## App Setup

### Prerequisites

* Installed [clang](https://clang.llvm.org/)
* Installed [gnu make](https://www.gnu.org/software/make/)

### Build and run 

```bash
make simpletron
./simpletron
```

## Operation manual

### Command and data format
DATA - four digit interger (-9999 .. +9999)

COMMAND - four digit positive integer, first two digit operation code last two digit operand 
```
1010 - read data from counsole to memory address 0010
4003 - go to 3rd instruction
```
### Supported commands

* READ  
  ```CPP
	#define READ 10	// Read a word from the terminal into 
				//a specific location in memory
  ```
   format +1050 - 10 operation code 50 operand - memory address 

* WRITE
  ```CPP
	#define WRITE 11	//Write a word from specific location
						//in memory to the terminal
  ```
  format +1150 - 11 operation code 50 operand - memory address 

* LOAD
  ```CPP
	#define LOAD 20		// Load a word from a specific memory location 
		   				// into accumulator
  ```

* STORE
  ```CPP
	#define STORE 21	// Store a word from accumulator into
						// a specific location in memory
   ```
* ADD
  ```CPP
	#define ADD 30		// Add word from specific memory location 
						// to accumulator
  ```

* SUBSTRACT
  ```CPP
	#define SUBSTRACT 31	// Substract  word from specific memory location 
							// from accumulator
  ```
* DIVIDE
  ```CPP
	#define DIVIDE 32		// Devide a word from accumulator 
							// by word from specific memory location 
  ```
* MULTIPLY
  ```CPP
	#define MULTIPLY 33		// Multiply a word from accumulator 
							// by word from specific memory location 
  ```
* BRANCH
  ```CPP
	#define BRANCH 40		// Branch to a specific location in memory
  ```
* BRANCHNEG
  ```
	#define BRANCHNEG 41	// Branch to a specific location in memory if 
							// the accumulator is negative
  ```
* BRANCHZERO
  ```
	#define BRANCHZERO 42	// Branch to a specific location in memory if 
							// the accumulator is zero
  ```

### Program examples 

#### Sum of two variables

```
00 ? 1007 // Read A and save to address 0007
01 ? 1008 // Read B ans save to address 0008
02 ? 2007 // Load A to accumulator
03 ? 3008 // Add B
04 ? 2109 // store accumulator to C (address 0009)
05 ? 1109 // output C value to console
06 ? 4300 // end of program
```
Output:
```
*** Program execution begins. ***
 ? 7
 ? 3
 > +0010
*** Simpletron execution terminated ***
REGISTERS:
accumulator:			+0010
instrcutionCounter:		   06
instructionRegister:		+4300
operationCode:			   43
operand:			   00

MEMORY:
 	    0	    1	    2	    3	    4	    5	    6	    7	    8	    9
0	+1007	+1008	+2007	+3008	+2109	+1109	+4300	+0007	+0003	+0010
10	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
20	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
30	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
40	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
50	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
60	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
70	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
80	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
90	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
```

#### Get a larger value of two

```
00 ? 1009 // Read A to address 0009
01 ? 1010 // Read B to address 0010
02 ? 2009 // Load to accumulator
03 ? 3110 // Substract B from accumulator
04 ? 4107 // if accumulator negative go to 07
05 ? 1109 // Write A to console
06 ? 4300 // End of program
07 ? 1110 // Write B to console 
08 ? 4300 // End of program
```

Output:
```
*** Program execution begins. ***
 ? 5
 ? 10
 > +0010
*** Simpletron execution terminated ***
REGISTERS:
accumulator:			-0005
instrcutionCounter:		   08
instructionRegister:		+4300
operationCode:			   43
operand:			   00

MEMORY:
 	    0	    1	    2	    3	    4	    5	    6	    7	    8	    9
0	+1009	+1010	+2009	+3110	+4107	+1109	+4300	+1110	+4300	+0005
10	+0010	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
20	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
30	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
40	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
50	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
60	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
70	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
80	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
90	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
```

```
*** Program execution begins. ***
 ? 7
 ? 3
 > +0007
*** Simpletron execution terminated ***
REGISTERS:
accumulator:			+0004
instrcutionCounter:		   06
instructionRegister:		+4300
operationCode:			   43
operand:			   00

MEMORY:
 	    0	    1	    2	    3	    4	    5	    6	    7	    8	    9
0	+1009	+1010	+2009	+3110	+4107	+1109	+4300	+1110	+4300	+0007
10	+0003	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
20	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
30	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
40	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
50	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
60	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
70	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
80	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
90	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
```

#### Get a sum of positive numbers
calculate the sum of positive numbers and exit if entered a negative number

```
00 ? 1099 // Input A (address 0099)
01 ? 2099 // Load A to Accumulator
02 ? 4106 // if Accumulator < 0 got to 0006
03 ? 3098 // Accumulator += SUM (address 0098)
04 ? 2198 // SUM = Accumulator
05 ? 4000 // go to 0000
06 ? 1198 // Print SUM 
07 ? 4300 // End 
```
 Output:
 ```
 *** Program execution begins. ***
 ? 1
 ? 1
 ? 1
 ? 10
 ? 20
 ? -1
 > +0033
*** Simpletron execution terminated ***
REGISTERS:
accumulator:			-0001
instrcutionCounter:		   07
instructionRegister:		+4300
operationCode:			   43
operand:			   00

MEMORY:
 	    0	    1	    2	    3	    4	    5	    6	    7	    8	    9
0	+1099	+2099	+4106	+3098	+2198	+4000	+1198	+4300	+0000	+0000
10	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
20	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
30	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
40	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
50	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
60	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
70	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
80	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
90	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0033	-0001
 ```

#### Calculate average
```
00 ? 1099 // Get Number of arguments 
01 ? 1098 // Step for counter
02 ? 2099 // Accumulator = Number of arguments
03 ? 2197 // Counter = Accumulator
04 ? 1096 // Get Nth argument
05 ? 2096 // Accumulator = Argument 
06 ? 3095 // Accumulator += Sum
07 ? 2195 // Sum = Accumulator
08 ? 2097 // Accumulator = Counter
09 ? 3198 // Accumulator -= Step
10 ? 4213 // If Accumulator == 0 go to 13
11 ? 2197 // Counter = Accumulator 
12 ? 4004 // Go to 04
13 ? 2095 // Accumulator = Sum 
14 ? 3299 // Accumulator /= Number of Arguments
15 ? 2194 // Result = Accumulator
16 ? 1194 // Print result 
17 ? 4300 // End
```
Output:
```
*** Program execution begins. ***
 ? 5 
 ? 1 
 ? 1 
 ? 2
 ? 3
 ? 4
 ? 5
 > +0003
*** Simpletron execution terminated ***
REGISTERS:
accumulator:			+0003
instrcutionCounter:		   17
instructionRegister:		+4300
operationCode:			   43
operand:			   00

MEMORY:
 	    0	    1	    2	    3	    4	    5	    6	    7	    8	    9
0	+1099	+1098	+2099	+2197	+1096	+2096	+3095	+2195	+2097	+3198
10	+4213	+2197	+4004	+2095	+3299	+2194	+1194	+4300	+0000	+0000
20	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
30	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
40	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
50	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
60	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
70	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
80	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
90	+0000	+0000	+0000	+0000	+0003	+0015	+0005	+0001	+0001	+0005
```

#### Get max number from numbers series 
```
00 ? 1099 // Read default max number 
01 ? 1098 // Read step of iteration
02 ? 1097 // Read Series size (Counter)
03 ? 1096 // Read Nth series number
04 ? 2096 // Accumulator = Nth number
05 ? 3199 // Accumulator -= max number
06 ? 4109 // If Accumulator < 0 go to 09
07 ? 2096 // Accumulator = Nth number
08 ? 2199 // Max number = Accumulator
09 ? 2097 // Accumulator = Iteration counter
10 ? 3198 // Accumulator -= iteration step
11 ? 2197 // Couunter = Accumulator
12 ? 4214 // If counter == 0 go to 14
13 ? 4003 // go to 3
14 ? 1199 // Print Max number
15 ? 4300 // End
```
Output:
```
*** Program execution begins. ***
 ? -1000
 ? 1
 ? 5
 ? 100
 ? -200
 ? 5
 ? 3
 ? 3
 > +0100
*** Simpletron execution terminated ***
REGISTERS:
accumulator:			+0000
instrcutionCounter:		   15
instructionRegister:		+4300
operationCode:			   43
operand:			   00

MEMORY:
 	    0	    1	    2	    3	    4	    5	    6	    7	    8	    9
0	+1099	+1098	+1097	+1096	+2096	+3199	+4109	+2096	+2199	+2097
10	+3198	+2197	+4214	+4003	+1199	+4300	+0000	+0000	+0000	+0000
20	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
30	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
40	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
50	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
60	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
70	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
80	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000	+0000
90	+0000	+0000	+0000	+0000	+0000	+0000	+0003	+0000	+0001	+0100
```
