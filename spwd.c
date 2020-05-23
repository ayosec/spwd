/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Ayose <ayosec@gmail.com>
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct options {
  unsigned char physical;
  unsigned long maxwidth;
  char*         pathalias;
  
};

void parseargs(int argc, char** argv, struct options* options) {
  int option;

  /* Default values */
  options->physical = 1;
  options->maxwidth = 40;
  options->pathalias = NULL;

  /* Check command line arguments */
  while((option = getopt(argc, argv, "PLhm:a:")) != -1) {
    switch(option) {
      case 'h':
        printf("ShorterPWD. Usage %s [OPTION]\n", argv[0]);
        exit(0);
        break;

      case 'P':
        options->physical = 1;
        break;

      case 'L':
        options->physical = 0;
        break;

      case 'a':
        options->pathalias = optarg;
        break;

      case 'm':
        {
          char *invalidpart;
          options->maxwidth = strtoul(optarg, &invalidpart, 10);
          if(*invalidpart) {
            fprintf(stderr, "Invalid number: %s\n", optarg);
            exit(1);
          }
        }
        break;

      default:
        exit(2);
    }
  }
}

void strchomp(char* str) {
  char* lastspace = NULL;
  for(; *str; str++)
    if(isspace(*str))
      lastspace = str;

  if(lastspace)
    *lastspace = '\0';
}

int main(int argc, char** argv)
{
  struct options options;
  char cwd[512];
  char *var;
  char *lastslash, *nextslash;

  parseargs(argc, argv, &options);

  strcpy(cwd, "<?>"); /* Default value to be used when getcwd/PWD fails */

  if(options.physical) {
    getcwd(cwd, sizeof(cwd));
  } else {
    if((var = getenv("PWD"))) {
      memset(cwd, 0, sizeof(cwd));
      strncpy(cwd, var, sizeof(cwd) - 1);
    }
  }

  /* We are going to use lastslash as a flag to detect if the
   * original path have been modified. If it remains NULL,
   * it means that nobody has modified it. If it is a non NULL
   * value, it will be the first slash to be shorted
   */
  lastslash = NULL;

  /* Check if we are under home. If so, we can short it with ~ */
  if((var = getenv("HOME"))) {
    int homelen = strlen(var);
    if(strncmp(var, cwd, homelen) == 0) {
      cwd[0] = '~';
      lastslash = cwd + 1;
      memmove(lastslash, cwd + homelen, strlen(cwd));
    }
  }

  /* Find a possible alias for the current directory */
  if(options.pathalias) {
    FILE *faliases = fopen(options.pathalias, "r");
    if(faliases == NULL) {
      perror(options.pathalias);
    } else {
      char line[1024];
      char* separator;
      size_t partlen;

      while(fgets(line, sizeof(line), faliases)) {
        if((separator = index(line, '='))) {
          strchomp(line);

          *separator = '\0';
          partlen = strlen(line);

          if((partlen < sizeof(cwd)) && strncmp(separator + 1, cwd, strlen(separator + 1)) == 0) {
            /* This will fail if the alias is longer than the path, but
             * I can assume that "nobody" will create an alias like that,
             * right?
             */
            memcpy(cwd, line, partlen);
            memmove(cwd + partlen, cwd + strlen(separator + 1), sizeof(cwd) - partlen);
            lastslash = cwd + partlen;
            break;
          }
        }
      }

      fclose(faliases);
    }
  }

  /* Short parts */
  if(lastslash == NULL)
    lastslash = index(cwd, '/');

  while(lastslash != NULL && strlen(cwd) > options.maxwidth) {
    int partsize;

    nextslash = index(lastslash + 1, '/');

    if(nextslash == NULL)
      break;

    partsize = nextslash - lastslash;
    if(partsize > 3)
      memmove(lastslash + 2, nextslash, strlen(cwd) + 1);

    lastslash += 2;
  }

  printf("%s\n", cwd);

  return 0;
}
