//
//  History.hpp
//  Programming Assignment 1 Club Zombie
//
//  Created by Gurbir Arora on 4/9/19.
//  Copyright © 2019 Gurbir Arora. All rights reserved.
//

#ifndef HISTORY_H
#define HISTORY_H

#include "globals.h"

class History {
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int rows;
    int cols;
    char grid[MAXROWS][MAXCOLS];
};

#endif
