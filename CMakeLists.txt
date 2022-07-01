idf_component_register(SRCS "bq27xxx_battery.c" "bq27xxx_battery_i2c.c" "bq27xxx_battery_hdq.c"
                       INCLUDE_DIRS "include"
                       REQUIRES freertos i2c)