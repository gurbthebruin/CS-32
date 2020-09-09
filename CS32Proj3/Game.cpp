




//
//  game.cpp
//  p3r1
//
//  Created by Gurbir Arora on 5/13/19.
//  Copyright © 2019 Gurbir Arora. All rights reserved.
//

#include "Game.h"
#include "Board.h"
#include "Side.h"
#include "Player.h"
#include <iostream>
#include <string>
using namespace std;
Game::Game(const Board& b, Player* south, Player* north): board(b), s(south), n(north), turn(SOUTH){
}
//Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first.
void Game::display() const{
    cout << "  ";
    for(int i = 1; i <= board.holes(); i++){
        cout << board.beans(NORTH, i) << " ";
    }
    cout << endl << board.beans(NORTH, 0) << "         " << board.beans(SOUTH, 0) << endl;
    cout << "  ";
    for(int i = 1; i <= board.holes(); i++){
        cout << board.beans(SOUTH, i) << " ";
    }
}
void Game::status(bool& over, bool& hasWinner, Side& winner) const{
    for(int i = 1; i <= board.holes(); i++){
        if (board.beans(NORTH, i) != 0 || board.beans(SOUTH, i) != 0 ){
            over = false;
        }
    }
    over = true;
    if(board.beans(NORTH, 0) != board.beans(SOUTH, 0)){
        over = true;
        hasWinner = true;
        if(board.beans(NORTH, 0) > board.beans(SOUTH, 0))
            winner = NORTH;
        else
            winner = SOUTH;
    }else {
        over = false;
        hasWinner = false;
    }
}
//If the game isn't over (i.e., more moves are possible), set over to false and do not change anything else. Otherwise, set over to true and hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side
bool Game::move(){
    int end = 0;
    bool over = false;
    bool hasWinner = false;
    Side soof;
    status(over, hasWinner, soof);
    if(over == true){
        return false;
    } else {
        if(turn == SOUTH){
            while (turn == SOUTH && end == 0){
                cout << "how many times?" << endl;
                display(); 
                board.sow(turn, s->chooseMove(board, turn), turn, end);
                cout << "end " << end << endl;
                if(turn == SOUTH && board.beans(turn, end) == 1 && board.beans(NORTH, end) != 0)
                    board.moveToPot(NORTH, end, SOUTH);
                    cout << "nooooo" << endl;
                    }
            cout << "woaj" << endl;

            turn = NORTH;
        } else if (turn == NORTH){
            while (turn == NORTH && end == 0){
                board.sow(turn, n->chooseMove(board, turn), soof, end);
                if(turn == NORTH && board.beans(turn, end) == 1 && board.beans(SOUTH, end) != 0)
                    board.moveToPot(SOUTH, end, NORTH);
            }
            turn = SOUTH;
        }
        return true;
    }
}
//If the game is over, return false. Otherwise, make a complete move for the player whose turn it is (so that it becomes the other player's turn) and return true. "Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. If the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening.
void Game::play(){
    bool over = false;
    bool b = true;
    bool hasWinner = false;
    Side winner = SOUTH;
    if(s->isInteractive()==false && n->isInteractive()==false){
        while(move()){
            cin.ignore(10000, '\n');
            cout << endl << "Press enter to continue" << endl;
            cin.get();
        }
    } else {
        while(b && (board.beansInPlay(NORTH) != 0 || board.beansInPlay(SOUTH) != 0)){
            b = move();
        }
    }
    status(over, hasWinner, winner);
    if(over == true && hasWinner == true)
        cout << "The winner is: " << winner;
    else if (over && !hasWinner)
        cout << "It's a tie!";
}
//Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function. (Note: If when this function is called, South has no beans in play, so can't make the first move, sweep any beans on the North side into North's pot and act as if the game is thus over.)
int Game::beans(Side s, int hole) const{
    return board.beans(s, hole);
}
//Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid. This function exists so that we and you can more easily test your program.
