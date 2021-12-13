## [Day 13: Transparent Origami](https://adventofcode.com/2021/day/13) ##

>You reach another volcanically active part of the cave. It would be nice if you could do some kind of thermal imaging so you could tell ahead of time which caves are too hot to safely enter.
>
>Fortunately, the submarine seems to be equipped with a thermal camera! When you activate it, you are greeted with:
>
>Congratulations on your purchase! To activate this infrared thermal imaging
>camera system, please enter the code found on page 1 of the manual.
>
>Apparently, the Elves have never used this feature. To your surprise, you manage to find the manual; as you go to open it, page 1 falls out. It's a large sheet of transparent paper! The transparent paper is marked with random dots and includes instructions on how to fold it up (your puzzle input). For example:
>```
>6,10
>0,14
>9,10
>0,3
>10,4
>4,11
>6,0
>6,12
>4,1
>0,13
>10,12
>3,4
>3,0
>8,4
>1,10
>2,14
>8,10
>9,0
>```
>fold along y=7
>fold along x=5
>
>The first section is a list of dots on the transparent paper. 0,0 represents the top-left coordinate. The first value, x, increases to the right. The second value, y, increases downward. So, the coordinate 3,0 is to the right of 0,0, and the coordinate 0,7 is below 0,0. The coordinates in this example form the following pattern, where # is a dot on the paper and . is an empty, unmarked position:
>```
>...#..#..#.
>....#......
>...........
>#..........
>...#....#.#
>...........
>...........
>...........
>...........
>...........
>.#....#.##.
>....#......
>......#...#
>#..........
>#.#........
>```
>Then, there is a list of fold instructions. Each instruction indicates a line on the transparent paper and wants you to fold the paper up (for horizontal y=... lines) or left (for vertical x=... lines). In this example, the first fold instruction is fold along y=7, which designates the line formed by all of the positions where y is 7 (marked here with -):
>```
>...#..#..#.
>....#......
>...........
>#..........
>...#....#.#
>...........
>...........
>-----------
>...........
>...........
>.#....#.##.
>....#......
>......#...#
>#..........
>#.#........
>```
>Because this is a horizontal line, fold the bottom half up. Some of the dots might end up overlapping after the fold is complete, but dots will never appear exactly on a fold line. The result of doing this fold looks like this:
>```
>#.##..#..#.
>#...#......
>......#...#
>#...#......
>.#.#..#.###
>...........
>...........
>```
>Now, only 17 dots are visible.
>
>Notice, for example, the two dots in the bottom left corner before the transparent paper is folded; after the fold is complete, those dots appear in the top left corner (at 0,0 and 0,1). Because the paper is transparent, the dot just below them in the result (at 0,3) remains visible, as it can be seen through the transparent paper.
>
>Also notice that some dots can end up overlapping; in this case, the dots merge together and become a single dot.
>
>The second fold instruction is fold along x=5, which indicates this line:
>```
>#.##.|#..#.
>#...#|.....
>.....|#...#
>#...#|.....
>.#.#.|#.###
>.....|.....
>.....|.....
>```
>Because this is a vertical line, fold left:
>```
>#####
>#...#
>#...#
>#...#
>#####
>.....
>.....
>```
>The instructions made a square!
>
>The transparent paper is pretty big, so for now, focus on just completing the first fold. After the first fold in the example above, 17 dots are visible - dots that end up overlapping after the fold is completed count as a single dot.
>
>How many dots are visible after completing just the first fold instruction on your transparent paper?
>
>--- Part Two ---
>
>Finish folding the transparent paper according to the instructions. The manual says the code is always eight capital letters.
>
>What code do you use to activate the infrared thermal imaging camera system?

#

## Part 1 ##

When mirroring points across a line, the new coordinate can be derived quite simply.

If we're mirroring along the `x` axis, the `y` values aren't going to change, so we only need to consider the `x` value of each coordinate. Also, if `x` is smaller than the axis line, then it won't be mirrored.

Otherwise, we need to consider how far away `x` is from the axis. For an axis position `A`, this distance is `x-A`, since `x` is greater than `A`. Then, we need to mirror this distance on the other side of the axis, which is simply `A-<distance>` or `A-(x-A) = 2A-x`. For one fold, this is enough.

## Part 2 ##

Now we need to go through all the mirror axis to get the final output. While I suspect it might take a while, I'll at least try the brute force approach before trying to optimise.

One observation is that, because x reflections don't affect y coordinates, we can do all the x reflections first, then all the y reflections.

Turned out, the simple approach was enough. I had already written a print method for debugging, so most the rest of the problem was simply mirroring points.