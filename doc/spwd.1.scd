spwd(1) "ShorterPWD SPWD_VERSION" "User Commands"

# NAME

spwd - Shorter PWD

# SYNOPSIS
spwd [OPTION]...

# DESCRIPTION

Prints the current path, trimming the parents to fit a certain width. It is
intended to be used in the prompt (*PS1* or equivalent).

*-m* _width_
	Target width of the path.

*-a* _path-aliases_
	Path for the aliases file.

*-L*
	use PWD from environment, even if it contains symlinks

*-P*
	use physical path, from *getcwd*(3)


If no option is specified, -P is assumed.

# ALIASES

spwd can replace a path prefix with an alias. To use this feature, write the
aliases in a file, and specify the path to it with the *-a* option. See
*ALIASES FORMAT* below for a description of the format.

# ALIASES FORMAT

Every line in the file defines a new alias, with the following format:

	alias = path

Lines beginning with *#* are ignored. Spaces around *=* are stripped.

# EXAMPLES

Trim path to fit 40 characters:

	PS1='$(spwd -m 40)\$ '


# SEE ALSO

*pwd*(1), *getcwd*(3)
