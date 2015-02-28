#ifndef FP2_H
#define FP2_H
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
#include <cmath>
using namespace std;

#include "inputer.h"
#include "prob.h"
#include "G.h"

#define SOLVED 0
#define CONFLICT -1
#define INCOMPLETED -2
#define PAINTED -3

#ifndef CLASSM
#define CLASSM
class m
{
    public:
    int x;
    int y;
    int v;
    double pi_size;
    int operator<(const m& t) const
    {
        return pi_size > t.pi_size;
    }
    bool operator==(const m& t) const
    {
        return ( x==t.x )&&( y==t.y ); 
    }
};
#endif
class FP2
{
public:
    set<unsigned int> P;
    map<unsigned int, set<unsigned int> > pclist;
    void init(int ,inputer&);
    prob FP;
    int fp2();
    int rfp2();
    int probe(int p);
    int probeG(int p,int c);
    int max_x,max_y;
    double max_pi_size;
    bool usepc;
protected:
private:
};

#endif
