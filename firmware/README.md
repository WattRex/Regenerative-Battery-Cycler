EPC_FW
Instructions for STM32 Cube IDE

In order to run this code from the STM32 Cube IDE, the following steps must be followed:

    Clone the code and checkout to a firmware branch: git checkout develop

    In the first deployment, or when project configuration is required:
        Copy all the content in <repo_path>/firmware/project_config to <repo_path>/firmware/STM32

    Open STM32 Cube IDE and locate the workspace in the firmware folder: <repo_path>/firmware

    Import project from the existing workspace:

        File
        Import
        Existing Project into Workspace
        Select root directory: <repo_path>/firmware
        Select "STM32" project ONLY
        Finish

    Configure project source code path:

        Project
        Properties
        C/C++ General
        Path and Symbols
        Source Location
        Add Folder
        Select "Sources" folder

        Apply and Close

    [OPTIONAL] If you want to update project configuration parameters you can also copy the folder <repo_path>/firmware/project_config/EPC_CONF to <repo_path>/firmware/Sources folder.

    Build the project and ENJOY !!! 😉
