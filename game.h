#ifndef GAME_H
#define GAME_H
char eliminate_gaps(int* grid, int x, int y);
void merge_step(int* grid, int** current_tile, int** previous_tile, char* did_merge_previous);
char slide(int* grid, int x, int y);
int count_zeroes(int* grid);
int spawn_random_tile(int* grid);
#endif GAME_H