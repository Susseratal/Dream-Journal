GTK_LIBS:=$(shell pkg-config --cflags --libs gtk+-3.0)

journal.exe: $(wildcard src/*.c src/*.h)
	@gcc src/*.c ${GTK_LIBS} -l sqlite3 -o $@

verbose:
	@echo "Building..."
	gcc src/*.c ${GTK_LIBS} -l sqlite3 -o $@
	@ls

clean:
	@echo "Removing journal.exe"
	@rm journal.exe
	@ls
