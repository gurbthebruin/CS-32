


//
//  Board.cpp
//  p3r1
//
//  Created by Gurbir Arora on 5/13/19.
//  Copyright © 2019 Gurbir Arora. All rights reserved.
//

#include "Board.h"
#include <string>
#include <iostream>
#include "Side.h"
using namespace std;
Board::Board(int nHoles, int nInitialBeansPerHole):  m_holes(nHoles), m_beans(nInitialBeansPerHole){
    if(nHoles <= 0)
        m_holes = 1;
    if(nInitialBeansPerHole < 0)
        m_beans = 0;
    nBeans = new int[m_holes+1];
    sBeans = new int[m_holes+1];
    nBeans[0] = 0;
    sBeans[0] = 0;
    for(int i = 1; i <= m_holes; i++){
        nBeans[i] = nInitialBeansPerHole;
        sBeans[i] = nInitialBeansPerHole;
    }
}
//Construct a Board with the indicated number of holes per side (not counting the pot) and initial number of beans per hole. If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.
int Board::holes() const{
    return m_holes;
}
//Return the number of holes on a side (not counting the pot).
int Board::beans(Side s, int hole) const{
    if(hole > m_holes || hole < 0){
        return -1;
    }
    if(s == NORTH){
        return nBeans[hole];
    } else if(s == SOUTH){
        return sBeans[hole];
    }
    return -1;
}
//Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.
int Board::beansInPlay(Side s) const{
    int beans = 0;
    if(s == NORTH){
        for(int i = 1; i <= m_holes; i++){
            beans+=nBeans[i];
        }
        return beans;
    }else if (s == SOUTH){
        for(int i = 1; i <= m_holes; i++){
            beans+=sBeans[i];
        }
        return beans;
    } else {
        return 0;
    }
}
//Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
int Board::totalBeans() const{
    int total = 0;
    int add = 0;
    for(int i = 0; i <= m_holes; i++){
        add = nBeans[i] + sBeans[i];
        total += add;
    }
    return total;
}
//Return the total number of beans in the game, including any in the pots.
bool Board::sow(Side s, int hole, Side& endSide, int& endHole){
    //If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything. Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The parameters endSide and endHole are set to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)
    int b = beans(s, hole);
    cout << b << endl;
    if(b == 0 || b == -1 || hole == 0){
        return false;
    }
    if(s == NORTH)
        nBeans[hole] = 0;
    else if (s == SOUTH)
        sBeans[hole] = 0;
    if(s == SOUTH){
        for(int i = hole; i <= m_holes; i++){
            sBeans[i]++;
            cout << b << endl;
            b--;
            endHole = i;
            if(i == m_holes && b >= 0){
                sBeans[0]++;
                endHole = 0;
            }
        }
        endSide = SOUTH;
        
    }
    return true; 
}

/*bool Board::sow(Side s, int hole, Side& endSide, int& endHole){
//If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything. Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The parameters endSide and endHole are set to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)
    int b = beans(s, hole);
    int counter1 = b / m_holes;
    if(b == 0 || b == -1 || hole == 0){
        return false;
    }
    if(s == NORTH)
        nBeans[hole] = 0;
    else if (s == SOUTH)
        sBeans[hole] = 0;
    if(counter1 > 0)
        counter1--;
    while(b / m_holes >= 0 && b > 0){
        if(b / m_holes == 0){
            if (s == NORTH && b <= hole){
                for(int i = hole - 1; i > 0; i--){
                    nBeans[i]++;
                    endHole = i;
                }
                endSide = NORTH;
                return true;
            } else if (s == SOUTH && b <= m_holes - hole + 1){
                if(b <= m_holes - hole + 1){
                    for(int i = hole + 1; i < m_holes + 1; i++){
                        sBeans[i]++;
                        endHole = i;
                    }
                    endSide = SOUTH;
            }
                return true;
        }
        } else if (s == NORTH) {
            int v = 0;
            for (int i = m_holes; i >= 0; i++){
                nBeans[i]++;
                v = i;
                b--;
            }
            if (b > 0){
                s = SOUTH;
            } else {
                endSide = NORTH;
                endHole = v;
            }
        } else if (s == SOUTH){
            int v = 0;
            for(int i = 1; i <= m_holes; i++){
                sBeans[i]++;
                v = i;
                b--;
                if(i == m_holes){
                    if (b - 1 > 0){
                    sBeans[0]++;
                    v = 0;
                    b--;
                    s = NORTH;
                    } else if (b > 0){
                        sBeans[0]++;
                        v = 0;
                        b--;
                    }
                }
            }
            if(b > 0){
                s = NORTH;
            } else{
                endSide = SOUTH;
                endHole = v;
            }
        }
}
 
    
    
    
    
    
    
    
    
    while(counter1 >= 0){
    if(s == NORTH){
        if(b <= hole){
            for(int i = hole - 1; i > 0; i--){
                nBeans[i]++;
                endHole = i;
            }
            endSide = NORTH;
            //case where beans can be distributed within side up to pot
        } else {
            for(int i = hole - 1; i > 0; i--){
                nBeans[i]++;
                b--;
            }
            for(int i = 1; i <= m_holes; i++){
                if(b <= 0){
                    endSide = SOUTH;
                    endHole = i;
                    return true;
                }
                sBeans[i]++;
                b--;
            }
        }
    } else if (s == SOUTH){
        if(b <= m_holes - hole + 1){
            for(int i = hole + 1; i < m_holes + 1; i++){
                sBeans[i]++;
                endHole = i;
                }
        endSide = SOUTH;
        } else {
            for(int i = hole + 1; i < m_holes + 1; i++){
                sBeans[i]++;
                b--;
            }
            for()
        }
     }
        counter1--;
    }
  }
 
    return true;
}
 */
bool Board::moveToPot(Side s, int hole, Side potOwner){
    int b = beans(s, hole);
    if(hole > m_holes || hole < 1){
        return false;
    }
    if(potOwner == NORTH)
        nBeans[0] += b;
    else if (potOwner == SOUTH)
        sBeans[0] += b;
    return true;
}
//If the indicated hole is invalid or a pot, return false without changing anything. Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.
bool Board::setBeans(Side s, int hole, int beans){
    if(hole > m_holes || hole < 0 || beans < 0)
        return false;
    if(s == NORTH)
        nBeans[hole] = beans;
    else if (s == SOUTH)
        sBeans[hole] = beans;
    return true;
}
//If the indicated hole is invalid or beans is negative, this function returns false without changing anything. Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. (This may change what beansInPlay and totalBeans return if they are called later.) This function exists solely so that we and you can more easily test your program: None of your code that implements the member functions of any class is allowed to call this function directly or indirectly. (We'll show an example of its use below.)
Board::~Board(){
}
