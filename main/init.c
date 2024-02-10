// call init hooks for components

#include "Player.h"
#include "Panel.h"
#include "esp_lcd_panel_ssd1306.h"

int
init_playercontext(void)
{
    init_panel();
}