## [Day 21: Dirac Dice](https://adventofcode.com/2021/day/21) ##

>There's not much to do as you slowly descend to the bottom of the ocean. The submarine computer challenges you to a nice game of Dirac Dice.
>
>This game consists of a single die, two pawns, and a game board with a circular track containing ten spaces marked 1 through 10 clockwise. Each player's starting space is chosen randomly (your puzzle input). Player 1 goes first.
>
>Players take turns moving. On each player's turn, the player rolls the die three times and adds up the results. Then, the player moves their pawn that many times forward around the track (that is, moving clockwise on spaces in order of increasing value, wrapping back around to 1 after 10). So, if a player is on space 7 and they roll 2, 2, and 1, they would move forward 5 times, to spaces 8, 9, 10, 1, and finally stopping on 2.
>
>After each player moves, they increase their score by the value of the space their pawn stopped on. Players' scores start at 0. So, if the first player starts on space 7 and rolls a total of 5, they would stop on space 2 and add 2 to their score (for a total score of 2). The game immediately ends as a win for any player whose score reaches at least 1000.
>
>Since the first game is a practice game, the submarine opens a compartment labeled deterministic dice and a 100-sided die falls out. This die always rolls 1 first, then 2, then 3, and so on up to 100, after which it starts over at 1 again. Play using this die.
>
>For example, given these starting positions:
>```
>Player 1 starting position: 4
>Player 2 starting position: 8
>```
>This is how the game would go:
>
>-    Player 1 rolls 1+2+3 and moves to space 10 for a total score of 10.
>-    Player 2 rolls 4+5+6 and moves to space 3 for a total score of 3.
>-    Player 1 rolls 7+8+9 and moves to space 4 for a total score of 14.
>-    Player 2 rolls 10+11+12 and moves to space 6 for a total score of 9.
>-    Player 1 rolls 13+14+15 and moves to space 6 for a total score of 20.
>-    Player 2 rolls 16+17+18 and moves to space 7 for a total score of 16.
>-    Player 1 rolls 19+20+21 and moves to space 6 for a total score of 26.
>-    Player 2 rolls 22+23+24 and moves to space 6 for a total score of 22.
>
>...after many turns...
>
>-    Player 2 rolls 82+83+84 and moves to space 6 for a total score of 742.
>-    Player 1 rolls 85+86+87 and moves to space 4 for a total score of 990.
>-    Player 2 rolls 88+89+90 and moves to space 3 for a total score of 745.
>-    Player 1 rolls 91+92+93 and moves to space 10 for a final score, 1000.
>
>Since player 1 has at least 1000 points, player 1 wins and the game ends. At this point, the losing player had 745 points and the die had been rolled a total of 993 times; 745 * 993 = 739785.
>
>Play a practice game using the deterministic 100-sided die. The moment either player wins, what do you get if you multiply the score of the losing player by the number of times the die was rolled during the game?
>
>--- Part Two ---
>
>Now that you're warmed up, it's time to play the real game.
>
>A second compartment opens, this time labeled Dirac dice. Out of it falls a single three-sided die.
>
>As you experiment with the die, you feel a little strange. An informational brochure in the compartment explains that this is a quantum die: when you roll it, the universe splits into multiple copies, one copy for each possible outcome of the die. In this case, rolling the die always splits the universe into three copies: one where the outcome of the roll was 1, one where it was 2, and one where it was 3.
>
>The game is played the same as before, although to prevent things from getting too far out of hand, the game now ends when either player's score reaches at least 21.
>
>Using the same starting positions as in the example above, player 1 wins in 444356092776315 universes, while player 2 merely wins in 341960390180808 universes.
>
>Using your given starting positions, determine every possible outcome. Find the player that wins in more universes; in how many universes does that player win?


#

## Part 1 ##

This problem is *heavily* steeped in mathematics, and while a brute force approach would easily solve Part 1, we may as well do *some* analysis of the problem, to see what we can learn.

First observation: using a 100-sided die is overkill, since a lot of rolls end up in the same place. Rolling an 18 has the same effect as rolling an 8, it just means you go around the game board again (which doesn't affect the score). Additionally, any set of 3 rolls from 1 to 100 is equal to a single roll from 1 to 10. This means we can reduce the 3 rolls of a 100-sided die to a single roll of a 10-sided die, and our whole problem can be reduced to modulo 10.

In fact, each roll, starting at 1 and increasing each time, forms groups of 3 values, the sum of which is equal to `3n-2 + 3n-1 + 3n = 9n-3` where `n` is a turn counter (1 on the first turn, 2 on the second, etc). What's more, `9n-3 == 7-n (mod 10)`, since stepping 9 steps forward on the board is equal to stepping 1 step back, and stepping 3 steps back is equal to stepping 7 steps forward.

Player 1 will have all the odd rolls (1,3,5...) while player 2 will have all the even rolls. This means player 1's rolls will follow the pattern 
```
6,4,2,0,8,6... (mod 10)
```
and their position on the board (relative to their initial position P1) will follow
```
6,0,2,2,0,6,0...
```
while player 2's rolls follow
```
5,3,1,9,7,5... (mod 10)
```
and their position on the board (relative to their initial position P2) will follow
```
5,8,9,8,5,0,3,4,3,0,5...
```
Both position sequences repeat, though player 2's sequence takes longer. 

What this allows us to do, is take each player's starting position, work out their position sequence (and thus their score sequence), then do 1000 divided by the sum of their score sequence, round down (to find how many full loops of the score sequence we iterate through), then iterate through the score sequence to figure out where exactly their score crosses 1000. Figure out how many turns it took this player, and how many turns it took the other player. These values can be used to find out who wins, how many rolls, and the score of the loser.

## Part 2 ##

Now the universe splits into 3 with each roll of the die, and each turn takes 3 rolls, meaning 27 universes per roll. This kind of exponential growth is far too difficult to brute force, so we need to reduce the game a bunch again.

Since things are now random, we can actually condense universes with equivalent scores into a single universe counter. That is, all universes where player 1 has a score of 10 can be grouped together.

The possible values we can roll on the die in 3 rolls are from 3 to 9, but there are 27 equally likely universes, which tells us that some rolls appear in more universes than others, and thus those rolls should be weighted. The weights we can apply to the rolls are
```
3 - 1
4 - 3
5 - 6
6 - 7
7 - 6
8 - 3
9 - 1
```
meaning that there are 7 of the 27 universes where a 6 is rolled (`1,2,3 - 1,3,2 - 2,1,3 - 2,3,1 - 3,1,2 - 3,2,1 - 2,2,2`), 6 universes where a 5 is rolled (`1,1,3 - 1,3,1 - 3,1,1 - 1,2,2 - 2,1,2 - 2,2,1`) etc.

This means we can break down a universe into 2 factors; the player's position and the player's score. Any score 21 or higher is a win, so we can ignore those possibilities too. This means we have at most 210 distinct universes at any one time (per player). The process is thus:
1. While player 1 and player 2 have a non-zero number of unfinished universes:
    1. Create a swap table of the 210 distinct universes, set all to 0.
    2. For each player 1 position and score:
        1. If there aren't any universes that match in position and score, skip to the next one.
        2. For each possible roll in the table above:
            1. Add the position and score to this universes position and score:
            3. Multiply the number of universes with this position and score by the weight from the above table to get `N`.
            2. If the score is 21 or more:
                1. Add up all the universes in player 2's position and score table.
                2. Multiply this sum by `N`, and add this to the player 1 win counter.
            3. Otherwise, set the count of universes with this new position and score in the swap table to `N`.
    3. Replace the current position and score table with the swap table.
    4. Repeat for player 2.