#include <stdio.h>

void print_char_bits(char c);
void print_int_bits(int i);
void print_mem_bits(void* p, int nbytes);

void print_int_bits(int x){


  for(int loops = sizeof(x) - 1; loops >= 0; loops++) {
    int compare = 1;
    compare = compare << 8;
    int tempX = x >> 8;
    printf("%d\n", tempX);

    for(int i = 0; i < 8; i++) {
      compare = compare >> i;
      int result = tempX & compare;
      if (result)
        printf("%d", 1);
      else
        printf("%d", 0);
    }

    printf(" ");
  }
}

void print_char_bits(char c){
  int compare;
  for(int i = 0; i < 8; i++) {
    compare = 0b10000000;
    compare = compare >> i;
    int result = c & compare;
    if (result)
      printf("%d", 1);
    else
      printf("%d", 0);
  }
}

int main(void){

  //print_char_bits('a');
  print_int_bits(5);
  printf("\n");

}