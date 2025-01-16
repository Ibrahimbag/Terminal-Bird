# Terminal Bird
A simple [Flappy Bird](https://en.wikipedia.org/wiki/Flappy_Bird) clone written in the [C language](https://en.wikipedia.org/wiki/C_(programming_language)) with [ncurses library](https://en.wikipedia.org/wiki/Ncurses) for terminal-based graphics. 

Player's objective is to navigate the bird through columns of pipes without colliding to them as much as possible.
## Installation
### Windows
First, we have to install WSL. You can simply install WSL by following this YouTube tutorial: https://www.youtube.com/watch?v=wjbbl0TTMeo&t=416s 

After installation, we can now install the required packages, dependencies and build our code by writing these commands to the shell: 
```console
$ sudo apt install git make gcc libncurses5-dev libncursesw5-dev

$ git clone https://github.com/Ibrahimbag/Terminal-Bird.git

$ cd Terminal-Bird

$ make && sudo make install
```
### GNU/Linux
To build our code, you need `git` `make` `ncurses-dev` and a compiler (such as `GCC`, `Clang` or etc) installed on your system.

To install all required packages to build on Debian/Ubuntu or their derivatives, first run this command:
```console
$ sudo apt install git make gcc libncurses5-dev libncursesw5-dev
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
Use <kbd>SPACE</kbd> key to fly, <kbd>Q</kbd> key to quit the game.

## Uninstall
Make sure you cd to the Terminal-Bird folder and run the following command to the terminal:
```console
$ make clean && sudo make uninstall
```
