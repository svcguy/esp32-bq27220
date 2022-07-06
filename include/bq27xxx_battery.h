/**
 * @file	bq27xxx_battery.h
 * @author	svcguy
 * @brief	An ESP-IDF port of TI's bq2xxx Linux driver
 * @version	0.1
 * @date	2022-07-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _BQ27XXX_BATTERY_H
#define _BQ27XXX_BATTERY_H

#include <stdint.h>
#include <stdbool.h>

#include "esp_err.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

typedef struct
{
	uint16_t	time_to_empty_min;
	uint16_t	time_to_full_min;
	uint16_t 	temperature_K;
	uint16_t 	voltage_mV;
	int16_t 	current_mA;
	uint16_t	full_capacity_mAh;
	int16_t		average_power_mWh;
	uint16_t	soc_percent;
	uint16_t	status;
}
bq27xxx_data_t;

typedef struct
{
	esp_err_t (*read)(bq27xxx_device_info_t *di, uint8_t reg, bool single);
	esp_err_t (*write)(bq27xxx_device_info_t *di, uint8_t reg, int16_t value, bool single);
	esp_err_t (*read_bulk)(bq27xxx_device_info_t *di, uint8_t reg, uint8_t *data, size_t len);
	esp_err_t (*write_bulk)(bq27xxx_device_info_t *di, uint8_t reg, uint8_t *data, size_t len);
	bool using_mutex;
	SemaphoreHandle_t *i2c_mutex;
}
bq27xxx_bus_t;

typedef struct
{
	bq27xxx_data_t	data;
	bq27xxx_bus_t	bus;
	TaskHandle_t	bq27xxx_task;
	uint16_t		design_capacity_mAh;
	uint16_t		op_status;
}
bq27xxx_device_info_t;

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

esp_err_t bq27xxx_init(bq27xxx_device_info_t *di);
esp_err_t bq27xxx_start_polling(bq27xxx_device_info_t *di);
esp_err_t bq27xxx_stop_polling(bq27xxx_device_info_t *di);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BQ27XXX_BATTERY_H */
