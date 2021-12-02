# Daily Notes for my Independent Study - September

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

## Wednesday, September 15

- Making good progress on fixing issues with the project - CLion debugger actually works
- Issues with copy constructors - figured out how constructor lists work

## Friday, September 17

- Started fixing it for submission online - has a cool visualizer
- Had to move everything to one file and compile it together

## Tuesday, September 21

- HackerRank submission worked, but the heuristic isn't good enough to beat their bot
- That's probably ok, the algorithm used is just a basic A* pathfinding bot so it's not very good
- Future bots will probably be more successful
- But this also gives a score which is nice

## Thursday, September 23

- Starting to mess around with the heuristic to see if I can get slightly better results
- Not much success

## Saturday, September 25

- Deciding on other algorithms to build out - probably a MCTS and a minimax of some sort
- Need to find more documentation on MCTS design

## Monday, September 26

- IT fixed my debugging issues which is nice
- Starting to figure out which components I'll change and how I'll make a visualizer