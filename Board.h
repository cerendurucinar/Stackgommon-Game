//
// Created by Ceren Duru Cinar on 30.03.2023.
//

#ifndef BOARD_H
#define BOARD_H
#include "CharStack.h"

struct slot
{
    slot * next;
    slot * prev;
    CharStack SlotStack;

    slot()
    {}
};

class Board
{
private:
    slot * head;
    slot * tail;
    int xCnt;
    int oCnt;

public:
    Board();
    void createEmptySlotEnd();
    void createSlotEnd(char ch, int num);
    void printBoard() const;
    bool noMove(char ch, int step);
    void createSlotBegin(char ch, int num);
    int validMove(char ch, int start_idx, int step_size, int direction);
    bool targetSlotFull(int target) const;
    void movePiece(int source, int target);
    void destroySlot(int dlt_idx);
    int evaluateGame() const;
    void clearBoard();
};

#endif //BOARD_H
