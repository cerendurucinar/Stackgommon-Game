
// Created by Ceren Duru Cinar on 30.03.2023.

#include "Board.h"
#include <string>
#include <iostream>

using namespace std;

//default constructor
Board::Board()
{
    head = NULL;
    tail = NULL;
    xCnt = 0;
    oCnt = 0;
}

void Board::createEmptySlotEnd()
// creates an empty slot at the end of the linked list
{
    slot * newSlot = new slot();
    CharStack stack;
    newSlot->SlotStack = stack;
    if (tail == NULL) //if the list is empty
    {
        tail = newSlot;
        head = tail;
        newSlot->next = NULL;
        newSlot->prev = NULL;
    }
    else
    {
        tail->next = newSlot;
        newSlot->prev = tail;
        newSlot->next = NULL;
        tail = newSlot;
    }
}

void Board::createSlotEnd(char ch, int num)
//pre: a character for the player and integer for number of elements
// creates a slot for the given character which includes num elements at the end of the linked list
{
    slot * newSlot = new slot();
    CharStack stack;
    // pushing the character num times to the stack
    for (int i = 1; i <= num; i++)
    {
        stack.push(ch);
        if (ch == 'x') // updating counts
        {
            xCnt++;
        }
        else
        {
            oCnt++;
        }
    }
    newSlot->SlotStack = stack; // putting stack in the slot
    if (tail == NULL) // if linked list is empty
    {
        tail = newSlot;
        head = tail;
        newSlot->next = NULL;
        newSlot->prev = NULL;
    }
    else
    {
        tail->next = newSlot;
        newSlot->prev = tail;
        newSlot->next = NULL;
        tail = newSlot;
    }

}

void Board::printBoard() const
// prints the game board according to the rules
 {
    slot * ptr = head;
    char pop_ch;
    string printMaterial;
    while (ptr != NULL)
    {
        string printMat = ""; // string variable to hold the stack information
        CharStack temp_stack; // temporary stack so as not to lose stack information when we pop
        if (ptr->SlotStack.isEmpty())
        {
            printMat = "    ";
        }
        while (!(ptr->SlotStack.isEmpty()))
        {
            ptr->SlotStack.pop(pop_ch);
            printMat += pop_ch;
            temp_stack.push(pop_ch);
        }
        unsigned long int prlen = printMat.length();
        for (int i = 0; i < (4 - prlen); i++ ) // adding the missing blank characters if any
        {
            printMat = " " + printMat ;
        }
        printMaterial = printMaterial + printMat;
        ptr->SlotStack = temp_stack; // changing slot information with the temporary stack so we do not lose info
        ptr = ptr->next;
    }

    for (int a = 0; a < 4; a++)
    {
        for (int j = 0; j < printMaterial.length()/4; j++) // we are using string as a matrix with 4 rows
        {
            cout << printMaterial.at(a + 4*j);
        }
        cout << endl;
    }
     for (int j = 0; j < printMaterial.length()/4; j++) // printing bases
     {
         cout << "^";
     }
     cout << endl;
 }

bool Board::noMove(char ch, int step)
//pre: a character for the player and an integer for step
// returns true if there is no possible moves for the given character, false otherwise
{
    slot * ptr = head;
    slot * move_ptr = head;
    char popped, cont_pop;
    bool result = false;
    while (ptr != NULL)
    {
        if (!(ptr->SlotStack.isEmpty())) // checking if slot is empty
        {
            ptr->SlotStack.pop(popped);
            if (popped != ch) // the char in the slot is not same as given
            {
                ptr->SlotStack.push(popped);
                ptr = ptr->next;
                move_ptr = ptr;
                result = true;
            }
            else
            {
                ptr->SlotStack.push(popped);
                for (int i = 0; i < step && move_ptr != NULL ; i++) // moving right
                {
                    move_ptr = move_ptr->next;
                }
                if (move_ptr != NULL) // check if link exceeded or not
                {
                    if (move_ptr->SlotStack.isFull()) // if the target slot is full, we cannot move there
                    {
                        result = true;
                    }
                    else
                    {
                        if (move_ptr->SlotStack.isEmpty() == false) // if the target slot is not empty
                        {
                            move_ptr->SlotStack.pop(cont_pop);
                            if (cont_pop != ch) // check target slot's character
                            {
                                result = true;
                            }
                            else
                            {
                                result = false;
                            }
                            move_ptr->SlotStack.push(cont_pop); // push it so there is not change
                        }
                        else // a char can always move if the target slot is empty
                        {
                            result = false;
                        }
                    }
                }
                move_ptr = ptr;
                if (result) // checking the result since we do not need to check left moves if there is a move to the right
                {
                    for (int i = 0; i < step && move_ptr != NULL ; i++) // moving left
                    {
                        move_ptr = move_ptr->prev;
                    }
                    if (move_ptr != NULL) // check if list is exceeded
                    {
                        if (move_ptr->SlotStack.isFull()) // check if target slot is full
                        {
                            result = true;
                        }
                        else
                        {
                            if (move_ptr->SlotStack.isEmpty() == false) // check if target slot is empty
                            {
                                move_ptr->SlotStack.pop(cont_pop);
                                if (cont_pop != ch) // check target slot's char
                                {
                                    result = true;
                                }
                                else
                                {
                                    result = false;
                                }
                                move_ptr->SlotStack.push(cont_pop); // push it so there is no change
                            }
                            else // a char can always move if the target slot is empty
                            {
                                result = false;
                            }
                        }
                    }
                }
                ptr = ptr->next;
                move_ptr = ptr;
            }
            if (!result) // condition to break the loop
            {
                break;
            }
        }
        else // if the slot is empty, proceed to next slot
        {
            result = true;
            ptr = ptr->next;
            move_ptr = ptr;
        }
    }
    return result;
}

void Board::createSlotBegin(char ch, int num)
//pre: a character for the player and integer for number of elements
// creates a slot for the given character which includes num elements at the beginning of the linked list
{
    slot * newSlot = new slot();
    slot * ptr = newSlot;
    CharStack stack;
    for (int i = 0; i < num; i++) // pushing num many chars
    {
        stack.push(ch);
        if (ch == 'x') // check the char and update counts
        {
            xCnt++;
        }
        else
        {
            oCnt++;
        }
    }
    ptr->SlotStack = stack;
    ptr->prev = NULL;
    ptr->next = head;
    head->prev = ptr;
    head = ptr;
}

int Board::validMove(char ch, int start_idx, int step_size, int direction)
// pre: a character for the player, an integer for starting index, an integer for the move size, an integer for the direction (0 or 1)
// returns 0 if the move is valid, returns 1 if starting index is out of bounds, returns 2 if target slot index is out of bounds,
// returns 3 if target slot is not full or does not belong to the player, returns 4 if starting index does not belong to the player
{
    slot * ptr = head;
    slot * move_ptr;
    int result = 0; // start at true
    char cont_pop;
    for (int i = 0; i < start_idx && ptr != NULL ; i++) // find the starting slot
    {
        ptr = ptr->next;
    }
    if (ptr == NULL) // if starting slot is out of range
    {
        result = 1;
    }
    else
    {
        move_ptr = ptr;
        if (!(ptr->SlotStack.isEmpty())) // if starting slot is not empty
        {
            ptr->SlotStack.pop(cont_pop); // check slot's character
            if (cont_pop != ch) // this means slot does not belong to the player
            {
                result = 4;
                ptr->SlotStack.push(cont_pop); // push so nothing is changed
            }
            else
            {
                ptr->SlotStack.push(cont_pop);
                if (direction == 0) // moving left
                {
                    for (int j = 0; j < step_size && move_ptr != NULL; j++) // moving
                    {
                        move_ptr = move_ptr->prev;
                    }
                    if (move_ptr == NULL) // this means target is out of bounds
                    {
                        result = 2;
                    }
                    else
                    {
                        if (move_ptr->SlotStack.isFull()) // check if target slot is full
                        {
                            result = 3;
                        }
                        else
                        {
                            if (!(move_ptr->SlotStack.isEmpty())) // if target is not empty
                            {
                                move_ptr->SlotStack.pop(cont_pop);
                                if (cont_pop != ch) // check the character
                                {
                                    result = 3;
                                }
                                move_ptr->SlotStack.push(cont_pop); // push it
                            }
                        }
                    }
                }
                else if (direction == 1) // moving right
                {
                    for (int j = 0; j < step_size && move_ptr != NULL; j++) // moving
                    {
                        move_ptr = move_ptr->next;
                    }
                    if (move_ptr == NULL) // this means target is out of bounds
                    {
                        result = 2;
                    }
                    else
                    {
                        if (move_ptr->SlotStack.isFull()) // check if target slot is full
                        {
                            result = 3;
                        }
                        else
                        {
                            if (!(move_ptr->SlotStack.isEmpty())) // if the target slot is not empty
                            {
                                move_ptr->SlotStack.pop(cont_pop);
                                if (cont_pop != ch) // check character
                                {
                                    result = 3;
                                }
                                move_ptr->SlotStack.push(cont_pop); // push it so nothing is changed
                            }
                        }
                    }
                }
            }
        }
        else // starting index is empty (does not belong to anyone)
        {
            result = 4;
        }
    }
    return result;
}

bool Board::targetSlotFull(int target) const
// pre: an integer for the target slot index
// returns true if the target slot is full, false otherwise
{
    slot * ptr = head;
    for (int i = 0; i < target; i++) // find the target slot
    {
        ptr = ptr->next;
    }
    return (ptr->SlotStack.isFull()); // check the stack
}

void Board::movePiece(int source, int target)
// pre: integers for the source and target slot indexes
// moves the piece and updates the board list
{
    slot * ptr = head;
    char popped;
    for (int i = 0; i < source; i++) // find the source slot
    {
        ptr = ptr->next;
    }
    ptr->SlotStack.pop(popped); // pop the element to move
    if (target - source > 0) // move right
    {
        for (int i = 0; i < (target - source); i++) // find the target slot
        {
            ptr = ptr->next;
        }
        ptr->SlotStack.push(popped);
    }
    else if (target - source < 0) // move left
    {
        for (int i = 0; i < (source - target); i++) // find the target slot
        {
            ptr = ptr->prev;
        }
        ptr->SlotStack.push(popped);
    }
}

void Board::destroySlot(int dlt_idx)
// pre: gets an integer for the slot's index to be deleted
// this function deletes the slot and updates the list
{
    slot * ptr = head;
    char popped;
    for (int i = 0; i < dlt_idx; i++) // go to the slot
    {
        ptr = ptr->next;
    }
    ptr->SlotStack.pop(popped);
    if (ptr == head) // deleting the first slot
    {
        head = head->next;
        delete ptr;
        head->prev = NULL;
        ptr = NULL;
    }
    else if (ptr == tail) // deleting the last slot
    {
        tail = tail->prev;
        tail->next = NULL;
        delete ptr;
        ptr = NULL;
    }
    else // deleting in the middle
    {
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        delete ptr;
        ptr = NULL;
    }
    if (popped == 'x') // updating counts
    {
        xCnt = xCnt - 4;
    }
    else
    {
        oCnt = oCnt - 4;
    }
}

int Board::evaluateGame() const
{
    int result = 3; // tie
    if (xCnt > oCnt) // x has more
    {
        result = 2;
    }
    else if (oCnt > xCnt) // o has more
    {
        result = 1;
    }
    return result;
}

void Board::clearBoard()
// deletes all the dynamically allocated slots
{
    slot * ptr = head;
    while (head != NULL) // loop to delete
    {
        head = head->next;
        delete ptr;
        ptr = head;
    }
    tail = head; // update for the tail so no risk of memory leak
}


