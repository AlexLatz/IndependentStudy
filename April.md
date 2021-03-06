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

## Thursday, April 8 - Friday, April 9

- Finished the grammar parsing exercise - coincidentally good recursion practice
  - Also ran into some random number stuff in C++, seems kinda controversial
  - either C rand() or C++17 uniform distributions
- But overall very happy with my C++ knowledge
  - Gonna move onto SFML development soon

- Links
  - <https://stackoverflow.com/questions/6942273/how-to-get-a-random-element-from-a-c-container>
    - People arguing about the best approach to generate an int in range

## Sunday, April 11

- Finished up chapter 7 and started chapter 8 notes
  - The book is starting to get a little dated (made in 1998)
  - Iterators are nowhere near as important imo
- Hopefully it gets a little more into the object-oriented differences
  - Then I'll be ready to start work in SFML

## Monday, April 12

- Finished chapter 8 notes, started chapter 9
  - Chapter 8 was all about generics and iterators - not super relevant
- Also fixed my documentation issues by connecting to a Github Codespace
  - This might be super useful for SFML dev because the documentation is important

## Wednesday, April 14 - Friday, April 16

- Finished chapter 9 notes - getting comfortable with C++ OOP syntax
  - None of the exercises were any good so I just created some points and a rect
- Also messed around with VSCode setup for SFML/C++ and keep running into weird issues
  - The lack of docs on only mac is really strange
  - It goes away when I use a codespace but those don't support SFML

## Tuesday, April 20

- Fixed SFML for VSCode on mac, need to find tutorials for it next
  - Got the documentation working which is good
- Started chapter 10 notes

## Thursday, April 29

- Been super busy with finishing robotics code and AP exams starting
  - Finally finished chapter 10 notes and began the exercises
- This chapter was actually super helpful - arrays and pointers make a lot of sense

