/*
SINGAPORE POLYTECHNIC 
SCHOOL OF COMPUTING
PROGRAMMING IN PYTHON AND C CA1 
ST2411
ASSIGNMENT 1
NAME: ALEK KWEK
ADMIN NO: P1804247
CLASS: DISM/FT/1A/23
YEAR OF ASSIGNMENT : 2018
*****************************

ASSIGNMENT OUTLINE 
This application is simulating a sales report generator for a 
departmental stores in United States of America.
The input data consists of series of sales records.
The application enables the users to submit the sales records
 and then print out an overall summaries of the sales for the entire year.
9 cities
Filename:p1804247.c
To compile the program
cc -o p1804247 p1804247.c p1804247helper.c 

The C program functionality
1. Usage of array of struct to maintain the sum of sales for individual cities.
2. Apply bubble sort scheme to get the top 3 and bottom 3 cities based on their sum of sales results.
3. Record field extraction using strtok() 
4. Handling multiple files I/O.
File IO functions: fopen(), fclose(), fgets(), fputs()
input file name should be obtained via the command line.
Read content from the input file line by line.
Extract the city name from the line.
append the content to the corresponding files:  
using city names as the file names. e.g Fort Worth.txt
Supporting files:

p1804247.h
p1804247helper.c

*/
// standard libraries
#include <stdio.h>    //standard library
#include <stdlib.h>   //standard library
#include <string.h>   //standard library for string operations
#include <time.h>     //library for time operation
#include <sys/stat.h> //library for checking files and directories in the system
#include "p1804247.h"

int main(int argc, char *argv[]) // get user input from the command line
{
  char *file;
  if (argc == 1 || argc > 2) //check number of arugments
  {
    //for number of arugments more than 2 or equal to 1
    printf("No file detected! Please enter a correct file name. Thank you\n"); // warn the user the reason why the program stopped
    if (argc == 1)
    {                                               //if arugment is equal to 1
      printf("usage ./salesSummary (text file)\n"); //explain to the user on how to enter a file name in the command line
    }
    else
    {
      //if arugment is more than 2
      printf("You have input more than one text file. Please use only one text file\n"); //explain to the user that they can only place one file name
    }
  }
  else
  { //if arugment is 2, this means correct input of the file name
    if ((strrchr(argv[1], '.')) != NULL)
    {
      if (strcmp(argv[1], ".txt") == 0) //check for .txt file extension
      {
        printf("Wrong file format: Program only accepts .txt files\n"); //tell the user when the file extension is incorrect
        return 0;
      }
    }
    first_time = malloc(255);      //allocate a memory of space 255 to the first_time to store the date and time
    first_time = setCurrentTime(); //get start time and place it in first_time
    char input[50];                //create a input of 50
    strcpy(input, argv[1]);        //copy the user input into input
    salesInput(input);             //call the function salesInput to extract contents from the file
    summary();                     //call the function summary to do calculate the sales

    return 0;
  }
}