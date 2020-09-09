//
//  createDiff.cpp
//  Projoeo
//
//  Created by Gurbir Arora on 6/3/19.
//  Copyright © 2019 Gurbir Arora. All rights reserved.

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <list>
#include <string>
#include <vector>

using namespace std;
bool getInt(istream& inf, int& n);
bool getCommand(istream& inf, char& cmd, int& length, int& offset);
bool applyDiff(istream& fold, istream& fdiff, ostream& fnew);
string createDiffHelper(const string& oldString, const string& newString, int STRINGLENGTH);

const int BUCKETMULTIPLIER = 1.1;

struct segment
{
    segment (int offset, const string& oldFileSegment)
    {
        m_offset = offset;
        m_oldFileSegment = oldFileSegment;
    }
    
    int m_offset;
    string m_oldFileSegment;
};



class oldTable
{
public:
    oldTable(int size);
    void insert(const string& partOfString, int offset);
    void print();
    int hashFunc(const string &hashMe, int numberbuckets); // returns index (bucket) to insert string into
    int num_buckets; // amount of buckets in the table
    vector<list<segment>> buckets; // each element of vector serves as the bucket
};

oldTable::oldTable(int size)
:num_buckets(size * BUCKETMULTIPLIER)
{
    buckets.resize(num_buckets);
}


void oldTable::print()
{
    for (int i = 0; i < buckets.size(); i++)
    {
        if (buckets[i].size() != 0)
        {
            for (list<segment>::const_iterator p = buckets[i].begin(); p != buckets[i].end(); p++)
            {
                cerr << "from index: " << i << " the element is|" << p->m_oldFileSegment << "|offset is " << p->m_offset << endl;
            }
        }
        else
            cerr << "this index " << i << " contains NO elements" << endl;
    }
}

int oldTable::hashFunc(const string& hashMe, int numberbuckets)
{
    hash<string> str_hash;
    size_t hashValue = str_hash(hashMe);
    unsigned int index = hashValue % numberbuckets;
    return index;
}

void oldTable::insert(const string& partOfString, int offset)
{
    int index = hashFunc(partOfString, num_buckets); // bucket will be what index of vector to put string into
    segment temporary(offset, partOfString); // create a temporary segment to be inserted into that bucket's list
    buckets[index].push_back(temporary);
}


string createDiffHelper(const string& oldFileString, const string& newFileString, int STRINGSIZE)
{
    int cCommandOffset, cCommandLength = 0;
    bool matchFound = false; // have we found a match while looking for string segment in hash table?
    
    string diffCommand; // string that we will ultimately return
    
    oldTable hashTable((int)oldFileString.size()); // create hash table with # of chars in the string
    
    for (int i = 0; i < oldFileString.size(); i++)
    {
        string temp = oldFileString.substr(i, STRINGSIZE); // i is the offset
        hashTable.insert(temp, i);
    }
    
    vector<char>tempACommands; // vector for storing chars not found in the old file string
    
    int j = 0;
    while (j < newFileString.size())
    {
        
        string curr = newFileString.substr(j, STRINGSIZE);
        int index =  hashTable.hashFunc(curr, hashTable.num_buckets);
        
        
        if (hashTable.buckets[index].size() != 0) // check that list is not empty (hash for string was found)
        {
            for (list<segment>::const_iterator p = hashTable.buckets[index].begin(); p != hashTable.buckets[index].end(); p++)
            {
                if (curr == p->m_oldFileSegment) // found match in hash table
                {
                    if (tempACommands.size() != 0) // add all the previous unfound chars to the diff command string
                    {
                        diffCommand += "A" + to_string(tempACommands.size()) + ":";
                        for (int i = 0; i < tempACommands.size(); i++)
                            diffCommand += tempACommands[i];
                    }
                    
                    tempACommands.clear(); // clear the vector to start over in inserting new chars to be added
                    
                    cCommandOffset = p->m_offset; // save offset value we found match in
                    cCommandLength = STRINGSIZE; // command length is currently STRINGSIZE
                    
                    int contOldIndex = p->m_offset + STRINGSIZE; // next index after last match
                    int contNewIndex = j + STRINGSIZE; // next index after last match
                    
                    while (newFileString[contNewIndex] == oldFileString[contOldIndex]) // comparing further match
                    {
                        if (contNewIndex >= newFileString.size() || contOldIndex >= oldFileString.size())
                            break; // reached end of either strings while comparing how many identical chars
                        contNewIndex++;
                        contOldIndex++;
                    }
                    
                    cCommandLength = contOldIndex - cCommandOffset; // ultimate length of command to feed into diff file (if no further match then it's just STRINGSIZE)
                    
                    if (cCommandLength + cCommandOffset <= oldFileString.size())
                    {
                        diffCommand += "C" + to_string(cCommandLength) + "," + to_string(cCommandOffset); // insert command into diff file
                        matchFound = true;
                        j = contNewIndex; // new index that we start to new step in the loop
                    }
                    
                    break; // break out of loop (already found match) in this bucket's linked list
                }
                else
                    matchFound = false; // have not found a match given that bucket WAS empty
            }
        }
        else
            matchFound = false; // have not found a match given that bucket was NOT empty (there were collisions)
        
        if (!matchFound)  // create the "add" command
        {
            tempACommands.push_back(newFileString[j]); // push back the first character of unfound string
            j++; // increment j by 1 to move the string analysis over by 1
        }
    }
    
    // final addition if there are no more matches
    if (tempACommands.size() != 0)
    {
        diffCommand += "A" + to_string(tempACommands.size()) + ":";
        for (int i = 0; i < tempACommands.size(); i++)
            diffCommand += tempACommands[i];
        
        tempACommands.clear();
    }
    return diffCommand; // return the finals diff string generated by helper function
}


void createDiff(istream& fold, istream& fnew, ostream& fdiff)
{
    vector<string> diffFiles; // create a vector that will store all the different diffs generated by helper function
    
    stringstream oldBuffer, newBuffer;
    oldBuffer << fold.rdbuf();
    string oldFileString(oldBuffer.str()); // read in the old string
    newBuffer << fnew.rdbuf();
    string newFileString(newBuffer.str()); // read in the new string
    
    int i = 2;
    while (i <= 50)
    {
        diffFiles.push_back(createDiffHelper(oldFileString, newFileString, i));
        i = i + 2; // N size increments of 2
    }
    
    string compare = diffFiles[0];
    
    for (int i = 0; i < diffFiles.size(); i++)
    {
        if (compare.size() > diffFiles[i].size())
            compare = diffFiles[i];
    }
    fdiff << compare;
}
