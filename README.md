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

- ~~Get date and render~~
- ~~Focus on input on app open~~
- ~~Write to file~~
- ~~Persist file entries~~
- ~~Add or create TODO items~~
- ~~Store TODO items~~ 
- ~~DRY task item element creation in loop~~
- Add bullet as a prefix
- Consolidate temp file depending on operating system i.e Linux vs Mac
- List file entries on the ui
- Dynamic measurements
