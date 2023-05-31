# cetamol
`v1.0 | The working update`

An intermediate language to make coding in migraine less of a headache.

## Hello world example
```
_MAIN_                  # Jump to MAIN

_^HELLOWORLD_           # Define HELLOWORLD function
e! -32- E				# Save the print index function to register_0
-72- E e. E .			# 'H'
-101- E e. E .			# 'e'
-108- E e. E ..			# 'll'
-111- E e. E .			# 'o'
E . E					# ' '
-87- E e. E .			# 'W'
-111- E e. E .			# 'o'
-114- E e. E .			# 'r'
-108- E e. E .			# 'l'
-100- E e. E .			# 'd'
-33- E e. E .			# '!'
^                       # Return to MAIN

_^MAIN_                 # Define MAIN function
_HELLOWORLD_            # Jump to HELLOWORLD function
```
See, it's slightly more readable than migraine's hello world example!

## cetamol functions
### Number generation
| Mode | Syntax |
| -- | -- |
| Function increment mode | \$ `number` \$ |

This will generate *n*-amount of function index increments

*e.g*
```
# program.mol
$1$
$5$
$10$

# outputs:
e
eeeee
eeeeeeeeee
```

| Mode | Syntax |
| -- | -- |
| Optimized number mode | -`number`- |

Saves the number to the current register. This will use the least amount of operations possible

*e.g*
```
# program.mol
-1-
-5-
-10-
-100-
-121-

# outputs:
e!ee!e!
e!eeeeeeeeee!e!
e!ee!e!.
e!ee!e!..
e!ee!ee.e!ee.e!
```

| Mode | Syntax |
| -- | -- |
| Fixed number mode | -f`number`- |

Saves the number to the current register. This will generate a fixed length amount of operations, I'm currently using this to implement tags. Internally the fixed digit count is 16 (meaning the maximum number this can generate is 10<sup>16</sup>-1).

*e.g*
```
# program.mol
-f1-
-f5-
-f10-
-f100-
-f121-

# outputs:
e!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!ee.eeeeeeeeeeeeeeee
e!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!eeeeeeeeee.eeeeeeee
e!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!ee.eeeeeeeeeeeeeeeee!.eeeeeeeeeeeeeeeeee
e!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!ee.eeeeeeeeeeeeeeeee!.eeeeeeeeeeeeeeeeeee!.eeeeeeeeeeeeeeeeee
e!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!ee.eeeeeeeeeeeeeeeee!eeee.eeeeeeeeeeeeeee!ee.eeeeeeeeeeeeeeee

```

`WARNING` fixed number mode will not reset the function index at the end, make sure to add an `e!` afterwards!

### Macros
| Macro character | Generates |
| -- | -- |
| > | Stack push |
| < | Stack pop |
| * | Guaranteed branch |
| ^ | Branch return |
| ~ | Call stack pop |

These macros will generate boilerplate migraine code.

*e.g*
```
# program.mol
>
<
*
^
~

# outputs:
e!eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee.e!
e!eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee!e!
e!e!Eee!e!eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee.
e!eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee!e!
e!eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee!e!
```

`WARNING` currently the Branch macro will not reset the function index after branching, so make sure to add an `e!` wherever you branch to!

### Tags
| Mode | Syntax |
| --- | --- |
| Definition mode | \_^`tag name`\_ |

Similar to assembly tags, essentially these allow you to define functions. You can define a new tag anywhere in your code.

*e.g*
```
# program.mol
_^print_
_^main_

# output:
# Won't output anything yet as there's no references made to these tags
```

| Mode | Syntax |
| --- | --- |
| Reference mode | \_`tag name`\_ |

Reference a defined tag. This will generate the address to the defined tag as well as guaranteed branching boilerplate

*e.g*
```
# program.mol
_main_

_^print_
e! -30- E -42- E e. E . ^

_^main_
_print_

# outputs:
e!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!eeeeeeee.eeeeeeeeeee!eeeeeeeeeeee.eeeeeee!eeeeeeeeeeeeeeeeee.e!Eee!e!eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee.

# print define
e!e!eeeeee!e!.Ee!eeeeeeee!e!eeee.e!Ee.E.e!eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee!e!

# main define
e!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!!eeeeeeeeeeeeeeeeeee!eeeeee.eeeeeeeeeeeee!eeeeeeeeeeeeeeee.eee!eeeeeeee.eeeeeeeeeee!Eee!e!eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee.
```
For clarity what this program does:

1. Branches to \_^main\_
1. Branches to \_^print\_
    1. Runs code that outputs 42 to the console
1. Branch returns from \_^print\_ to \_^main\_
1. Finishes executing

Bam! We defined main and ran a print function!

`WARNING` since this uses branches, it has the same problem as stated in the warning above. Make sure to reset your function index like we do in the start of the print function!

# To do:
1. Update guaranteed branch macro, or make separate macro that pushes registers to stack
1. Implement user macro defines, something like `[MACRO NAME][MACRO DEFINE]`, and later referenced as: `[MACRO NAME]`
    1. This miiight take a hot minute to add, considering I need to make sure the macro define either gets inserted before migraine generation OR gets turned into migraine code on define
1. Add conditional branch macro, probably the `?` character
1. Remove guaranteed branch from tags, allow it to just dereference to an address (useful for making conditional loops)
