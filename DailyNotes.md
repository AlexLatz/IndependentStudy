# Daily Notes for my Independent Study

## Friday, March 19

- Meeting with Mr. Griest
  - Starting my daily notes
  - Learning C++ through Accelerated CPP
  - SDL vs. SFML - decided probably SDL because of the low-level control
    - Important for writing the AI agents - need ability to control the environment
  - Digital note-taking - handwritten vs. digital, markdown or vim
    - Right now, leaning towards vim notes - we'll see what actually ends up being usable
  - Sharing digital notes through GitHub
  - For next week - continuing to learn C++, trying to find a good SDL resource
    - Finish chapter 5 exercises, potentially start chapter 6 notes

- Links
  - <https://www.libsdl.org/> - SDL2 homepage
  - <https://www.sfml-dev.org/> - SFML homepage
  - <https://pandoc.org/> - digital notetaking converter - possibly chain into vim

## Sunday, March 21

- Deep dive into vim config on Windows
  - Almost done configuring on mac, decided to use WSL2 and Windows Terminal
    - (the new windows terminal is very nice)
  - May eventually consider switching back to Manjaro Linux w/ i3-gaps
  - Will do some more coding tmrw, just wanted to consider switching to vim for C++
  - vscode's C++ support is iffy on mac, and vim is very portable (nice for mult computers)
- I'll get to chapter 5 exercises tmrw, just wanted to work on env setup first

- Links
  - <https://github.com/MaskRay/ccls> - c++ language server
  - <https://github.com/neoclide/coc.nvim> - vim lsp autocompletion plugin
  - need these two for setting up vim c++ dev

## Monday, March 22

- Mostly finished with vim config, started chapter 5 exercises
  - Went with coc.nvim and clangd for c++ lsp
  - Had to switch to neovim to fix weird autocomplete menu refresh issues
  - vim is so nice - plus more functional docs than on mac vscode
- Permutation index exercise
  - Decided to take my own approach, but may revert to book algorithm if mine doesn't work out
  - Had to look up what this was because the exercise seemed really boring at first

- Links
  - <https://github.com/jackguo380/vim-lsp-cxx-highlight> - semantic highlighting for c++ in vim

## Tuesday, March 23

- Configured mac vim, finished exercise 5-1
  - This exercise was a little complicated
    - had to create my own algorithm because the textbook's didn't make sense
  - I'll probably skip some of the exercises in this unit - they're busy work
  - Just want to make sure I'm confident with C++ collections and iterators
- Mac terminal customization is so cool
  - Still need to switch to neovim on mac, but waiting for my llvm 11 update first
  - also need to setup some sort of compiler/multiplexer for running code

- Links
  - <https://github.com/sonph/onehalf> - the greatest color scheme of all time

## Thursday, March 25

- Switched to neovim on mac, set up a compiler zsh alias
  - Finally pretty happy with my mac c++ workflow
- Finished enough chapter 5 exercises to feel confident, moving on to chapter 6

- Links
  - <https://blog.lftechnology.com/command-line-productivity-with-zsh-aliases-28b7cebfdff9>
    - how to do zsh aliases

## Saturday, March 27 - Monday, March 29

- Began chapter 6 notes, continued to tweak vim
  - Very close to switching to it full-time
- Also have been considering SFML over SDL because it's more barebones than I thought

## Tuesday, March 30 - Wednesday, March 31

- Paused work on Accelerated CPP because of an interesting APCS-A project
  - Decided to implement an AI in the Connect 4 project
  - Lots of quarantine free time so it should be good
- Fully finished the base game for Connect 4 so I can scrap the AI if I run out of time
  - Missing a heuristic for alpha-beta pruning minimax search, trying to implement it
  - Some sort of threat-based heuristic seems promising
- Also could do MCTS just because the heuristic is painful to make
  - May consider this if I find some better pseudocode or example

- Links
  - <https://asingleneuron.wordpress.com/2012/08/04/connect-four/>
    - one person's approach to alpha-beta pruning for connect four
    - Good idea for the heuristic, might try a variation of this
  - <https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning>
    - Good pseudocode and explanation for the algorithm
  - <https://web.archive.org/web/20180629163426/http://mcts.ai/>
    - archived version of old site that detailed MCTS stuff
    - very good resource, part of a Essex/Bradford project that ended in 2013
