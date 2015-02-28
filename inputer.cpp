#include "inputer.h"

inputer :: inputer()
{

    inputData.resize(1001);
    for (int i = 0; i < 1001; ++i)
    {
        inputData[i].resize(51);
        for (int j = 0; j < 51; ++j)
            inputData[i][j].resize(14);
    }
    inputFileName = "input.txt";
    fin.open( inputFileName.c_str() , std::fstream::in );
    input();
    fin.close();
}

int inputer :: input()
{
    char c;
    while( fin.get(c) )
    {
        int probNum = 0;
        if(c == '$')
        {
            while( fin.get(c) )
            {
                if( !('0'<=c && c<='9'))
                    break;
                probNum *= 10;
                probNum += c-'0';
            }
        }
        else
        {
            puts("garbage:");
            putchar(c);
            fgetc(stdin);
            continue;
        }
        
        //cout << "start read" << probNum << endl;
        for(int i = 0 ; i<50 ; ++i)
        {
            //cout << i << "\t";
            int _count = 1;
            while(fin.get(c))
            {
                int _num = c - '0';
                fin.get(c);
                if( c == 10 )   //  equals ENTER
                {
                    inputData[probNum][i][_count] = _num;
                    inputData[probNum][i][0] = _count;
                    break;
                }
                else if( c == 9 )   // equals TAB
                {
                    inputData[probNum][i][_count] = _num;
                    _count++;
                }
                else
                {
                    _num = _num * 10 + c - '0';
                    inputData[probNum][i][_count] = _num;
                    fin.get(c);
                    if( c == 10 )
                    {
                        inputData[probNum][i][0] = _count;
                        break;
                    }
                    else
                    {
                        _count++;
                    }
                }
            }
        }
    }
    return 0;
}

void inputer :: getProb(int n ,int ret[][14]) const
{
    for(int i = 0 ; i<51 ; ++i)
        for(int j = 0 ; inputData[n][i][j]!=0 ; ++j)
            ret[i][j] = inputData[n][i][j];
    return ;
}
