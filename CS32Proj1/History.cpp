//
//  History.cpp
//  Programming Assignment 1 Club Zombie
//
//  Created by Gurbir Arora on 4/9/19.
//  Copyright © 2019 Gurbir Arora. All rights reserved.
//

#include "History.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols) {
    rows = nRows - 1;
    cols = nCols - 1;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            grid[i][j] = '.';
}

bool History::record(int r, int c) {
    if (r < 1 || r - 1 > rows || c < 1  || c - 1 > cols) {
        return false;
    }
    int newR = r - 1;
    int newC = c - 1;
    
    if (grid[newR][newC] == 'Z') {
        return true;
    }
    
    if (grid[newR][newC] == '.') {
        grid[newR][newC] = 'A';
    }
    else {
        grid[newR][newC]+=1;
    }
    
    return true;
    
}

void History::display() const {
    clearScreen();
    for (int i = 0; i <= rows; i++)
    {
        for (int j = 0; j <= cols; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
    cout << endl;
}
