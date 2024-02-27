# Flappy Bird in C
A simple Flappy Bird clone written in the C language and ncurses library for terminal-based graphics. 

Player's objective is to navigate the bird through columns of pipes without colliding to them as much as possible.
## Installation
First off, we have to install the ncurses library.

Debian/Ubuntu or their derivatives:
```bash
$ sudo apt install libncurses5-dev
```

RHEL or their derivatives:
```bash
$ sudo yum install ncurses-devel
```

Fedora or their derivatives:
```bash
$ sudo dnf install ncurses-devel
```

After installing the ncurses library, we can now compile our code.

```bash
$ gcc flappybird.c -o flappybird -lncurses
# or you can also use the clang compiler 
$ clang flappybird.c -o flappybird -lncurses
```

## How to play
To start the game, simply run the compiled binary.
```bash
$ ./flappybird
```

Use **SPACE** key to fly, **Q** key to quit the game.

Use the command down below to display debug panel while playing:
```bash
$ ./flappybird debug
```
