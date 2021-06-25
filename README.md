<h3><b>Brief:</b></h3>

You can create a very simple model of forest fires using a cellular automaton in the form a 2D
grid of cells. Each cell can be in one of three states; either ‘empty’, ‘tree’, or ‘fire’. The next
generation of cells follows these rules:

• A ‘fire’ cell will turn into an ‘empty’ cell.

• A ‘tree’ that is within the 8-neighbourhood of a ‘fire’ cell will itself become ‘fire’.

• A ‘tree’ will burn (due to a lightning strike) 1 time in L.

• An ‘empty’ space will become a ‘tree’ (spontaneous growth) 1 time in G.
<br></br>

See also:

https://en.wikipedia.org/wiki/Forest-fire_model

https://www.aryan.app/randomstuff/forestfire.html

You can experiment with different values of L and G, but a useful starting point is G = 250 and
L = 10 G.

Exercise 4.5 Write a program which creates an empty 2D grid of cells, 80 wide and 30 high.
Then, apply the rules above to iterate the simulation, so that the next generation is created
from the previous one.
Print out every generation onto the screen, using a space to represent an empty cell, the @
character for a tree, and * for fire cells. Display the board for 1000 generations using plain
text. You may assume that the grid is always 80 cells by 30


Ensure your code is C90 (ANSI) compliant, and fully follows the house-style guidelines. Show
that your code has been developed using short, well-tested functions via the use of assert()
testing.
