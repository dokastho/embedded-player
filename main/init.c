// call init hooks for components

#include "Player.h"
#include "Panel.h"
#include "fs.h"

int
init_playercontext(void)
{
    init_panel();
    if (init_fs() != 0)
    {
        return -1;
    }
    return 0;
}