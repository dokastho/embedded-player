// OLED Panel methods

#include <stdio.h>
#include "ssd1306.h"
#include "font8x8_basic.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "Panel.h"

SSD1306_t panel;

int
init_panel(void)
{
    spi_master_init(&panel, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO);
    ssd1306_init(&panel, 128, 64);
    
    ssd1306_clear_screen(&panel, false);
	ssd1306_contrast(&panel, 0xff);
	ssd1306_display_text_x3(&panel, 0, "BOOT", 5, false);
    
	vTaskDelay(1000 / portTICK_PERIOD_MS);
    ssd1306_clear_screen(&panel, false);
    return ESP_OK;
}

void
panel_clear()
{
    ssd1306_clear_screen(&panel, false);
}

void
panel_display_text(char* text, unsigned length)
{
    ssd1306_display_text(&panel, 0, text, length, false);
}

void
panel_display_text_horizontal_scroll(char* text, unsigned length)
{
    ssd1306_display_text(&panel, 0, text, length, false);
    ssd1306_hardware_scroll(&panel, SCROLL_RIGHT);
}