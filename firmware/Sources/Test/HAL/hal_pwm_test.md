# EPC_FW TEST PWM

### Previus actions in HW enviroment for PWM Test

In order to see the output of the PWM is neccesary to connect the 
osciloscope to the output pin of the PWM (in the case of the NUCLEO F334R8 is the PA8).

### Software actions for PWM Test

This test is automatically done, it will start the pwm with a duty after 5 seconds it will stop for another 2.5 seconds.
After the stop the duty will be change to 75% and 25% for 2.5s each then it wil be disable and the test finished.