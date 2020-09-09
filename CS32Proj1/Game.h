//
//  Game.hpp
//  Programming Assignment 1 Club Zombie
//
//  Created by Gurbir Arora on 4/3/19.
//  Copyright © 2019 Gurbir Arora. All rights reserved.
//
#ifndef GAME_H
#define GAME_H

class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};

#endif
