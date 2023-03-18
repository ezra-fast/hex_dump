/* Date: November 18, 2022
 * Author: Ezra Fast
 * Description: This code is for Programming Essentials Lab Assignment 7 Problem 2. It takes as input the name of a hex file, reads the contents, and prints formatted output.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// In house function prototypes:
void print_header_format(void);
void concluder(float summarization_number, unsigned char magic_number[]);

int main(void)
{
    // First variable declarations:
    FILE * hex_file;
    char file_name[10];
    int printable = 0;
    printf("Enter the file name: ");
    scanf("%s", file_name); // Note to self: different line for the TDM Compiler.
    hex_file = fopen(file_name, "rb"); // because it's a binary file
    if (hex_file == NULL)
    {
        printf("That Hex File is NULL");
        return 1;
    }

    print_header_format(); // abstraction of the header/format printing

    // Variable declarations:
    int count = 0;
    unsigned char current;
    unsigned int offset = 0;
    unsigned char character_format[1000];
    unsigned char magic_number[8]; 

    for(int i = 1; feof(hex_file) == 0; i++) 
    {
        if (i == 1)
        {
            printf("| %06X | ", offset); // printing the first offset
        }

        current = fgetc(hex_file); // Reading and printing the hex values from the file
        printf("%02X ", current);

        if (i >= 1 && i <= 4)
        {
            magic_number[i - 1] = current; // appending the first 4 characters to an unsigned char array to print out the magic number later
        }

        character_format[i - 1] = current; // appending the current character to the unsigned char array of every file character

        if (i % 8 == 0 && i != 0)
        {
            printf("  "); 
        }
        if (i % 16 == 0 && i != 0 || feof(hex_file))
        {
            printf("|");
            for (int tu = 0; tu < 16; tu++)
            {
                if (isprint(character_format[(i - 16) + tu]) != 0) // checking for printable characters
                {
                    printf(" %c", character_format[(i - 16) + tu]); // printing printable characters and incrementing a count thereof
                    printable++;
                }
                else
                {
                    printf(" .");
                }
            }
            printf(" |");
            if (!feof(hex_file))
            {
                printf("\n");
                printf("| %06X | ", offset + 16);
                offset = offset + 16; // incrementing the offset
            }
        }
        count++; // stores the character count
    }

    float summarization_number = 0;
    summarization_number = ((float)printable / (float)count); // getting an exact proportion of printable characters to compare to benchmarks

    concluder(summarization_number, magic_number); // abstraction of the final printing

    fclose(hex_file);

    return 0;
}

void print_header_format(void)
{
    printf("\n==================================================================================================\n");
    printf("| Offset | \t\t    Hexadecimal data\t\t       |    \tCharacter Format\t |");
    printf("\n==================================================================================================\n");
}

void concluder(float summarization_number, unsigned char magic_number[])
{
    printf("\n\n");

    // strrev(magic_number); // works with the TDM compiler ... NOT in Linux.

    printf("Magic Number: 0x%02X%02X%02X%02X\n\n", magic_number[3], magic_number[2], magic_number[1], magic_number[0]);

    if (summarization_number >= 0.75)
    {
        printf("Conclusion: This is a text file (75%%+ ascii)\n");
    }
    else if (summarization_number >= 0.25 && summarization_number < 0.75)
    {
        printf("Conclusion: This was possibly a text file (25%% - 74%% ascii)\n");
    }
    else if (summarization_number < 0.25)
    {
        printf("Conclusion: This is a binary file (<25%% ascii)\n\n");
    }
    printf("\n");
}
