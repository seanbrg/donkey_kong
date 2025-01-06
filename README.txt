ID: 318938743 211544002
Sean Berger and Anna Ber

Donkey Kong
-----------

there are several features in this game that are beyond what was required in the assignment and are deserving of bonus points in our eyes:
- the game is colored in the method that was suggested in the document. we tried using colors close to the original game.
  color mode is on by default but it can be toggled off in a settings menu that is accessible by pressing (2) in the main menu.
- there are three difficulty tiers: easy, normal and hard. each difficulty makes the game speed faster and allows more barrels to spawn by lowering the amount of game-loop cycles between each barrel spawn.
  the hardest difficulty spawns twice as many barrels. good luck with that one.
  the difficulty can also be switched in the settings menu.
- pausing the game (by pressing ESC) raises a little window that also allows to exit the current game and return to the main menu.

furthermore,
when designing this assignment we strived to make it modular in order to support more features and bigger scale in future assignments. we did so while adhering to the OOP principles we were taught in class. one example of this is in our design of the stages:
the game board is not drawn by hand but rather loads a "stage" object that we construct with a function. the stage object is responsible for adding the game elements to the board, and stages can act as a linked list, they have a pointer to "next". so we can potentially already support multi-level gameplay and dynamic level generation.


