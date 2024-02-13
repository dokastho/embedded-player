#include "fs.h"
#include "driver/sdspi_host.h"
#include "sdmmc_cmd.h"
#include "esp_vfs_fat.h"
#include "esp_log.h"

int init_fs()
{
    printf("starting fs...\n");
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = GPIO_NUM_5;
    slot_config.host_id = host.slot;

    spi_bus_config_t bus_cfg = {
        .mosi_io_num = GPIO_NUM_23,
        .miso_io_num = GPIO_NUM_19,
        .sclk_io_num = GPIO_NUM_18,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };
    if (spi_bus_initialize(host.slot, &bus_cfg, SDSPI_DEFAULT_DMA) != ESP_OK) {
        printf("error spi bus init\n");
        return -1;
    }
    esp_vfs_fat_mount_config_t mount_config = VFS_FAT_MOUNT_DEFAULT_CONFIG();
    sdmmc_card_t* card;

    host.max_freq_khz = SDMMC_FREQ_DEFAULT;

    if (esp_vfs_fat_sdspi_mount("/sdcard", &host, &slot_config, &mount_config, &card) != ESP_OK)
    {
        printf("error sd card fs mount\n");
        return -1;
    }

    printf("fs init OK\n");
    return ESP_OK;
}