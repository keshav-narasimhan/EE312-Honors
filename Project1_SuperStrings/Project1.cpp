// SuperStrings <Project1.cpp>
// EE 312 Project <1> submission by
// <Keshav Narasimhan>
// <____>
// Slip days used: <0>
// Spring 2021
// Copy-paste contents of this file at the top of every .c or .h file that you write or modify.

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types

/*
All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)

You must write this function (printSuperStrings). Do not change the way the function is declared (i.e., it has
exactly two parameters, each parameter is a standard (mundane) C string (see Instruction).
*/

/*
* FUNCTION DECLARATIONS
* numStrings = returns the number of words in the inputted array
* findIndex = returns the index of next word in array given index of the end of previous word
* lengthOfString = returns the length of word at given index in given array
*/

int numStrings(char str []);
int findIndex (int i, char str []);
int lengthOfString (int i, char str []);

void printSuperStrings(char targets [], char candidates [])
{
    /*
    * num_of_strings = stores the number of words in strings array
    * num_of_superstr = stores the number of words in superstrings array
    */
    int num_of_strings = numStrings(targets);
    int num_of_superstrings = numStrings(candidates);

    /*
    * LOCAL VARIABLE DECLARATIONS
    * str_index = index of word in "strings" (will be incremented when checking if chars match up)
    * str_index_constant = index of word in "strings" (will stay constant to check if str_index is at end of word if it is a superstring)
    * index_str = used to move to next word in "strings" array each iteration of the loop
    * 
    * superstr_index = index of word in "superstrings" (will be incremented when checking if chars match up)
    * str_index_constant = index of word in "superstrings" (will stay constant to use for loop to print word if superstring)
    * index_superstr = used to move to next word in "superstrings" array each iteration of the loop
    * 
    * str_length = length of current word in "strings" array
    * superstr_length = length of current word in "superstrings" array
    */
    int index_str = 0;
    int str_index = index_str;
    int index_superstr = 0;
    int superstr_index = index_superstr;
    int str_length = 0;
    int superstr_length = 0;
    int str_index_constant = str_index;
    int superstr_index_constant = superstr_index;

    /*
    * Nested For Loop = main bulk of code
    * outer loop = loops through words in the "strings" array
    * inner loop = loops through words in the "superstrings" array
    */
    for (int i = 0; i < num_of_strings; i++)
    {
        str_index = findIndex(index_str, targets);                // finds index of current word in "strings"
        str_index_constant = str_index;                           // keep index of word in "strings" in another var that won't be changed
        str_length = lengthOfString(str_index_constant, targets); // length of current word in "strings"

        for (int j = 0; j < num_of_superstrings; j++)
        {
            superstr_index = findIndex(index_superstr, candidates);         // finds index of current word in "superstrings"
            index_superstr = superstr_index;                                // keep index of word in "superstrings" in another var (will update to find next word in array)
            superstr_index_constant = superstr_index;                       // keep index of word in "superstrings" in another var that won't be changed
            superstr_length = lengthOfString(superstr_index, candidates);   // length of current word in "superstrings"

            if (superstr_length >= str_length)
            {
                /*
                * if current word in "superstrings" is greater than/equal to current word in "strings"
                * iterate through word in "superstrings" and check if it truly is a superstring of current word in "strings"
                * if it is, print the current word in "superstrings"
                */
                for (int k = 0; k < superstr_length; k++)
                {
                    if (targets[str_index] == candidates[superstr_index])
                    {
                        str_index++;
                        superstr_index++;
                    }
                    else
                        superstr_index++;
                }
                if (str_index == str_index_constant + str_length)
                {
                    for (int l = superstr_index_constant; l < superstr_index_constant + superstr_length; l++)
                    {
                        printf("%c", candidates[l]);
                    }
                    printf("\n");
                }
            }

            str_index = str_index_constant;             // reinitialize index of current word in "strings" to its initial value prior to calculations
            index_superstr += superstr_length;          // update index that will be used to find the next word in "superstrings"
        }
        index_str = str_index;
        index_str += str_length;                        // update index that will be used to find the next word in "strings"
        index_superstr = 0;                             // update index of "superstrings" to 0 so that it will start with the first word in the array and go from there
    }
    /*
    * ANOTHER FUNCTION DECLARATION
    * testPrintStrings() = prints out all words in inputted array
    * not a method used in program, used to develop Phase 1 of programming assignment
    */ 
    //void testPrintStrings(char c []);
    //testPrintStrings(candidates);
    //testPrintStrings(targets);
}

int numStrings(char targets [])
{
    /*
    * returns num of words in 'targets' array
    */

    int numWords = 0;
    int index = 0;
    int wordLength = 0;

    if (targets[0] == '\0')
        return 0;
    
    while (targets[index] != '\0')
    {
        /*
        * while the current character is not signifying the end of the array
        * if the current character is either a lowercase/uppercase letter
        * calculate the length of the current word in the array
        * update index to bypass this word
        * update numWords by 1 since we found a word in string
        * else move to next character in the array
        * repeat this until we reach the end of the array
        */
        if ((targets[index] >= 65 && targets[index] <= 90) || (targets[index] >= 97 && targets[index] <= 122))
        {
            wordLength = lengthOfString(index, targets);
            index += wordLength;
            numWords++;
        }
        else
        {
            index++;
        }
    }

    return numWords;
}

int findIndex(int i, char str [])
{
    /*
    * returns index of next word in 'str' given current index
    */

    int index = i; // initialize local var called index

    // keep incrementing index until we reach an alphabetical character
    while (str[index] < 65 || (str[index] > 90 && str[index] < 97) || str[index] > 122)
    {
        index++;
    }

    // return value of index
    return index;
}

int lengthOfString(int i, char str [])
{
    /*
    * returns length of word in 'str' given starting index
    */

    int length = 0;

    while ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
    {
        /*
        * while the character is an alphabetic character (uppercase or lowercase)
        * increase length by 1 & update i to check the next char on next iteration
        */
        length++;
        i++;
    }

    return length;
}

// void testPrintStrings(char strings []) 
// {
//     /*
//     * function I used to test if I would be able to print every word in 'strings'
//     */

//     int index = 0; // initalize local var called index

//     while (strings[index] != '\0')
//     {
//         /*
//         * while the character in the array is not the end of the array 
//         * if character is newline/tab/space, than print a newline
//         * else print the character
//         * this will print every word in the array, each on a separate line
//         */
//         if (strings[index] == ' ' || strings[index] == '\t' || strings[index] == '\n')
//         {
//             printf("\n");
//         }
//         else
//         {
//             printf("%c", strings[index]);
//         }
//         index++;
//     }
// }
