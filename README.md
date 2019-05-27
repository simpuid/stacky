# Stacky

## About Stacky

Stacky is an esoteric programming language involving stacks and only stacks. Everything in this language is a stack and stacks can transfer elements to another stack. Some special stacks are added in this language to execute special tasks.

## Stacky Specification

### Memory System

Stacks store everything as element. Each element of the stack is an 8-bit number(0-255 inclusive). Theoretically, stacks can hold an infinite number of elements, and the number of different stacks is also infinite, but due to implementation constraints, the actual capacity can be limited. The interpreter maintains a pointer of a stack. The pointer points to the current source stack.

### Operations

You can perform two types of operations in Stacky.

* __Move__ operation (denoted by `>`) is used to move an element from source stack to target stack.
* __Copy__ operation (denoted by `+`) is used to copy an element from source stack to target stack.

Both operations are binary operations, so the syntax was designed to resolve source stack and target stack from code.  

### Loops Blocks

* __Zero Check Block__ (denoted by `[ ]`). If the top element of the source stack is non-zero at the start of this block `[` , then the statement inside this block will execute. If the top element inside the source stack(can be a different stack) is still non-zero at the end `]` , then it loops from the start again.
* __Empty Check Block__(denoted by `{ }`), Same as __Zero Check Block__, but the condition is changed. The statements inside the block will execute if the source stack is non-empty. Same condition for looping.

### Stack and Number Stack

* Any combination of alphabets `a-z and A-Z` represents a stack of that name.
* Any combination of numbers `0-9` represents a number stack of that value. Elements are 8-bit in size, so the values are modulo 256.

### Rules

* Stacks, which follow an operator, represent target stack for that operator and source stack for the next operator.
* Stacks, which _do not_ follow an operator, represent change in source stack pointer.  
  Example-  
  The code `C>A+B` implies  
  1. `C` - Set the source stack pointer to __C__,
  2. `>A` - Perform move(`>`) operation with target __A__ and set the source stack pointer to __A__,
  3. `+B` - Perform copy(`+`) operation with target __B__ and set the source stack pointer to __B__,
* Staring token of the code should always be a stack or a number stack.  
  Example-  
  `{A>B}` is wrong, however `A{A>B}` is correct.
* Number stack can be only treated as source but never as target.  
  Example-  
  `45>A` is correct but `A>45` is wrong.
* Code inside `{ }` and `[ ]` will loop until the respective condition is met.

### Operator Chaining

The move(`>`) and copy(`+`) operators can be chained together to form bigger operators like `>>>+>`.  
Chained operators are first performed on the source stack while treating an intermediate queue as target stack, and then the queue is transferred to the actual target stack.  
Using an intermediate queue grants us perk to use the same stack as source and target. Example-

* `A+A` will duplicate the top element of __A__ and set the source stack to __A__.
* `A>>>A` will reverse the top three elements of __A__ and set the source stack to __A__.
* `A>>>+A` will reverse the top three elements of __A__, add a copy of 4th element on top of them and set the source stack to __A__.

### Number Stack

Number stack is a special stack which is always empty. Both operations will create an element holding the value of this stack. Pushing elements to this stack will destroy them because it remains always empty.  
Example-

* `45>A` will put an element valued 45 to stack __A__ and set the source stack to __A__.

Since the elements are 8-bit unsigned integers, therefore the last 8-bit of the numbers are stored in the elements.  
Example-

* `45>A` and `301>A` results the same.

### Loops

Loops will execute the statements inside them until the required conditions are met.  
Example-  
`A{>B A}` will transfer all elements of __A__ to __B__ in reverse order.  
`A` at the start will set the source stack to __A__.  
The following `{` will execute code inside the block (assuming that __A__ is non-empty at this point).  
`>B` will transfer the top element of source stack (__A__ in this case) to __B__ and set the source stack to __B__.  
The next `A` will set the source stack to __A__ so the following `}` will check again for source stack to be non-empty.  
Same goes for the `[]` block.

#### Loops as if block

Loops can be used as if conditional by setting the source stack to any empty stack at the end of inner block. Example

* `45>>>>A{A>B 0}` will transfer 45 from __A__ to __B__ once because at the end( `}` ) the source stack is set to number stack 0 and number stacks are always empty.

### Special Stacks

Some special stacks are added to extend functionality.

* `io` stack. __io__ as a source provides interface to read the console input buffer. __io__ as a target provides interface to write console output.
  Example-  

  * `66>io` will print _B_ and  
  * `io>A` will transfer the first character of input to __A__.

  `>` will transfer one charcter from input buffer to target stack.  
`+` will copy one character from input buffer to target stack.  
The distinction can be made by `io>>>io` and `io+++io`, first code will take 3 character inputs and prints them while the second code will take 1 character input and prints it 3 times.  
The `+` operator only _copies_ the character from input buffer. __io__ becomes empty when the input stream becomes empty.
* `add` stack. If there are more than 1 element in __add__ then they become one element whose value is sum of all elements of __add__  
  Example  
`33>add33>add>io` will print _B_ (_ASCII_ value _66 = 33+33_)
* `and` stack. It performs same as __add__ but the operation it performs is _bitwise AND_(`&`).
* `or` stack. It performs same as __add__ but the operation it performs is _bitwise OR_(`|`).
* `rsft` stack. Any element pushed to __rsft__ will get _right shifted by one place_.  
  Example-  
`132>rsft>io` will print _B_ (ascii code `66` which is `132 >> 1`)
* `lsft` stack. It is same as __rsft__ however the operation it performs is _left shift by one place_.
* `inv` stack. It is same as __rsft__ however the operation it performs is _bitwise INVERT_(`~`).

## Implementation

The `cpp` directory contains a c++ implementation of the language. Execute makefile `cpp/Makefile` which result in the creation of executable `cpp/program`. Execute it by `./cpp/program <source_file_name>` to start the interpreter.
