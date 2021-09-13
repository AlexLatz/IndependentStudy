# Daily Notes for my Independent Study - August

## Monday, August 23

- Got C++ working with VSCode on my new mac
  - Had to install gcc and set my C++ compiler to cpp-11 for docs to work
- Found a HackerRank problem to work on for practice
  - Called clickomania, began building out the game structure

## Wednesday, August 25

- Continued work on Clickomania - finished the sliding functionality
  - Began work on the disjoint sets, structuring for the AI

## Thursday, August 26

- Met with Mr. Griest, considered expanding the project into the study
  - May increase the board size and test building out more complex AIs

## Monday, August 30

- Fixed disjoint set creation - reversed the sorting operator and equality operators
  - Also did some optimizations - no longer checking the set on each coordinate
  - This saves roughly 2 seconds per board - so it makes the AI like 2 million times faster

## Tuesday, August 31

- Added removing set of blocks and sliding functionality - works well together
  - Excited about making the AI for this - it's an interesting game

## Wednesday, September 1

- Decided on a heuristic - number of blocks left on screen + number of moves from root node
- Began work on the AI wrapper class

## Friday, September 3

- Messed around with object-oriented file structure, separated everything out
- Fixed issues with the copy constructors

## Tuesday, September 7

- Did some pointer work, think I got everything passing through correctly
- Dealing with the C++ priority queue adapter - it has a weird read-only pop/top structure

## Thursday, September 9

- Met with Mr. Griest
  - Realized that I could make the grids const while talking with him
- More restructuring, header define guards

## Friday, September 10

- Lots of compiler work - managed to get it building and running
  - The program crashes - out of memory error so it's time to debug
- VSCode debugger problems

## Saturday, September 11

- Switched to CMake to make the building process easier - now the debug menu kinda works
- Had to compile in x86_64 because VSCode isn't fully working natively on M1 Macs yet

## Monday, September 13

- More CMake problems - debugger won't show local variables, crashes often
- Changing IDEs to CLion to hopefully get more help with building and debugging