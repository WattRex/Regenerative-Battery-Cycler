# EPC_FW TEST CAN

### Previus actions in HW enviroment for CAN Test

In order to be able to test the HAL CAN is mandatory to connect the transciever and the PCanViewer.
You should be aware of the PCanViewer app configuration as it must be the same as the one in the device.
Once the message has been received in the PCanViewer you have 5 seconds to send manually a message and receive back a new message.

### Previus actions in SW enviroment to use CAN

By default, the CAN protocol accepts all the messages received, 
in order to use the filters the function HAL_CanFilters should be called after the initialization of the module.

For the test is not necesary to aply the filter as it will do it internally 
To receive correctly a message in the test the message must have a StdId between 0x130 and 0x13F.