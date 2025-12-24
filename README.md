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

The characters `Q`, `L`, `V`, and `R` have special meaning.  The original
problem allows any uppercase letter of the English alphabet. To keep the
branching factor low, we only allow the letter `X` in addition to the special
ones above, but this could be any character. If a solution contains multiple
occurrences of `X`, then it has to be investigated separately which ones have to
be identical characters, which is beyond the scope of the current work.

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
