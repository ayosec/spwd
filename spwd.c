
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
  char *lastslash, *nextslash;
  int partsize;

  int option;
  unsigned long maxwidth = 40;

  /* Check command line arguments */
  while((option = getopt(argc, argv, "hm:")) != -1) {
    switch(option) {
      case 'h':
        printf("Smarter PWD. Usage %s [-m N]\n", argv[0]);
        exit(0);
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

  getcwd(cwd, sizeof(cwd));
  lastslash = cwd;

  while(strlen(cwd) > maxwidth) {
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
