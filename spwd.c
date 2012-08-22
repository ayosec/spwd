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

int main(int argc, char** argv)
{
  char cwd[512];
  char *home;
  char *lastslash, *nextslash;
  unsigned char physical = 1;

  int option;
  unsigned long maxwidth = 40;

  /* Check command line arguments */
  while((option = getopt(argc, argv, "PLhm:")) != -1) {
    switch(option) {
      case 'h':
        printf("Smarter PWD. Usage %s [OPTION]\n", argv[0]);
        exit(0);
        break;

      case 'P':
        physical = 1;
        break;

      case 'L':
        physical = 0;
        break;

      case 'm':
        {
          char *invalidpart;
          maxwidth = strtoul(optarg, &invalidpart, 10);
          if(*invalidpart) {
            fprintf(stderr, "Invalid number: %s\n", invalidpart);
            exit(1);
          }
        }
        break;

      default:
        fprintf(stderr, "Invalid option: %c\n", option);
        exit(2);
    }
  }

  if(physical) {
    getcwd(cwd, sizeof(cwd));
  }
  else {
    strncpy(cwd, getenv("PWD"), sizeof(cwd) - 1);
  }


  /* Check if we are under home. If so, we can short it with ~ */
  if((home = getenv("HOME"))) {
    int homelen = strlen(home);
    if(strncmp(home, cwd, homelen) == 0) {
      cwd[0] = '~';
      memmove(cwd + 1, cwd + homelen, strlen(cwd));
    }
  }

  /* Short parts */
  lastslash = index(cwd, '/');
  while(strlen(cwd) > maxwidth) {
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
