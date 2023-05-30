# EPC_FW

### Instructions for STM32 Cube IDE

In order to run this code from the STM32 Cube IDE, the following steps must be followed:
- Clone the code and checkout to a firmware branch: `git checkout develop`
- Open STM32 Cube IDE and locate the workspace in the firmware folder: `<repo_path>/firmware`
- Import project from the existing workspace: 
>- File
>- Import
>- Existing Project into Workspace
>- Select root directory: `<repo_path>/firmware`
>- Finish
- Configure project source code path:
>- Project
>- Properties
>- C/C++ General
>- Path and Symbols
>- Source Location
>- Link folder
>- Check Link to folder in the file system
>- Select source code folder: `<repo_path>/firmware/Sources`
>- Apply and Close
- Build the project and ENJOY !!! :wink:

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