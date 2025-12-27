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

## Comparison of the three approaches

The following table lists runtime with maximum lenght of 11 on an average
laptop:

| approach  | runtime |
| --------- | ------- |
| recursive | 16.5 s  |
| memoize   | 125.0 s |
| construct | 6.0 s   |

The recursive approach is straightforward and fast. Often times with recursion,
memoization improves runtime. However, the memoized version is much slower in
this case. Most of the performance penalty comes from copying the string to
store in the cache. This could be sped up slightly by storing all the strings in
`main()`, and modifying `RelationshipCache::related()` to take `View` arguments
and store those in the caches. However, at the end of the run with
`kMaxLength = 11`, the related cache has only 20 entries, and the not related
cache has only 76,958,607 entries (compare that to 17,592,186,044,416 possible
pairs of combinations of 11 character length each drawn from 4 letters). The
related cache does not receive a single hit, and the not related cache has a hit
rate of $1.2\cdot10^{-7}$. So no optimization is likely to make memoization
worth it.

The reason for this is that with the recursive approach, the vast majority of
`related()` calls return false. For a typical pair of combinations, the nested
`related()` calls terminate after only the first or second call. Hence only a
very small portion of combination space is explored. And the arguments are
typically different for different starting points, resulting in exceedingly low
cache hit rate. It must be kept in mind that the starting point of these
recursions is always a pair of identical combinations, which represent a tiny
fracion of all possible pairs of combinations.

Note that recursion could potentially be sped up ever so slightly by inlining
`Q_related()`, `L_related()`, `V_related()` and `R_related()`, only checking if
the first combination is empty once, and being a little more economical with
checking its first character. However, there is not a lot of room for
improvement here.

The construct algorithm turns out to be faster than the recursive one. By the
end of the run it finds a total of 4,288,020 pairs of specially related
combinations of length at most 11. Even though construction means deeper
branching that iteration, maybe a firstful of steps from each starting point as
opposed to very few in the typical case, and construction involves string
copies, it is still faster, because recursion examines all possible combinations
up to length 11, while construction only seeds using the Q property over all
possible combinations up to length 9 (so that even with the Q character
prepended and appended it fits in the length limit of 11).

## Alternatives for View

View is a reimplementation of the base functionality of `std::string_view` plus
support for reversing string order.

Another approach would be to make use of `std::string_view::reverse_iterator`.
For example, a base class could be provided as an interface, with a templated
derived class that saves `begin()` and `end()` (and possibly caches length so as
not having to call `std::distance` every time) and implements the virtual
methods of the base class. Then the derived class could be instantiated once
with `std::string_view::iterator` and once with
`std::string_view::reverse_iterator` as template argument, and the `reverse()`
implementation of each could return an instance of the other class.

`operator==()` between all combinations of the two different types could have a
templated implementation using iterators, and would need to be explicitly
instantiated for the four cases.

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
consist of characters `Q`, `L`, `V` and `R`. The code in this repository make
used of this property to slightly reduce the branching factor. Note that even
with an extra character `X` included in the set of allowed characters, no other
solutions were found up to length 15, corroborating the statement of the 2016
paper by Makay.
