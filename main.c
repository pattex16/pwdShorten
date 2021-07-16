#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHORTENED_DIR_CHARS 3
#define HOME_SYMBOL '~'
#define SEPARATOR_SYMBOL '/'
#define REPLACEMENT_SYMBOL '+'

//argc = arguments count
//argv[0] = ./pwdShort
//argv[1] = $PWD
//argv[2] = $HOME

bool isCurrentDir(char* s) //check if you are examining the current directory
{
  bool result = true;
  int i = 0;
  while (s[i] != '\0') {
    if (s[i] == '/')
      result = false;
    i++;
  }
  return result;
}

int main(int argc, char* argv[])
{
  long int pwdLen = strlen(argv[1]);
  if (argv[1][1] == '\0'){
    printf("/");
    return 0;
  }
  long int homeLen = strlen(argv[2]);

  bool tilde = true;
  for (int i = 0; i < homeLen; i++)
    if (argv[1][i] != argv[2][i]) //check if you are in a subdirectory of your home
      tilde = false;

  int i;
  if (tilde) {
    printf("%c", HOME_SYMBOL); //home directory is substituded with a HOME_SYMBOL
    i = homeLen - 1;
  } else
    i = -1; //if you are not in a subdirectory of your home, '/' is left

  if (argv[1][homeLen] == '\0') //if you are actually in your home dir stop printing
    return 0;

  int charMax = 0;
  bool isReplacementPrinted = false;
  while (true) {

    i++;

    if (isCurrentDir(&argv[1][i])) { //current directory is printed with all of its characters
      printf("%c", argv[1][i]);
      if (argv[1][i + 1] == '\0')
        break;
      continue;
    }

    if (charMax > SHORTENED_DIR_CHARS-1 && isReplacementPrinted==false){ //print the REPLACEMENT_SYMBOL
      printf("%c",REPLACEMENT_SYMBOL);
      isReplacementPrinted = true;
    }

    if (argv[1][i] == '/') { //print each SEPARATOR_SYMBOL
      charMax = 0;
      isReplacementPrinted = false;
      printf("%c", SEPARATOR_SYMBOL);
      continue;
    }

    if (!isCurrentDir(&argv[1][i]) && charMax < SHORTENED_DIR_CHARS) { //for each subdirectory print the first SHORTENED_DIR_CHARS chars
      charMax++;
      //comment from here...
      if (argv[1][i] == '.') { //.dotdirs should have SHORTENED_DIR_CHARS+1 chars, including the dot
        printf(".%c", argv[1][i + 1]);
        i++;
      }
      //...to here if you dont want to have one extra char when shortening dotdirs
      else
        printf("%c", argv[1][i]); //print the SHORTENED_DIR_CHARS characters
      isReplacementPrinted = false;
      continue;
    }

  }
  printf("%c", '\0'); //end with a nice '\0'
  return 0;
}
