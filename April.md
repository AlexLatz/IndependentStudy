# Daily Notes for my Independent Study - April

## Thursday, April 1

- Built the alpha-beta pruning portion of my Connect 4 AI
  - It was broken and I was running out of time to submit
  - Decided to push it to another branch and polish the project
- Added colors and polished the UI and error handling for submission
  - Ended up being 1 minute late because of checkstyle reconfig
- Fixed the AI - I accidentally wrote maximin search
  - Picked the worst possible moves (all in one column)
  - Also added a fix for feasible 3-in-a-row diags in the heuristic
  - It seems to be really good for now

- Links
  - <https://stackoverflow.com/questions/5762491/how-to-print-color-in-console-using-system-out-println>
    - had a cool way of doing terminal colors - supported in IntelliJ windows!

## Friday, April 2 - Sunday, April 4

- Spent more time messing with the heuristic
  - The bot isn't perfect - should be able to force a draw
  - But I really don't want to rebuild the heuristic
  - Decided to clean it up and finish
- Fixed the UI - problems with scanner.nextInt()
  - Turns out invalid input with nextInt leaves it in stdin
  - You have to call scanner.nextLine() or close the scanner to refresh
- Also added a re-evaluation function that prevents last-minute blunders

## Wednesday, April 7

- Finished chapter 6 and started chapter 7 notes
  - Skipped chapter 6 exercises because I really don't need more c++ library practice
  - Found an interesting exercise in chapter 7 so doing that
- Grammar parsing system - recursive calls into a map so it should be good
- The connect 4 AI was good practice - definitely should use MCTS next time
  - Or maybe refine the heuristic because mine was kinda weak
