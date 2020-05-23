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
#include <ctype.h>
#include <stddef.h>

char* str_trim(char* str) {
  char* lastspace = NULL;
  char* start = NULL;
  for(; *str; str++) {
    if(isspace(*str)) {
      if(lastspace == NULL) {
        lastspace = str;
      }
    } else {
      lastspace = NULL;

      if(start == NULL) {
        start = str;
      }
    }
  }

  if(lastspace) {
    *lastspace = '\0';
  }

  return start;
}
