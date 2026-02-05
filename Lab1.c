/******************************************************************************



              Online C Compiler.

        Code, Compile, Run and Debug C program online.

Write your code in this editor and press "Run" button to compile and execute it.



*******************************************************************************/



/* Name: [Mohamed Ali] */ // Your student name

/* Student ID: [N01440760] */ // Your student ID



#include <stdio.h> // Include standard input/output library
#include <stdlib.h> // Include standard library





struct Account {

  unsigned int account_number; // Variable  account number

  char account_type;      // Variable  account type

  char *last_name;       // Pointer for last name string

  char *first_name;      // Pointer for first name string

  float balance;        // Variable  account balance

  char reserved[6];      // Reserved space array

};



int main(void)

{

  // Define variables using animal names

  char cat;          // character variable

  short dog;          // short variable

  int lion;          // int variable

  long eel;         // long variable

  float fish;         // float variable

  double monkey;        // double variable



  // Define pointer variables

  int *lionPtr;        // pointer to int

  long *eelPtr;       // pointer to long

  float *fishPtr;       // pointer to float

  double *eaglePtr;      // pointer to double



  // Define struct variables

  struct Account mice;    // struct Account variable

  struct Account *micePtr;  // pointer to the struct



  // Display sizes using the sizeof operator

  printf("sizeof(char) = %zu\n", sizeof(cat));    // Print size of char

  printf("sizeof(short) = %zu\n", sizeof(dog));   // Print size of short

  printf("sizeof(int) = %zu\n", sizeof(lion));    // Print size of int

  printf("sizeof(long) = %zu\n", sizeof(eel));   // Print size of long

  printf("sizeof(float) = %zu\n", sizeof(fish));   // Print size of float

  printf("sizeof(double) = %zu\n", sizeof(monkey)); // Print size of double



  // Display sizes of pointers

  printf("sizeof(int*) = %zu\n", sizeof(lionPtr));  // Print size of int pointer

  printf("sizeof(long*) = %zu\n", sizeof(eelPtr)); // Print size of long pointer

  printf("sizeof(float*) = %zu\n", sizeof(fishPtr)); // Print size of float pointer

  printf("sizeof(double*) = %zu\n", sizeof(eaglePtr));// Print size of double pointer



  // Display size of the struct and struct pointer

  printf("sizeof(struct Account) = %zu\n", sizeof(mice));   // Print struct size

  printf("sizeof(struct Account*) = %zu\n", sizeof(micePtr)); // Print struct pointer size



  return 0; // Return 0 to show successful completion

}
