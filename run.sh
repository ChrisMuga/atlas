gcc src/main.c raygui.so $(pkg-config --libs --cflags raylib) -o target/atlas; ./target/atlas
