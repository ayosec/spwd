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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "spwd.h"

#define STDOUT 1

static void usage() {
  char usage[] = {
#include "../build/USAGE.h"
  };

  ssize_t len = sizeof(usage);
  ssize_t offset = 0;
  while(offset < len) {
    ssize_t w = write(STDOUT, usage + offset, len - offset);
    if(w > 0) {
      offset += w;
    }

    if(w == 0 || (w < 0 && errno != EAGAIN)) {
      break;
    }
  }

  exit(0);
}

void extract_options(int argc, char** argv, struct options* options) {
  int option;

  /* Default values */
  options->physical = 1;
  options->maxwidth = 40;
  options->pathalias = NULL;

  /* Check command line arguments */
  while((option = getopt(argc, argv, "PLhm:a:")) != -1) {
    switch(option) {
      case 'h':
        usage();
        break;

      case 'P':
        options->physical = 1;
        break;

      case 'L':
        options->physical = 0;
        break;

      case 'a':
        options->pathalias = strdup(optarg);
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
