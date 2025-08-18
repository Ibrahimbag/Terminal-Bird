# Terminal Bird 🐦

![Video Demo](demo.gif) \
Terminal used in the gif: [cool-retro-term](https://github.com/Swordfish90/cool-retro-term)

A simple [Flappy Bird](https://en.wikipedia.org/wiki/Flappy_Bird) clone written in the [C language](https://en.wikipedia.org/wiki/C_(programming_language)) with [ncurses library](https://en.wikipedia.org/wiki/Ncurses) for [terminal-based graphics](https://en.wikipedia.org/wiki/Text-based_user_interface).

Player's objective is to navigate the bird through columns of pipes (not to be confused with [UNIX pipes](https://en.wikipedia.org/wiki/Pipeline_(Unix))) without colliding to them as much as possible.

## Installation ⬇️

### Windows 🪟

First, we have to install [WSL](https://learn.microsoft.com/en-us/windows/wsl/about). You can simply install WSL by following this [YouTube tutorial](https://www.youtube.com/watch?v=wjbbl0TTMeo&t=416s)

After installation, we can now install the required packages, dependencies and build our code by writing these commands to the shell:

```console
sudo apt install git build-essential libncurses5-dev libncursesw5-dev libsqlite3-dev libcjson-dev

git clone https://github.com/Ibrahimbag/Terminal-Bird.git

cd Terminal-Bird

make && sudo make install
```

### GNU/Linux 🐧

To build our code, you need [`git`](https://git-scm.com/), [`make`](https://www.gnu.org/software/make/), [C standart library](https://en.wikipedia.org/wiki/C_standard_library), [`ncurses`](https://invisible-island.net/ncurses/), [`sqlite3`](https://www.sqlite.org/), [`cjson`](https://github.com/DaveGamble/cJSON) and a compiler (such as [`GCC`](https://gcc.gnu.org/), [`Clang`](https://clang.llvm.org/) or etc) installed on your system.

#### Debian/Ubuntu or their derivatives

```console
sudo apt install git build-essential libncurses5-dev libncursesw5-dev libsqlite3-dev libcjson-dev libsdl2-dev libsdl2-mixer-dev
```

#### Arch Linux or their derivatives

install SDL2 from either <https://aur.archlinux.org/packages/sdl2> or sdl12-compat

```console
sudo pacman -S sdl12-compat
```

and then

```console
sudo pacman -S git base-devel ncurses sqlite cjson sdl2_mixer
```

#### Building the code

After installing all the required packages, we can now clone and build our code:

```console
git clone https://github.com/Ibrahimbag/Terminal-Bird.git

cd Terminal-Bird

make && sudo make install
```

## How to play 🎮

To start the game, simply run the compiled binary:

```console
terminal-bird
```

Use Arrow keys to navigate menus,
<kbd>SPACE</kbd> key to fly,
<kbd>Q</kbd> key to quit the game.

## Uninstall 🗑️

Make sure you cd to the Terminal-Bird folder and run the following command to the terminal:

```console
make clean && sudo make uninstall
```

## Configuring your game ⚙️

Although most people are probably fine with the default configurations, \
You can configure some things in Terminal Bird, such as game speed, colors, \
display, keybinds, etc.

Unfortunately, for now I didn't implement the TUI menu for configuring the game; \
However, you can configure it by editing the configuration file like how written in the \
description at the uncompleted options menu.

Here down below are the ways how you can configure the game:

### Edit the configuration file located at ~/.Terminal-Bird/configurations.json

> [!WARNING]
> When you build the game code again, configurations gets overwritten

```console
[YOUR_TEXT_EDITOR] ~/.Terminal-Bird/configurations.json
```

And change the values like how you want

### Edit the configuration file from the cloned repo and build it again

cd into the cloned repo and then run this command:

``` console
[YOUR_TEXT_EDITOR] configurations.json
```

and change the values like how you want \
then, clean and build the game again:

``` console
make clean && make
```

## Troubleshooting 🔧

### Can't open database: unable to open database file

Building the code in root causes this issue.
To fix this, first uninstall the game:

```console
make clean && sudo make uninstall
```

and then build it again like this:

```console
make && sudo make install
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

## Sounds

Sounds are taken from here: <https://www.101soundboards.com/boards/10178-flappy-bird-sounds>
