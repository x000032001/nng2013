#ifndef BACKTRACK_H
#define BACKTRACK_H
#include <time.h>
#include <bitset>
#include "prob.h"
#include "G.h"
#include "FP2.h"

#define SOLVED 0
#define CONFLICT -1
#define INCOMPLETED -2
#define PAINTED -3

class backtrack
{
public:
	backtrack(int,FP2*);
	int dfs(G&);
    int n;
	FP2 *fp;
	int lx;
private:
	bool stop;
	bool finish;
};

#endif
