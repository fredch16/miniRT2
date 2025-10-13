## 📜 About Project

> _The aim of this project is to code a C library regrouping usual functions that you'll be allowed to use in all your other projects._


	🚀 TLDR: this project consists of coding basic C functions (see below), which are then
	compiled into a library for use in other projects of the cursus.

> [!NOTE]  
> Because of 42 School norm requirements:
> * Each function can't have more than 25 lines of code.
> * All variables are declared and aligned at the top of each function.
> * Projects should only use the explicitly allowed functions.

## 📑 Functions List

### Functions from `<ctype.h>` library
* [`ft_isascii`](libft/ft_isascii.c)	- test for ASCII character.
* [`ft_isalnum`](libft/ft_isalnum.c)	- alphanumeric character test.
* [`ft_isalpha`](libft/ft_isalpha.c)	- alphabetic character test.
* [`ft_isdigit`](libft/ft_isdigit.c)	- decimal-digit character test.
* [`ft_isprint`](libft/ft_isprint.c)	- printing character test (space character inclusive).
* [`ft_tolower`](libft/ft_tolower.c)	- upper case to lower case letter conversion.
* [`ft_toupper`](libft/ft_toupper.c)	- lower case to upper case letter conversion.

### Functions from `<stdlib.h>` library
* [`ft_atoi`](libft/ft_atoi.c)		  - convert ASCII string to integer.
* [`ft_calloc`](libft/ft_calloc.c)	- memory allocation.

### Functions from `<strings.h>` library
* [`ft_bzero`](libft/ft_bzero.c)		  - write zeroes to a byte string.
* [`ft_memset`](libft/ft_memset.c)		- write a byte to a byte string.
* [`ft_memchr`](libft/ft_memchr.c)		- locate byte in byte string.
* [`ft_memcmp`](libft/ft_memcmp.c)		- compare byte string.
* [`ft_memmove`](libft/ft_memmove.c)	- copy byte string.
* [`ft_memcpy`](libft/ft_memcpy.c)		- copy memory area.

### Functions from `<string.h>` library
* [`ft_strlen`](libft/ft_strlen.c)		  - find length of string.
* [`ft_strchr`](libft/ft_strchr.c)		  - locate character in string (first occurrence).
* [`ft_strrchr`](libft/ft_strrchr.c)	  - locate character in string (last occurence).
* [`ft_strnstr`](libft/ft_strnstr.c)	  - locate a substring in a string (size-bounded).
* [`ft_strncmp`](libft/ft_strncmp.c)		  - compare strings (size-bounded).
* [`ft_strdup`](libft/ft_strdup.c)			- save a copy of a string (with malloc).
* [`ft_strlcpy`](libft/ft_strlcpy.c)		- size-bounded string copying.
* [`ft_strlcat`](libft/ft_strlcat.c)		- size-bounded string concatenation.

### Non-standard functions
* [`ft_putchar_fd`](libft/ft_putchar_fd.c)	- output a character to given file.
* [`ft_putstr_fd`](libft/ft_putstr_fd.c)		- output string to given file.
* [`ft_putendl_fd`](libft/ft_putendl_fd.c)	- output string to given file with newline.
* [`ft_putnbr_fd`](libft/ft_putnbr_fd.c)		- output integer to given file.
* [`ft_itoa`](libft/ft_itoa.c)					    - convert integer to ASCII string.
* [`ft_substr`](libft/ft_substr.c)				  - extract substring from string.
* [`ft_strtrim`](libft/ft_strtrim.c)			  - trim beginning and end of string with the specified characters.
* [`ft_strjoin`](libft/ft_strjoin.c)			  - concatenate two strings into a new string (with malloc).
* [`ft_split`](libft/ft_split.c)				    - split string, with specified character as delimiter, into an array of strings.
* [`ft_strmapi`](libft/ft_strmapi.c)			  - create new string from modifying string with specified function.
* [`ft_striteri`](libft/ft_striteri.c)			  - applies the specific function on each character of the string.

### Linked list functions

* [`ft_lstnew`](libft/srcs/lst/ft_lstnew.c)				- create new list.
* [`ft_lstsize`](libft/srcs/lst/ft_lstsize.c)			- count elements of a list.
* [`ft_lstlast`](libft/srcs/lst/ft_lstlast.c)			- find last element of list.
* [`ft_lstadd_back`](libft/srcs/lst/ft_lstadd_back.c)	- add new element at end of list.
* [`ft_lstadd_front`](libft/srcs/lst/ft_lstadd_front.c)	- add new element at beginning of list.
* [`ft_lstdelone`](libft/srcs/lst/ft_lstdelone.c)		- delete element from list.
* [`ft_lstclear`](libft/srcs/lst/ft_lstclear.c)			- delete sequence of elements of list from a starting point.
* [`ft_lstiter`](libft/srcs/lst/ft_lstiter.c)			- apply function to content of all list's elements.
* [`ft_lstmap`](libft/srcs/lst/ft_lstmap.c)				- apply function to content of all list's elements into new list.

## 👨‍💻 Usage
### Requirements

The library is written in C language and thus needs the **gcc compiler** and some standard **C libraries** to run.

### Instructions

To pull files ↙️
```bash
git clone git@github.com:fredch16/libft.git
```
**1. Compiling the library**

To compile the library, run:

```shell
$ cd path/to/libft && make
```

**2. Using it in your code**

To use the library functions in your code, simply include its header:

```C
#include "libft.h"
```

and, when compiling your code, add the required flags:

```shell
-lft -L path/to/libft.a -I path/to/libft.h
```