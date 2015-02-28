#include "backtrack.h"

backtrack :: backtrack(int s,FP2 *fps)
{
    lx=0;
    finish = false;
    stop = false;
    n=s;
    fp = fps;
}

int backtrack :: dfs(G &g)
{
    lx++;

    if( 0 )
    {
        stop = true;
        fp->FP.g.print(n);
        return SOLVED;
    }
    
    // Do FP ( G )
	int state;
    fp->FP.g = g;
    fp->FP.setline( g.x , g.y ); 
    state = fp->fp2();

    // return IF COMPLETE
    if( state == SOLVED )
    {
        finish = true;
        fp->FP.g.print(n);
        return SOLVED;
    }

    if( state == CONFLICT )
    {
        return CONFLICT;
    }

    G origin = fp->FP.g;
    // origin bk method
    int x = fp->max_x , y = fp->max_y;

    g = origin;  
    g.grid[x][y] = '0';
    g.x = x;
    g.y = y;
    dfs(g);

    if( finish == true || stop == true ) return SOLVED; 

    g = origin;  
    g.grid[x][y] = '1';
    g.x = x;
    g.y = y;
    dfs(g);
    
    if( finish == true || stop == true ) return SOLVED; 

    return CONFLICT;
}
