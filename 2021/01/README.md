## [Day 1: Sonar Sweep](https://adventofcode.com/2021/day/1) ##

>You're minding your own business on a ship at sea when the overboard alarm goes off! You rush to see if you can help. Apparently, one of the Elves tripped and accidentally sent the sleigh keys flying into the ocean!
>
>Before you know it, you're inside a submarine the Elves keep ready for situations like this. It's covered in Christmas lights (because of course it is), and it even has an experimental antenna that should be able to track the keys if you can boost its signal strength high enough; there's a little meter that indicates the antenna's signal strength by displaying 0-50 stars.
>
>Your instincts tell you that in order to save Christmas, you'll need to get all fifty stars by December 25th.
>
>Collect stars by solving puzzles. Two puzzles will be made available on each day in the Advent calendar; the second puzzle is unlocked when you complete the first. Each puzzle grants one star. Good luck!
>
>As the submarine drops below the surface of the ocean, it automatically performs a sonar sweep of the nearby sea floor. On a small screen, the sonar sweep report (your puzzle input) appears: each line is a measurement of the sea floor depth as the sweep looks further and further away from the submarine.
>
>For example, suppose you had the following report:
>```
>199
>200
>208
>210
>200
>207
>240
>269
>260
>263
>```
>This report indicates that, scanning outward from the submarine, the sonar sweep found depths of 199, 200, 208, 210, and so on.
>
>The first order of business is to figure out how quickly the depth increases, just so you know what you're dealing with - you never know if the keys will get carried into deeper water by an ocean current or a fish or something.
>
>To do this, count the number of times a depth measurement increases from the previous measurement. (There is no measurement before the first measurement.) In the example above, the changes are as follows:
>```
>199 (N/A - no previous measurement)
>200 (increased)
>208 (increased)
>210 (increased)
>200 (decreased)
>207 (increased)
>240 (increased)
>269 (increased)
>260 (decreased)
>263 (increased)
>```
>In this example, there are 7 measurements that are larger than the previous measurement.
>
>How many measurements are larger than the previous measurement?
>
>--- Part Two ---
>
>Considering every single measurement isn't as useful as you expected: there's just too much noise in the data.
>
>Instead, consider sums of a three-measurement sliding window. Again considering the above example:
>```
>199  A      
>200  A B    
>208  A B C  
>210    B C D
>200  E   C D
>207  E F   D
>240  E F G  
>269    F G H
>260      G H
>263        H
>```
>Start by comparing the first and second three-measurement windows. The measurements in the first window are marked A (199, 200, 208); their sum is 199 + 200 + 208 = 607. The second window is marked B (200, 208, 210); its sum is 618. The sum of measurements in the second window is larger than the sum of the first, so this first comparison increased.
>
>Your goal now is to count the number of times the sum of measurements in this sliding window increases from the previous sum. So, compare A with B, then compare B with C, then C with D, and so on. Stop when there aren't enough measurements left to create a new three-measurement sum.
>
>In the above example, the sum of each three-measurement window is as follows:
>```
>A: 607 (N/A - no previous sum)
>B: 618 (increased)
>C: 618 (no change)
>D: 617 (decreased)
>E: 647 (increased)
>F: 716 (increased)
>G: 769 (increased)
>H: 792 (increased)
>```
>In this example, there are 5 sums that are larger than the previous sum.
>
>Consider sums of a three-measurement sliding window. How many sums are larger than the previous sum?


#

## Part 1 ##

For this first part, the majority of the puzzle lies in parsing the input data to be usable. Luckiy, C++ streams make this much easier, and the data format is very simple in the first place, so something along the lines of
```
container data;
while (file)
  int i;
  file >> i;
  container.push_back(i);
```
is enough to parse. After that, we iterate over the container, and increment a counter if any element is larger than the previous one.

## Part 2 ##

This part of the puzzle asks about the sum of consecutive triples, but this can be simplified.

Given 4 consecutive values A, B, C and D, the two triples are A+B+C and B+C+D. Because of the overlap in B and C, the only time B+C+D is greater than A+B+C is when D > A. This means we don't have to do the sum in the first place, we just have to compare all values 3 steps apart instead of 1 step apart like in Part 1.