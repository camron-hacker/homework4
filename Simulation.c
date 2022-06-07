/*
 *  File: Simulation.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* If there are custom classes/source files that you write, with
   custom functions, and you want those functions available for use in
   THIS .c file, then include the header file for the custom .c
   file(s) you've written, using the #include directive. For example:

   #include "SomeFile.h"

 */

void Simulate(char f[], int mem_size, int page_size) {
  
  printf("File name: %s\n", f);
  printf("Memory Size: %i\n", mem_size);
  printf("Page Size: %i\n", page_size);

  //establish variables
  int place = 0;
  int faults = 0;
  char line[12];
  int page_count = mem_size/page_size;
  int page_table[2][page_count];
  //initialize the page table
  for(int i = 0; i < page_count; i++){
    page_table[0][i] = -1;
    page_table[1][i] = 0;
  }
  //printf("%i", page_table[1][place]);

  //open file for reading
  FILE *file = fopen(f, "r");
  //check filestream
  if (file == NULL) {
      printf("Error: file pointer is null.\n");
      exit(1);
  }
  //main while loop, gets lines from input
  while (fgets(line, sizeof(line), file)){
    //variables
    char page[8];
    int page_bits = (int) log2((double) page_count);
    //printf("%i\n", page_bits);
    memcpy(page, line, 8);
    page[8] = '\0';

    int i;
    int found = 0;
    //printf("Page: %i\n", hexParse(page));

    for (i = 0; i < page_count; i++ ){
      //check for presence in table
      if(hexParse(page, page_bits) == page_table[0][i])
      {
        //printf("FOUND! %i %i\n", hexParse(page, page_bits), page_table[0][i]);
        found = 1;
      }
    }

    //if not found
    if(found == 0){
      //printf("NOT FOUND! %i %i\n", hexParse(page, page_bits), page_table[0][i]);
      faults++;

      while(1){
        //driving algorithm for second chance
        if(page_table[1][place] == 0){
          page_table[1][place] = 1;
          page_table[0][place] = hexParse(page, page_bits);
          break;
        } 
        else{
          page_table[1][place] = 0;
          place++;
        }

      }
    }
  }
  printf("Faults: %i\n", faults);


}

//parses the hex of the address into something readable
int hexParse(char page[], int bits){
  int count = 0;
  int page_sum = 0;

  while(page[count] && bits >= 0){

    switch(page[count]){
      case '0' : page_sum += (0 << bits);
        break;
      case '1' : page_sum += (1 << bits);
        break;
      case '2' : page_sum += (2 << bits);
        break;
      case '3' : page_sum += (3 << bits);
        break;
      case '4' : page_sum += (4 << bits);
        break;
      case '5' : page_sum += (5 << bits);
        break;
      case '6' : page_sum += (6 << bits);
        break;
      case '7' : page_sum += (7 << bits);
        break;
      case '8' : page_sum += (8 << bits);
        break;
      case '9' : page_sum += (9 << bits);
        break;
      case 'a' : page_sum += (10 << bits);
        break;
      case 'b' : page_sum += (11 << bits);
        break;
      case 'c' : page_sum += (12 << bits);
        break;
      case 'd' : page_sum += (13 << bits);
        break;
      case 'e' : page_sum += (14 << bits);
        break;
      case 'f' : page_sum += (15 << bits);
        break;
    }
    bits -= 4;
    count++;
  }
  return page_sum;
}

int main(int argc, char *argv[]) {
  // Run simulate
  if(argc >= 5 || argc <= 3){
    printf("Malformed simulation arguments; Correct use like: './Simulation trace.txt 64 4' \n");
    exit(1);
  }
  //printf("%s %s %s\n", argv[1], argv[2], argv[3]);

  Simulate(argv[1], atoi(argv[2]), atoi(argv[3]));

}
