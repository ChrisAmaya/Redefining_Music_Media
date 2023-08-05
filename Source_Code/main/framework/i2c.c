/*
 * i2c.c
 *
 * Purpose: This code will be used to configure and create an API that uses I2C for the ESP32-S3
 * 
 *  Created on: Aug 1st, 2023
 *      Author: Addi Amaya
 */


#include "driver/i2c.h"

#define I2C_MASTER_NUM              I2C_NUM_0

// Config function for I2C0 with SDA and SCL being pulled up
esp_err_t i2c_config(int SDA, int SCL, int ClkSpeed){
    
    i2c_config_t config = {
    .mode = I2C_MODE_MASTER,
    .sda_io_num = SDA,
    .scl_io_num = SCL,
    .sda_pullup_en = GPIO_PULLUP_ENABLE,
    .scl_pullup_en = GPIO_PULLUP_ENABLE,
    .master.clk_speed = ClkSpeed,
    };
    
    if (i2c_param_config(I2C_NUM_0, &config)!=0){
        return ESP_FAIL;
    }
    
    if (i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0)!=0){
        return ESP_FAIL;
    }

    return ESP_OK;
}

// Function to write data to an I2C device
esp_err_t i2c_write_data(uint8_t device_address, uint8_t register_address, uint8_t *data, size_t data_len) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    esp_err_t ret;

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (device_address << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, register_address, true);
    i2c_master_write(cmd, data, data_len, true);
    i2c_master_stop(cmd);

    ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

// Function to read data from an I2C device
esp_err_t i2c_read_data(uint8_t device_address, uint8_t register_address, uint8_t *data, size_t data_len) {
    if (data_len == 0) {
        return ESP_FAIL;
    }

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    esp_err_t ret;

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (device_address << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, register_address, true);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (device_address << 1) | I2C_MASTER_READ, true);
    if (data_len > 1) {
        i2c_master_read(cmd, data, data_len - 1, I2C_MASTER_ACK);
    }
    i2c_master_read_byte(cmd, data + data_len - 1, I2C_MASTER_NACK);
    i2c_master_stop(cmd);

    ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}