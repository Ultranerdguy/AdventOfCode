## [Day 14: Extended Polymerization](https://adventofcode.com/2021/day/14) ##

>The incredible pressures at this depth are starting to put a strain on your submarine. The submarine has polymerization equipment that would produce suitable materials to reinforce the submarine, and the nearby volcanically-active caves should even have the necessary input elements in sufficient quantities.
>
>The submarine manual contains instructions for finding the optimal polymer formula; specifically, it offers a polymer template and a list of pair insertion rules (your puzzle input). You just need to work out what polymer would result after repeating the pair insertion process a few times.
>
>For example:
>
>NNCB
>```
>CH -> B
>HH -> N
>CB -> H
>NH -> C
>HB -> C
>HC -> B
>HN -> C
>NN -> C
>BH -> H
>NC -> B
>NB -> B
>BN -> B
>BB -> N
>BC -> B
>CC -> N
>CN -> C
>```
>The first line is the polymer template - this is the starting point of the process.
>
>The following section defines the pair insertion rules. A rule like AB -> C means that when elements A and B are immediately adjacent, element C should be inserted between them. These insertions all happen simultaneously.
>
>So, starting with the polymer template NNCB, the first step simultaneously considers all three pairs:
>```
>    The first pair (NN) matches the rule NN -> C, so element C is inserted between the first N and the second N.
>    The second pair (NC) matches the rule NC -> B, so element B is inserted between the N and the C.
>    The third pair (CB) matches the rule CB -> H, so element H is inserted between the C and the B.
>```
>Note that these pairs overlap: the second element of one pair is the first element of the next pair. Also, because all pairs are considered simultaneously, inserted elements are not considered to be part of a pair until the next step.
>
>After the first step of this process, the polymer becomes NCNBCHB.
>
>Here are the results of a few steps using the above rules:
>```
>Template:     NNCB
>After step 1: NCNBCHB
>After step 2: NBCCNBBBCBHCB
>After step 3: NBBBCNCCNBBNBNBBCHBHHBCHB
>After step 4: NBBNBNBBCCNBCNCCNBBNBBNBBBNBBNBBCBHCBHHNHCBBCBHCB
>```
>This polymer grows quickly. After step 5, it has length 97; After step 10, it has length 3073. After step 10, B occurs 1749 times, C occurs 298 times, H occurs 161 times, and N occurs 865 times; taking the quantity of the most common element (B, 1749) and subtracting the quantity of the least common element (H, 161) produces 1749 - 161 = 1588.
>
>Apply 10 steps of pair insertion to the polymer template and find the most and least common elements in the result. What do you get if you take the quantity of the most common element and subtract the quantity of the least common element?
>
>--- Part Two ---
>
>The resulting polymer isn't nearly strong enough to reinforce the submarine. You'll need to run more steps of the pair insertion process; a total of 40 steps should do it.
>
>In the above example, the most common element is B (occurring 2192039569602 times) and the least common element is H (occurring 3849876073 times); subtracting these produces 2188189693529.
>
>Apply 40 steps of pair insertion to the polymer template and find the most and least common elements in the result. What do you get if you take the quantity of the most common element and subtract the quantity of the least common element?

#

## Part 1 ##

The nature of this problem is that the input almost (at most) doubles every time we iterate across the polymer. For this first part, with 10 steps, this won't result in too large a result that we can't just brute force it, but I suspect something more refined will be necessary in Part 2.

## Part 2 ##

I was right. Part 2 asks us to repeat this for about 40 steps, which, in both theory and practice, takes far to long, so another approach is needed.

One observation is that, since insertion happens simultaneously, and all equivalent pairs behave the same, is that we can instead store a map from all possible pairs, to a count of their occurance in the polymer. Then, each step consists of applying the insertion rules to the map inputs, and incrementing the occurance counter from those. For example, the polymer sequence
```
NNNNN
```
can instead be encoded as 
```
NN 4
```
to signify that there are 4 pairs of NN in the polymer.

To apply a rule such as
```
NN -> C
```
we take the count of pair `NN`, and increment the counts of `NC` and `CN` by that count, resulting in
```
NC 4
CN 4
```
Lastly, to find the difference between the most common and least common characters, we increment a per-character counter based on **just the first** character in each pair. In the example above, that would result in
```
Counts:
N = 4
C = 4
```
This does forget the last character in the polymer, but fortunately, the last character in the polymer never changes, so we can remember it at the begining, and add it back in at the end, which gives
```
Counts:
N = 5
C = 4
```