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
using namespace std;

#include "inputer.h"
#include "prob.h"
#include "backtrack.h"

#define SOLVED 0
#define CONFLICT -1
#define INCOMPLETED -2

int main()
{
    // clear output file 
#ifndef NOFILE
    std::fstream fs ("output.txt" , std::fstream::out );
    fs.close();
#endif

    std::fstream flog ("log.txt" , std::fstream::out );

    inputer input;
    map< string , map<uint64_t ,uint32_t> > big_table;

    time_t ed = time(NULL);
    clock_t edp = clock_t();
	for( int probNum = 1 ; probNum <= 1000 ; ++probNum )
    {
        FP2 fp;
        fp.init(probNum ,input);
        fp.FP.preTable( big_table );
        //fgetc(stdin);
        fp.FP.setline(31,31);
        fp.usepc = true;
        int res = fp.fp2();
        fp.usepc = false;
        printf("$%d",probNum);
        flog << "$" << probNum << "\t";
		int xddd=0;
        if ( res != INCOMPLETED )
        {
            fp.FP.g.print(probNum);
            flog << "\t0\t" ;
        }
        else  
        {
            backtrack bk(probNum,&fp);
            fp.FP.g.x = fp.FP.g.y = 31;
            bk.dfs(fp.FP.g);
            flog << "\t" << bk.lx << "\t";
			xddd=bk.lx;
        }
        printf("\tDONE\t");

        printf("time:%4lds\t\t%d\n", (long)(time(NULL)-ed),xddd);
        flog << (double( (clock()-edp))) / CLOCKS_PER_SEC << "\t" << time(NULL)-ed << endl; 
        edp = clock();
    }

    flog.close();
	return 0;
}
