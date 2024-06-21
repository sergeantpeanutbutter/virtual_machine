#include <stdio.h>
#include <stdlib.h>

#define SIZE_ARRAY 500
int PAS[SIZE_ARRAY];
int base( int BP, int L)
{
    int arb = BP; // arb = activation record base
    while ( L > 0) //find base L levels down
    {
        arb = PAS[arb];
        L--;
    }
    
    return arb;
}


// Function to print the stack's contents
void printStack(int SP, int BP) 
{
    for (int i = SIZE_ARRAY - 1; i >= SP; i--) 
    {
        printf("%d ", PAS[i]);
         // Remove | if there's only one AR and stack has been modified
        if (i == BP+1 && SP != BP && SP != 500) 
        {
            printf("| ");
        }
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid input 'a.out inputtxt.file");
        exit(1);
    }
    //if run == 0 stop the program
    int run = 1;

    //this is to keep track of the pointers
    int BP = 499;
    int SP = 500;
    int PC = 10;

    //These are the IRs
    int IR_OP;
    int IR_L;
    int IR_M;

    //Variables to read in the integers from the text file
    FILE *file;
    int number;
    int i = 0;
    int text[SIZE_ARRAY];
    //initialize the reading input array to 0
    for(int i = 0; i<SIZE_ARRAY; i++)
    {
        text[i] = 0;
    }

    // Open the file for reading and store the numbers into a text called array
    file = fopen(argv[1], "r");
    if (file == NULL) {
            fprintf(stderr, "Could not open file\n");
            return 1;
    }

    // Read integers for the IR and store them in an
    while (fscanf(file, "%d", &number) != EOF) {
        text[i++] = number;
    }

    // Close the file
    fclose(file);

    //initialize the address space to 0
    for (int i = 0; i<(sizeof(PAS)/sizeof(PAS[0])); i++)
    {
        PAS[PC + i] = text[i];
    }

    //printing the initial values
    printf("\t\tPC\tBP\tSP\tstack\n");
    printf("Initial values:\t");
    printf("%d\t", PC);
    printf("%d\t", BP);
    printf("%d\t", SP);
    printf("\n\n");
    
    while (run == 1)
    {
        //fetch
        IR_OP = PAS[PC];
        IR_L = PAS[PC + 1];
        IR_M = PAS[PC + 2];
        PC = PC + 3;

        //exec
        switch (IR_OP)
        {
            //Load into
        case 1:
            SP = SP - 1;
            PAS[SP] = IR_M;
            printf("  LIT %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
            printStack(SP, BP);
            break;
        
        case 2:
            //RTN top of the stack
            if(IR_M == 0)
            {
                SP = BP+1;
                BP = PAS[SP-2];
                PC = PAS[SP-3];
                printf("  RTN %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
                printStack(SP, BP);
            }
            //add
            if(IR_M == 1)
                {
                PAS[SP+1] = PAS[SP+1] + PAS[SP];
                SP = SP+1;
                printf("  ADD %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
                printStack(SP, BP);
                }

            //subtract
            if(IR_M == 2)
            {
                PAS[SP+1] = PAS[SP + 1] - PAS[SP];
                SP = SP+1;
                printf("  SUB %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
                printStack(SP, BP);
            }

            //Multiply
            if(IR_M == 3)
            {
                PAS[SP+1] = PAS[SP+1] * PAS[SP];
                SP = SP+1;
                printf("  MUL %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
                printStack(SP, BP);
            }
            
            //Divide
            if(IR_M == 4)
            {
                PAS[SP+1] = PAS[SP+1]/PAS[SP];
                SP = SP+1;
                printf("  DIV %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
                printStack(SP, BP);
            }
            //Equal to
            if(IR_M == 5)
            {
                PAS[SP+1] = PAS[SP+1] == PAS[SP];
                SP = SP+1;
                printf("  EQL %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
                printStack(SP, BP);
            }
            //Not Equal to
            if(IR_M == 6)
            {
                PAS[SP+1] = PAS[SP+1] != PAS[SP];
                SP = SP+1;
                printf("  NEQ %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
                printStack(SP, BP);
            }
            //Less than
            if(IR_M == 7)
            {
                PAS[SP+1] = PAS[SP+1] < PAS[SP];
                SP = SP+1;
                printf("  LSS %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
                printStack(SP, BP);
            }
            //Less than or equal to
            if(IR_M == 8)
            {
                PAS[SP+1] = PAS[SP+1] <= PAS[SP];
                SP = SP+1;
                printf("  LEQ %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
                printStack(SP, BP);
            }
            //Greater than
            if(IR_M == 9)  
            {
                PAS[SP+1] = PAS[SP+1] > PAS[SP];
                SP = SP+1;
                printf("  GTR %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
                printStack(SP, BP);
            }
            //Greater than or equal to
            if(IR_M == 10)
            {
                PAS[SP+1] = PAS[SP+1] >= PAS[SP];
                SP = SP+1;
                printf("  GEQ %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
                printStack(SP, BP);
            }
            break;
        case 3:
            SP = SP - 1;
            PAS[SP] = PAS[base(BP,IR_L) - IR_M];
            printf("  LOD %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
            printStack(SP, BP);
            break;

        case 4:
            PAS[base(BP, IR_L)-IR_M] = PAS[SP];
            SP = SP + 1;
            printf("  STO %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
            printStack(SP, BP);
            break;

        case 5:
        //Call
            printf("  CAL %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
            PAS[SP-1] = base(BP, IR_L);
            PAS[SP-2] = BP;
            PAS[SP-3] = PC;
            BP = SP - 1;
            PC = IR_M;
            printStack(SP, BP);
            break;

        case 6:
        //Allocate space in the stack
            SP = SP - IR_M;
            printf("  INC %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
            printStack(SP, BP);
            break;
        
        case 7:
        //Jump
            PC = IR_M;
            printf("  JMP %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
            printStack(SP, BP);
            break;
        
        case 8:
        //Conditional jump
            if (PAS[SP] == 0)
            {
                PC = IR_M;
            }
            SP = SP+1;
            printf("  JPC %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
            printStack(SP, BP);
            break;
        
        case 9:
        //Print or scan in depending on the IR_M
            if(IR_M == 2)
            {
                SP = SP - 1;
                printf("Please enter an integer: ");
                fscanf(stdin,"%d", &PAS[SP]);
                printf("  SYS %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
                printStack(SP, BP);
            }
            if(IR_M == 1)
            {
                printf("Output result is: %d\n", PAS[SP]);
                SP = SP + 1;
                printf("  SYS %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
                printStack(SP, BP);
            }
            if(IR_M == 3)
            {
                printf("  SYS %d %d\t%d\t%d\t%d\t", IR_L, IR_M, PC, BP, SP);
                printStack(SP, BP);
                run = 0;
            }
            break;
        default:
            break;
        }
    }

}


