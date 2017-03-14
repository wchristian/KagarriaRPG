#include "sources.h"

int main()
{
    initscr();
    signal( SIGWINCH, NULL );
    displayStats( getPC() );
    endwin();
    exit( 0 );
}
