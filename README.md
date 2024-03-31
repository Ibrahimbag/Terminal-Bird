# Flappy Bird in C
A simple [Flappy Bird](https://en.wikipedia.org/wiki/Flappy_Bird) clone written in the [C language](https://en.wikipedia.org/wiki/C_(programming_language)) with [ncurses library](https://en.wikipedia.org/wiki/Ncurses) for terminal-based graphics. 

Player's objective is to navigate the bird through columns of pipes without colliding to them as much as possible.
## Installation
### Windows
First, we have to install WSL. You can simply install WSL by following this YouTube tutorial: https://www.youtube.com/watch?v=wjbbl0TTMeo&t=416s 

After installation, we can now install the required packages and dependencies to build our code by writing these commands to the shell: 
```bash
$ sudo apt install git make clang libncurses5-dev libncursesw5-dev

$ git clone https://github.com/Ibrahimbag/Flappy-Bird-In-C.git

$ cd Flappy-Bird-In-C

$ make
```
### GNU/Linux
To build our code, you need `git` `make` `clang` and `ncurses-dev` installed on your system.

You can follow this tutorial to install ncurses: https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/

After installing all the required packages, we can now clone and build our code:
```bash
$ git clone https://github.com/Ibrahimbag/Flappy-Bird-In-C.git

$ cd Flappy-Bird-In-C

$ make
```

## How to play
To start the game, simply run the compiled binary:
```bash
$ ./flappybird
```

Use **SPACE** key to fly, **Q** key to quit the game.

Use the command down below to display debug panel while playing:
```bash
$ ./flappybird debug
```
