# Unix and C Programming (UCP1000)
# Diploma of Information Technology - Stage 2
# Curtin College - Trimester 2, 2021

ASSIGNMENT ONE
Simple ASCII-based Laser Tank Game

CREATED AND TESTED WITH 
-------------------------------------------------------------------------------
> Visual Studio Code Remote WSL - Ubuntu 20.04
> Vim in Ubuntu 20.04 Live Server (VM used in CS2000 unit) 

COMPILING AND RUNNING THE PROGRAM
-------------------------------------------------------------------------------
To compile the program, use make then run with ./laserTank
<row_size> <col_size> <player_row> <player_col> <player_direction> 
<enemy_row> <enemy_col> <enemy_direction>. Make sure to input
correct command line arguments otherwise the game will not work.

WHAT WORKS IN THE GAME
-------------------------------------------------------------------------------
> Accepts nine command-line arguments including the executable called
  ./laserTank
> Checks validity of command-line arguments before allocating memory for
  the map and starting the game.
> Successfully allocates memory for a 2D char array initialize characters
  based on command-line arguments.
> Refreshes the terminal screen and prints an updated map after every 
  accepted user input for player tank movement.
> Complete player tank movement according to assignment specifications.
> Enemy tank shoots laser as soon as player tank moves in front of it.
> Laser animation changes color every time it moves a block forward.
> No border movement errors for laser and player tank movement.
> Winning or losing condition runs correctly.
> No memory leaks (repeatedly checked using valgrind).

RECOMMENDATIONS OR IMPROVEMENTS
-------------------------------------------------------------------------------
> Use of keyboard input for player movement.
> Scanf *might* be the cause for the glitch (I have now accepted this as 
  a feature and not a bug).
> User input for player movement is imperfect as multiple input of either 
  n, s, w, or e is accepted. For example, wwwww will make the player tank
  teleport forward. Here enters the power of assumptions, please do 
  input the correct command for this.
> However, it does not display game instructions during laser animation so 
  do not enter anything.
> But if you still try to enter something, I'm pretty sure it doesn't do
  anything to the player tank.
> Could fix a few lines of code for cleaner work (maybe some other 
  advanced C functions) but it works. 
> Any other unchecked bug is open for criticism. Happy to receive feedback 
  on this.
!!! UPDATE: Game is not as glitchy on VM Ubuntu. !!! 

-------------------------------------------------------------------------------
# This program was written solely by Kai-Yu Yu as part of a UCP1000 unit
# requirement. All C programming concepts or logic used in this assignment 
# were referenced/learned from unit lecture slides, tutorial discussions, 
# Github repository for ANSI color codes, and a 2D array image from 
# Google images to visualize movement in the array.
