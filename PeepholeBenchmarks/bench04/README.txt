Ismail Badawi
Carla Morawicz

JOOS Benchmark -- Battle Connect Four

This program is a modified version of Connect4, where several special moves
have been introduced to make the game more interesting and fun. The provided
ones mainly delete tokens in certain patterns, but since all the moves are
are implemented by overriding a method in an abstract class, any move one can
think of could theoretically be added. Maybe one that deletes random tokens on
the board, or rotates the board 90 degrees, or swaps the player's tokens, or 
allows a player to place more than one token, or to let his token replace the
one on which it falls instead of landing on top of it, or place it on the
bottom of a column moving everything else up, or...

For testing purposes, the first input is an integer indicating either
deterministic mode, or random mode. Each player is allocated three
special moves from our list of special moves -- in deterministic mode, these
moves are always the same in the same order. Our provided input files all
start with 1 for deterministic mode (but the game should be played in random
mode, obviously.)

Compile with `joosc *.java`, run with `java Game`.
