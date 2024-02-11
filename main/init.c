// call init hooks for components

#include "Player.h"
#include "Panel.h"

int
init_playercontext(void)
{
    init_panel();
    return 0;
}