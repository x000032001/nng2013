#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

#ifndef inputer_H
#define inputer_H

class inputer
{
public:
    inputer();
    void getProb(int ,int [][14]) const;
private:
    string inputFileName;
    int input();
    fstream fin;
    vector<vector<vector<int> > > inputData;

};

#endif
