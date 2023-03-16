# migraine
An esoteric language that is guaranteed to give you a headache.

You will need to take some paracetemol after attempting to code in this, have a look:

## Hello World example
```
eeeeee!e!eeee.e!Eeeeeeeeeeeeeee!e!eeee.Ee.E.e!ee!e!.ee.Ee.E.
e!ee!e!.eeeeeeeeeeeeeeee.Ee.E..e!ee!..Ee.E.e!eeeeee!e!
eeee.Ee.E.e!eeeeeeeeeeeeeeee!e!eeeeeeeeeeeeee.Ee.E.e!ee!..E
e.E.e!ee!.eeeeee.Ee.E.e!ee!e!.eeeeeeeeeeeeeeee.Ee.E.e!ee!e!..
Ee.E.e!eeeeee!.Ee.E.e!
```
Disgustingly beautiful right?

## How do I use this nightmare?
migraine has only 4 operation characters, but it lets you do everything you need.
| Character | Operation | Purpose |
| --- | --- | --- |
| ``e`` | Function index increment | Iterates through the function list |
| ``.`` | Execute function | Executes the current function determined by the function index. Passes through the current register |
| ``!`` | Execute function pass 0 | Very similar to ``.`` however this purposefuly passes 0 to the function instead of a register |
| ``E`` | Swap register | Swap the current register |

migraine uses a function list that you iterate through using these operators in order to create logic. You might notice, you can only increment!

How do you decrement? This function list has a special function when the function index is odd, it has a goto function that allows you to traverse the function list however you fancy. ``e!`` is used quite a bit in programs as it sets the function index back to 0.

### The function list
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

Woah woah, okay before we continue. This number function is pretty versatile. You can chain them using ``.`` to assemble numbers.

``ee ee ee!`` would set the current register to 3. If we were to then do ``ee.`` immediately afterwards, the current register would now be 34.

Say we want to reset the current register back to 0, we can do ``e!`` to reset the function index to 0, and then ``!`` which would set the current register to 0



