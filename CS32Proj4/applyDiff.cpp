//
//  applydiff.cpp
//  Projoeo
//
//  Created by Gurbir Arora on 6/3/19.
//  Copyright © 2019 Gurbir Arora. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;



bool getInt(istream& inf, int& n)
{
    char ch;
    if (!inf.get(ch)  ||  !isascii(ch)  ||  !isdigit(ch))
        return false;
    inf.unget();
    inf >> n;
    return true;
}

bool getCommand(istream& inf, char& cmd, int& length, int& offset)
{
    if (!inf.get(cmd)  ||  (cmd == '\n'  &&  !inf.get(cmd)) )
    {
        cmd = 'x';  // signals end of file
        return true;
    }
    char ch;
    switch (cmd)
    {
        case 'A':
            return getInt(inf, length) && inf.get(ch) && ch == ':';
        case 'C':
            return getInt(inf, length) && inf.get(ch) && ch == ',' && getInt(inf, offset);
    }
    return false;
}

bool applydiff(istream& fold, istream& fdiff, ostream& fnew){
    char command;
    int length, offset = 0;
    
    while (getCommand(fdiff, command, length, offset))
    {
        if (command == 'x')
            return true; // reached end of diff
        
        switch (command)
        {
            case 'A':
            {
                for (int i = 0; i < length; i++)
                {
                    char temp;
                    if (!fdiff.get(temp)) // reached end of file? (length > chars to add)
                        return false;
                    fnew << temp; // write temp char into newf
                }
                break;
            }
            case 'C':
            {
                streampos position = offset;
                fold.seekg(position);
                
                // allocate memory for file content
                char* buffer = new char[length];
                
                // read content of infile
                if (!fold.read (buffer,length))
                {
                    delete [] buffer;
                    return false; // if we cannot read full command
                }
                
                // write to outfile
                fnew.write (buffer,length);
                
                // release dynamically-allocated memory
                delete[] buffer;
                break;
            }
        }
    }
    return false; // diff file is malformed
}
