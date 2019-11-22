CC =  gcc
CFLAGS =  -Og -Wall
MAIN =  main.o
OBJECTS =  metaws.o
EXE = i3metaws
LIBS =

INSTALL_DIR = /usr/local

$(EXE): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

run: $(EXE)
	./$(EXE) ${ARGS}

install: $(EXE)
	mkdir -p $(INSTALL_DIR)/bin
	cp -f $(EXE) $(INSTALL_DIR)/bin
	chmod 775 $(INSTALL_DIR)/bin/$(EXE)

uninstall:
	rm -f $(INSTALL_DIR)/bin/$(EXE)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	-@rm -f $(EXE) *.o 2>/dev/null || true

