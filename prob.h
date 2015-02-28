#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <bitset>
#include <set>
#include <stdint.h>
using namespace std;
#include "inputer.h"
#include "G.h"
#ifndef PROB_H
#define PROB_H

#define SOLVED 0
#define CONFLICT -1
#define INCOMPLETED -2
class prob
{
public:
    prob();
    void init(int,inputer&);
    int propagate();
    void print(int) const;
    uint64_t getLine(int) const;

    int fix0(int,int);
    int fix1(int,int);
    int fix(int,int);

    uint64_t paint_dp(int,int);
    uint64_t paint1(int,int);
    uint64_t paint0(int,int);
    uint64_t paint_p(int,int);
    uint64_t paint(int,int);

    bitset<51> chk_line;
    int data[51][14];
    int procLine;

    void setline(int ,int);
    string desToHash(int) const;
    map<uint64_t ,uint32_t> *finish_table[50];
    map<uint64_t ,uint64_t> paint_table[50];
    uint64_t line;

    void preTable( map< string , map<uint64_t ,uint32_t> >&  );

    bool firstonoff;
    void reservefix();
    void reservepaint();
    int fix_dp_arr[27][15];
    uint64_t paint_dp_arr [27][15];
    vector<pixel> pi;
    G g;
private:
    const static uint64_t noAns = 0xFFFFFFFFFFFFFFFF;
};

#endif
