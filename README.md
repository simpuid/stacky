# Stacky

## About Stacky

Stacky is an esoteric programming language involving stacks and only stacks. Everything in this language is a stack and stacks can transfer elements to another stack. Some special stacks are added in this language to execute several tasks.

## Stacky Specification

### Memory System

Stacks store everything as element. Each element of the stack is an 8-bit number. Theoretically, stacks can hold an infinite number of elements but due to implementation limitations, the capacity can be limited. The number of different stacks is also infinite.

### Operations

You can perform two types of operations in Stacky.

* _Move_ operation (denoted by `>`) is used to move an element from source stack to target stack
* _Copy_ operation (denoted by `+`) is used to copy an element from source stack to target stack

Both operation are binary operations so the syntax was designed to resolve source stack and target stack from code.  

### Loops Blocks

* _Zero check block_ (denoted by `[ ]`), it loops until the top element of source stack is non-zero.
* _Empty check block_(denoted by `{ }`), it loops until the source stack is non-empty.

### Stack and Number Stack

* Any combination of alphabets `a-z A-Z` represents a stack of that name
* Any combination of numbers `0-9` represents a number stack of that value (modulo 256 of that value) (number stack is a special stack)

### Tokens

Code is formed by tokens containing `a-z A-Z`,`0-9`,`>`,`+`,`[`,`]`,`{`,`}`

* `a-z A-Z` represents a stack
* `0-9` represents a number stack
* `>` represents move operator
* `+` represents copy operator
* `[` and `]` represents the zero check condition block
* `{` and `}` represents the empty check condition block

### Rules

* Stacks which follows a bunch of operator represents target stack for those operations and source stack for next operations. Example  
`>+>A` means to perform `>`,`+`and again `>` operation from source stack to stack _A_ and then set the source stack to stack _A_
* Stacks which _do not_ follow operators represents source stack. Example  
`A` means to set source stack to _A_
* Staring point of the code should be a stack or a number stack. Example
`{A>B}` is wrong, however `A{A>B}` is correct.
* Number stack can be only treated as source but never as target. Example  
`45>A` is correct but `A>45` is wrong.
* Code inside `{ }` and `[ ]` will loop until the respective condition is met.

### Operator Chaining

The `>` and `+` operators can be chained to form bigger operators like `>+>>>>+>>>`  
Multiple operators are first performed on the source stack while treating an intermediate queue as target stack and then the queue is transfered to the target stack.  
Using an intermediate queue grants us perk to use same stack as source and target. Example

* `A+A` will duplicate the top element of stack _A_ and set the source stack to stack _A_
* `A>>>A` will reverse the top three elements of stack _A_ and set the source stack to stack _A_
* `A>>>+A` will reverse the top three elements of stack _A_, add a copy of 4th element on top of them and set the source stack to stack _A_

### Number Stack

The number stack is special stack which is always empty but `>` and `+` operations will transfer and copy an element containing the value of that number. That's why they are never used as targer stack. Example  

* `45>A` will put an element valued 45 to stack _A_ and set the source stack to stack _A_

Since the elements are 8-bit unsigned integers, therefore the last 8-bit of the numbers are stored in elements.

### Loops

Loops will perform the statements inside them until the required condition is met. Example
`A{>B A}` will transfer all elements of stack _A_ to stack _B_ in reverse order.`A` at start will set the source stack to _A_ so the following `{` will execute code inside the block (assuming that stack _A_ is not empty). `>B` will transfer the top element of source stack (stack _A_ in this case) to stack _B_ and set the source stack to stack _B_. The next `A` will set the source stack to stack _A_ so the following `}` will check again for source stack(stack _A_ in this case) to be non-empty.  
Same goes for the `[]` block  

#### Loops as if block

Loops can be used as if conditional by just setting the source stack to any empty stack at the end of inner block. Example

* `45>>>>A{A>B 0}` will transfer 45 from stack _A_ to stack _B_ once because at the end of inside block the source stack is set to number stack 0 and number stacks are always empty.

### Special Stacks

Some special stacks are added to improve functionality

* `io` stack. Stack _io_ as a source will give elements whose value is same as the ASCII code of console input character. Stack _io_ as a target will print the ASCII character of the element's value. Example  
`66>io` will print _B_ and  
 `io>A` will transfer the first character of input to stack _A_.  
`>` will transfer one charcter from input buffer to target stack.  
`+` will copy one character from input buffer to target stack.  
The distinction can be made by `io>>>io` and `io+++io`, first code will take 3 character inputs and prints them while the second code will take 1 character input and prints it 3 times.  
The `+` operator only copies the character form input buffer. If the last operation from _io_ is `+` then stack _io_ is not empty(it's buffer has one element) otherwise it's empty.
* `add` stack. If you push any element to stack _add_ and if it is not empty then the new element will get added to the top element of it otherwise the element is pushed normally. Example  
`33>add33>add>io` will print _B_ (ascii value `66`)
* `and` stack. It performs same as stack _add_ but the operation it performs is bitwise AND `&`.
* `or` stack. It performs same as stack _add_ but the operation it performs is bitwise OR `|`.
* `rsft` stack. Any element pushed to stack _rsft_ will get right shifted by one place. Example  
`132>rsft>io` will print _B_ (ascii code `66` which is `132 >> 1`)
* `lsft` stack. It is same as stack _rsft_ however the operation it performs is left shift by one place.
* `inv` stack. It is same as stack _rsft_ however the operation it performs is bitwise INVERT.
* `bin` stack. It is an always empty stack having top value returned as zero. It should be used to dump all the unrequired elements. Using this as source is same as using number stack _0_. Example  
`A>bin` will delete the top element of stack _A_

## Implementation

The `cpp` directory contains a c++ implementation of the language. Execute makefile `cpp/Makefile` which result in the creation of executable `cpp/program`. Execute it while passing the name of text file containing the code as commandline argument to start the interpreter.
