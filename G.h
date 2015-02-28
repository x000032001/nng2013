#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <ctime>
#include <set>
#include "stdint.h"
using namespace std;
#ifndef G_H_INCLUDED
#define G_H_INCLUDED

class pixel
{
    public:
        uint8_t   x;
        uint8_t   y;
        uint8_t val;

        void flip()
        {
            if( val != '0' && val != '1' )
            {
                cout << "big disease val=" << val << endl;
                fgetc(stdin);
            }
            val = ( val == '0' ? '1' : '0' );
        }

        void set(unsigned int n)
        {
            val = n & 0xFF;
            n >>= 8;
            y   = n & 0xFF;
            n >>= 8;
            x   = n & 0xFF;
        }

        unsigned int get(void)
        {
            return (x<<16) | (y<<8) | val; 
        }
};
  
class G
{
public:
    G();
    void print(int) const;
    char grid[25][25];
    int x,y;
};
#endif // G_H_INCLUDED
