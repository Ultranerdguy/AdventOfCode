## [Day 18: Snailfish](https://adventofcode.com/2021/day/18) ##

>You descend into the ocean trench and encounter some snailfish. They say they saw the sleigh keys! They'll even tell you which direction the keys went if you help one of the smaller snailfish with his math homework.
>
>Snailfish numbers aren't like regular numbers. Instead, every snailfish number is a pair - an ordered list of two elements. Each element of the pair can be either a regular number or another pair.
>
>Pairs are written as [x,y], where x and y are the elements within the pair. Here are some example snailfish numbers, one snailfish number per line:
>```
>[1,2]
>[[1,2],3]
>[9,[8,7]]
>[[1,9],[8,5]]
>[[[[1,2],[3,4]],[[5,6],[7,8]]],9]
>[[[9,[3,8]],[[0,9],6]],[[[3,7],[4,9]],3]]
>[[[[1,3],[5,3]],[[1,3],[8,7]]],[[[4,9],[6,9]],[[8,2],[7,3]]]]
>```
>This snailfish homework is about addition. To add two snailfish numbers, form a pair from the left and right parameters of the addition operator. For example, [1,2] + [[3,4],5] becomes [[1,2],[[3,4],5]].
>
>There's only one problem: snailfish numbers must always be reduced, and the process of adding two snailfish numbers can result in snailfish numbers that need to be reduced.
>
>To reduce a snailfish number, you must repeatedly do the first action in this list that applies to the snailfish number:
>
>-    If any pair is nested inside four pairs, the leftmost such pair explodes.
>-    If any regular number is 10 or greater, the leftmost such regular number splits.
>
>Once no action in the above list applies, the snailfish number is reduced.
>
>During reduction, at most one action applies, after which the process returns to the top of the list of actions. For example, if split produces a pair that meets the explode criteria, that pair explodes before other splits occur.
>
>To explode a pair, the pair's left value is added to the first regular number to the left of the exploding pair (if any), and the pair's right value is added to the first regular number to the right of the exploding pair (if any). Exploding pairs will always consist of two regular numbers. Then, the entire exploding pair is replaced with the regular number 0.
>
>Here are some examples of a single explode action:
>
>-    [[[[[9,8],1],2],3],4] becomes [[[[0,9],2],3],4] (the 9 has no regular number to its left, so it is not added to any regular number).
>-    [7,[6,[5,[4,[3,2]]]]] becomes [7,[6,[5,[7,0]]]] (the 2 has no regular number to its right, and so it is not added to any regular number).
>-    [[6,[5,[4,[3,2]]]],1] becomes [[6,[5,[7,0]]],3].
>-    [[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]] becomes [[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]] (the pair [3,2] is unaffected because the pair [7,3] is further to the left; [3,2] would explode on the next action).
>-    [[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]] becomes [[3,[2,[8,0]]],[9,[5,[7,0]]]].
>
>To split a regular number, replace it with a pair; the left element of the pair should be the regular number divided by two and rounded down, while the right element of the pair should be the regular number divided by two and rounded up. For example, 10 becomes [5,5], 11 becomes [5,6], 12 becomes [6,6], and so on.
>
>Here is the process of finding the reduced result of [[[[4,3],4],4],[7,[[8,4],9]]] + [1,1]:
>```
>after addition: [[[[[4,3],4],4],[7,[[8,4],9]]],[1,1]]
>after explode:  [[[[0,7],4],[7,[[8,4],9]]],[1,1]]
>after explode:  [[[[0,7],4],[15,[0,13]]],[1,1]]
>after split:    [[[[0,7],4],[[7,8],[0,13]]],[1,1]]
>after split:    [[[[0,7],4],[[7,8],[0,[6,7]]]],[1,1]]
>after explode:  [[[[0,7],4],[[7,8],[6,0]]],[8,1]]
>```
>Once no reduce actions apply, the snailfish number that remains is the actual result of the addition operation: [[[[0,7],4],[[7,8],[6,0]]],[8,1]].
>
>The homework assignment involves adding up a list of snailfish numbers (your puzzle input). The snailfish numbers are each listed on a separate line. Add the first snailfish number and the second, then add that result and the third, then add that result and the fourth, and so on until all numbers in the list have been used once.
>
>For example, the final sum of this list is [[[[1,1],[2,2]],[3,3]],[4,4]]:
>```
>[1,1]
>[2,2]
>[3,3]
>[4,4]
>```
>The final sum of this list is [[[[3,0],[5,3]],[4,4]],[5,5]]:
>```
>[1,1]
>[2,2]
>[3,3]
>[4,4]
>[5,5]
>```
>The final sum of this list is [[[[5,0],[7,4]],[5,5]],[6,6]]:
>```
>[1,1]
>[2,2]
>[3,3]
>[4,4]
>[5,5]
>[6,6]
>```
>Here's a slightly larger example:
>```
>[[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]
>[7,[[[3,7],[4,3]],[[6,3],[8,8]]]]
>[[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]
>[[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]]
>[7,[5,[[3,8],[1,4]]]]
>[[2,[2,2]],[8,[8,1]]]
>[2,9]
>[1,[[[9,3],9],[[9,0],[0,7]]]]
>[[[5,[7,4]],7],1]
>[[[[4,2],2],6],[8,7]]
>```
>The final sum [[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]] is found after adding up the above snailfish numbers:
>```
>  [[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]
>+ [7,[[[3,7],[4,3]],[[6,3],[8,8]]]]
>= [[[[4,0],[5,4]],[[7,7],[6,0]]],[[8,[7,7]],[[7,9],[5,0]]]]
>
>  [[[[4,0],[5,4]],[[7,7],[6,0]]],[[8,[7,7]],[[7,9],[5,0]]]]
>+ [[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]
>= [[[[6,7],[6,7]],[[7,7],[0,7]]],[[[8,7],[7,7]],[[8,8],[8,0]]]]
>
>  [[[[6,7],[6,7]],[[7,7],[0,7]]],[[[8,7],[7,7]],[[8,8],[8,0]]]]
>+ [[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]]
>= [[[[7,0],[7,7]],[[7,7],[7,8]]],[[[7,7],[8,8]],[[7,7],[8,7]]]]
>
>  [[[[7,0],[7,7]],[[7,7],[7,8]]],[[[7,7],[8,8]],[[7,7],[8,7]]]]
>+ [7,[5,[[3,8],[1,4]]]]
>= [[[[7,7],[7,8]],[[9,5],[8,7]]],[[[6,8],[0,8]],[[9,9],[9,0]]]]
>
>  [[[[7,7],[7,8]],[[9,5],[8,7]]],[[[6,8],[0,8]],[[9,9],[9,0]]]]
>+ [[2,[2,2]],[8,[8,1]]]
>= [[[[6,6],[6,6]],[[6,0],[6,7]]],[[[7,7],[8,9]],[8,[8,1]]]]
>
>  [[[[6,6],[6,6]],[[6,0],[6,7]]],[[[7,7],[8,9]],[8,[8,1]]]]
>+ [2,9]
>= [[[[6,6],[7,7]],[[0,7],[7,7]]],[[[5,5],[5,6]],9]]
>
>  [[[[6,6],[7,7]],[[0,7],[7,7]]],[[[5,5],[5,6]],9]]
>+ [1,[[[9,3],9],[[9,0],[0,7]]]]
>= [[[[7,8],[6,7]],[[6,8],[0,8]]],[[[7,7],[5,0]],[[5,5],[5,6]]]]
>
>  [[[[7,8],[6,7]],[[6,8],[0,8]]],[[[7,7],[5,0]],[[5,5],[5,6]]]]
>+ [[[5,[7,4]],7],1]
>= [[[[7,7],[7,7]],[[8,7],[8,7]]],[[[7,0],[7,7]],9]]
>
>  [[[[7,7],[7,7]],[[8,7],[8,7]]],[[[7,0],[7,7]],9]]
>+ [[[[4,2],2],6],[8,7]]
>= [[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]
>```
>To check whether it's the right answer, the snailfish teacher only checks the magnitude of the final sum. The magnitude of a pair is 3 times the magnitude of its left element plus 2 times the magnitude of its right element. The magnitude of a regular number is just that number.
>
>For example, the magnitude of [9,1] is 3*9 + 2*1 = 29; the magnitude of [1,9] is 3*1 + 2*9 = 21. Magnitude calculations are recursive: the magnitude of [[9,1],[1,9]] is 3*29 + 2*21 = 129.
>
>Here are a few more magnitude examples:
>```
>    [[1,2],[[3,4],5]] becomes 143.
>    [[[[0,7],4],[[7,8],[6,0]]],[8,1]] becomes 1384.
>    [[[[1,1],[2,2]],[3,3]],[4,4]] becomes 445.
>    [[[[3,0],[5,3]],[4,4]],[5,5]] becomes 791.
>    [[[[5,0],[7,4]],[5,5]],[6,6]] becomes 1137.
>    [[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]] becomes 3488.
>```
>So, given this example homework assignment:
>```
>[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]
>[[[5,[2,8]],4],[5,[[9,9],0]]]
>[6,[[[6,2],[5,6]],[[7,6],[4,7]]]]
>[[[6,[0,7]],[0,9]],[4,[9,[9,0]]]]
>[[[7,[6,4]],[3,[1,3]]],[[[5,5],1],9]]
>[[6,[[7,3],[3,2]]],[[[3,8],[5,7]],4]]
>[[[[5,4],[7,7]],8],[[8,3],8]]
>[[9,3],[[9,9],[6,[4,9]]]]
>[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]]
>[[[[5,2],5],[8,[3,7]]],[[5,[7,5]],[4,4]]]
>```
>The final sum is:
>```
>[[[[6,6],[7,6]],[[7,7],[7,0]]],[[[7,7],[7,7]],[[7,8],[9,9]]]]
>```
>The magnitude of this final sum is 4140.
>
>Add up all of the snailfish numbers from the homework assignment in the order they appear. What is the magnitude of the final sum?
>
>--- Part Two ---
>
>You notice a second question on the back of the homework assignment:
>
>What is the largest magnitude you can get from adding only two of the snailfish numbers?
>
>Note that snailfish addition is not commutative - that is, x + y and y + x can produce different results.
>
>Again considering the last example homework assignment above:
>```
>[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]
>[[[5,[2,8]],4],[5,[[9,9],0]]]
>[6,[[[6,2],[5,6]],[[7,6],[4,7]]]]
>[[[6,[0,7]],[0,9]],[4,[9,[9,0]]]]
>[[[7,[6,4]],[3,[1,3]]],[[[5,5],1],9]]
>[[6,[[7,3],[3,2]]],[[[3,8],[5,7]],4]]
>[[[[5,4],[7,7]],8],[[8,3],8]]
>[[9,3],[[9,9],[6,[4,9]]]]
>[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]]
>[[[[5,2],5],[8,[3,7]]],[[5,[7,5]],[4,4]]]
>```
>The largest magnitude of the sum of any two snailfish numbers in this list is 3993. This is the magnitude of [[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]] + [[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]], which >reduces to [[[[7,8],[6,6]],[[6,0],[7,7]]],[[[7,8],[8,8]],[[7,9],[0,6]]]].
>
>What is the largest magnitude of any sum of two different snailfish numbers from the homework assignment?

#

## Part 1 ##

This looks fairly complex on the surface, so lets try to break it down.
1. We have a structure defining a Number
2. Each node in the Number is either a Pair or a Value
3. Each Pair has 2 child nodes
4. Each Value has a single value stored in it
5. Each node can be evaluated into a value
6. Adding 2 Numbers creates a Pair of them, then reduced the Number
7. Pairs with a depth of 4 or more need to 'explode' outwards
8. Values with a value of 10 or more split into Pairs
9. If a Number has no Pairs that can explode or Values that can split, it's fully reduced

That's a lot to work on, but it's a bit more managable now.

Points 1-4 suggest a tree structure, where each node is either a Pair or a Value. Something like
```
class Node
  // Empty

class Pair : Node
  Node* left
  Node* right

class Value : Node
  int value

class Number
  Node* rootNode
```
Point 5 introduces an `evaluate` method that can be overriden
```
class Node
  virtual int evaluate()

class Pair : Node
  Node* left
  Node* right
  int evaluate() return 3*left->evalutate() + 2*right->evalutate()

class Value : Node
  int value
  int evaluate() return value
```
Point 6 defines addition between two Numbers
```
class Number
  Node* rootNode

Number operator+(Number l, Number r) return Number{Pair{l.rootNode, r.rootNode}}
```
Points 7-9 define more complex behaviours.

To explode, we can pass down a depth value, incrementing each time we step down a level. If the depth is 4 or more, and both child nodes are Values, then we explode outwards. To explode outwards, we separate the left and right explosions. For each one, we walk back up the tree, passing the Value node through, and try to add it to the inner-most child. This gives us a few more methods to implement, as well as tracking the parent node
```
class Node
  Node* parent
  virtual int evalulate()
  virtual bool DoExplosion(int depth) // recursive down
  virtual void ExplodeLeft(Node* value) // recursive up
  virtual void ExplodeRight(Node* value) // recursive up
  virtual bool AddRight(Node* value) // recursive down
  virtual bool AddLeft(Node* value) // recursive down
```
This might look like a lot, but it allows us a lot of flexibility in how we navigate the tree.

To split a Value is much easier. We walk through the tree to find the first Value that says it can split. We then tell the parent to split its child node into a new Pair of Values, and then delete the old child (which C++ std::shared_ptr can do for us). This looks like
```
class Node
  ... // exisiting code from above
  virtual bool SplitChild() // recursive down
```
Lastly, we need to reduce a Number. We should be fairly simple
```
class Number
  void Reduce()
    while (rootNode->DoExplosion() || rootNode->SplitChild()) {}
```
Taking advantage of short-circuit evaluation to simplify the instruction loop.

The last task, that wasn't on the list of points, it to actually parse the input. I'll use a similar method as I have on other challenges, with a recursive parsing. From a string input, read a Node like so
```
Node* ReadNode(string input, int index)
  if (input[index] == '[')
    Pair* out
    out->left = ReadNode()
    input.ignore(1)
    out->right = ReadNode()
    input.ignore(1)
    return out
  else
    return Value{to_number(input)}
```

## Part 2 ##

Now we need to find the largest pair sum. The input is short enough that I reckon we should be able to brute force this part, because it's nearly 1am on the 19th and I don't have the energy to do a thorough analysis of the problem to see if there's a shortcut.