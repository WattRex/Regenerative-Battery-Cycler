# EPC_FW TEST I2C

### Previus actions in HW enviroment for GPIO I2C

In order to be able to test the HAL I2C is mandatory to connect the SDA and SCL pins to the temperature sensor.

### Previus actions in SW enviroment for GPIO I2C

This test is automatically done. The test will make 1 read per second during 5 seconds. 
If any of the reads is incorrect the test will failed and get an error result.
