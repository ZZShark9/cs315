#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//helper methods
char detectInput(char *input);
char* twosComp(char* b);
int biggestPlace(int u, int i);
//transformation methods
char* u2b(int u);
char* s2b(int s);
char* h2b(char* x);
char* b2h(char* b);
int b2u(char* b);
int b2s(char* b);


int main(int argc, char** argv) {
  if (argc != 2){
     printf("Please input a singe number\n");
  } else {
    char type = detectInput(argv[1]);

    //starting with unsigned
    if (type == 'u') {
      char* binary = u2b(atoi(argv[1]));
      char* hex = b2h(binary);

      printf("%s (base 10) ", argv[1]);
      int i;
      for(i=0; binary[i] != '\0'; i++) {
        if (i % 4 == 0) {
          printf(" ");
        }
        printf("%c", binary[i]);
      }
      printf(" (base 2) 0b%s (base 2) 0x%s (base 16)", binary, hex);

      free(binary);
      free(hex);
    } else if (type == 's') {
      char* binary = s2b(atoi(argv[1]));
      char* hex = b2h(binary);

      printf("%s (base 10) ", argv[1]);
      int i;
      for(i=0; binary[i] != '\0'; i++) {
        if (i % 4 == 0) {
          printf(" ");
        }
        printf("%c", binary[i]);
      }
      printf(" (base 2) 0b%s (base 2) 0x%s (base 16)", binary, hex);

      free(binary);
      free(hex);
    } else if (type == 'b') {
      char* basicBinary = argv[1] + 2;
      int u = b2u(basicBinary);
      int s = b2s(basicBinary);
      char* hex = b2h(basicBinary);

      printf("%s (base 2) %d (base 10) %d (base 10 signed) 0x%s (base 16)", argv[1], u, s, hex);
    
      free(hex);
    } else if (type == 'x') {
      char* binary = h2b(argv[1] + 2);
      int u = b2u(binary);
      int s = b2s(binary);

      printf("%s (base 16) ", argv[1]);
      int i;
      for(i=0; binary[i] != '\0'; i++) {
        if (i % 4 == 0) {
          printf(" ");
        }
        printf("%c", binary[i]);
      }
      printf(" (base 2) 0b%s (base 2) %d (base 10) %d (base 10 signed)", binary, u, s);
    
      free(binary);
    }

    printf("\n");
  }
}

/*detects which type the input argument is 
and checks some for validity */
char detectInput(char* input) {
  int i;
  if (input[1] == 'b') {
  for(i=2; input[i] != '\0'; i++) {
    if (input[i] != '0' && input[i] != '1')
      return 'f';
  }
    return 'b';
  } else if (input[1] == 'x') {
    return 'x';
  } else if (input[0] == '-') {
    return 's';
  } else {
    return 'u';
  }
}

/* returns the twos compliment of a binary number */ 
char* twosComp(char* binary) {
  int digits = 0;
  int i;
  for(i=0; binary[i] != '\0'; i++) {
    digits++;
  }
  char* result = malloc(digits);

  //flip digits
  for(i=0; i<digits; i++){
    if (binary[i] == '0')
      result[i] = '1';
    else
      result[i] = '0';
  }

  int minusOne = b2u(result);
  minusOne++;
  result = u2b(minusOne);

  return result;
}

/*returns the place of the most significant 1 in the binary of an int*/
int biggestPlace(int u, int i) {
  if ((1 << i) > u) {
    return i-1;
  } else if ((1 << i) == u) {
    return i;
  } else {
    return biggestPlace(u, i+1);
  }
}

/*transforms an unsigned int into binary*/
char* u2b(int u) {
  int place = biggestPlace(u, 0);
  int size = place + 1;
  char result[size];
  int i;
  for(i=0; i<size; i++) {
    result[i] = '0';
  }
  result[0] = '1';
  u -= (1 << place);

  while (u != 0) {
    place = biggestPlace(u, 0);
    result[(size - place - 1)] = '1';
    u -= (1 << place);
  }

  //adds starting 0s for cleanliness
  int diff = 4 - ((size+4) % 4);
  char* final = malloc(size + diff + 1);
  for(i=0; i<diff; i++) {
    final[i] = '0';
  }
  for(i=0; i<size; i++){
    final[i+diff] = result[i];
  }

  return final;
}

/* transforms signed int to binary */
char* s2b(int s) {
  char* binary = u2b(s * (-1));
  binary = twosComp(binary);
  printf("binary after 2s: %s\n", binary);

  return binary;
}

/* transforms hex to binary */
char* h2b(char* x) {
  int i, count;
  int digits = 0;
  for(i=0; x[i] != '\0'; i++) {
    digits++;
  }
  char* binary = malloc(digits*4 +1);
  for(i=0; i<digits; i++){
    switch(x[i]) {
      case 'f':
      case 'F':
        binary[i*4] = '1';
        binary[i*4+1] = '1';
        binary[i*4+2] = '1';
        binary[i*4+3] = '1';
        break;
      case 'e':
      case 'E':
        binary[i*4] = '1';
        binary[i*4+1] = '1';
        binary[i*4+2] = '1';
        binary[i*4+3] = '0';
        break;
      case 'd':
      case 'D':
        binary[i*4] = '1';
        binary[i*4+1] = '1';
        binary[i*4+2] = '0';
        binary[i*4+3] = '1';
        break;
      case 'c':
      case 'C':
        binary[i*4] = '1';
        binary[i*4+1] = '1';
        binary[i*4+2] = '0';
        binary[i*4+3] = '0';
        break;
      case 'b':
      case 'B':
        binary[i*4] = '1';
        binary[i*4+1] = '0';
        binary[i*4+2] = '1';
        binary[i*4+3] = '1';
        break;
      case 'a':
      case 'A':
        binary[i*4] = '1';
        binary[i*4+1] = '0';
        binary[i*4+2] = '1';
        binary[i*4+3] = '0';
        break;
      default:
        printf("");
        char* binChunk = u2b( x[i] -'0' );
        int j;
        for(j=0; j<4; j++){
          binary[i*4+j] = binChunk[j];
        }
        free(binChunk);
    }
  }

  return binary;
}

/*converts a binary decimal to hex*/
char* b2h(char* b) {
  int digits = 0;
  int i;
  for(i=0; b[i] != '\0'; i++) {
    digits++;
  }

  digits = digits / 4;
  char* result = malloc(digits + 1);

  int j, count;
  for(i=0; i<digits; i++){
    count = 0;
    for(j=0; j<4; j++){
      if (b[i * 4 + j] == '1'){
        count += (1 << (3-j));
      }
    }
    switch (count) {
      case 10:
        result[i] = 'A';
        break;
      case 11:
        result[i] = 'B';
        break;
      case 12:
        result[i] = 'C';
        break;
      case 13:
        result[i] = 'D';
        break;
      case 14:
        result[i] = 'E';
        break;
      case 15:
        result[i] = 'F';
        break;
      default:
        result[i] = (char) (count+'0');
    }
  }
  return result;
}

/*transforms binary to unsigned int */
int b2u(char* b) {
  int digits = 0;
  int i;
  for(i=0; b[i] != '\0'; i++) {
    digits++;
  }
  int count = 0;
  for(i=0; i<digits; i++) {
    if (b[i] == '1') {
      count += (1 << (digits-i-1));
    }
  }
  return count;
}

/*transforms binary to signed int */
int b2s(char* b) {
  int digits = 0;
  int i;
  for(i=0; b[i] != '\0'; i++) {
    digits++;
  }
  int count = 0;
  int first = 1;
  for(i=0; i<digits; i++) {
    if (b[i] == '1' && first == 1) {
      count -= (1 << (digits-i-1));
      first = 0;
    } else if (b[i] == '1' && first == 0) {
      count += (1 << (digits-i-1));
    }
  }
  return count;
}
