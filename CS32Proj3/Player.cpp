//
//  Player.cpp
//  p3r1
//
//  Created by Gurbir Arora on 5/13/19.
//  Copyright © 2019 Gurbir Arora. All rights reserved.
//

#include "Player.h"
#include "Side.h"
#include "Board.h"
#include "Game.h"
#include <iostream>
#include <string>
using namespace std;
Player::Player(std::string name): n(name){}
//Create a Player with the indicated name.
std::string Player::name() const{
    return n;
}
//Return the name of the player.
bool Player::isInteractive() const{
    return false;
}
//Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
Player::~Player(){}
//Since this class is designed as a base class, it should have a virtual destructor.

HumanPlayer::HumanPlayer(string name): Player(name), n(name){
}
bool HumanPlayer::isInteractive() const{
    return true;
}
int HumanPlayer::chooseMove(const Board& b, Side s) const{
    int i = -20;
    while(i < 0 || i > b.holes()){
        cout << endl << "Make your valid move: " << endl;
        cin >> i;
    }
    return i; 
}
HumanPlayer::~HumanPlayer(){

}
