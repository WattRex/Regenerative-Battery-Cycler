# EPC_FW TEST MID DABS

## Important to know

This test is only to try the led status not the measurements.
This test is automatically done. The test will make 1 read per second during 5 seconds. 
If any of the reads is incorrect the test will failed and get an error result.

### Previus actions in HW enviroment for MID DABS

In order to be able to test the MID DABS MEAS is mandatory to connect the SDA and SCL pins to the temperature sensor.
While in order to test the leds status is neccesary to connect 4 leds to the respective GPIOs as following:
-Led0 -> PC4
-Led1 -> PC5
-Led2 -> PB0
-Led3 -> PB1
