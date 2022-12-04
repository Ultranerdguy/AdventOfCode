## [Day 4: Camp Cleanup](https://adventofcode.com/2022/day/4) ##

> Space needs to be cleared before the last supplies can be unloaded from the ships, and so several Elves have been assigned the job of cleaning up sections of the camp. Every section has a unique ID number, and each Elf is assigned a range of section IDs.
> 
> However, as some of the Elves compare their section assignments with each other, they've noticed that many of the assignments overlap. To try to quickly find overlaps and reduce duplicated effort, the Elves pair up and make a big list of the section assignments for each pair (your puzzle input).
> 
> For example, consider the following list of section assignment pairs:
> ```
> 2-4,6-8
> 2-3,4-5
> 5-7,7-9
> 2-8,3-7
> 6-6,4-6
> 2-6,4-8
> ```
> For the first few pairs, this list means:
> 
> * Within the first pair of Elves, the first Elf was assigned sections 2-4 (sections 2, 3, and 4), while the second Elf was assigned sections 6-8 (sections 6, 7, 8).
> * The Elves in the second pair were each assigned two sections.
> * The Elves in the third pair were each assigned three sections: one got sections 5, 6, and 7, while the other also got 7, plus 8 and 9.
> 
> This example list uses single-digit section IDs to make it easier to draw; your actual list might contain larger numbers. Visually, these pairs of section assignments look like this:
> ```
> .234.....  2-4
> .....678.  6-8
> 
> .23......  2-3
> ...45....  4-5
> 
> ....567..  5-7
> ......789  7-9
> 
> .2345678.  2-8
> ..34567..  3-7
> 
> .....6...  6-6
> ...456...  4-6
> 
> .23456...  2-6
> ...45678.  4-8
> ```
> Some of the pairs have noticed that one of their assignments fully contains the other. For example, 2-8 fully contains 3-7, and 6-6 is fully contained by 4-6. In pairs where one assignment fully contains the other, one Elf in the pair would be exclusively cleaning sections their partner will already be cleaning, so these seem like the most in need of reconsideration. In this example, there are 2 such pairs.
> 
> In how many assignment pairs does one range fully contain the other?
> 
> --- Part Two ---
> 
> It seems like there is still quite a bit of duplicate work planned. Instead, the Elves would like to know the number of pairs that overlap at all.
> 
> In the above example, the first two pairs (2-4,6-8 and 2-3,4-5) don't overlap, while the remaining four pairs (5-7,7-9, 2-8,3-7, 6-6,4-6, and 2-6,4-8) do overlap:
> 
> * 5-7,7-9 overlaps in a single section, 7.
> * 2-8,3-7 overlaps all of the sections 3 through 7.
> * 6-6,4-6 overlaps in a single section, 6.
> * 2-6,4-8 overlaps in sections 4, 5, and 6.
> 
> So, in this example, the number of overlapping assignment pairs is 4.
> 
> In how many assignment pairs do the ranges overlap?

#

## Part 1 ##

This challenge gives us a series of pairs of one-dimensional ranges, and asks us to count how many pairs contain a range that is fully contained by the other range in the pair.

The format for the input is on a line by line basis, and it takes the form `range,range`, where `range` is defined as `value-value`. For parsing and managing data, I'll create a range object, which will also provide some methods to check if it contains another range, and a single static method to check if two ranges overlap in general.

Given two ranges `A = [a1,a2]` and `B = [b1,b2]`, we can determine if one range is contained within the other with a single operation `(b1-a1) * (a2-b2) >= 0`. If both brackets are positive, then `b1>a1` and `b2<a2`, so `B` is contained in `A`. If both are negative, then `A` is contained in `B`, but the product is still positive. If either bracket is `0`, then they share either their low or high range, so one is guaranteed to be contained in the other.

## Part 2 ##

This extends the problem from fully overlapping areas to partially overlapping. This gives two extra cases to check; `a2` in `B` (and `a1 < b1`), and `a1` in `B` (and `a2 > b2`). The cases of `b1` or `b2` in `A` are covered by these cases as well. In fact, if we remove the requirement that `a1 < b1` or `a2 > b2`, these cases are true when there's a full overlap as well, so we can instead just use these conditions to check for partial overlap.

If we just consider the range `A2 = [a2,a2]`, then we can reuse our fully overlapping check from earlier to determine if `a2` is in `B`, and similarly for `A1 = [a1,a1]`.