#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "Player.h"
#include "Panel.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "nvs_flash.h"
#include "audio_element.h"
#include "audio_pipeline.h"
#include "audio_event_iface.h"
#include "audio_common.h"
#include "esp_peripherals.h"
#include "bluetooth_service.h"
#include "mp3_decoder.h"

#include "audio_idf_version.h"
#include "esp_netif.h"


int run_app(void)
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
#if (ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 1, 0))
    ESP_ERROR_CHECK(esp_netif_init());
#else
    tcpip_adapter_init();
#endif

    esp_log_level_set("*", ESP_LOG_INFO);
    audio_pipeline_handle_t pipeline;
    audio_element_handle_t fatfs_stream_reader, mp3_decoder, bt_stream_writer;

    // display
    panel_display_text("Hello Grace!", 13);

    // bluetooth
    bluetooth_service_cfg_t bt_cfg = {
        .device_name = "ESP-ADF-SOURCE",
        .mode = BLUETOOTH_A2DP_SOURCE,
        .remote_name = CONFIG_BT_REMOTE_NAME,
    };
    if (bluetooth_service_start(&bt_cfg) != ESP_OK)
    {
        return -1;
    }
    bt_stream_writer = bluetooth_service_create_stream();

    mp3_decoder_cfg_t mp3_cfg = DEFAULT_MP3_DECODER_CONFIG();
    mp3_decoder = mp3_decoder_init(&mp3_cfg);

    audio_pipeline_cfg_t pipeline_cfg = DEFAULT_AUDIO_PIPELINE_CONFIG();
    pipeline = audio_pipeline_init(&pipeline_cfg);

    audio_pipeline_register(pipeline, mp3_decoder,        "mp3");
    audio_pipeline_register(pipeline, bt_stream_writer,   "bt");

    const char *link_tag[3] = {"mp3", "bt"};
    audio_pipeline_link(pipeline, &link_tag[0], 3);

    bt_stream_writer = bluetooth_service_create_stream();
    
    return 0;
}
