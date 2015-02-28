#include "prob.h"

prob :: prob()
{
    firstonoff = false;
    procLine = 0;
}

inline void prob :: print(int n) const
{
    g.print(n);
}

void prob :: init(int probNum ,inputer &a)
{
    for(int i = 0 ; i<25 ; ++i)
        for(int j = 0 ; j<25 ; ++j)
            g.grid[i][j] = '2';


    a.getProb(probNum,data);
}

inline uint64_t prob :: getLine(int num) const
{
    uint64_t ret=0; 
    ret |= 0x1LL << 2;
    if( num <= 25 )
    {
        // 1~25
        for( int i = 0 ; i<25 ; ++i )
            ret |= (g.grid[num-1][i] - '0' + 0x1LL ) << ( (i+2) << 1 );
        return ret;
    }

    // 26~50
    for( int i = 0 ; i<25 ; ++i )
        ret |= (g.grid[i][num-26] - '0' + 0x1LL ) << ( (i+2) << 1 );
    return ret;
}

string prob :: desToHash(int line) const
{
    string res = "XX";
    for( int i = 0 ; i <= data[line][0] ; ++i )
    {
        res += data[line][i]+'0';
        res += '~';
    }
    return res;
}

void prob :: setline(int x ,int y)
{
    x++;
    y++;

    if( x != 32 && y != 32 )
    {
        chk_line.set(x); 
        chk_line.set(y+25); 
    }
    else
    {
        chk_line.set(); 
    }

}

int prob::propagate()
{
    pi.clear();

    int num = 1;
    while( 1 )
    {
        for( num = 1 ; num <= 50 && chk_line.test(num) == 0 ; ++num )
            ;
            if(num > 50)
                break;
        line = getLine(num);

        procLine = num-1;

        uint64_t new_line = paint_dp(26,data[procLine][0]);

        if( new_line == noAns )
        {
            return CONFLICT; 
        }

        for(int i = 1 ; i<=25 ; ++i)
        {
            char old_pixel , new_pixel;

            old_pixel = (char)(( line     & ( 0x3LL << ((1+i)<<1) )) >> ((1+i)<<1)) + '0' - 1;
            new_pixel = (char)(( new_line & ( 0x3LL << ((1+i)<<1) )) >> ((1+i)<<1)) + '0' - 1;
            if( old_pixel != new_pixel )
            {
                if(num<=25)
                {
                    // num = 1~25
                    pixel p;
                    p.x = num-1;
                    p.y = i-1;
                    p.val = new_pixel;
                    chk_line.set(i+25); 
                    pi.push_back(p);
                    g.grid[num-1][i-1] = new_pixel; 
                }
                else
                {
                    // num = 26~50
                    pixel p;
                    p.x = i-1;
                    p.y = num-26;
                    p.val = new_pixel;
                    chk_line.set(i); 
                    pi.push_back(p);
                    g.grid[i-1][num-26] = new_pixel; 
                }
            }
        }

        chk_line.reset(num);

    }

    for(int i = 0 ; i < 25 ; ++i)
        for(int j = 0 ; j < 25 ; ++j)
            if( g.grid[i][j] == '2' )
                return INCOMPLETED;

    return SOLVED;
}

int prob :: fix0(int i,int j)
{
    uint64_t val = ( line & ( 0x3LL << (i<<1) )) >> (i<<1);

    if(val==2)
        return 0;
    return fix(i-1,j);
}

int prob :: fix1(int i,int j)
{
    int dj = data[procLine][j];
    if( j>=1 && i>=dj+1 )
    {
        for(int c = i-dj+1 ; c<=i ; ++c)
        {
            uint64_t val = ( line & ( 0x3LL << (c<<1) )) >> (c<<1);
            if(val==1)
                return 0;
        }
        uint64_t val = ( line & ( 0x3LL << ((i-dj)<<1) )) >> ((i-dj)<<1);
        if(val==2)
            return 0;

        return fix(i-dj-1,j-1);
    }
    return 0;
}

int prob :: fix(int i,int j)
{
    if( fix_dp_arr[i][j] == -1 )
    {
        int ret = 0;
        if( i == 0 && j == 0 )
            ret = 1;
        else if( i == 0 && j >= 1 )
            ret = 0;
        else
            ret = ( fix1(i,j) | fix0(i,j) );
        fix_dp_arr[i][j] = ret;
        return ret;
    }
    return fix_dp_arr[i][j];
}

uint64_t prob :: paint1(int i,int j)
{
    int dj = i-data[procLine][j];
    uint64_t t=0;
    for( int n = dj+1 ; n <= i  ; ++n )
    {
        t |= (0x2LL << (n << 1));
    }

    t |= (0x1LL << (dj << 1));
    t |= paint( dj -1 , j-1);
    return t;
}

uint64_t prob :: paint0(int i,int j)
{
    uint64_t t = 0;

    t |= (0x1LL << (i << 1));
    t |= paint( i-1 , j );
    return t;
}

uint64_t prob :: paint_p(int i,int j)
{
    uint64_t t = 0;
    int f0 = fix0(i,j) , f1 = fix1(i,j);
    if( f0==1 && f1==0 )
        return paint0(i,j);
    if( f1==1 && f0==0 )
        return paint1(i,j);
    t |= paint0(i,j) | paint1(i,j);
    return t; 
}

uint64_t prob :: paint(int i,int j)
{
    uint64_t t = 0;
    if( paint_dp_arr[i][j] == noAns )
    {
        if( i != 0 )
            t = paint_p(i,j);
        paint_dp_arr[i][j] = t;
        return t;
    }
    return paint_dp_arr[i][j];
}

inline uint64_t prob :: paint_dp(int i , int j)
{

    if( (*finish_table[procLine]).find(line) != (*finish_table[procLine]).end() )
    {
        uint32_t val = (*finish_table[procLine])[line]; 
        uint64_t ret = 0;
        for( int i = 1 ; i <= 25 ; ++i )
        {
            if( (val&(0x1<<(i+1))) )
                ret |= 0x2LL<<((i+1)*2);
            else
                ret |= 0x1LL<<((i+1)*2);
        }
        //printf("%x\n%lx\n",val,ret);
        //fgetc(stdin);
        return ret;
    }
    
    if( (paint_table[procLine]).find(line) == (paint_table[procLine]).end() )
    {
        reservefix();
        reservepaint();
        
        if( 0 == fix(26,data[procLine][0]))
        {   // if we can't fix this line the answer is ~0
            (paint_table[procLine])[line] = noAns; 
        }
        else
        {  // now we got answer
            uint64_t result = paint(i,j) ; 

            bool test = false;
            uint64_t re = result;
            for( int i = 0 ; i < 30 ; ++i )
            {
                char n = re & 0x3LL ;
                if( n == 3 )
                    test = true;
                re >>= 2;
            }

            if( test == false )
            {
                uint32_t val = 0;
                for( int i = 1 ; i <= 25 ; ++i )
                {
                    uint32_t n = ( result     & ( 0x3LL << ((1+i)<<1) )) >> ((1+i)<<1);
                    if( n == 2 )
                    {
                        val |= 0x1 << (i+1); 
                    }
                    //cout << i << " " << n << " " << val << "\n";
                }
                //fgetc(stdin);
                (*finish_table[procLine])[line] = val;
            }
            else
                (paint_table[procLine])[line] = result;
            return result;
        }
    }

    return (paint_table[procLine])[line];
}

void prob :: preTable( map< string , map<uint64_t ,uint32_t> > &table )
{
    for( int j = 0 ; j < 50 ; ++j )
        finish_table[j] = &table[ desToHash(j) ];
}

void prob :: reservefix()
{
    for( int x = 0 ; x < 26+1 ; ++x )
        for( int y = 0 ; y < 14+1 ; ++y )
            fix_dp_arr[x][y] = -1;
}

void prob :: reservepaint()
{
    for( int x = 0 ; x < 26+1 ; ++x )
        for( int y = 0 ; y < 14+1 ; ++y )
            paint_dp_arr[x][y] = noAns; 
}
