# Flappy Bird in C
A simple Flappy Bird clone made by using the C language.

# Compiling and executing the code
First off, we have to install the ncurses library.

Debian/Ubuntu or their derivatives
```console
$ sudo apt install libncurses5-dev
```

Fedora or their derivatives
```console
$ sudo dnf install ncurses-devel
```

After installing the ncurses library, we can now compile our code.

```console
$ gcc flap.c -o flap -lncurses
or 
$ clang flap.c -o flap -lncurses
```

then run it 
```console
$ ./flap
```
