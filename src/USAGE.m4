spwd SPWD_VERSION
https://github.com/ayosec/spwd

Prints the current path, trimming the parents to fit a certain width.

Usage:

    spwd [OPTIONS]

    PS1='\u@\h $(spwd -m 40)\$ '


Options:

    -P            Print physical path (getcwd(3)).
    -L            Print logical path ($PWD),
    -m [width]    Set target width for the printed path.
    -a [path]     Path of the aliases file.

