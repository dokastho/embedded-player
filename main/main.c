#include "Player.h"

void app_main(void)
{
    if (init_playercontext() != 0)
    {
        cleanup_playercontext_crash();
        return;
    }
    run_app();
    cleanup_playercontext();
}
