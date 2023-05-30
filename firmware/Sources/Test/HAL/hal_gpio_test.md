# EPC_FW TEST GPIOS

### Previus actions in HW enviroment for GPIO Test

In order to be able to test the HAL GPIO is mandatory to connect the 2 pins desired to test.
So the output pin will be conected to a input pin.

In this project the available output pins are in a enum like this:

    HAL_GPIO_OUT_OutDisable = 0,   /**<   DRMOS- OUT Disable - PA9  **/
    HAL_GPIO_OUT_Led0,             /**<   STATUS LED 0 GPIO  - PC4  **/
    HAL_GPIO_OUT_Led1,             /**<   STATUS LED 1 GPIO  - PC5  **/
    HAL_GPIO_OUT_Led2,             /**<   STATUS LED 2 GPIO  - PB0  **/
    HAL_GPIO_OUT_Led3,             /**<   STATUS LED 3 GPIO  - PB1  **/

So are the available input pins:

    HAL_GPIO_IN_ThermalWarn,  /**<  DRMOS - Thermal Warn - PA10 **/
    HAL_GPIO_IN_Status3v3,    /**<  DC/DC 3v3 Status     - PB14 **/
    HAL_GPIO_IN_Status5v0,    /**<  DC/DC 5v0 Status     - PB15 **/

### Previus actions in SW enviroment for GPIO Test

In order to be able to test the HAL GPIO is mandatory to write the output and input pins in the HAL_GPIO_Test function.
The two options to write the pins are writting the name of the pin or the position of the enum, 
internally it will understand which pin is asociated.