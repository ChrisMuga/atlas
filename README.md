# ATLAS

A TODOs app built in C

# Built with

- C
- Raylib

## How to run

- Run the shell script

```sh
# Building in Mac
. ./build-mac

# Running the build in Mac
. ./run-mac

# TODO: building and running in Linux
. ./run.sh
```

## Creating the raygui.dynlib for Mac

```sh
gcc -o raygui.dynlib src/includes/raygui.c -shared -fpic -DRAYGUI_IMPLEMENTATION -framework OpenGL -lm -lpthread -ldl libraylib.a -framework IOKit -framework Cocoa -framework OpenGL
```

## TODOs

- Add or create TODO items 
- Store TODO items 
