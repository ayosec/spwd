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

#include "spwd.h"
#include <stdio.h>
#include <string.h>

void replace_alias(char* path, char* cwd, size_t cwd_size, char** lastslash) {
  FILE *faliases;
  char *alias, *target, *separator;
  char buf[1024];
  size_t alias_len;

  faliases = fopen(path, "r");

  if(faliases == NULL) {
    perror(path);
    return;
  }

  while(fgets(buf, sizeof(buf), faliases)) {
    if(buf[0] == '#') {
      continue;
    }

    if((separator = index(buf, '='))) {
      *separator = '\0';
      alias = str_trim(buf);
      target = str_trim(separator + 1);

      if(alias == NULL) {
        continue;
      }

      alias_len = strlen(alias);

      if(strncmp(target, cwd, strlen(target)) == 0) {
        memmove(cwd + alias_len, cwd + strlen(target), cwd_size - alias_len);
        memcpy(cwd, alias, alias_len);
        *lastslash = cwd + alias_len;
        break;
      }
    }
  }

  fclose(faliases);
}
