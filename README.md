# tictactoe
A blazing-fast, optimal tic-tac-toe agent written in C++.

Some of the numerous optimizations made:
- Negamax search with alpha-beta pruning.
- Representation of positions as bitboards.
- Optimized move-ordering.
- Transposition table storing the results of previously searched
nodes.
- Leaf evaluation heuristics (leaf nodes are scored based on
the number of moves played and the game result).

This implementation is a _proof of concept_: tic-tac-toe has a
relatively small search tree when compared to games like chess
or Go and can be solved without such optimizations.

However, it demonstrates the utilization of high-level 
search algorithms that can be applied to _significantly more
complex games._

See the performance benchmarking results
(each the average of 10,000 trials):

|Initial Board State|Parameters|Mean Time|
|----|----|----|
|Empty|Transposition table reset between trials|634 μs|
|Empty|Transposition table preserved between trials|41 μs|

You can experiment with the agent for yourself using
`Benchmark.cpp`.