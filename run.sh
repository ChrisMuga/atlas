gcc src/main.c $(pkg-config --libs --cflags raylib) -o target/atlas; ./target/atlas
