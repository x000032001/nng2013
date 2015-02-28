#include "FP2.h"

void FP2 :: init(int n,inputer& a)
{
    FP.init(n,a);
}


int FP2 :: fp2()
{
    max_pi_size = 0;
    int ret = FP.propagate();
    if( ret != INCOMPLETED )
    {
        return ret;
    }

    for( int i = 0 ; i < 25 ; ++i )
    {
        for( int j = 0 ; j < 25 ; ++j )
        {
            if( FP.g.grid[i][j] == '2' )
            {
                pixel tmp;
                tmp.x = i;
                tmp.y = j;
                tmp.val = 63;
                P.insert(tmp.get());
            }
        }
    }
   
    while( !P.empty() )
    {
        unsigned int p = *(P.begin());
        P.erase(P.begin());
        pixel _p;
        _p.set(p);
        _p.val = 0;

        int res = probe(p);
        if( res != INCOMPLETED )
            return res;
    }

    return INCOMPLETED;

}

inline int FP2 :: probe(int p)
{
    // probeG( p , 0 ) start
    G origin = FP.g;

    pixel _h;
    _h.set(p);
    _h.val = '0';
    map<unsigned int, set<unsigned int> >::iterator it = pclist.find(_h.get());
    if( it != pclist.end() )
    {
        pixel _h_p = _h;
        _h_p.flip();
        for(  set<unsigned int>::iterator b = it->second.begin() ; b != it->second.end() ; ++b )
        {
            int _data = *b;
            pixel __p;
            __p.set( _data);
            __p.flip();
            if( usepc ) pclist[ __p.get() ].insert( _h_p.get() );
        }

        for(  set<unsigned int>::iterator b = it->second.begin() ; b != it->second.end() ; ++b )
        {
            int _data = *b;
            pixel __p;
            __p.set( _data);
            FP.g.grid[__p.x][__p.y] = __p.val;
            FP.setline( __p.x , __p.y );
        }
    }
    // update G by pclist finish

    FP.g.grid[ _h.x ][ _h.y ] = '0';
    FP.setline( _h.x , _h.y );
    int p0 = FP.propagate();
    G g0g = FP.g;
    vector<pixel> g0r = FP.pi;
    int p0pi = g0r.size();

    _h.val = '1';
    if( p0 != CONFLICT && usepc )
        for( vector<pixel>::iterator it = FP.pi.begin() ; it != FP.pi.end() ; ++it )
        {
            it->flip();
            pclist[ it->get() ].insert( _h.get() );
            it->val=63;
            P.insert( it->get() );
        }

    // probeG( p , 0 ) finish 

    // probeG( p , 1 ) start
    FP.g = origin;


    it = pclist.find(_h.get());
    if( it != pclist.end() )
    {
        pixel _h_p = _h;
        _h_p.flip();
        for(  set<unsigned int>::iterator b = it->second.begin() ; b != it->second.end() ; ++b )
        {
            int _data = *b;
            pixel __p;
            __p.set( _data );
            __p.flip();
            if( usepc ) pclist[ __p.get() ].insert( _h_p.get() );
        }
        for(  set<unsigned int>::iterator b = it->second.begin() ; b != it->second.end() ; ++b )
        {
            int _data = *b;
            pixel __p;
            __p.set( _data);
            FP.g.grid[__p.x][__p.y] = __p.val;
            FP.setline( __p.x , __p.y );
        }
    }
    // update G by pclist finish

    
    FP.g.grid[ _h.x ][ _h.y ] = '1';
    FP.setline( _h.x , _h.y );
    int p1 = FP.propagate();
    G g1g = FP.g;
    vector<pixel> g1r = FP.pi;
    int p1pi = g1r.size();

    _h.val = '0';
    if( p1 != CONFLICT && usepc )
        for( vector<pixel>::iterator it = FP.pi.begin() ; it != FP.pi.end() ; ++it )
        {
            it->flip();
            pclist[ it->get() ].insert( _h.get() );
            it->val=63;
            P.insert( it->get() );
        }

    FP.g = origin;
    // probeG( p , 1 ) finish 
    

    /*
    double minp = p1pi > p0pi ? p0pi : p1pi;
    double logp0 = log( (double)p0pi+1.0 )+1.0;
    double tmp = minp + abs(logp0-logp1);
    */
    // mul method
    //cout << "check pi.size" << p1pi << " " << p0pi << endl;
    double tmp = (p1pi+1)*(p0pi+1);

    if( tmp > max_pi_size )
    {
        max_pi_size = tmp;
        max_x = _h.x;
        max_y = _h.y;
    }

    if( p0 == CONFLICT && p1 == CONFLICT )
    {
        //printf("CONF on both");
        return CONFLICT;
    }
    else if( p0 == CONFLICT )
    {
       _h.val = '1';
       g1r.push_back( _h );
       FP.g = g1g;
       //for( int i = 0 ; i < g1r.size() ; ++i )
       //         FP.g.grid[g1r[i].x][g1r[i].y] = g1r[i].val; 
    }

    else if( p1 == CONFLICT )
    {
       _h.val = '0';
       g0r.push_back( _h );
       FP.g = g0g;
       //for( int i = 0 ; i < g0r.size() ; ++i )
       //         FP.g.grid[g0r[i].x][g0r[i].y] = g0r[i].val; 
    }
    else
    {
        G comp;
        for( int i = 0 ; i<25 ; ++i )
            for( int j = 0 ; j<25 ; ++j )
                comp.grid[i][j] = 'Z';
        
    
        for( size_t i = 0 ; i < g0r.size() ; ++i )
            comp.grid[g0r[i].x][g0r[i].y] = g0r[i].val;
        
    
        for( size_t i = 0 ; i < g1r.size() ; ++i )
            if( comp.grid[g1r[i].x][g1r[i].y] == g1r[i].val )
                FP.g.grid[g1r[i].x][g1r[i].y] = g1r[i].val; 
    }
    return INCOMPLETED;
}

