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
