# Enabling Windows for Linux commands in windows
## setup
1. create folder for linux executable symlinks
2. download into folder binary wsl-call.exe from [releases](releases/)
    default binary is 64 bit, if you want to use 32 bit one `wsl-call32.exe` should be renamed into `wsl-call.exe` before use.
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

# Note for node users 
`n` node manager allows to switch between node/npm versions. But it would keep separate copies for root and main user.

    C:\Users\suns\bin>n 8.17.0

By default `npm` is not available from wsl. To find where npm is used from:

    C:\Users\suns>which npm
    /usr/local/bin/npm

Then from directory listed in PATH apply following aliasing:

    C:\Users\suns\bin>wsl-call.exe /usr/local/bin/npm

Happy coding!