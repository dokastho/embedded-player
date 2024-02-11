#include <stdio.h>

#include "Player.h"
#include "Panel.h"
// #include "freertos/task.h"
#include "bt_app_core.h"

int
run_app(void)
{
    // display
    panel_display_text("Hello Grace!", 13);

    // bluetooth
    bt_app_task_start_up();
    char input[2];
    unsigned int addr_index;
    while (1)
    {
        fpurge(stdin);
        printf("Select device or 'r' to refresh > ");
        fgets(input, 2, stdin);
        printf("\n");

        if (input[0] == 'r')
        {
            bt_app_dev_ls();
        }
        addr_index = atoi(input);
        if (addr_index < DEVICE_LIST_LEN)
        {
            break;
        }
    }
    
    return 0;
}
