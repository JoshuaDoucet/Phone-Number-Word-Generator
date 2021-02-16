/*
Date: 04-13-2019
Programmer - JD
Project - Phone Number Word Generator
Description:The program takes a user inputted phone number and file name, and outputs
      all textual keypad representations of that phone number to the provided file name. 
      The output file will be located within the project folder for this application.
*/

//Max length of file name
#define MAX_FILE_NAME 100
#define PHONE_NUM_LENGTH 7

#include <stdio.h>
#include <math.h>

//Generates all textual representations of aPhoneNum and outputs the list of generated text
//to the file name provided as a parameter
void genWordsFromPhoneNum(const unsigned int aPhoneNum, const char aFileName[MAX_FILE_NAME]);

//Obtains a phone number and a file name from a user through stdin
unsigned int getInputs(char aFileName[MAX_FILE_NAME]);

//take an integer and place each of its digits into the array digits
void intToIntArray(unsigned int number, unsigned int digits[PHONE_NUM_LENGTH]);


int main(void) {
   //Program title
   printf_s("Phone-number Word Generator\n-----------------------\n");

   //User inputted sentinel
   char again = 'Y';

   while (again == 'Y' || again == 'y') {
      //String that will represent a file name that stores textual phone numbers
      char wordsFileName[MAX_FILE_NAME] = { 0 };
      //Phone number to be converted to textual representations
      unsigned int phoneNum = 0;

      //Get phone number and file name from user
      phoneNum = getInputs(wordsFileName);
      //Generate a file with textual representations of phoneNum
      genWordsFromPhoneNum(phoneNum, wordsFileName);

      puts("\nStrings that represent the entered number have been save to the desired output file");
      printf_s("Generate strings for another phone number? (Y/N): ");
      scanf_s(" %c", &again);
   }
   return 0;
}//end main

void genWordsFromPhoneNum(const unsigned int aPhoneNum, const char aFileName[MAX_FILE_NAME]) {
   //Pointer to file that will store all textual phone# conversions
   FILE *wordsFilePtr = 0;
   //Open the user inputted file name for writing
   wordsFilePtr = fopen(aFileName, "w");

   //EX: index column 2 represents the values that can represents the number 2 on a keypad
   const char digitToLetter[4][10] =
   //    0    1    2    3    4    5    6    7    8    9
     { {'-', '-', 'A', 'D', 'G', 'J', 'M', 'P', 'T', 'W'},
       {'-', '-', 'B', 'E', 'H', 'K', 'N', 'R', 'U', 'X'},
       {'-', '-', 'C', 'F', 'I', 'L', 'O', 'S', 'V', 'Y'},
       {'-', '-', '-', '-', '-', '-', '-', 'Q', '-', 'Z'} }; 
   //Extra row in the event that Q and Z need to be handled, - indicated no letter is assigned

   //Phone number with single digits in each element of an array
   unsigned int digits[PHONE_NUM_LENGTH] = { 0 };

   //Fill digits array with digits from aPhoneNum
   //EX 2335555 in digits = {2,3,3,5,5,5,5}
   intToIntArray(aPhoneNum, digits);

   //Print file header to output file
   fprintf(wordsFilePtr, "Strings that represent the phone number: %u\n--------------------\n",
      aPhoneNum);

   //Print all string that represent aPhoneNum to the file at wordsFilePtr
   //Conts the number of generated strings
   unsigned int count = 1;
   //digits[0], if d0Let = 1, The variable of interest is the leftmost digit in digits and the second 
   // letter that can represent the leftmost digit. EX: id digits[0] = 3, and d0Let = 1, the the letter
   // of interest is digitToLetter[1][3] which is 'E'
   for (int d0Lett = 0; d0Lett < 3; d0Lett++) {
      //For each letter representing digits[1]
      for (int d1Lett = 0; d1Lett < 3; d1Lett++) {
         //For each letter representing digits[2]
         for (int d2Lett = 0; d2Lett < 3; d2Lett++) {
            //For each letter representing digits[3]
            for (int d3Lett = 0; d3Lett < 3; d3Lett++) {
               //For each letter representing digits[4]
               for (int d4Lett = 0; d4Lett < 3; d4Lett++) {
                  //For each letter representing digits[5]
                  for (int d5Lett = 0; d5Lett < 3; d5Lett++) {
                     //For each letter representing digits[6]
                     for (int d6Lett = 0; d6Lett < 3; d6Lett++) {
                        fprintf(wordsFilePtr, "String #%4d, ", count);
                        fprintf(wordsFilePtr, "%c", digitToLetter[d0Lett][digits[0]]);
                        fprintf(wordsFilePtr, "%c", digitToLetter[d1Lett][digits[1]]);
                        fprintf(wordsFilePtr, "%c", digitToLetter[d2Lett][digits[2]]);
                        fprintf(wordsFilePtr, "%c", digitToLetter[d3Lett][digits[3]]);
                        fprintf(wordsFilePtr, "%c", digitToLetter[d4Lett][digits[4]]);
                        fprintf(wordsFilePtr, "%c", digitToLetter[d5Lett][digits[5]]);
                        fprintf(wordsFilePtr, "%c\n", digitToLetter[d6Lett][digits[6]]);
                        count++;
                     }
                  }
               }
            }
         }
      }
   }

   fclose(wordsFilePtr);
}//end genWordsFromPhoneNum

unsigned int getInputs(char aFileName[MAX_FILE_NAME]) {
   //Phone# to convert to textual representations, cannot include 0's or 1's
   unsigned int aPhoneNum = 0;

   //Get phone number from user
   printf_s("\nEnter a 7 digit phone number with no spaces or dashes.\n");
   printf_s("Numbers with 0's or 1's CANNOT be converted to text.\nPhone #: ");
   scanf_s("%ud", &aPhoneNum);

   //Get file name from user
   printf_s("\nEnter a file name to store the generated words in.\n");
   printf_s("The entered filename should end with a .txt extension.\nFile Name: ");
   while (getchar() != '\n' && getchar() != ' '); //Clear stdin
   scanf("%s", aFileName);

   return aPhoneNum;
}//end getInputs

void intToIntArray(unsigned int number, unsigned int digits[PHONE_NUM_LENGTH]) {
   //Place each digit in aPhoneNum into its own element in digits
   int numToProcess = number;
   for (unsigned int digit = 0; digit < PHONE_NUM_LENGTH; digit++) {
      //Get current digit value. Ex if left most digit is 2, then currentValue = 2
      //when digit = 0
      unsigned int placeHolder = 1000000 / pow(10, digit);
      int currentValue = floor(numToProcess / placeHolder);
      digits[digit] = currentValue;
      //Remove leftmost digit from numToProcess
      numToProcess -= currentValue * placeHolder;
   }
}//end intToIntArray