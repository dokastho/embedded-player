#include "fs.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_types.h"

int init_fs()
{
    printf("starting fs...\n");

    sdspi_device_config_t dev_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    dev_config.gpio_cs = GPIO_NUM_15;
    dev_config.gpio_wp = -1;
    dev_config.gpio_cd = -1;
    dev_config.gpio_int = -1;
    sdspi_dev_handle_t handle;
    if (sdspi_host_init_device(&dev_config, &handle) != ESP_OK)
    {
        printf("error sdspi host init\n");
        return -1;
    }
    
    sdmmc_host_t config = SDSPI_HOST_DEFAULT();
    sdmmc_card_t card;
    config.slot = handle;
    if (sdmmc_card_init(&config, &card) != ESP_OK)
    {
        printf("error sdmmc card init\n");
        return -1;
    }

    printf("fs init OK\n");
    return ESP_OK;
}