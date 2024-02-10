#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "Player.h"

void
cleanup_playercontext(void)
{
    unsigned timeout = 10;
    printf("Restarting in %d seconds...\n", timeout);
    vTaskDelay((1000 * timeout) / portTICK_PERIOD_MS);
    fflush(stdout);
    esp_restart();
}