#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "game.h"

char eliminate_gaps(int* grid, int x, int y) {
    char did_move = 0;
    char keep_going = 1;
    while(keep_going) {
        keep_going = 0;
        for(int i = 0; i < GRID_SIZE; i++) {
            for(int j = 0; j < GRID_SIZE; j++) {
                const int i_2 = i+y;
                const int j_2 = j+x;
                char adjacent_tile_in_bounds = (i_2 >= 0 && i_2 < GRID_SIZE) && (j_2 >= 0 && j_2 < GRID_SIZE);
                if(adjacent_tile_in_bounds) {
                    int* current_tile = grid + i * GRID_SIZE + j;
                    int* adjacent_tile = grid + i_2 * GRID_SIZE + j_2;
                    if(*current_tile != 0 && *adjacent_tile == 0 && adjacent_tile_in_bounds) {
                        *adjacent_tile = *current_tile;
                        *current_tile = 0;
                        did_move = 1;
                        keep_going = 1;
                    }
                }   
            }
        }
    } 
    return did_move;
}
void merge_step(int* grid, int** current_tile, int** previous_tile, char* did_merge_previous) {
    if(**current_tile != 0) {
        if(*previous_tile != NULL && **previous_tile == **current_tile && !*did_merge_previous) {
            **previous_tile = 2 * (**previous_tile);
            **current_tile = 0;
            *did_merge_previous = 1;
        } else *did_merge_previous = 0;
    }
    *previous_tile = *current_tile;
}
char slide(int* grid, int x, int y) {
    char did_move = 0;
    char did_merge_previous = 0;
    did_move = eliminate_gaps(grid, x, y);
    int* previous_tile;
    int* current_tile;
    if(x == 1)
        for(int i = 0; i < GRID_SIZE; i++) {
            for(int j = GRID_SIZE-1; j >= 0; j--) {
                current_tile = grid + i*GRID_SIZE + j;
                merge_step(grid, &current_tile, &previous_tile, &did_merge_previous);
            }
        }
    if(x == -1)
        for(int i = 0; i < GRID_SIZE; i++) {
            for(int j = 0; j < GRID_SIZE; j++) {
                current_tile = grid + i*GRID_SIZE + j;
                merge_step(grid, &current_tile, &previous_tile, &did_merge_previous);
            }
        }
    if(y == 1)
        for(int j = 0; j < GRID_SIZE; j++) {
            for(int i = GRID_SIZE-1; i >= 0; i--) {
                current_tile = grid + i*GRID_SIZE + j;
                merge_step(grid, &current_tile, &previous_tile, &did_merge_previous);
            }
        }
    if(y == -1)
        for(int j = 0; j < GRID_SIZE; j++) {
            for(int i = 0; i < GRID_SIZE; i++) {
                current_tile = grid + i*GRID_SIZE + j;
                merge_step(grid, &current_tile, &previous_tile, &did_merge_previous);
            }
        }
    did_move = did_move || eliminate_gaps(grid, x, y);
    return did_move;
}
int count_zeroes(int* grid) {
    // Counts the number of zeroes in the 2048 grid.
    int zeroes = 0;
    for(int i = 0; i < GRID_SIZE*GRID_SIZE; i++) {
        if(grid[i] == 0) zeroes++;
    }
    return zeroes;
}
int spawn_random_tile(int* grid) {
    // Adds a non-zero tile to a random location in the 2048 grid, holding either a 2 or a 4.
    int zeroes = 0;
    int zero_indexes[GRID_SIZE*GRID_SIZE]; // List of indexes in grid* that hold 0
    for(int i = 0; i < GRID_SIZE*GRID_SIZE; i++) {
        if(grid[i] == 0) {
            zero_indexes[zeroes] = i;
            zeroes++;
        };
    }
    if(zeroes > 0) {
        int value = 2;
        if(rand() % 2 == 0) value = 4;
        grid[zero_indexes[rand() % zeroes]] = value;
        return 0;
    }
    return 1;
}