# migraine
`v1.1 | Call stack update`

An esoteric language that is guaranteed to give you a headache.

You will need to take some paracetamol after attempting to code in this, have a look:

## Hello World example
```
eeeeee!e!eeee.e!Eeeeeeeeeeeeeee!e!eeee.Ee.E.e!ee!e!.ee.Ee.E.
e!ee!e!.eeeeeeeeeeeeeeee.Ee.E..e!ee!..Ee.E.e!eeeeee!e!
eeee.Ee.E.e!eeeeeeeeeeeeeeee!e!eeeeeeeeeeeeee.Ee.E.e!ee!..E
e.E.e!ee!.eeeeee.Ee.E.e!ee!e!.eeeeeeeeeeeeeeee.Ee.E.e!ee!e!..
Ee.E.e!eeeeee!.Ee.E.e!
```
Disgustingly beautiful right?

There now exists a migraine generator to ease the pain! [Check it out](Cetamol/README.md)

## migraine interpreter internals
- 2 Immediate integer registers
  - Where you'll be storing immediate values from functions
  - The current usable register can be swapped with ``E``
- Function index
  - Accesses all functions
  - Can be traversed with ``e`` and, when the index is odd, ``! or .`` will execute a goto function
  - Resets to 0 if the index is larger than the function list
- Program counter
  - Keeps track of how far it is within the program
  - Can be traversed through the branch function
- """Unlimited""" integer stack
  - Lets you store values from registers. Basically makes this whole language functional
  - Can be accessed through sevaral stack functions

## How do I use this nightmare?
migraine has only 4 operation characters, but it lets you do everything you need.
| Character | Operation | Purpose |
| --- | --- | --- |
| ``e`` | Function index increment | Iterates through the function list |
| ``.`` | Execute function | Executes the current function determined by the function index. Passes the current register to the function as a parameter |
| ``!`` | Execute function pass 0 | Very similar to ``.`` however this purposefuly passes 0 to the function instead of a register |
| ``E`` | Swap register | Swap the current register |

The interpreter has *also* been setup to ignore all characters following a ``#`` character, this allows for comments in code files. Yipee! Documentation!

### The function list
migraine uses a function list that you iterate through using the operators above in order to create logic. You might notice, you can only increment!

How do you decrement? This function list has a special function when the function index is an odd number, it has a goto function that allows you to traverse the function list however you fancy. ``e!`` is used quite a bit in programs as it sets the function index back to 0.

| Index | Function | Purpose |
| --- | --- | --- |
| 0 | number_0 | Sets the rightmost digit in the current register to 0 |
| 2 | number_1 | Sets the rightmost digit in the current register to 1 |
| 4 | number_2 | Sets the rightmost digit in the current register to 2 |
| 6 | number_3 | Sets the rightmost digit in the current register to 3 |
| 8 | number_4 | Sets the rightmost digit in the current register to 4 |
| 10 | number_5 | Sets the rightmost digit in the current register to 5 |
| 12 | number_6 | Sets the rightmost digit in the current register to 6 |
| 14 | number_7 | Sets the rightmost digit in the current register to 7 |
| 16 | number_8 | Sets the rightmost digit in the current register to 8 |
| 18 | number_9 | Sets the rightmost digit in the current register to 9 |

Okay before we continue. This number function is pretty versatile. You can chain them using ``.`` to assemble numbers.

``ee ee ee!`` would set the current register to 3. If we were to then do ``ee.`` immediately afterwards, the current register would now be 34.

Say we want to reset the current register back to 0, we can do ``e!`` to reset the function index to 0, and then ``!`` which would set the current register to 0

This works because the number function internally looks something like this:
```
int number(int intRegister, int digit)
{
    return (intRegister * 10) + digit;
}
```
It will always shift to the left to allow for a new digit, however when you pass 0 through (instead of a register) it resets.
| Index | Function | Purpose |
| --- | --- | --- |
| 20 | add | Adds the non-current register to the current register |
| 22 | subtract | Subtracts the current register from the non-current register |
| 24 | multiply | Multiplies the non-current register to the current register |
| 26 | divide | Divides the current register from the non-current register |
| 28 | input | Gets input from stdin through the console, copies to the current register |
| 30 | output_int | Output the current register as an integer to the console |
| 32 | output_char | Output the current register as a character to the console |
| 34 | compare_equals | Check if the current register is equal to the non-current register, the current register will be overriden with the result |
| 36 | compare_greater | Check if the current register is greater than the non-current register, the current register will be overriden with the result |
| 38 | branch | If the current register has a value greater than 0, it will set the program counter to the non-current register <br /> `v1.1 Change` <br />Pushes the current address to the call stack before branching |
| 40 | branch_return | Return to the last address saved on the call stack | 
| 42 | callstack_pop | Pop the last address saved on the call stack | 
| 44 | stack_push | Push the current register to the stack | 
| 46 | stack_pop | Pop from the top of the stack and override the current register with the popped value |
| 48 | stack_read | Read the stack by accessing at an index provided by the current register, the current register will be overriden with the read value |
| 50 | stack_write | Write to the stack by accessing at an index provided by the current register, overrites the stack entry with a new value from the non-current register |

Annnndd, that's all of them! That's the official function list however due to migraine being structured this way, it is completely possible to amend more functions to it. *The only issue is, the higher the index, the more ``e``'s are required to access them!!!*

All functions listed in the table (notice goto is left out, it's a special little guy) follow this pattern:
```cpp
currentRegister = function(EITHER currentRegister OR 0);
```
The result will always be given back to the current register.

I recommend checking out the ./Examples folder as I've included a few usable code demos with documentation!

## Latest update changes
Ok so.... This change breaks the ABI, v1.0 programs will not run on v1.1. LUCKILY I can gurantee that I am the only individual using this at the minute so I'm allowed to break things :P

We really need a call stack if we want any meaningful programs to be made, it makes sense to group these new functions next to the pre-existing branch function as that is directly involved.