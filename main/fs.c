#include "fs.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"
#include "esp_vfs_fat.h"
#include "esp_log.h"

int init_fs()
{
    printf("starting fs...\n");

    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = GPIO_NUM_5;
    
    sdspi_dev_handle_t handle;
    if (sdspi_host_init_device(&slot_config, &handle) != ESP_OK)
    {
        printf("error sdspi host init\n");
        return -1;
    }
    
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    esp_vfs_fat_mount_config_t mount_config = VFS_FAT_MOUNT_DEFAULT_CONFIG();
    // fs_conf.format_if_mount_failed = true;
    sdmmc_card_t* card;

    host.slot = handle;
    // config.max_freq_khz = SDMMC_FREQ_PROBING;
    host.max_freq_khz = SDMMC_FREQ_DEFAULT;
    // config.max_freq_khz = SDMMC_FREQ_HIGHSPEED;

    if (esp_vfs_fat_sdspi_mount("/sdcard", &host, &slot_config, &mount_config, &card) != ESP_OK)
    {
        printf("error sd card fs mount\n");
        return -1;
    }

    printf("fs init OK\n");
    return ESP_OK;
}