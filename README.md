![Video Demo](demo.gif) \
Terminal used in the gif: [cool-retro-term](https://github.com/Swordfish90/cool-retro-term)

# Terminal Bird
A simple [Flappy Bird](https://en.wikipedia.org/wiki/Flappy_Bird) clone written in the [C language](https://en.wikipedia.org/wiki/C_(programming_language)) with [ncurses library](https://en.wikipedia.org/wiki/Ncurses) for [terminal-based graphics](https://en.wikipedia.org/wiki/Text-based_user_interface). 

Player's objective is to navigate the bird through columns of pipes without colliding to them as much as possible.
## Installation
### Windows
First, we have to install [WSL](https://learn.microsoft.com/en-us/windows/wsl/about). You can simply install WSL by following this [YouTube tutorial](https://www.youtube.com/watch?v=wjbbl0TTMeo&t=416s) 

After installation, we can now install the required packages, dependencies and build our code by writing these commands to the shell: 
```console
$ sudo apt install git build-essential libncurses5-dev libncursesw5-dev libsqlite3-dev libcjson-dev

$ git clone https://github.com/Ibrahimbag/Terminal-Bird.git

$ cd Terminal-Bird

$ make && sudo make install
```
### GNU/Linux
To build our code, you need `git`, `make`, standart C libraries, `ncurses-dev`, `libsqlite3-dev`, `libcjson-dev` and a compiler (such as `GCC`, `Clang` or etc) installed on your system.

To install all required packages to build on Debian/Ubuntu or their derivatives, first run this command:
```console
$ sudo apt install git build-essential libncurses5-dev libncursesw5-dev libsqlite3-dev libcjson-dev
```
You can follow this tutorial to install ncurses on other distros: https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/

After installing all the required packages, we can now clone and build our code:
```console
$ git clone https://github.com/Ibrahimbag/Terminal-Bird.git

$ cd Terminal-Bird

$ make && sudo make install
```

## How to play
To start the game, simply run the compiled binary:
```console
$ terminal-bird
```
Use Arrow keys to navigate menus,
<kbd>SPACE</kbd> key to fly, 
<kbd>Q</kbd> key to quit the game.

## Uninstall
Make sure you cd to the Terminal-Bird folder and run the following command to the terminal:
```console
$ make clean && sudo make uninstall
```

## Configuring your game
Although most people are probably fine with the default configurations, \
You can configure some things in Terminal Bird, such as game speed, colors, \
display, keybinds, etc.

Unfortunately, for now I didn't implement the TUI menu for configuring the game; \
However, you can configure it by editing the configuration file like how written in the \
description at the uncompleted options menu.

Here down below are the ways how you can configure the game 
1. Edit the configuration file located at ~/.Terminal-Bird/configurations.json \
        ```
        $ [YOUR_TEXT_EDITOR] ~/.Terminal-Bird/configurations.json
        ```
        \
        and change the values like how you want
        \
        IMPORTANT NOTE: When you build the game again, configurations gets overwritten

2. Edit the configuration file from the cloned repo and build it again \
        cd into the cloned repo and then run this command: \
        ```
        $ [YOUR_TEXT_EDITOR] configurations.json
        ```
        \
        and change the values like how you want
        \
        then, clean and build the game again:

        $ make clean && make

## Troubleshooting

### Can't open database: unable to open database file
Building the code in root causes this issue.
To fix this, first uninstall the game:
```console
$ make clean && sudo make uninstall
```

and then build it again like this:

```console
$ make && sudo make install
```

### Terminal is tearing a lot while playing the game
I don't know the explanation for this; However, this happens to me in some terminals such as Windows 11 default command line, xterm, uxterm and etc. \
If you are experiencing the same issue, then consider changing your terminal.

### Terminal shows replacement character "�" in the game
If your terminal doesn't support some characters displayed on the game,\
it will show the replacement characters "�" instead.

I didn't implemented configurations for characters used for bird and pipe yet.
So, there are two solutions you can apply:

1. Change your terminal
2. Edit the src/visuals.c file, replace or remove the characters not supported in your terminal and build the code again
