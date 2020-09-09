//
//  Header.h
//  Programming Assignment 1 Club Zombie
//
//  Created by Gurbir Arora on 4/3/19.
//  Copyright © 2019 Gurbir Arora. All rights reserved.
//
#ifndef GLOBALS_H
#define GLOBALS_H

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();

const int MAXROWS = 20;              // max number of rows in the arena
const int MAXCOLS = 30;              // max number of columns in the arena
const int MAXZOMBIES = 150;          // max number of zombies allowed
const int INITIAL_ZOMBIE_HEALTH = 2;

const int UP      = 0;
const int DOWN    = 1;
const int LEFT    = 2;
const int RIGHT   = 3;
const int NUMDIRS = 4;

#endif
