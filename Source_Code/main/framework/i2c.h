/*
 * i2c.h
 *
 *  Created on: Aug 1st, 2023
 *      Author: Addi Amaya
 */

#ifndef FRAMEWORK_I2C_H_
#define FRAMEWORK_I2C_H_

#include <stdint.h>
#include "esp_err.h"

esp_err_t i2c_config(int SDA, int SCL, int ClkSpeed);
esp_err_t i2c_write_data(uint8_t device_address, uint8_t register_address, uint8_t *data, size_t data_len);
esp_err_t i2c_read_data(uint8_t device_address, uint8_t register_address, uint8_t *data, size_t data_len);

#endif /* FRAMEWORK_I2C_H_ */
