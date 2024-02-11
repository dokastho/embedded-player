#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#include "Player.h"
#include "Panel.h"
#include "bt_app_core.h"

void getLineInput(char buf[], size_t len)
{
    memset(buf, 0, len);
    fpurge(stdin); // clears any junk in stdin
    char *bufp;
    bufp = buf;
    while (true)
    {
        vTaskDelay(100 / portTICK_PERIOD_MS);
        *bufp = getchar();
        if (*bufp != '\0' && *bufp != 0xFF && *bufp != '\r') // ignores null input, 0xFF, CR in CRLF
        {
            //'enter' (EOL) handler
            if (*bufp == '\n')
            {
                *bufp = '\0';
                break;
            } // backspace handler
            else if (*bufp == '\b')
            {
                if (bufp - buf >= 1)
                    bufp--;
            }
            else
            {
                // pointer to next character
                bufp++;
            }
        }

        // only accept len-1 characters, (len) character being null terminator.
        if (bufp - buf > (len)-2)
        {
            bufp = buf + (len - 1);
            *bufp = '\0';
            break;
        }
    }
}

int run_app(void)
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
        fflush(stdout);
        getLineInput(input, 2);
        printf("%s\n", input);

        if (input[0] == 'r')
        {
            bt_app_dev_ls();
            continue;
        }
        addr_index = atoi(input);
        if (addr_index < DEVICE_LIST_LEN)
        {
            break;
        }
    }

    bt_app_sel_target(addr_index);

    return 0;
}
