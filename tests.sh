#!/bin/bash
#
# shellcheck disable=SC2088

EXIT=0

set -euo pipefail

fail() {
  echo -e "\\033[31m$*\\033[m"
  EXIT=1
}

spec() {
  title="$1"
  cmd="$2"
  expected="$3"

  printf "* %-30s" "$title"
  found="$(sh -c "$cmd")" || (fail "EXIT $?"; return 1)
  if [ "$expected" != "$found" ]
  then
    fail FAILED
    echo "  EXPECTED: $expected"
    echo "     FOUND: $found"
    return 0
  fi

  echo -e "\\033[32mOK\\033[m"
}

zeros() {
  head < /dev/zero -c "$1" | tr \\0 0
}

make -s
BIN="$(pwd)/build/spwd.dbg"

# Use a known path to launch tests

mkdir -p /tmp/.spwd/lorem/ipsum/dolor/sit/amet/consectetur
cd /tmp/.spwd/lorem/ipsum/dolor/sit/amet/consectetur


# Base logic

spec "full path" \
  "$BIN -m 100" \
  "/tmp/.spwd/lorem/ipsum/dolor/sit/amet/consectetur"

spec "short path" \
  "$BIN -m 30" \
  "/t/./l/i/d/s/amet/consectetur"

spec "only last path" \
  "$BIN -m 1" \
  "/t/./l/i/d/s/a/consectetur"


# Support for $HOME

spec "use HOME" \
  "HOME=/tmp/.spwd/lorem $BIN -m 100" \
  "~/ipsum/dolor/sit/amet/consectetur"

spec "use HOME, short path" \
  "HOME=/tmp/.spwd/lorem $BIN -m 24" \
  "~/i/d/s/amet/consectetur"

spec "HOME, only last path" \
  "HOME=/tmp/.spwd/lorem $BIN -m 1" \
  "~/i/d/s/a/consectetur"


# Logical paths

spec "use logical paths" \
  "PWD=/x $BIN -L" \
  "/x"

spec "support long values" \
  "PWD=/$(zeros 1000) $BIN -L" \
  "/$(zeros 510)"

spec "logical to physical" \
  "PWD=/x $BIN -L -P -m 1" \
  "/t/./l/i/d/s/a/consectetur"


# Path aliases

ALIASES=/tmp/.spwd/aliases
cat > "$ALIASES" <<EOF
[AMET]  = /tmp/.spwd/lorem/ipsum/dolor/sit/amet

Invalid lines
=

# NOP=/tmp/.spwd/lorem/ipsum
THE IPSUM=/tmp/.spwd/lorem/ipsum
EOF

spec "first path alias" \
  "PWD=/tmp/.spwd/lorem/ipsum/dolor $BIN -a $ALIASES -L -m 100" \
  "THE IPSUM/dolor"

spec "second path alias" \
  "cd /tmp/.spwd/lorem/ipsum/dolor/sit/amet/consectetur && $BIN -a $ALIASES -m 100" \
  "[AMET]/consectetur"



exit $EXIT
