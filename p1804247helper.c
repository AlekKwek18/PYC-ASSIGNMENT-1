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
 Filename: p1804247helper.c 
 define all the helper functions for the p1804247.c 
*/

#include <stdio.h>    //standard library
#include <stdlib.h>   //standard library
#include <string.h>   //standard library for string operations
#include <time.h>     //library for time operation
#include <sys/stat.h> //library for checking files and directories in the system
#include "p1804247.h"

int numCity = 0;
int numCat = 0;
/* source: p1804247helper.c */
/* define all the helper functions for the p1804247.c */
char *setCurrentTime()
{
  time_t t = time(NULL);                                   //create a time_t variable t
  struct tm *tm_info;                                      //create struct
  time(&t);                                                // get current time
  tm_info = localtime(&t);                                 //get current time
  char *date_format = malloc(sizeof(char) * 255);          //aollcate a memory to date_format
  strftime(date_format, 50, "%a %b %d %H:%M:%S", tm_info); //print in the format of D M D HH:MM:SS
  return date_format;
  free(date_format); //free the date_format
}
/*summary prints the sales calculations in this format for example

Thu Nov 29 10:51:24
Total sales of the year is      2325.68

The Average Sales from  9 Cities :
                                         258.41

Top Three Cities
===============================================
Pittsburgh                               493.51
Austin                                   379.60
Fort Worth                               367.45
===============================================

Bottom Three Cities
===============================================
San Jose                                 214.05
San Diego                                 66.08
Corpus Christi                            25.38
===============================================

The Average Sales from  8 Item Categories:
                                         290.71

Top Three Item Categories
===============================================
Pet Supplies                             493.51
Men's Clothing                           461.23
Cameras                                  379.60
===============================================

Bottom Three Item Categories
===============================================
Children's Clothing                      235.63
Women's Clothing                         153.57
Music                                     66.08
===============================================

Program ended at Thu Nov 29 10:51:24
*/
void summary()
{
  char *lines = "===============================================";
  double Sales = totalSales();      // calcalute total sales
  double Mean = average(Sales);     // calcalute the average using the totalsales
  sortingAlgorithm(CITY);           //sort city's sales from smallest to biggest
  sortingAlgorithm(CAT);            //sort items sales from sammlest to biggest
  double catSales = averageSales(); //calcalute average
  printf("%s\n", first_time);       // prints the start date format

  printf("Total sales of the year is\t%.2f\n\n", Sales);    //Prints the total sales
  printf("The Average Sales from\t%d Cities :\n", numCity); //Prints the number of cities in the text file
  printf("\t\t\t\t\t %.2f\n\n", Mean);                      //Prints the average sales
  if (numCity <= 3)                                         //if the number of city is less than or equals to 3, print a different variant as stated in the assignment
  {
    printf("Sales Figures by Cities\n"); //Prints cities
    printf("%s\n", lines);               //prints the ==============
    topthree(CITY);                      //list out the top three cities from biggest to smallest
    printf("%s\n\n", lines);             //prints the ===========
  }
  else // if the number of cities is bigger than 3, this code will take action
  {
    printf("Top Three Cities\n");
    printf("%s\n", lines);   //prints the =========
    topthree(CITY);          //list out the top three cities from biggest to smallest
    printf("%s\n\n", lines); //prints the =========
    printf("Bottom Three Cities\n");
    printf("%s\n", lines);   //prints the =========
    bottomthree(CITY);       //list down bottom three cities from biggest to smallest
    printf("%s\n\n", lines); //prints the ==========
  }
  printf("The Average Sales from\t%d Item Categories:\n", numCat); //prints the total number of items
  printf("\t\t\t\t\t %.2f\n\n", catSales);                         //prints the average item sales
  if (numCat <= 3)                                                 //if the number of item is less than or equals to 3, print a different variant as stated in the assignment
  {
    printf("Sales FIgures by Item Categories\n");
    printf("%s\n", lines);   //prints the =========
    topthree(CAT);           //list out the top three cities from biggest to smallest
    printf("%s\n\n", lines); //prints the =========
  }
  else // if the number of items is bigger than 3, this code will take action
  {
    printf("Top Three Item Categories\n");
    printf("%s\n", lines);   //prints the ==========
    topthree(CAT);           //list out the top three items from biggest to smallest
    printf("%s\n\n", lines); //prints the ==========
    printf("Bottom Three Item Categories\n");
    printf("%s\n", lines);   //prints the ========
    bottomthree(CAT);        //list down bottom three items from biggest to smallest
    printf("%s\n\n", lines); //prints the =========
  }
  char *last_time = setCurrentTime();         //get the current time when the summary page has finished printing
  printf("Program ended at %s\n", last_time); //prints the end time
  return;
}
/*Sales input */

void salesInput(char *fileName)
{

  const int SIZE = 255;                 //create constant int SIZE with size of 255
  char line[SIZE], *city, *token, *cat; //create char line to store the content of the file line by line, city to store city from strtok, token to store the token from strtok
  //cat is store the category from strtok
  const char tab[5] = "\t";          /* let "\t" be tab[5] for dlim in the strtok */
  double sales;                      //create a double variable to store sales
  FILE *fileInput;                   // create a pointer called fileinput to open the sales text file
  char output_line[SIZE];            //create a string to store line of sales to be sent to the output file
  fileInput = fopen(fileName, READ); //open fileName which is the name of the sales text file and read the content of the file
  // for file validation only
  int year, month, day, hour, min;
  double money;
  char state[50], items[50];
  //
  if (fileInput == NULL) //check if the file exist
  {
    //if file doesn't exist, give warning shown below
    printf("File does not exist! - leaving program....\n");
    exit(0); //exit and stop the program
  }
  else
  {
    //if file exist

    while (fgets(line, SIZE, fileInput) != NULL)
    {

      if (numCity < ARRAY_SIZE)//check the number of cities exceeds the size of the array
      {

        /*if (strcmp(line, "\n") == 0) //if line has no line, end the program
        {
          wrongFormat();
        }*/
        strcpy(output_line, line); // copy the line of the text to the output file

        token = strtok(line, tab); // use strtok to get the date
        
        //if file input do not have the year-month-date, then stop the program
       /* if (sscanf(token, "%d-%d-%d", &year, &month, &day) == 0)
        {
          wrongFormat();
          return;
        }*/

        token = strtok(NULL, tab); //use strtok to get the time
        
        //if file input do not have the hour:min, then stop the program
     /*   if (sscanf(token, "%d:%d", &hour, &month) == 0)
        {
          wrongFormat();
          return;
        }*/

        city = strtok(NULL, tab); //use strtok to get the city
        
                                  //if file input do not have a string, then stop the program
      /*  if (sscanf(city, "%s", state) == 0)
        {
          wrongFormat();
          return;
        }*/

        cat = strtok(NULL, tab); //use strtok to get items
        
        //if file input do not have a string, then stop the program
     /*   if (sscanf(cat, "%s", items) == 0)
        {
          wrongFormat();
          return;
        }*/

        token = strtok(NULL, tab); //use strtok to get sales
        
        //if file input do not have double, then stop the program
      /*  if (sscanf(token, "%lf", &money) == 0)
        {
          wrongFormat();
          return;
        }
        else
        { */
          //if there is sales, contiune process
          sales = atof(token);
          addCity(city, sales);          //Calling the addCity function
          addCat(cat, sales);            //Calling the addCat function
          outputfile(output_line, city); //Calling the outputfile function
       // }
      }
      else
      {
        printf("You have exceed the limit of the program. The maximum number of cities is %d and the number of cities you have is %d\n", ARRAY_SIZE, numCity);
        exit(0);
      }
    }
  }
  fclose(fileInput); //closing the file
  return;
}

//this function prints the warning message if the context of the text does not match the format
void wrongFormat()
{
  printf("\033[31mFile in the wrong format!\n=========================\033[0m\nLeaving program...\n");
  printf("Please insert the file in this format: \"yyyy/mm/dd hh:ss city  item  sales payment\"\n");
  printf("For example:2012-01-01	09:00	Austin	Cameras	379.6	Visa\n");
  exit(0);
}
/*
Use top three after the  sorting algorithm has finished sorting the array from smallest to biggest
For top three, the array size of n -> arr[n], the top three biggest cities is 
calculated from the biggest to the smallest by arr[n-1],arr[n-2],arr[n-3] respectively
*/
void topthree(char *type)
{
  int topThree;
  //Max number of lines allowed: 45
  int maxLines = 45;     // For the printing of cities/items and sales
  int remainingLine = 0; //Remaining line of the spacing
  char *Spaces;
  char salesChar[10];
  if (strcmp(type, "city") == 0) //For sorting city struct
  {
    //topThree = n - 1
    //Top 1: arr[n-1]
    //Top 2: arr[n-2]
    //TOp 3: arr[n-3]
    for (topThree = numCity - 1; topThree >= numCity - 3; topThree--)//print the top three from the biggest to the smallest
    {
      snprintf(salesChar, sizeof(salesChar), "%.2f", cities[topThree].sales);//convert float sales to char sales
      remainingLine = maxLines - strlen(cities[topThree].city) - strlen(salesChar); //calcaute the remaining spacing
      Spaces = spaces(remainingLine);//call the spaces function
      printf("%s%s%.2f\n", cities[topThree].city, Spaces, cities[topThree].sales);//print the citiy and the sales of the top three
      free(Spaces);//free spaces from the memory
    }
  }
  else //For sorting items struct
  {
    for (topThree = numCat - 1; topThree >= numCat - 3; topThree--)//print the top three from the biggest to the smallest
    {
      snprintf(salesChar, sizeof(salesChar), "%.2f", cat[topThree].sales);//convert float sales to char sales
      remainingLine = maxLines - strlen(cat[topThree].type) - strlen(salesChar); //calcaute the remaining spacing
      Spaces = spaces(remainingLine);//call the spaces function
      printf("%s%s%.2f\n", cat[topThree].type, Spaces, cat[topThree].sales);//print the citiy and the sales of the top three
      free(Spaces);//free spaces from the memory
    }
  }
}
/*
Use bottom three after the  sorting algorithm has finished sorting the array from smallest to biggest
For top three, the array size of n -> arr[n], the bottom three biggest cities is 
calculated from the biggest to the smallest by arr[0],arr[1],arr[2] respectively
*/
//BottomThree = 2
//Top 1: arr[2]
//Top 2: arr[1]
//TOp 3: arr[0]
void bottomthree(char *type)
{
  int bottomThree;
  //Max number of lines allowed: 45
  int maxLines = 45;// For the printing of cities/items and sales
  int remainingLine = 0; //Remaining line of the spacing
  char *Spaces;
  char salesChar[10];
  if (strcmp(type, "city") == 0) //For sorting city struct
  {
    for (bottomThree = 2; bottomThree >= 0; bottomThree--)//print the bottom three from the biggest to the smallest
    {
      snprintf(salesChar, sizeof(salesChar), "%.2f", cities[bottomThree].sales);//convert float sales to char sales
      remainingLine = maxLines - strlen(cities[bottomThree].city) - strlen(salesChar);//calcaute the remaining spacing
      Spaces = spaces(remainingLine);//call the spaces function
      printf("%s%s%.2f\n", cities[bottomThree].city, Spaces, cities[bottomThree].sales);//print the citiy and the sales of the bottom three
      free(Spaces);//free spaces from the memory
    }
  }
  else
  {//For items 
    for (bottomThree = 2; bottomThree >= 0; bottomThree--)//print the bottom three from the biggest to the smallest
    {
      snprintf(salesChar, sizeof(salesChar), "%.2f", cat[bottomThree].sales);//convert float sales to char sales
      remainingLine = maxLines - strlen(cat[bottomThree].type) - strlen(salesChar);//calcaute the remaining spacing
      Spaces = spaces(remainingLine);//call the spaces function
      printf("%s%s%.2f\n", cat[bottomThree].type, Spaces, cat[bottomThree].sales);//print the citiy and the sales of the bottom three
      free(Spaces);//free spaces from the memory
    }
  }
}
char *spaces(int lines)
{
  char *space = malloc(sizeof(int) * lines); //allocate a memory space for the size of the spacing
  strcpy(space, " ");                        //copy " " into space
  for (int i = 0; i <= lines; i++)
  {
    strcat(space, " "); //create a loop to add more space depending on the number of lines needed
  }
  return space;
}
/*
Both the topthree and the bottom three uses the same sorting algorithm - the Bubble sort algorithm
==================================================================================================
HOW BUBBLE SORT ALGORITHM WORKS

EXAMPLE

 * * * * * * * * * * * * * * * * * * * * * * * * *
 *       *       *       *       *       *       *
 *   2   *   7   *   3   *    7  *   3   *   2   *
 *       *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * * * * *
 An array of size 6 arr[6] with the values of 2,7,3,7,3,2 and set a counter to the size of the array counter = 6
 The first pass involves reading the first two values
 * * * * * * * * * * * * * * * * * * * * * * * * *
 *       *       *       *       *       *       *
 *   2   *   7   *   3   *   7   *   3   *   2   *
 *       *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * * * * *
     ^       ^
 If the value the arr[1] is smaller than the value of arr[0], then swap them. Otherwise, do not swap
 The second pass reads the second and third values of the array  
 * * * * * * * * * * * * * * * * * * * * * * * * *
 *       *       *       *       *       *       *
 *   2   *   7   *   5   *   7   *   3   *   2   *
 *       *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * * * * *
             ^       ^  
 Using the same method as just now, since the value of arr[2] is smaller than arr[1], we swap them
 * * * * * * * * * * * * * * * * * * * * * * * * *
 *       *       *       *       *       *       *
 *   2   *   3   *   7   *   7   *   3   *   2   *
 *       *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * * * * *
             ^       ^  
 After it has been swaped, the third pass starts
 * * * * * * * * * * * * * * * * * * * * * * * * *
 *       *       *       *       *       *       *
 *   2   *   3   *   7   *   7   *   3   *   2   *
 *       *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * * * * *
                     ^       ^
 However this time, the value of arr[2] and arr[3] are the same. No swapping is required when both values are the same
 The fourth pass starts
 * * * * * * * * * * * * * * * * * * * * * * * * *
 *       *       *       *       *       *       *
 *   2   *   3   *   7   *   7   *   3   *   2   *
 *       *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * * * * *
                             ^       ^   
 Since arr[4] is smaller than arr[3], swapping is needed
 * * * * * * * * * * * * * * * * * * * * * * * * *
 *       *       *       *       *       *       *
 *   2   *   3   *   7   *   3   *   7   *   2   *
 *       *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * * * * *
                             ^       ^   
 Fifth pass                            
 * * * * * * * * * * * * * * * * * * * * * * * * *
 *       *       *       *       *       *       *
 *   2   *   3   *   7   *   3   *   7   *   2   *
 *       *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * * * * *
                                     ^       ^
 At the fifth pass, since arr[5] is smaller than arr[4], swapping is required
 * * * * * * * * * * * * * * * * * * * * * * * * *
 *       *       *       *       *       *       *
 *   2   *   3   *   7   *   3   *   2   *   7   *
 *       *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * * * * *
                                     ^       ^
 The end of the array has been reached. Decrement the counter by 1.
 Counter = 5
 Number of passes = Counter - 1;
 Number of passes:4
 The counter will determine the size of the array that is in effect of the bubble sort pointer: ^
 * * * * * * * * * * * * * * * * * * * * * 
 *       *       *       *       *       *
 *   2   *   3   *   7   *   3   *   2   *
 *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * 
 arr[5] is out since it is not needed for the alogorithm.
 Repeat the process 
 First pass
 * * * * * * * * * * * * * * * * * * * * * 
 *       *       *       *       *       *
 *   2   *   3   *   7   *   3   *   2   *
 *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * 
     ^       ^
 arr[1] < arr[0]:False -> no swap
 Second pass
 * * * * * * * * * * * * * * * * * * * * * 
 *       *       *       *       *       *
 *   2   *   3   *   7   *   3   *   2   *
 *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * 
             ^       ^
 arr[2] < arr[1]:False -> no swap
 Third pass
 * * * * * * * * * * * * * * * * * * * * * 
 *       *       *       *       *       *
 *   2   *   3   *   7   *   3   *   2   *
 *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * 
                     ^       ^
 arr[3] < arr[2]:True -> swap
 * * * * * * * * * * * * * * * * * * * * * 
 *       *       *       *       *       *
 *   2   *   3   *   3   *   7   *   2   *
 *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * 
                     ^       ^       
 Forth pass
 * * * * * * * * * * * * * * * * * * * * * 
 *       *       *       *       *       *
 *   2   *   3   *   3   *   7   *   2   *
 *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * 
                             ^       ^    
 arr[4] < arr[3]:Ture -> swap
 * * * * * * * * * * * * * * * * * * * * * 
 *       *       *       *       *       *
 *   2   *   3   *   3   *   2   *   7   *
 *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * 
                             ^       ^
 Counter--;
 Counter:4
 Number of passes:3  
 * * * * * * * * * * * * * * * * * 
 *       *       *       *       * 
 *   2   *   3   *   3   *   2   * 
 *       *       *       *       * 
 * * * * * * * * * * * * * * * * *  
 First pass 
 * * * * * * * * * * * * * * * * * 
 *       *       *       *       * 
 *   2   *   3   *   3   *   2   * 
 *       *       *       *       * 
 * * * * * * * * * * * * * * * * *                                                                                    
     ^       ^
 arr[1] < arr[0]:False -> no swap
 Second pass
 * * * * * * * * * * * * * * * * * 
 *       *       *       *       * 
 *   2   *   3   *   3   *   2   * 
 *       *       *       *       * 
 * * * * * * * * * * * * * * * * *                                                                                    
             ^       ^
 arr[2] < arr[1]:False -> no swap
 Third pass
 * * * * * * * * * * * * * * * * * 
 *       *       *       *       * 
 *   2   *   3   *   3   *   2   * 
 *       *       *       *       * 
 * * * * * * * * * * * * * * * * *                                                                                    
                     ^       ^
 arr[3] < arr[2]:True -> swap
 * * * * * * * * * * * * * * * * * 
 *       *       *       *       * 
 *   2   *   3   *   2   *   3   * 
 *       *       *       *       * 
 * * * * * * * * * * * * * * * * *                                                                                    
                     ^       ^    
 Counter--;
 Counter:3
 Number of passes:2
 * * * * * * * * * * * * * 
 *       *       *       * 
 *   2   *   3   *   2   * 
 *       *       *       * 
 * * * * * * * * * * * * *                                                                                    
 First pass
 * * * * * * * * * * * * * 
 *       *       *       * 
 *   2   *   3   *   2   * 
 *       *       *       * 
 * * * * * * * * * * * * * 
     ^       ^
 arr[1] < arr[0]:Flase -> no swap
 Second pass
 * * * * * * * * * * * * * 
 *       *       *       * 
 *   2   *   3   *   2   * 
 *       *       *       * 
 * * * * * * * * * * * * * 
             ^       ^
 arr[2] < arr[1]:True -> swap
 * * * * * * * * * * * * * 
 *       *       *       * 
 *   2   *   2   *   3   * 
 *       *       *       * 
 * * * * * * * * * * * * * 
             ^       ^
 Counter--;
 Counter:2
 Number of passes:1
 * * * * * * * * * 
 *       *       * 
 *   2   *   2   * 
 *       *       * 
 * * * * * * * * * 
 First pass
 arr[1] < arr[0]:False -> no swap
 After counter reaches 2, stop the sorting algorithm
 BEFORE
 * * * * * * * * * * * * * * * * * * * * * * * * *
 *       *       *       *       *       *       *
 *   2   *   7   *   3   *    7  *   3   *   2   *
 *       *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * * * * *     
 AFTER
 * * * * * * * * * * * * * * * * * * * * * * * * *
 *       *       *       *       *       *       *
 *   2   *   2   *   3   *    3  *   7   *   7   *
 *       *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * * * * *      
 It sorted from smallest to biggest
 TAKING TOP THREE CITIES 
 * * * * * * * * * * * * * * * * * * * * * * * * *
 *       *       *       *       *       *       *
 *   2   *   2   *   3   *    3  *   7   *   7   *
 *       *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * * * * * 
                              ^      ^       ^
 TAKING BOTTOM THREE CITIES 
 * * * * * * * * * * * * * * * * * * * * * * * * *
 *       *       *       *       *       *       *
 *   2   *   2   *   3   *    3  *   7   *   7   *
 *       *       *       *       *       *       *
 * * * * * * * * * * * * * * * * * * * * * * * * *
     ^       ^       ^                                                 
In this case, the counter is the counter of that determines the number of passes.
size is the number of passes
tmp and tmp2 are temproary struct that allows for swapping

*/
void sortingAlgorithm(char *type)
{
  int counter, size; // create counter and size
  if (strcmp(type, "city") == 0) // check if struct type is city
  {
    struct City tmp;  //create temporary city struct tmp for swapping
    struct City tmp2; //create temporary city struct tmp2 for swapping
    for (counter = 0; counter < numCity - 1; counter++) // this is for the counter that determines the number of passes
    {
      for (size = 0; size < numCity - counter - 1; size++) // size is the number of passes
      {
        if (cities[size].sales > cities[size + 1].sales) // if arr[a+1] is larger than arr[a], then swap then
        {
          //swapping
          tmp = cities[size + 1]; //arr[a+1] is moved into tmp
          tmp2 = cities[size]; //arr[a] is moved into tmp2
          cities[size] = tmp; //arr[a] gets value of arr[a+1]
          cities[size + 1] = tmp2; //arr[a+1] gets value of arr[a]
        }
      }
    }
    return;
  }
  else 
  {
    struct Category tmp; //create temporary city struct tmp for swapping
    struct Category tmp2;//create temporary city struct tmp2 for swapping
    for (counter = 0; counter < numCat - 1; counter++) // this is for the counter that determines the number of passes
    {
      for (size = 0; size < numCat - counter - 1; size++) // size is the number of passes
      {
        if (cat[size].sales > cat[size + 1].sales) // if arr[a+1] is larger than arr[a], then swap then
        {
          tmp = cat[size + 1];//arr[a+1] is moved into tmp
          tmp2 = cat[size];//arr[a] is moved into tmp2
          cat[size] = tmp;//arr[a] gets value of arr[a+1]
          cat[size + 1] = tmp2;//arr[a+1] gets value of arr[a]
        }
      }
    }
  }

}

void addCat(char name[], double sales)
{
  int i;//create i
  for (i = 0; i < numCat; i++)//for loop for adding item name and sales into struct
  {
    if (strcmp(cat[i].type, name) == 0) //if a item exist in the struct
    {
      cat[i].sales += sales; //add sales into the struct sales
      return;
    }
  }
  //if item does not exist in the struct 
  strcpy(cat[i].type, name); //copy city name into struct cat 
  cat[i].sales = sales;//copy sales into struct cat
  numCat++;//increase the number of items by 1
  return;
}
void outputfile(char line[], char *city)
{ 
  struct stat st;
  FILE *fileOutput;
  char file_type[5] = ".txt";
  char directory[11] = "./reports/";
  if (stat(directory, &st) == -1)
  {
    mkdir(directory, 0777); //chmod 777 allow read,write,execute of directory reports/
  }
  char *fileName = malloc((sizeof(city) + sizeof(file_type) + sizeof(directory) + 1));
  strcpy(fileName, directory); //add directory to fileName -> fileName: ./reports/
  strcat(fileName, city);      //add city to fileName -> e.g fileName: ./reports/Arlington
  strcat(fileName, file_type); //add file extension to fileName -> fileName: ./reports/Arlingon.txt
  fileOutput = fopen(fileName, "a+"); //Do write and append on the file
  fprintf(fileOutput, line, 0);       //output line to file
  free(fileName);   //free fileName from memory
  fclose(fileOutput); //free fileOutput from memory
  return;
}
void addCity(char name[], double sales)
{
  int i;//create i
  for (i = 0; i < numCity; i++)//for loop for adding city name and sales into struct
  {
    if (strcmp(cities[i].city, name) == 0)
    {
      cities[i].sales += sales;//add sales into the struct sales
      return;
    }
  }
    //if city does not exist in the struct 
  strcpy(cities[i].city, name); //copy city name into struct city 
  cities[i].sales = sales;//copy sales into struct city
  numCity++;//increase the number of city by 1
  return;
}
/*
For city
1) create a double variable called sales
2) create an integer variable called i and let i = 0
3) add cat[i] into sales
4) incrmenet i
5) repeat step 3 to 4 until i is equal to the number of category
6) Return sales
*/
double totalSales()
{
  double sales = 0.0; //step 1
  for (int i = 0; i <= numCity; i++) //step 3 -4 
  {
    sales += cities[i].sales;
  }
  return sales; // step 6
}
/*
* The average sales is calculated by the formula
*
*   Average = total sales / number of cities
*
*
*/
double average(double totalSales)
{
  return (totalSales) / (numCity);
}
/*
Calculating the  total and average sales for items
Alogrithm
1) create a double variable called sales
2) create an integer variable called i and let i = 0
3) add cat[i] into sales
4) incrmenet i
5) repeat step 3 to 4 until i is equal to the number of category
6) The average sales is calculated by the formula
*
*   Average = total sales / number of cities
After it is done, return sale
*/
double averageSales()
{
  double sales = 0.0;//step 1

  for (int i = 0; i <= numCat; i++) //step 3 - 4
  {
    sales += cat[i].sales;
  }

  return (sales) / (numCat);// step 6
}