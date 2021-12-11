## [Day 9: Smoke Basin](https://adventofcode.com/2021/day/9) ##

>These caves seem to be lava tubes. Parts are even still volcanically active; small hydrothermal vents release smoke into the caves that slowly settles like rain.
>
>If you can model how the smoke flows through the caves, you might be able to avoid it and be that much safer. The submarine generates a heightmap of the floor of the nearby caves for you (your puzzle input).
>
>Smoke flows to the lowest point of the area it's in. For example, consider the following heightmap:
>```
>2199943210
>3987894921
>9856789892
>8767896789
>9899965678
>```
>Each number corresponds to the height of a particular location, where 9 is the highest and 0 is the lowest a location can be.
>
>Your first goal is to find the low points - the locations that are lower than any of its adjacent locations. Most locations have four adjacent locations (up, down, left, and right); locations on the edge or corner of the map have three or two adjacent locations, respectively. (Diagonal locations do not count as adjacent.)
>
>In the above example, there are four low points, all highlighted: two are in the first row (a 1 and a 0), one is in the third row (a 5), and one is in the bottom row (also a 5). All other locations on the heightmap have some lower adjacent location, and so are not low points.
>
>The risk level of a low point is 1 plus its height. In the above example, the risk levels of the low points are 2, 1, 6, and 6. The sum of the risk levels of all low points in the heightmap is therefore 15.
>
>Find all of the low points on your heightmap. What is the sum of the risk levels of all low points on your heightmap?
>
>--- Part Two ---
>
>Next, you need to find the largest basins so you know what areas are most important to avoid.
>
>A basin is all locations that eventually flow downward to a single low point. Therefore, every low point has a basin, although some basins are very small. Locations of height 9 do not count as being in any basin, and all other locations will always be part of exactly one basin.
>
>The size of a basin is the number of locations within the basin, including the low point. The example above has four basins.
>
>The top-left basin, size 3:
>```
>2199943210
>3987894921
>9856789892
>8767896789
>9899965678
>```
>The top-right basin, size 9:
>```
>2199943210
>3987894921
>9856789892
>8767896789
>9899965678
>```
>The middle basin, size 14:
>```
>2199943210
>3987894921
>9856789892
>8767896789
>9899965678
>```
>The bottom-right basin, size 9:
>```
>2199943210
>3987894921
>9856789892
>8767896789
>9899965678
>```
>Find the three largest basins and multiply their sizes together. In the above example, this is 9 * 14 * 9 = 1134.
>
>What do you get if you multiply together the sizes of the three largest basins?

#

## Part 1 ##

The plan for this first part of the puzzle is to simply iterate through the entire grid, checking the adjacent cells to see if any of them are greater than or equal to the current cell. It's a simple problem for now, so there's no need to overcomplicate it yet.

## Part 2 ##

Now that we need to find and count the sizes of basins, it can be made significantly easier if we refactor everything into a grid object. This way, we can implement methods to find a basin, count the size and perform various flood fill algorithms.

I'll use a queue to perform a flood fill, with a counter that increments every time we pop an element from the queue. At the same time, we'll set the popped element to 9, so that we don't count it again in the future when we try to find another basin. Then we'll return the counter, and start another flood fill from the first non-9 element. Once there are no more non-9 elements, we can sort and find the answer.