## [Day 12: Passage Pathing](https://adventofcode.com/2021/day/12) ##

>With your submarine's subterranean subsystems subsisting suboptimally, the only way you're getting out of this cave anytime soon is by finding a path yourself. Not just a path - the only way to know if you've found the best path is to find all of them.
>
>Fortunately, the sensors are still mostly working, and so you build a rough map of the remaining caves (your puzzle input). For example:
>```
>start-A
>start-b
>A-c
>A-b
>b-d
>A-end
>b-end
>```
>This is a list of how all of the caves are connected. You start in the cave named start, and your destination is the cave named end. An entry like b-d means that cave b is connected to cave d - that is, you can move between them.
>
>So, the above cave system looks roughly like this:
>```
>    start
>    /   \
>c--A-----b--d
>    \   /
>     end
>```
>Your goal is to find the number of distinct paths that start at start, end at end, and don't visit small caves more than once. There are two types of caves: big caves (written in uppercase, like A) and small caves (written in lowercase, like b). It would be a waste of time to visit any small cave more than once, but big caves are large enough that it might be worth visiting them multiple times. So, all paths you find should visit small caves at most once, and can visit big caves any number of times.
>
>Given these rules, there are 10 paths through this example cave system:
>```
>start,A,b,A,c,A,end
>start,A,b,A,end
>start,A,b,end
>start,A,c,A,b,A,end
>start,A,c,A,b,end
>start,A,c,A,end
>start,A,end
>start,b,A,c,A,end
>start,b,A,end
>start,b,end
>```
>(Each line in the above list corresponds to a single path; the caves visited by that path are listed in the order they are visited and separated by commas.)
>
>Note that in this cave system, cave d is never visited by any path: to do so, cave b would need to be visited twice (once on the way to cave d and a second time when returning from cave d), and since cave b is small, this is not allowed.
>
>Here is a slightly larger example:
>```
>dc-end
>HN-start
>start-kj
>dc-start
>dc-HN
>LN-dc
>HN-end
>kj-sa
>kj-HN
>kj-dc
>```
>The 19 paths through it are as follows:
>```
>start,HN,dc,HN,end
>start,HN,dc,HN,kj,HN,end
>start,HN,dc,end
>start,HN,dc,kj,HN,end
>start,HN,end
>start,HN,kj,HN,dc,HN,end
>start,HN,kj,HN,dc,end
>start,HN,kj,HN,end
>start,HN,kj,dc,HN,end
>start,HN,kj,dc,end
>start,dc,HN,end
>start,dc,HN,kj,HN,end
>start,dc,end
>start,dc,kj,HN,end
>start,kj,HN,dc,HN,end
>start,kj,HN,dc,end
>start,kj,HN,end
>start,kj,dc,HN,end
>start,kj,dc,end
>```
>Finally, this even larger example has 226 paths through it:
>```
>fs-end
>he-DX
>fs-he
>start-DX
>pj-DX
>end-zg
>zg-sl
>zg-pj
>pj-he
>RW-he
>fs-DX
>pj-RW
>zg-RW
>start-pj
>he-WI
>zg-he
>pj-fs
>start-RW
>```
>How many paths through this cave system are there that visit small caves at most once?
>
>--- Part Two ---
>
>After reviewing the available paths, you realize you might have time to visit a single small cave twice. Specifically, big caves can be visited any number of times, a single small cave can be visited at most twice, and the remaining small caves can be visited at most once. However, the caves named start and end can only be visited exactly once each: once you leave the start cave, you may not return to it, and once you reach the end cave, the path must end immediately.
>
>Now, the 36 possible paths through the first example above are:
>```
>start,A,b,A,b,A,c,A,end
>start,A,b,A,b,A,end
>start,A,b,A,b,end
>start,A,b,A,c,A,b,A,end
>start,A,b,A,c,A,b,end
>start,A,b,A,c,A,c,A,end
>start,A,b,A,c,A,end
>start,A,b,A,end
>start,A,b,d,b,A,c,A,end
>start,A,b,d,b,A,end
>start,A,b,d,b,end
>start,A,b,end
>start,A,c,A,b,A,b,A,end
>start,A,c,A,b,A,b,end
>start,A,c,A,b,A,c,A,end
>start,A,c,A,b,A,end
>start,A,c,A,b,d,b,A,end
>start,A,c,A,b,d,b,end
>start,A,c,A,b,end
>start,A,c,A,c,A,b,A,end
>start,A,c,A,c,A,b,end
>start,A,c,A,c,A,end
>start,A,c,A,end
>start,A,end
>start,b,A,b,A,c,A,end
>start,b,A,b,A,end
>start,b,A,b,end
>start,b,A,c,A,b,A,end
>start,b,A,c,A,b,end
>start,b,A,c,A,c,A,end
>start,b,A,c,A,end
>start,b,A,end
>start,b,d,b,A,c,A,end
>start,b,d,b,A,end
>start,b,d,b,end
>start,b,end
>```
>The slightly larger example above now has 103 paths through it, and the even larger example now has 3509 paths through it.
>
>Given these new rules, how many paths through this cave system are there?


#

## Part 1 ##

We're tasked now with finding all routes through a cave system, from `start` to `end`. Once again, we can utilise stacks to keep track of where we've been, to make sure we hit all the right places.

For a couple of problems now, I've used stacks rather than recursion. My justification is that, under the hood, recursive functions are just using the stack memory anyway, but they can end up using much more memory as they have to redeclare every variable in the function. Some languages even have limits to how far a recursive function can go (Python's default recursion limit is 1000, though this can be overriden with the `sys` module). By utilising a stack structure manually, we have more control over the memory usage, and can even go further than regular recursion will normally take us. We just have to do things a bit more manually, but practicing this now will make it easier in the future.

My plan here it to use a depth-first-search (DFS) algorithm, starting from `start`, to find all the paths. Each node will have an ordered array (ordering doesn't really matter, as long as it doesn't change halfway through) of adjacent nodes, and we'll keep track of three different things;
- A stack of the current path
- A set of all small caves that we've visited on this path
- A counter of all the times we've hit an end node

As we walk into one node to another, we

1. Look at the last child node we visited, and set the new node to the next child
1. Check if the new node is in the visited set, skipping if true
1. Add the new node to the path stack
    - If the new node is lowercase, add it to the visited set

And as we back up from one node to another

1. Remove the old node from the path stack
1. If the old node was in the visited set, remove it from the set
1. If the old node was the `end` node, increment the counter

Armed with this algorithm, we should be able to walk through the caves.

## Part 2 ##

Now the problem has changed slightly, where we can visit small caves up to two times (with exception to the start and end caves).

In addition to a container tracking all the small caves that have been visited so far, we also need to keep track of which small cave we've visited twice, and make sure that we don't visit it anymore, or visit any other caves. My plan here is to add single pointer to track this cave. If the pointer is null, we can enter another small cave again. When we leave that small cave (as we pop from the stack), we set the pointer to null first, then when we leave it again, we remove it from the visited set.