# Make IsEven

## Documentation
### In-app doc
By executing the command; `$ mk_isEven doc`, you can have this documentation:
```
USAGE:
	In EBNF (I use the one from this website: https://www.garshol.priv.no/download/text/bnf.html#id2.1. with <> before and after symbol), the program can be called following the symbol `<call>`.
	call := `mk_isEven, [<number> | "doc" | "-h" | "--help"] <number>? ["--verbose" | "-v"]`
	number := [+|-] ('0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9')+

Parameters:
	-1st parameter (int) == ~: If is an positive interger is passed, the number of tests to use; If is an negative number is passed, prints the default amount.
	-1st parameter (str)     : This is an alternate 1st parameter, it prints this help and returns EXIT_DOC.
	-2nd parameter (int)     == -1: If an positive integer (including 0) is passed, the number to test just after creating the python script. 
Else it will not include the code to run the function at the end of the script.

Exit codes:
	-EXIT_DOC	== -1: The program printed this documentation.
	-EXIT_SUCCESS	==  0: The program executed just fine.
	-EXIT_FAILURE	==  1: The program exited because of an unknown cause.
	-EXIT_415	==  2: The program didn't understood an argument.
```
### More detailed doc
#### Usage (parameters)
You can pass from 0 to 3 argument to the program, each has a different purpose:

|      number/name     |        type       | default value |  description  | alternate use |
|:--------------------:|:-----------------:|:-------------:|:-------------:|:-------------:|
|    1<sup>st</sup>    | `int` or `string` |  $\emptyset$  | As an integer, represents the number of `if...else`s created (v. [first-example](#first-ex)). If unexpected results when negative.  |   As a string, the scripts allows only `"doc"`, `"-h"` and `"--help"` to display the doc, else it will stop with error code [`EXIT_415`](#exit-codes)   |
|    2<sup>nd</sup>    |       `int`       |      `-1`     |  As a positive interger, represents the number to test first (v. [second example](#second-ex)).  | As a negative number, the function will not be called at the end |
|   `--verbose`/`-v`   |    $\emptyset$    |   $\emptyset$  |  The program will print in the console its current state  |  |


#### Exit codes
I implemented four exit codes. The sign of exit code will indicate how the program ended: a positve sign means an error occured and a negative sign (or 0) means that the program ended successfully.
Here they are:
- **EXIT_SUCCESS** (`0`): The program created/modified the python script.
- **EXIT_DOC** (`-1`): The program ended by printing the documentation.
- **EXIT_FAILURE** (`1`): The program encountered an unknown error.
- **EXIT_415** (`2`): Like the [HTTP response code](https://developer.mozilla.org/en-US/docs/Web/HTTP/Status/415), the program didn't understand an argument.

## Build from source
I personnally use **g++** in order to build my C++ scripts.

To download gcc for Windows, [click on this direct link](https://github.com/msys2/msys2-installer/releases/download/2024-01-13/msys2-x86_64-20240113.exe).  
For linux users, you can download gcc with your package manager (_pacman_ on Arch, _apt_ on Debian, etc).

With gcc installed, just run the command:  
```
$ g++ mk_isEven.cpp -o mk_isEven.exe 			# The `-o` flag lets you choose your executable name
```
in whatever folder your source code is. You can know run your `mk_isEven.exe` is the executable of the same name.

Verify that you have [Python](https://www.python.org/downloads/) installed since the program runs this command when [testing the number](#second-ex):
```
$ python3 isEven.py <second argument passed>
```

## Examples
<a name="first-ex"></a> 
`$ mk_isEven 3`  
Result (isEven.py):
```
import sys

def is_even(n : int) -> bool:
	"""Checks if the number is even, n must be below 3."""
	n = abs(int(n))

	if(n == 0):
		return True
	elif(n == 1):
		return False
	elif(n == 2):
		return True
	return False
```
________

<a name="second-ex"></a> 
`mk_isEven 90 50`  
Result (isEven.py):
```
import sys

def is_even(n : int) -> bool:
	"""Checks if the number is even, n must be below 89."""
	n = abs(int(n))

	if(n == 0):
		return True
	elif(n == 1):
		return False
	elif(n == 2):
		return True
	# ...
	elif(n == 89):
		return False
	return False

#Calls the function with the first cmd line arg
if(len(sys.argv) >= 1):
	print(is_even(sys.argv[1]))
```

Result (terminal):
```
$ mk_isEven 90 50
True
```
________
