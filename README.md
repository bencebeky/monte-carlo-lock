# Monte Carlo Lock

The following problem is from the book The Lady or the Tiger? by Raymond
Smullyan, First Edition, 1982, Random House Inc, Chapter 8, The Mystery of the
Monte Carlo Lock, page 107:

A lock takes combinations of letters. Some combinations open the lock, some jam
it permanently, and some are neutral. For any combinations `x` and `y` the
following properties hold:

* Property `Q`: For any combination `x`, the combination `QxQ` is specially
  related to `x`.
* Property `L`: If `x` is specially related to `y`, then `Lx` is specially
  related to `Qy`.
* Property `V` (the reversal property): If `x` is specially related to `y`, then
  `Vx` is specially related to the reverse of `y`.
* Property `R` (the repetition property): If `x` is specially related to `y`,
  then `Rx` is specially related to `yy` (the repeat of `y`).
* Property `Sp`: If `x` is specially related to `y`, then if `x` jams the lock,
  `y` is neutral, and if `x` is neutral, then `y` jams the lock.

From Property `Sp`, it follows that if combination `x` is specially related to
itself, then it opens the lock. Note that there might be other combinations that
open the lock, but it cannot be proven for any combination other than those
that are specially related to themselves based on the information above.

The original task is to find any combination that we know opens the lock, that
is, one that is specially related to itself. This repository contains code to
find all combinations that are specially related to themselves up to a fixed
length.

## Recursive approach

The first implementation, in [recursive.cc](recursive.cc), goes through all
possible strings, and checks each whether it is specially related to itself. The
main loop keeps a `std::string` object, but in order to avoid copying, the
recursive calls pass around a `View`, which is a class much like
`std::string_view` except it also supports reversed strings.

## Recursive approach with memoization

The second implementation, [memoize.cc](memoize.cc), uses the same recursive
approach, except every time it is determined about a pair a combinations whether
the first one is specially related to the second one, this information is saved
in a map.

## Ground-up approach

The third implementation, [construct.cc](construct.cc), builds up a set of
all pairs of combinations that are specially related up to the length limit.

## Comparison of the tree approaches

TODO runtime, memory usage

## Alternatives for View

View is a reimplementation of the base functionality of `std::string_view` plus
support for reversing string order.

Another approach would be to make use of `std::string_view::reverse_iterator`.
For example, a base class could be provided as an interface, with a templated
derived class that saves `begin()` and `end()` (and possibly caches length so as
not having to call `std::distance` every time) and implements the virtual
methods of the base class. Then the derived class could be instantiated once
with `std::string_view::iterator` and once with
`std::string_view::reverse_iterator` as template argument.

`operator==()` between two different types would still need to be implemented
explicitly.

## Solutions

The shortest combination that is specially related to itself is ten characters
long. Here are all the combinations up to length 15:

```
# length 10
VRLVQVRLVQ
RVLVQRVLVQ

# length 11
VLVRQVLVRQQ
VLRVQVLRVQQ

# length 14
VVVRLVQVVVRLVQ
VVRVLVQVVRVLVQ
VRLVVVQVRLVVVQ
VRVVLVQVRVVLVQ
RVLVVVQRVLVVVQ
RVVVLVQRVVVLVQ

# length 15
VLVVVRQVLVVVRQQ
VLVVRVQVLVVRVQQ
VLVRVVQVLVRVVQQ
VLRVVVQVLRVVVQQ
VVVLVRQVVVLVRQQ
VVVLRVQVVVLRVQQ
```

Géza Makay presents the general form of all solutions in the 2016 paper [All
Solutions of the Mystery of the Monte Carlo
Lock](https://www.researchgate.net/publication/311707847_All_Solutions_of_the_Mystery_of_the_Monte_Carlo_Lock):
$\texttt{V} ^k \texttt{RV} ^l \texttt{LV} ^m \texttt{QV} ^k \texttt{RV} ^l \texttt{LV} ^m \texttt{Q}$
and
$\texttt{V} ^m \texttt{LV} ^k \texttt{RV} ^l \texttt{QV} ^m \texttt{LV} ^k \texttt{RV} ^l \texttt{QQ}$,
where $k+l$ and $m$
are odd integers.

One consequence of these general forms is that although Smullyan states that
combinations may contain any letter of the alphabet, solutions in fact may only
consist of characters `Q`, `L`, `V` and `R`.
