# Enabling Windows for Linux commands in windows
## setup
1. create folder for linux executable symlinks
2. download into folder binary wsl-call.exe from releases
3. run `wsl-call.exe -all` to generate executables which match commands in linux PATH
4. add folder to windows environment PATH

## enable particular command
If you want to use Linux shell commands like 'npm', the alias could be created by

    wsl-call.exe ~/n/bin/node
    wsl-call.exe ~/n/bin/npm

or
    wsl-call.exe /usr/bin/node
    wsl-call.exe /usr/bin/npm

without full path the linux PATH is used for command invoking

    wsl-call.exe ifconfig

The linux full path is preserved in `COMMAND.wslpath` next to command executable `COMMAND.exe`
