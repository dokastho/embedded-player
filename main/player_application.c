#include <stdio.h>

#include "Player.h"
#include "Panel.h"

int
run_app(void)
{
    printf("working...\n");
    panel_display_text("Hello Grace!", 13);
    return 0;
}
