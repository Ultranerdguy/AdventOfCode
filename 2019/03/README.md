# Day 3 #

## [Day 3: Crossed Wires](https://adventofcode.com/2019/day/3) ##

>The gravity assist was successful, and you're well on your way to the Venus refuelling station. During the rush back on Earth, the fuel management system wasn't completely installed, so that's next on the priority list.
>
>Opening the front panel reveals a jumble of wires. Specifically, two wires are connected to a central port and extend outward on a grid. You trace the path each wire takes as it leaves the central port, one wire per line of text (your puzzle input).
>
>The wires twist and turn, but the two wires occasionally cross paths. To fix the circuit, you need to find the intersection point closest to the central port. Because the wires are on a grid, use the Manhattan distance for this measurement. While the wires do technically cross right at the central port where they both start, this point does not count, nor does a wire count as crossing with itself.
>
>For example, if the first wire's path is `R8,U5,L5,D3`, then starting from the central port (o), it goes right 8, up 5, left 5, and finally down 3:
>```
>...........
>...........
>...........
>....+----+.
>....|....|.
>....|....|.
>....|....|.
>.........|.
>.o-------+.
>...........
>```
>Then, if the second wire's path is `U7,R6,D4,L4,` it goes up 7, right 6, down 4, and left 4:
>
>```
>...........
>.+-----+...
>.|.....|...
>.|..+--X-+.
>.|..|..|.|.
>.|.-X--+.|.
>.|..|....|.
>.|.......|.
>.o-------+.
>...........
>```
>
>These wires cross at two locations (marked X), but the lower-left one is closer to the central port: its distance is 3 + 3 = 6.
>
>Here are a few more examples:
>```
>    R75,D30,R83,U83,L12,D49,R71,U7,L72
>    U62,R66,U55,R34,D71,R55,D58,R83 = distance 159
>    R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51
>    U98,R91,D20,R16,D67,R40,U7,R15,U6,R7 = distance 135
>```
>What is the Manhattan distance from the central port to the closest intersection?

#

## Part 1 ##

For this challenge, we're asked to find intersection points between two wires. This is where a little maths starts to come in handy

For two wires with endpoints `A,B` and `C,D`, we know that the two wires intersect if there exist values `S` and `T` such that
```
A + S(B-A) = C + T(D-C)
0 <= S <= 1
0 <= T <= 1
```
Simplifying, we get
```
A-C + S(B-A) - T(D-C) = 0
```
This looks like 1 equation in 2 variables, but these are 2D points, so there's actually 2 equations here. If we rename a few variables for readability
```
E = C-A
F = B-A
G = D-C

SFx - TGx = Ex
SFy - TGy = Ey
```
Which can be written as a matrix equation
```
|Fx, -Gx| * |S| = E
|Fy, -Gy|   |T|
```
And now we can solve for S and T. By left multiplying by the matrix inverse, we get
```
|S| = (1/(GxFy - FxGy)) * |-Gy, Gx||Ex|
|T|                       |-Fy, Fx||Ey|
```
Which simplifies to
```
S = (GxEy - ExGy)/(GxFy - FxGy)
T = (FxEy - ExFy)/(GxFy - FxGy)
```
After checking that both `S` and `T` lie in the range `[0,1]`, we can then use either `S` or `T` to find the collision point.

With one minor caveat. When the matrix determinant `GxFy - FxGy = 0`, this implies that our two wires are facing the same (or directly opposite) direction, or that one or more of the wires has zero length.

Luckily, this can be checked separately. We can prevent wires of zero length from being added in the first place by ignoring any input that specifies a zero length. This is unlikely, but it's an easy enough edge case to handle.

This just leaves when the wires travel along the same line. If they intersect, then at least two of the four following statements must be true
```
A lies on the line C-D
B lies on the line C-D
C lies on the line A-B
D lies on the line A-B
```
Just handling the first case
```
A = C + U(D-C)
CA = A-C
CD = D-C
CA = UCD
CAx = UCDx
CAy = UCDy
CAx/CDx = CAy/CDy = U
CAxCDy = CAyCDx = UCDxCDy
```
And a successful hit happens when `0 <= U <= 1`, or `0 <= CAx <= CDx` with the collision happening at `A`.

We repeat this process for each endpoint, and we'll have found all possible collisions between 2 wires.

Now to repeat this process for all the wires. Oh, and we still need to actually read them in from file.

## Part 2 ##

