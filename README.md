# Smarter PWD

This is something like a *pwd for long paths*. If you print the full path in your command line prompt, it becomes a bit annoying when you go into a really deep directory: your cursor will be almost at the right side of the terminal window, so it will be inevitable to jump to another line. Now, with SPWD, instead of adding the full path (with `\w` in Bash), you can add a call to this program, and the path will trimmed to fix in your preferred width.

For example, take a look at this typical path:

```
$ cd /tmp
$ mkdir -p lorem/ipsum/dolor/sit/amet/consectetur/adipisicing/elit/sed/do/eiusmod
$ PS1='$(spwd -m 40)$ '
/tmp$ cd lorem/ipsum/dolor/sit/
/tmp/lorem/ipsum/dolor/sit$ cd amet/consectetur/adipisicing/elit/
/t/l/i/d/s/a/c/adipisicing/elit$ cd sed/do/eiusmod/
/t/l/i/d/s/a/c/a/elit/sed/do/eiusmod$ pwd
/tmp/lorem/ipsum/dolor/sit/amet/consectetur/adipisicing/elit/sed/do/eiusmod
```

As you can see, the path parts are reduced to their first letter, until the full string is smaller than 40 characters. The last part is never trimmed. The shortest version of the previous path will be `/t/l/i/d/s/a/c/a/e/s/d/eiusmod`.

You can force that the minimal path is always used with `spwd -m 1`.

SPWD is written in plain C to reduce overhead as most as possible.

## Installation

Clone the [repository](https://github.com/ayosec/spwd.git) and compile the program

```
$ cd /some/path
$ git clone https://github.com/ayosec/spwd.git
$ cd spwd
$ make
```

Then, edit your shell initialization script (like `~/.bashrc`), and make a call to `swpd`. If your `$PS1` variable is defined with something like

```
export PS1='\u@\h:\w\$ '
```

You have to replace the `\w` string with `$(/some/path/spwd/spwd -m 40)`, like

```
export PS1='\u@\h:$(/some/path/spwd/spwd -m 40)\$ '
```

Then, reload the session and you will enjoy your shorter paths.
