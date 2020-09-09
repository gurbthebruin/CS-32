//
//  main.m
//  p3r1
//
//  Created by Gurbir Arora on 5/13/19.
//  Copyright © 2019 Gurbir Arora. All rights reserved.
//
#include "Board.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>
using namespace std; 
int main() {
    
    Board b(3,5);
    
    HumanPlayer n("N");
    HumanPlayer s("S");
    Game g(b, &n, &s);
    g.play();
    return 0;
}
