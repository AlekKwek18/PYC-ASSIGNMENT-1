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
File name : p1804247.h

/* header file is responsible to maintain all the:
1)#define statements.  
2)function prototypes.
3)struct declarations.
*/
#define READ "r"          //create a constant for read operation for file
#define WRITE "w"         //create a constant for write operation for file
#define WRITE_APPEND "a+" //create a constant for write and append for file
#define CITY "city"       //create a constant for "city"
#define CAT "cat"         //create a costant for "cat"
#define ARRAY_SIZE 1000   //create a constant array size of size one million for both struct city and category which is the max size
char *first_time;                // this is for the time stamp at the start of the program

struct City
{
  char city[255];
  double sales; //sales
};
//creating a struct called category
struct Category
{
  char type[255];
  double sales;
};
struct Category cat[ARRAY_SIZE]; //create a category struct, short for cat of size 1000000
struct City cities[ARRAY_SIZE];  //create a city strcut of size 1000000

//prototype for functions
double totalSales();
double averageSales();
double average(double totalSales);
void salesInput(char *fileName);
void addCity(char name[], double sales);
void addCat(char name[], double sales);
void outputCity(char line[]);
void printcity();
void printcat();
void outputfile(char line[], char *city);
void summary();
void sortingAlgorithm(char *type);
void topthree(char *type);
char *spaces(int lines);
void bottomthree(char *type);
char *setCurrentTime();
void wrongFormat();

char *first_time;                // this is for the time stamp at the start of the program
