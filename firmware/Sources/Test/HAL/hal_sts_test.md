# EPC_FW TEST STS30-DIS WITH I2C

### Previus actions in HW enviroment for I2C

In order to be able to test the HAL STS is mandatory to connect the SDA and SCL pins to the temperature sensor.

### Previus actions in SW enviroment for I2C

This test is automatically done. The test will make 1 read per second during 5 seconds. 
If any of the reads is incorrect the test will failed and get an error result.
