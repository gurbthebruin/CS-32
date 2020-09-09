//
//  Sequence.hpp
//  Proj2Final
//
//  Created by Gurbir Arora on 4/23/19.
//  Copyright © 2019 Gurbir Arora. All rights reserved.
//

#ifndef Sequence_h
#define Sequence_h
#include <string>
using ItemType = std::string;

class Sequence{
public:
    Sequence();
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    //Desructor, copy constructor, assginment operator
    ~Sequence();
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& oppa);
private:
    struct Node{
        ItemType m_item;
        Node*     m_next;
        Node*     m_prev;
    };
    
    Node* m_head;
    int   m_size;
    /*
     Node* finder(const ItemType& item) const;
     Node* finder(int pos) const;
     */
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

//Inline implementation
inline
bool Sequence::empty() const{
    return size() == 0;
}
inline
int Sequence::size() const{
    return m_size;
}
#endif /* Sequence_h */
