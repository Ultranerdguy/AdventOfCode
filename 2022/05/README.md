## [Day 5: Supply Stacks](https://adventofcode.com/2022/day/5) ##

> The expedition can depart as soon as the final supplies have been unloaded from the ships. Supplies are stored in stacks of marked crates, but because the needed supplies are buried under many other crates, the crates need to be rearranged.
> 
> The ship has a giant cargo crane capable of moving crates between stacks. To ensure none of the crates get crushed or fall over, the crane operator will rearrange them in a series of carefully-planned steps. After the crates are rearranged, the desired crates will be at the top of each stack.
> 
> The Elves don't want to interrupt the crane operator during this delicate procedure, but they forgot to ask her which crate will end up where, and they want to be ready to unload them as soon as possible so they can embark.
> 
> They do, however, have a drawing of the starting stacks of crates and the rearrangement procedure (your puzzle input). For example:
> ```
>     [D]    
> [N] [C]    
> [Z] [M] [P]
>  1   2   3 
> 
> move 1 from 2 to 1
> move 3 from 1 to 3
> move 2 from 2 to 1
> move 1 from 1 to 2
> ```
> In this example, there are three stacks of crates. Stack 1 contains two crates: crate Z is on the bottom, and crate N is on top. Stack 2 contains three crates; from bottom to top, they are crates M, C, and D. Finally, stack 3 contains a single crate, P.
> 
> Then, the rearrangement procedure is given. In each step of the procedure, a quantity of crates is moved from one stack to a different stack. In the first step of the above rearrangement procedure, one crate is moved from stack 2 to stack 1, resulting in this configuration:
> ```
> [D]        
> [N] [C]    
> [Z] [M] [P]
>  1   2   3 
> ```
> In the second step, three crates are moved from stack 1 to stack 3. Crates are moved one at a time, so the first crate to be moved (D) ends up below the second and third crates:
> ```
>         [Z]
>         [N]
>     [C] [D]
>     [M] [P]
>  1   2   3
> ```
> Then, both crates are moved from stack 2 to stack 1. Again, because crates are moved one at a time, crate C ends up below crate M:
> ```
>         [Z]
>         [N]
> [M]     [D]
> [C]     [P]
>  1   2   3
> ```
> Finally, one crate is moved from stack 1 to stack 2:
> ```
>         [Z]
>         [N]
>         [D]
> [C] [M] [P]
>  1   2   3
> ```
> The Elves just need to know which crate will end up on top of each stack; in this example, the top crates are C in stack 1, M in stack 2, and Z in stack 3, so you should combine these together and give the Elves the message CMZ.
> 
> After the rearrangement procedure completes, what crate ends up on top of each stack?
> 
> --- Part Two ---
> 
> As you watch the crane operator expertly rearrange the crates, you notice the process isn't following your prediction.
> 
> Some mud was covering the writing on the side of the crane, and you quickly wipe it away. The crane isn't a CrateMover 9000 - it's a CrateMover 9001.
> 
> The CrateMover 9001 is notable for many new and exciting features: air conditioning, leather seats, an extra cup holder, and the ability to pick up and move multiple crates at once.
> 
> Again considering the example above, the crates begin in the same configuration:
> ```
>     [D]    
> [N] [C]    
> [Z] [M] [P]
>  1   2   3 
> ```
> Moving a single crate from stack 2 to stack 1 behaves the same as before:
> ```
> [D]        
> [N] [C]    
> [Z] [M] [P]
>  1   2   3 
> ```
> However, the action of moving three crates from stack 1 to stack 3 means that those three moved crates stay in the same order, resulting in this new configuration:
> ```
>         [D]
>         [N]
>     [C] [Z]
>     [M] [P]
>  1   2   3
> ```
> Next, as both crates are moved from stack 2 to stack 1, they retain their order as well:
> ```
>         [D]
>         [N]
> [C]     [Z]
> [M]     [P]
>  1   2   3
> ```
> Finally, a single crate is still moved from stack 1 to stack 2, but now it's crate C that gets moved:
> ```
>         [D]
>         [N]
>         [Z]
> [M] [C] [P]
>  1   2   3
> ```
> In this example, the CrateMover 9001 has put the crates in a totally different order: MCD.
> 
> Before the rearrangement process finishes, update your simulation so that the Elves know where they should stand to be ready to unload the final supplies. After the rearrangement procedure completes, what crate ends up on top of each stack?

#

## Part 1 ##

We're now asked to manipulate stacks of crates, and the puzzle gives us an ascii diagram of the stacks we start with, as well as a series of instructions for moving the  crates. I suspect the hardest part of this task is going to be decoding the ascii diagram into usable stacks.

First step will be to read in the diagram. If we read until we get an empty line, then use the positions of the numbers in the last line as indices for all the lines above, then we can create an array of stacks from bottom to top.

Reading in the instructions will be simpler. If we create an instruction object, and define how it reads from an input stream, it will be easy enough to read all the instructions in a single loop.

The last part will be manipulating the stacks, but that will just be a manual process.

## Part 2 ##

Now the crane can move multiple crates at once. I had a feeling this was going to be the case, which is why the move operation was moved into a function despite its simplicity. Now we just need to redo the move. We're take advantage of another stack to reverse the order, then move from the temporary stack to the destination.