# Text Adventure Game (C++)

A turn-based, text-based dungeon adventure written in C++ for CSCI 1300 (Starting Computing) at CU Boulder, Spring 2023, by Tawhid Ather and Mallory Phillips.

Players explore a grid map, meet NPCs who pose riddles, fight monsters, and manage party status (health, inventory, money) until they win or lose. Game content is loaded from text files:

- `monsters.txt`: monster names and difficulty
- `riddles.txt`: NPC riddles and answers
- `npcDialogue.txt`: NPC lines
- `results.txt`: end-of-game stats are written here

Code is split into classes for the map (`Map.h`, `map.cpp`), players, monsters, NPCs and game status, with `game.cpp` as the main loop.

## Build and run

```bash
g++ -std=c++17 game.cpp map.cpp players.cpp monsters.cpp NPC.cpp status.cpp -o game
./game
```
