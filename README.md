# push_swap : 42 Cursus project [![pgueugno's 42 push_swap Score](https://badge42.vercel.app/api/v2/cl4cqx7ks006409jn1s8sg534/project/2165528)](https://github.com/JaeSeoKim/badge42)
<p align="left"> <a href="https://www.cprogramming.com/" target="_blank" rel="noreferrer"> <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/c/c-original.svg" alt="c" width="40" height="40"/> </a> </p>

### Overview
- Sort data on a stack, with a limited set of instructions, using the lowest possible number of actions.
- Write a program named "*push_swap*" that takes as an argument the stack A formatted as a list of integers. The first argument should be at the top of the stack
  - The program must display the smallest list of instructions possible to sort the stack A, the smallest number being at the top
  - Instructions must be separated by a ’\n’ and nothing else
- Write another program named "*checker*" that takes as an argument the stack A formatted as a list of integers
  - If after executing those instructions, the stack A is actually sorted and the stack B is empty, then the program must display "*OK*" followed by a ’\n’ on the standard
output. Otherwise it will displayer "*KO*" or "*Error*"

The goal is to sort the stack A with the lowest possible number of operations with the "*push_swap*" program and to check the result validity with the "*checker*" program.

### Specifications
In order to obtain the best performances with the simplest solution, the "*push_swap*" program uses a combination of a quicksort and an insertion sort algorithm.

The authorized operations are the following:
- sa (swap a): Swap the first 2 elements at the top of stack a.
  Do nothing if there is only one or no elements.
- sb (swap b): Swap the first 2 elements at the top of stack b.
  Do nothing if there is only one or no elements.
- ss : sa and sb at the same time.
- pa (push a): Take the first element at the top of b and put it at the top of a.
  Do nothing if b is empty.
- pb (push b): Take the first element at the top of a and put it at the top of b.
  Do nothing if a is empty.
- ra (rotate a): Shift up all elements of stack a by 1.
  The first element becomes the last one.
- rb (rotate b): Shift up all elements of stack b by 1.
  The first element becomes the last one.
- rr : ra and rb at the same time.
- rra (reverse rotate a): Shift down all elements of stack a by 1.
  The last element becomes the first one.
- rrb (reverse rotate b): Shift down all elements of stack b by 1.
  The last element becomes the first one.
- rrr : rra and rrb at the same time.
