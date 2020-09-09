//
//  Player.hpp
//  Programming Assignment 1 Club Zombie
//
//  Created by Gurbir Arora on 4/3/19.
//  Copyright © 2019 Gurbir Arora. All rights reserved.
//

#ifndef PLAYER_H
#define PLAYER_H

class Arena;

class Player
{
public:
    // Constructor
    Player(Arena *ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;
    
    // Mutators
    void   stand();
    void   moveOrAttack(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_age;
    bool   m_dead;
};

#endif
