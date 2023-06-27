# EPC_FW TEST MID PWR

## Important to know

This test will try to make a control of the current to the default value of 1000mA,
in order to change the value of the reference, it has to be written the I_ref variable as live expression.
Afterwards, it can be change while running the program.

### Previus actions in HW enviroment for MID DABS

In order to be able to test the MID PWR the test board will be needed as well as a source and a battery.
Verify the parameters of the EPC_CONF are correct, as the test board only support currents +-11A.
