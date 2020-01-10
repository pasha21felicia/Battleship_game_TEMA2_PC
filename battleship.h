#ifndef BATTLESHIP_H
#define BATTLESHIP_H
#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define K_DOWN        0102            
#define K_UP          0101

#define NORTH 0
#define SOUTH 1
#define WEST  2
#define EAST  3

void read(char **line, char *nume);
int getRandoms(int lower, int upper);
int main_menu(char, char[], char[], char[], int);
void new_game(int argc, char *argv[], char **jucator, char comp[20][20], char comp_aux[12][22], int *comp_score, int *jucator_score);
void resume(char **jucator, char comp[20][20], char comp_aux[12][22], int *comp_score, int *jucator_score);
int checkNORTH(int ship_lenth, int row, int col, char comp[20][20]);
int checkSOUTH(int ship_lenth, int row, int col, char comp[20][20]);
int checkEAST(int ship_lenth, int row, int col, char comp[20][20]);
int checkWEST(int ship_lenth, int row, int col, char comp[20][20]);
void placeNORTH(int ship_length, int row, int col, char comp[20][20]);
void placeSOUTH(int ship_length, int row, int col, char comp[20][20]);
void placeEAST(int ship_length, int row, int col, char comp[20][20]);
void placeWEST(int ship_length, int row, int col, char comp[20][20]);
void create_boards(int argc, char *argv[], char **jucator, char comp[20][20], char comp_aux[12][22]);
void game(char **jucator, char comp[20][20], char comp_aux[12][22], int *comp_score, int *jucator_score);
int check_player_ships(char **jucator);
int check_comp_ships(char jucator[12][22]);
void winner(char **jucator, char comp_aux[12][22], int *comp_score, int *jucator_score);
void destroy_in_advance(char comp_aux[12][22], int *jucator_score, char **jucator, int *comp_score);


#endif