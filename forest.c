#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "neillsimplescreen.h"

#define HEIGHT 30
#define WIDTH 80
#define G 250
#define L 2500
#define NUMOFGENERATIONS 1000
#define WAIT 0.0001

enum cellstate {EMPTY, TREE, FIRE};
typedef enum cellstate cellstate;

/* TEST CODE*/
void test(void);
void testApplyRules(void);
void testFireWithNoNeighboursBecomesEmpty(void);
void testTreeCatchesFireIfANeighbourIsOnFire(void);
void testCheckInBounds(void);
void testInitBoard(void);
void testNeighbourOnFire(void);
bool testAreAllEmpty(cellstate board[HEIGHT][WIDTH]);
void testApplyRulesInBoundsCheck(void);
/* END OF TEST CODE */

bool lightning();
bool spontaneousGrowth();
bool checkInBounds(int y, int x);
void initBoard(cellstate board[HEIGHT][WIDTH]);
bool neighbourOnFire(cellstate board[HEIGHT][WIDTH], int y, int x);
void applyRules(cellstate board[HEIGHT][WIDTH], int y, int x);
void printForest(cellstate board[HEIGHT][WIDTH]);
void executeGenerations(cellstate board[HEIGHT][WIDTH], int numOfGenerations);

int main(void)
{
    cellstate board[HEIGHT][WIDTH];
    test();

    initBoard(board);
    neillclrscrn();
    executeGenerations(board, NUMOFGENERATIONS);

    return 0;
}
/* TEST CODE */
void test(void)
{
    testCheckInBounds();
    testNeighbourOnFire();
    testInitBoard();
    testApplyRules();
}

void testApplyRules(void)
{
    testApplyRulesInBoundsCheck();
    testFireWithNoNeighboursBecomesEmpty();
    testTreeCatchesFireIfANeighbourIsOnFire();
}

void testInitBoard(void)
{
    cellstate board[HEIGHT][WIDTH];
    initBoard(board);
    assert(testAreAllEmpty(board) == true);
}

bool testAreAllEmpty(cellstate board[HEIGHT][WIDTH])
{
    int y, x;

    for(y = 0; y < HEIGHT; y++) {
        for(x = 0; x < WIDTH; x++) {
            if (board[y][x] != EMPTY) {
            return false;
            }
        }
    }
    return true;
}

void testCheckInBounds(void)
{
    int y, x;
    /* check out of bounds coordinates at the left of the grid fails */
    for (y = 0; y < HEIGHT; y++) {
        assert(checkInBounds(y, -1) == false);
    }

    /* check out of bounds coordinates at the right of the grid fails */
    for (y = 0; y < HEIGHT; y++) {
        assert(checkInBounds(y, WIDTH + 1) == false);
    }

    /* check out of bounds coordinates at the top of the grid fails */
    for (x = 0; x < WIDTH; x++) {
        assert(checkInBounds(-1, x) == false);
    }

    /* check out of bounds coordinates at the bottom of the grid fails */
    for (x = 0; x < WIDTH; x++) {
        assert(checkInBounds(HEIGHT + 1, x) == false);
    }

    /* check all in bounds coordinates are in bounds */
    for (y = 0; y < HEIGHT; ++y) {
        for (x = 0; x < WIDTH; ++x) {
            assert(checkInBounds(y, x) == true);
        }
    }
}

void testFireWithNoNeighboursBecomesEmpty(void)
{
    cellstate board[HEIGHT][WIDTH];
    initBoard(board);
    board[1][1] = FIRE;
    applyRules(board, 1, 1);
    assert(board[1][1] == EMPTY);
}

void testTreeCatchesFireIfANeighbourIsOnFire(void)
{
    cellstate board[HEIGHT][WIDTH];
    initBoard(board);
    board[1][1] = TREE;
    board[2][2] = FIRE;
    applyRules(board, 1, 1);
    assert(board[1][1] == FIRE);
}

void testNeighbourOnFire(void)
{
    cellstate board[HEIGHT][WIDTH];
    initBoard(board);
    board[0][0] = FIRE;
    assert(neighbourOnFire(board, 1, 1) == true);

    board[0][0] = EMPTY;
    board[0][1] = FIRE;
    assert(neighbourOnFire(board, 1, 1) == true);

    board[0][1] = EMPTY;
    board[0][2] = FIRE;
    assert(neighbourOnFire(board, 1, 1) == true);

    board[0][2] = EMPTY;
    board[1][0] = FIRE;
    assert(neighbourOnFire(board, 1, 1) == true);

    board[1][0] = EMPTY;
    board[2][0] = FIRE;
    assert(neighbourOnFire(board, 1, 1) == true);

    board[2][0] = EMPTY;
    board[2][1] = FIRE;
    assert(neighbourOnFire(board, 1, 1) == true);

    board[2][1] = EMPTY;
    board[2][2] = FIRE;
    assert(neighbourOnFire(board, 1, 1) == true);

    board[2][2] = EMPTY;
    board[1][2] = FIRE;
    assert(neighbourOnFire(board, 1, 1) == true);
}

void testApplyRulesInBoundsCheck(void)
{
    int y, x;
    cellstate board[HEIGHT][WIDTH];
    initBoard(board);

    /* check out of bounds coordinates at the left of the grid do nothing*/
    for (y = 0; y < HEIGHT; y++) {
        applyRules(board, y, -1);
        assert(testAreAllEmpty(board) == true);
    }

    /* check out of bounds coordinates at the right of the grid do nothing*/
    for (y = 0; y < HEIGHT; y++) {
        applyRules(board, y, WIDTH + 1);
        assert(testAreAllEmpty(board) == true);
    }

    /* check out of bounds coordinates at the top of the grid do nothing*/
    for (x = 0; x < WIDTH; x++) {
        applyRules(board, -1, x);
        assert(testAreAllEmpty(board) == true);
    }

    /* check out of bounds coordinates at the bottom of the grid do nothing*/
    for (x = 0; x < WIDTH; x++) {
        applyRules(board, HEIGHT + 1, x);
        assert(testAreAllEmpty(board) == true);
    }
}
/* END OF TEST CODE */

bool lightning()
{
    return (rand() % L) == 0;
}

bool spontaneousGrowth()
{
    return (rand() % G) == 0;
}

bool checkInBounds(int y, int x)
{
    return (y >= 0 && y < HEIGHT) && (x >= 0 && x < WIDTH);
}

void initBoard(cellstate board[HEIGHT][WIDTH])
{
    int y, x;

    for(y = 0; y < HEIGHT; y++) {
        for(x = 0; x < WIDTH; x++) {
            board[y][x] = EMPTY;
        }
    }
}

bool neighbourOnFire(cellstate board[HEIGHT][WIDTH], int y, int x)
{
    if (checkInBounds(y-1, x) && board[y-1][x] == FIRE) {
        return true;
    }
    if (checkInBounds(y-1, x-1) && board[y-1][x-1] == FIRE) {
        return true;
    }
    if (checkInBounds(y, x-1) && board[y][x-1] == FIRE) {
        return true;
    }
    if (checkInBounds(y+1, x-1) && board[y+1][x-1] == FIRE) {
        return true;
    }
    if (checkInBounds(y+1, x) && board[y+1][x] == FIRE) {
        return true;
    }
    if (checkInBounds(y+1, x+1) && board[y+1][x+1] == FIRE) {
        return true;
    }
    if (checkInBounds(y, x+1) && board[y][x+1] == FIRE) {
        return true;
    }
    if (checkInBounds(y-1, x+1) && board[y-1][x+1] == FIRE) {
        return true;
    }
    return false;
}

void applyRules(cellstate board[HEIGHT][WIDTH], int y, int x)
{
    if (!checkInBounds(y, x)) {
        return;
    }
    if (board[y][x] == EMPTY && spontaneousGrowth()) {
        board[y][x] = TREE;
        return;
    }
    if (lightning()) {
        board[y][x] = FIRE;
        return;
    }
    if (board[y][x] == FIRE) {
        board[y][x] = EMPTY;
        return;
    }
    if (board[y][x] == TREE && neighbourOnFire(board, y, x)) {
        board[y][x] = FIRE;
        return;
    }
}

void printForest(cellstate board[HEIGHT][WIDTH])
{
    int y, x;

    for(y = 0; y < HEIGHT; y++) {
        for(x = 0; x < WIDTH; x++) {
            if (board[y][x] == EMPTY) {
                printf(" ");
            }
            if (board[y][x] == TREE) {
                neillfgcol(green);
                printf("@");
            }
            if (board[y][x] == FIRE) {
                neillfgcol(red);
                printf("*");
            }
        }
        printf("\n");
    }
    neillbusywait(WAIT);
    neillcursorhome();
}

void executeGenerations(cellstate board[HEIGHT][WIDTH], int numOfGenerations)
{
    int i, y, x;

    for (i = 0; i < numOfGenerations; i++) {
        for (y = 0; y < HEIGHT; y++) {
            for (x = 0; x < WIDTH; x++) {
                applyRules(board, y, x);
                printForest(board);
            }
        }
    }
}
