//dboh, a simple decimal, binary, octal, hex number converter

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <limits.h>

#define NAME "c"

extern char * ascii_table[];

int startsWith(const char *str, const char *pre)
{
  size_t lenpre = strlen(pre), lenstr = strlen(str);
  return lenstr < lenpre ? 0 : memcmp(pre, str, lenpre) == 0;
}

void chopN(char *str, size_t n)
{
  size_t len = strlen(str);
  if (n > len)
    return;  // Or: n = len;
  memmove(str, str+n, len - n + 1);
}

char quads[16][5] = {"0000", "0001", "0010", "0011", "0100", "0101","0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110","1111"};

const char * hex_to_bin_quad(unsigned char c)
{
  if (c >= '0' && c <= '9') return quads[     c - '0'];
  if (c >= 'A' && c <= 'F') return quads[10 + c - 'A'];
  if (c >= 'a' && c <= 'f') return quads[10 + c - 'a'];
  return NULL;
}

void usage()
{
  printf(NAME " - converter\n");
  printf("\n");
  printf("Number base:\n");
  printf(NAME " <unsigned number>\n");
  printf("    convert number between 2/8/10/16 base.\n");
  printf("    '0b' for binary, '0o' for octal, '0x' for hex.\n");
  printf("\n");
  printf("ASCII:\n");
  printf(NAME " a<number>\n");
  printf("    convert ASCII value to visible char or descriptions.\n");
  printf("\n");
  printf(NAME " s<char or string>\n");
  printf("    convert char or string to corresponding ASCII value.\n");
  exit(0);
}

int main(int argc, char **argv)
{
  if(argc != 2 || startsWith(argv[1], "-"))
    usage();

  // flag to conv ascii value to char or desc.
  int asciiconv = 0;

  // default base value.
  int base = 10;
  char *input = argv[1];

  unsigned long number = 0;

  char *next;
 
  // convert chars to it's ascii value
  if(strlen(input) > 1 && startsWith(input, "s")) {
    chopN(input, 1);
    printf("Input: ");
    for( int i = 0; i < strlen(input); i++) {
      printf("%c\t", input[i]);
    }
    printf("\n");
    printf("ASCII: ");
    for( int i = 0; i < strlen(input); i++) {
      printf("%d\t", input[i], input[i]);
    }
    printf("\n");
    exit(0);
  }


  if(strlen(input) > 2 && startsWith(input, "0b")) {
    chopN(input, 2);
    base = 2;
  }
 
  if(strlen(input) > 2 && startsWith(input, "0o")) {
    chopN(input, 2);
    base = 8;
  }
 
  if(strlen(input) > 2 && startsWith(input, "0x")) {
    chopN(input, 2);
    base = 16;
  }

  // convert ascii value to visible char or descriptions.
  if(strlen(input) > 1 && startsWith(input, "a")) {
    chopN(input, 1);
    base = 10;
	  asciiconv = 1;
  }

  number = strtoul(input, &next, base);

  // if strtol failed
  if ((next == input) || (*next != '\0')) {
    fprintf(stderr, "invalid input\n");
    usage();
    exit(1);
  }

  if(asciiconv) {
    if(number < 0 || number > 127) {
      printf("Your input %d is out of ascii range\n", number);
      usage();
      exit(1);
    }
    printf("%s\n", ascii_table[number]);
    exit(0);
  }

  printf("dec: %lu\n", number);

  char * hex_str = malloc(16);

  if(number <= 0xff) {
    printf("hex: 0x%.2lx\n", number);
    sprintf(hex_str,"%.2lx", number);
  } else if(number <= 0xffff) {
    printf("hex: 0x%.4lx\n", number);
    sprintf(hex_str,"%.4lx", number);
  } else if(number <= 0xffffffff) {
    printf("hex: 0x%.8lx\n", number);
    sprintf(hex_str,"%.8lx", number);
  } else if(number <= 0xffffffffffff) {
    printf("hex: 0x%.12lx\n", number);
    sprintf(hex_str,"%.12lx", number);
  } else if(number <= 0xffffffffffffffff) {
    printf("hex: 0x%.16lx\n", number);
    sprintf(hex_str,"%.16lx", number);
  }

  printf("oct: 0o%lo\n", number);

  printf("bin:");

 
  while(*hex_str != '\0')
  {
        printf(" %s", hex_to_bin_quad(*hex_str));
        hex_str++;
  }
  printf("\n");
}
