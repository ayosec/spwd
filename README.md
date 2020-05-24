# ShorterPWD

ShorterPWD is a tool to show the current path, trimming the parents to fit a certain width. It is intended to be used in the prompt (`PS1` or equivalent).

## Example

First, we start in a *very* long path:

```console
$ mkdir -p /tmp/lorem/ipsum/dolor/sit/amet/consectetur/adipisicing/elit/sed/do/eiusmod

$ cd /tmp/lorem/ipsum/dolor/sit/amet/consectetur/adipisicing/
```

Then, with `spwd -m 40` we print the path trimmed to 40 characters:

```console
$ spwd -m 40
/t/l/i/d/s/amet/consectetur/adipisicing

$ cd elit/sed/do/eiusmod

$ spwd -m 40
/t/l/i/d/s/a/c/a/elit/sed/do/eiusmod

$ spwd -m 20
/t/l/i/d/s/a/c/a/e/s/d/eiusmod
```

The parents are trimmed to their first character until the length of the path is smaller than the value in the `-m` option. The last part is never trimmed.

You can always trim all parents with `spwd -m 0`.

## Installation

Use `make install` to compile and install the tool.

```
$ git clone https://github.com/ayosec/spwd.git
$ cd spwd
$ make test
$ sudo make install
```

By default it is installed in `/usr/local/bin`. If you want a different destination use the `DEST` variable. For example, to install the tool in `/usr/bin`, type:

```bash
$ sudo make DEST=/usr install
```

## Usage

To use spwd in your prompt, replace the sequence `\w` with `$(spwd -m XX)` in your `PS1` variable.

For example, instead of:

```bash
PS1='\u@\h \w\$ '
```

Use:

```bash
PS1='\u@\h $(spwd -m 40)\$ '
```

## Aliases

spwd can replace a path prefix with an alias.

The aliases are defined in a file with the following format:

```
alias1 = path1

# Comment
alias2 = path2
```

To use them, add the `-a path` option to the `spwd` command.

Theses aliases are never trimmed.

### Example

First, create a file `~/.config/spwd/aliases`:

```
[My Projects] = /here/are/my/projects
[Work] = /home/user/content/work
```

Then, update the `PS1` variable to include the `-a` option:

```bash
PS1='\u@\h $(spwd -m 40 -a ~/.config/spwd/aliases)\$ '
```

Now, we can see our alias in the prompt instead of the full path.

```
~ $ cd /here/are/my/projects/something

[My Projects]/something $
```

## Tests

To launch the tests type `make test` in the root directory.
