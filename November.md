# Daily Notes for my Independent Study - November

# Tuesday, November 2nd

- Started editing disjoint generation - decided on recursive references vs list version
- Looking more promising than the original

# Wednesday, November 3rd

- Finished disjoint rewrite - much more successful on HackerRank

# Thursday, November 4th

- Started working on IDA* implementation - should hopefully be less memory-greedy

# Saturday, November 6th

- More progress - just need to fine tune its heuristics bc of inaccurate answers

# Monday, November 8th

- Lots of work towards IDA*
- Got it working - but only for super simple problems and it takes a while
- Hopefully there's a solution - the heuristic for this problem is apparently really complex
- Will maybe switch to SP-MCTS if I can't make any progress

# Tuesday, November 9th

- Tweaked IDA* a little more to get color-based heuristics - it only really works for simple problems and not as well

# Wednesday, November 10th

- Began work on migrating to SP-MCTS version - found some papers that helped a lot
- <https://dke.maastrichtuniversity.nl/m.winands/documents/CGSameGame.pdf>

# Friday, November 12th

- MCTS coming along - still converting code

# Monday, November 15th

- Finished barebones MCTS - now time for testing and debugging

# Tuesday, November 16th

- Did about an hour of testing, it definitely works but still trying to iron out some bugs in object deletion
- Leaf sorting now working and I think the UCT does as well
- Hopefully should be pretty solid as soon as I fix the bugs

# Thursday, November 18th

- Found a solution to the memory issues - pointer children
- The pointer children have weird sorting issues
- Met with Mr. Griest

# Saturday, November 20th

- Fixed the sorting issues - MCTS working!
- It's very good with about 10 seconds, but it has 1.75 max
- Working on optimizations - its already better than A*