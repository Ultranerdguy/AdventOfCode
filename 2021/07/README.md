## [Day 7: The Treachery of Whales](https://adventofcode.com/2021/day/7) ##

>A giant whale has decided your submarine is its next meal, and it's much faster than you are. There's nowhere to run!
>
>Suddenly, a swarm of crabs (each in its own tiny submarine - it's too deep for them otherwise) zooms in to rescue you! They seem to be preparing to blast a hole in the ocean floor; sensors indicate a massive underground cave system just beyond where they're aiming!
>
>The crab submarines all need to be aligned before they'll have enough power to blast a large enough hole for your submarine to get through. However, it doesn't look like they'll be aligned before the whale catches you! Maybe you can help?
>
>There's one major catch - crab submarines can only move horizontally.
>
>You quickly make a list of the horizontal position of each crab (your puzzle input). Crab submarines have limited fuel, so you need to find a way to make all of their horizontal positions match while requiring them to spend as little fuel as possible.
>
>For example, consider the following horizontal positions:
>```
>16,1,2,0,4,2,7,1,2,14
>```
>This means there's a crab with horizontal position 16, a crab with horizontal position 1, and so on.
>
>Each change of 1 step in horizontal position of a single crab costs 1 fuel. You could choose any horizontal position to align them all on, but the one that costs the least fuel is horizontal position 2:
>```
>    Move from 16 to 2: 14 fuel
>    Move from 1 to 2: 1 fuel
>    Move from 2 to 2: 0 fuel
>    Move from 0 to 2: 2 fuel
>    Move from 4 to 2: 2 fuel
>    Move from 2 to 2: 0 fuel
>    Move from 7 to 2: 5 fuel
>    Move from 1 to 2: 1 fuel
>    Move from 2 to 2: 0 fuel
>    Move from 14 to 2: 12 fuel
>```
>This costs a total of 37 fuel. This is the cheapest possible outcome; more expensive outcomes include aligning at position 1 (41 fuel), position 3 (39 fuel), or position 10 (71 fuel).
>
>Determine the horizontal position that the crabs can align to using the least fuel possible. How much fuel must they spend to align to that position?

>--- Part Two ---
>
>The crabs don't seem interested in your proposed solution. Perhaps you misunderstand crab engineering?
>
>As it turns out, crab submarine engines don't burn fuel at a constant rate. Instead, each change of 1 step in horizontal position costs 1 more unit of fuel than the last: the first step costs 1, the second step costs 2, the third step costs 3, and so on.
>
>As each crab moves, moving further becomes more expensive. This changes the best horizontal position to align them all on; in the example above, this becomes 5:
>```
>    Move from 16 to 5: 66 fuel
>    Move from 1 to 5: 10 fuel
>    Move from 2 to 5: 6 fuel
>    Move from 0 to 5: 15 fuel
>    Move from 4 to 5: 1 fuel
>    Move from 2 to 5: 6 fuel
>    Move from 7 to 5: 3 fuel
>    Move from 1 to 5: 10 fuel
>    Move from 2 to 5: 6 fuel
>    Move from 14 to 5: 45 fuel
>```
>This costs a total of 168 fuel. This is the new cheapest possible outcome; the old alignment position (2) now costs 206 fuel instead.
>
>Determine the horizontal position that the crabs can align to using the least fuel possible so they can make you an escape route! How much fuel must they spend to align to that position?


#

## Part 1 ##

This puzzle can be summarized as
> Given a sequence of N values (a<sub>i</sub>), find the integer value m that minimises
>
> sum<sup>N</sup><sub>i=1</sub>(|a<sub>i</sub> - n|)

By definition, the value `n` that would satisfy this is the median value of the data. This simplified the problem massively, as now we just need to sort the data, find the middle element, and calculate the sum of the fuel requirements.

## Part 2 ##

The second part changes the sum requirements drastically. Now the equation to minimise is built on triangle numbers. If `T(n)` is the `n`<sup>`th`</sup> triangle number (equal to `n(n+1)/2`), then we need to minimise

>sum<sup>N</sup><sub>i=1</sub>(T(|a<sub>i</sub> - n|))

With Part 1, we can prove that plugging the median value into `n` would minimise the equation by considering what happens when we slowly increase `n` by a little bit at a time. I feel like we can take a similar approach here.

If we have a sequence of values `s`<sub>`i`</sub>, we can consider what happens to a variable `n` as it walks through these values. Let `j1` and `j2` integers such that `s`<sub>`j1`</sub>` < n < s`<sub>`j2`</sub>, then a small change in `n` will increase the fuel cost of all `s`<sub>`i`</sub>` <= n` by `n - s`<sub>`i`</sub>, and decrease the fuel cost of all `s`<sub>`i`</sub>` > n` by `s`<sub>`i`</sub>` - n`. The minimum point will thus be when the sum of all these differences equals `0`. In computing this value, and pulling the `n` terms out of the sums reveals the **mean** to be the solution.

The problem restricts us to integer positions only, but it's easy enough to see that if the mean is greater than the median, rounding down gets us the next best option, and vice versa when the mean is less than the median.