//
//  Sequence.cpp
//  Proj2Final
//
//  Created by Gurbir Arora on 4/23/19.
//  Copyright © 2019 Gurbir Arora. All rights reserved.
//

#include "Sequence.h"
Sequence::Sequence(): m_size(0){
    m_head = new Node;
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
}
int Sequence::insert(int pos, const ItemType& value){
    if (pos < 0 || pos > m_size){
        return -1;
    }
    // if out of bounds return
    Node* p;
    int count = 0;
    //use to track relative position within list
    for (p = m_head->m_next; count!=pos && p != m_head; p = p->m_next){
        count++;
    }
    if (pos == count){
        m_size++;
        //increment size on insert
        Node* hold = new Node;
        hold->m_item = value;
        hold->m_next = p;
        hold->m_prev = p->m_prev;
        hold->m_prev->m_next = hold;
        p->m_prev=hold;
        return pos;
    }
    return -1;
}
int Sequence::insert(const ItemType& value) {
    int pos = 0;
    //use to track relative position within list
    Node* p = new Node;
    Node* hold = new Node;
    for (p = m_head->m_next; value > p->m_item && p != m_head; p = p->m_next){
        pos++;
    }
    hold->m_item = value;
    hold->m_next = p; //p is moved forward so hold's next is p
    hold->m_prev = p->m_prev; //hold's prev is p's original prev
    //update p->m_prev and p
    hold->m_prev->m_next = hold;
    p->m_prev = hold;
    m_size++;
    //increment m_size on insert
    return pos;
}
bool Sequence::erase(int pos){
    Node* p;
    int count = 0;
    //use to track relative position within list
    if (pos < 0 || pos > size()){  // not found
        return false;
    }
    //if out of position bounds throw exception
    for (p =m_head->m_next; p!=m_head && count != pos; p = p->m_next){
        count++;
    }
    if(p != m_head){
        p->m_prev->m_next = p->m_next;
        p->m_next->m_prev = p->m_prev;
        delete p;
        m_size--;
        return true;
    }
    return false;
}
int Sequence::remove(const ItemType& value){
    int counter = 0;
    while(erase(find(value))){
        counter++;
    }
    return counter;
}
bool Sequence::get(int pos, ItemType& value) const{
    Node* p;
    int count = 0;
    if(pos < 0){
        return false;
    }
    for(p = m_head->m_next; p!=m_head && count != pos; p = p->m_next){
        count++;
    }
    if(p == m_head){
        return false;
    }
    value=p->m_item;
    return true;
}
bool Sequence::set(int pos, const ItemType& value){
    Node* p;
    int count = 0;
    if (pos < 0){
        return false;
    }
    for(p = m_head->m_next; p!=m_head && count!= pos; p = p->m_next){
        count++;
    }
    if (p == m_head){
        return false;
    }
    p->m_item = value;
    return true;
}
int Sequence::find(const ItemType& value) const{
    Node *curr = new Node;
    int count = 0;
    for (curr=m_head->m_next; curr != m_head && value != curr->m_item; curr = curr->m_next){
        count++;
    }
    if (curr == m_head){
        return -1;
    }
    if (curr->m_item == value){
        return count;
    }
    else{
        return -1;
    }
}
void Sequence::swap(Sequence& other){
    // swap head pointers
    Node* tHead = m_head;
    m_head = other.m_head;
    other.m_head = tHead;
    
    // swap sizes
    int size = m_size;
    m_size = other.m_size;
    other.m_size = size;
}


/*Sequence::Node* Sequence::finder(const ItemType& value) const{
 // Do a linear search through the list
 Node* p;
 for (p = m_head->m_next; p != m_head && p->m_item != value; p = p->m_next)
 ;
 return p;
 }
 Sequence::Node* Sequence::finder(int pos) const{
 Node* current = m_head; // Initialize current
 int count = 0;
 while (current != nullptr && count != pos){
 current = current->m_next;
 count++;
 }
 //while (current != nullptr && current->m_item != item)
 return current;
 }
 */
Sequence::~Sequence(){
    // Delete the m_size non-dummy nodes plus the dummy node
    for (Node* p = m_head->m_prev ; m_size >= 0; m_size--){
        Node* toDel = p;
        p = p->m_prev;
        delete toDel;
    }
}

Sequence::Sequence(const Sequence& other): m_size(other.m_size){
    // Create dummy node; don't initialize its pointers
    m_head = new Node;
    Node* prev = m_head;
    for (Node* p = other.m_head->m_next; p != other.m_head; p = p->m_next){
        // Create a copy of the node p points to
        Node* p2 = new Node;
        p2->m_item = p->m_item;
        
        // Connect the new node to the previous one
        p2->m_prev = prev;
        prev->m_next = p2;
        
        // Reset prev to last node created
        prev = p2;
    }
    
    // Connect last node created to m_head
    m_head->m_prev = prev;
    prev->m_next = m_head;
}

Sequence& Sequence::operator=(const Sequence& oppa){
    if (this != &oppa){
        Sequence temp(oppa);
        swap(temp);
    }
    return *this;
}

int subsequence(const Sequence& seq1, const Sequence& seq2){
    ItemType item;
    ItemType item_2;
    int s1 = seq1.size();
    int s2 = seq2.size();
    if (s1 < s2 || s2 == 0){
        return -1;
    }
    for (int i = 0; i < s1; i++) {
        int j = 0;
        for (j = 0; j < s2; j++) {
            if (i + j == s1){
                return -1;
            }
            seq1.get(i+j, item);
            seq2.get(j, item_2);
            if (item != item_2){
                break;
            }
        }
        if (j == s2){
            return i;
        }
    }
    return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result){
    Sequence s;
    ItemType item;
    ItemType item_2;
    
    int insertAt = 0; //mark where to insert (the end)
    for (int pos = 0; seq1.get(pos, item) || seq2.get(pos, item_2); pos++) {
        if (seq1.get(pos, item)) {
            s.insert(insertAt, item);
            insertAt++; //tempResults has grown
        }
        if (seq2.get(pos, item_2)) {
            s.insert(insertAt, item_2);
            insertAt++;
        }
    }
    result = s;
}
