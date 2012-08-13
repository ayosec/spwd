
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

int main(int argc, char** argv)
{
  char cwd[512];
  char *lastslash, *nextslash;
  int partsize;
  unsigned int maxwidth = 40;

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

  printf("%s", cwd);

  return 0;
}
