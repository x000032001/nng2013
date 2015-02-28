#include "G.h"

G :: G()
{
    x = 0;
    y = 0;
}

void G :: print(int n) const
{
    #ifdef NOFILE 
    cout << "$" << n << endl;
    for(int i = 0 ; i<25 ; ++i)
    {
        for(int j = 0 ; j<25 ; ++j)
        {
            cout << (grid[j][i]=='2'?'_':grid[j][i]);
        }
        cout << endl;
    }
    #else
    std::fstream fs ("output.txt" , std::fstream::out | std::fstream::app );
    fs << "$" << n << endl;
    srand(time(NULL));
    for(int i = 0 ; i<25 ; ++i)
    {
        for(int j = 0 ; j<25 ; ++j)
        {
            if( grid[j][i] == '2' )
                fs << ('0' + rand()%2);
            else
                fs << grid[j][i];
            if( j != 24 )
                fs << '\t';
        }
        fs << endl;
    }
    #endif
}
