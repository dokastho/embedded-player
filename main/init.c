// call init hooks for components

#include "Player.h"
#include "Panel.h"

int
init_playercontext(void)
{
    if (init_panel() != 0)
    {
        return -1;
    }
    return 0;
}