// Nicholas Donofrio
// Tiny Harvard Achitecture ISA Simulator

/* Instructions:
  1. In shell type "gcc main.c"
  2. Then type "./main in.txt"
  3. Enter your number into the input value
*/

// Libraries
#include <stdio.h>
#include <stdlib.h>

// Global Constants
#define MAX_PROGRAM_SIZE 1000
#define BUFFER_SIZE 500

// Instruction Structure
typedef struct Instruction 
{
  int opCode, deviceOrAddress;
} Instruction;

// Function Prototypes
void printError(char *error);
void readFile(char *fileName, Instruction *programMemory);
void fetchCycle(int *programCounter, int *MAR, Instruction *MDR, Instruction *IR, Instruction *programMemory);
void printHeader(int programCounter, int accumulator, int *dataMemory);

// Function to print an error message
void printError(char *error) 
{
  fprintf(stderr, "%s", error);
}

// Function to read instructions from a file and store them in programMemory
void readFile(char *fileName, Instruction *programMemory) 
{
  // Attempt to open the specified file in read mode
  FILE *inputFile = fopen(fileName, "r");

  // Handle file opening error
  if (inputFile == NULL) 
  {
    // Construct an error message indicating the failure to open the file
    char error[BUFFER_SIZE];
    snprintf(error, sizeof(error), "ERROR: could not open file %s\n\n", fileName);

    // Print the error message to standard error
    printError(error);

    // Exit the program with an error code
    exit(1);
  }

  // Read instructions from the file and store them in programMemory
  char line[BUFFER_SIZE];
  int i = 10;

  // Iterate through each line in the file
  while (fgets(line, BUFFER_SIZE, inputFile) != NULL) 
  {
    // Check if the line is not empty
    if (strcmp(line, "\n")) 
    {
      // Declare variables to store the opcode and deviceOrAddress
      int opCode, deviceOrAddress;

      // Extract opcode and deviceOrAddress from the line
      sscanf(line, "%d %d", &opCode, &deviceOrAddress);

      // Store the extracted values in the programMemory array
      programMemory[i].opCode = opCode;
      programMemory[i].deviceOrAddress = deviceOrAddress;

      // Increment the index in programMemory for the next instruction
      i++;
    }
  }

  // Close the file as it is no longer needed
  fclose(inputFile);
}

// Function to simulate the fetch cycle
void fetchCycle(int *programCounter, int *MAR, Instruction *MDR, Instruction *IR, Instruction *programMemory)
{
  // Set Memory Address Register (MAR) to the current Program Counter value
  *MAR = *programCounter;

   // Load the OpCode and deviceOrAddress from the Instruction Memory (IM) into the Memory Data Register (MDR)
  MDR->opCode = programMemory[*MAR].opCode;
  MDR->deviceOrAddress = programMemory[*MAR].deviceOrAddress;

   // Copy the contents of MDR into the Instruction Register (IR
  *IR = *MDR;

  // Increment the Program Counter to point to the next instruction in the sequence
  (*programCounter)++;
}

// Function to print the current state of the machine
void printHeader(int programCounter, int accumulator, int *dataMemory) 
{
  printf("PC = %d | A = %d, DM = [", programCounter, accumulator);

  // Print contents of dataMemory
  for (int i = 0; i < 10; i++) 
  {
    printf("%d,", dataMemory[i]);
  }

  printf("]\n\n");
}

// Main
int main(int argc, char **argv) 
{
  // Check if the correct number of command-line arguments is provided
  if (argc != 2) 
  {
    fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
    return 1;
  }

  // Declare and initialize variables
  Instruction programMemory[MAX_PROGRAM_SIZE];
  readFile(argv[1], programMemory);

  // Print initial messages
  printf("Assembling Program...\n");
  printf("Program Assembled.\nRun.\n\n");

  // Initialize CPU registers and memory
  int programCounter = 10, MAR, accumulator = 0, dataMemory[10] = {0};
  Instruction MDR, IR;

  // Main execution loop
  for (;;) 
  {
    // Print the current state of the machine
    printHeader(programCounter, accumulator, dataMemory);

    // Fetch the next instruction
    fetchCycle(&programCounter, &MAR, &MDR, &IR, programMemory);

    // Switch statement to execute instructions based on opcode
    switch (IR.opCode) 
    {
      case 1:  // LOAD(1) - 001
        MAR = IR.deviceOrAddress;
        printf("/*loading memory location %d to accumulator*/\n", MAR);
        accumulator = dataMemory[MAR];
        break;

      case 2:  // ADD(2) - 010
        MAR = IR.deviceOrAddress;
        printf("/*loading memory location %d to be added to accumulator value %d*/\n", MAR, accumulator);
        accumulator += dataMemory[MAR];
        break;

      case 3:  // STORE(3) - 011
        MAR = IR.deviceOrAddress;
        printf("/*storing accumulator in memory location %d\n", MAR);
        dataMemory[MAR] = accumulator;
        break;

      case 4:  // SUB(4) - 100
        MAR = IR.deviceOrAddress;
        printf("/*loading memory location %d to be subtracted from accumulator value %d*/\n", MAR, accumulator);
        accumulator -= dataMemory[MAR];
        break;

      case 5:  // IN(5) - 101
        printf("/*input value*/\n");
        scanf("%d", &accumulator);
        break;

      case 6:  // OUT(6) - 110
        printf("/*outputting accumulator to screen*/\n");
        printf("%d\n\n", accumulator);
        break;

      case 7:  // END(7) - 111
        printf("Program complete\n");
        return 0;

      case 8:  // JMP(8) - 1000
        MAR = IR.deviceOrAddress;
        printf("/*jumping to memory location %d*/\n", MAR);
        programCounter = MAR;
        break;

      case 9:  // SKIPZ(9) - 1001
        if (accumulator == 0)
          programCounter++;
        break;

      default:
      printf("Error: Unknown opcode %d. Exiting program.\n", IR.opCode);
      exit(1);

    }

    // Check for program completion
    if (IR.opCode == 7)
      break;
  }

  return 0;
}