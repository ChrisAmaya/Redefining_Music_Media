#include <stdio.h>
#include "framework/i2c.h"


#define TSL2591_ADDR        0x29 // Address of the TSL2591 sensor


void app_main() {
    // Initialize I2C with your desired SDA, SCL, and clock speed
    int SDA_PIN = 5;
    int SCL_PIN = 4;
    int CLOCK_SPEED = 400;
    esp_err_t i2c_config_result = i2c_config(SDA_PIN, SCL_PIN, CLOCK_SPEED);
    if (i2c_config_result != ESP_OK) {
        printf("I2C configuration failed\n");
        return;
    }

    while (1) {
        // Example data to write to the sensor (you may need to refer to the TSL2591 datasheet for specific commands)
        uint8_t write_data[2] = {0x80, 0x01}; // Example: Writing 0x01 to register 0x80

        // Write data to the TSL2591 sensor
        esp_err_t write_result = i2c_write_data(TSL2591_ADDR, 0x00, write_data, sizeof(write_data));
        if (write_result != ESP_OK) {
            printf("I2C write failed\n");
            return;
        }

        // Read data from the TSL2591 sensor
        uint8_t read_data[2] = {0};
        esp_err_t read_result = i2c_read_data(TSL2591_ADDR, 0x80, read_data, sizeof(read_data));
        if (read_result != ESP_OK) {
            printf("I2C read failed\n");
            return;
        }

        // Process the data if needed (convert it to the appropriate format)
        uint16_t full = (read_data[0] << 8) | read_data[1];

        // Print the data to the terminal
        printf("Full spectrum: %d\n", full);

        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1000ms before reading again
    }
}





