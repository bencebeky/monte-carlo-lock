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

The original task is to find any combination that opens the lock. This
repository contains code to find all combinations that are specially related to
themselves up to a fixed length.
