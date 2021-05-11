# branch-n-propagate
Backtracking framework with callbacks, branches, bounds and propagation

## Design
This is a header-only library, no need to compile and link it. Just include `bnp.hpp` and use as in the `main.cpp` example file with `DummySum` problem.

`Bnp` stands for branch and propagate: a generic backtracking algorithm with the possibility of applying propagations in each step. Specifically, it implements the following algorithm:

- If problem is solved, then done
- If not, propagate while there is something to propagate
  - Once impossible to propagate, then branch based on a branching strategy
  - Keep recursing

In order to make this work the user must implement specifics for the problem at hand.