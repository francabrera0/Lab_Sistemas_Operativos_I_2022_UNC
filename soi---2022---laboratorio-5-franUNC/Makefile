CFLAGS = -Wall -Werror -pedantic -g
include = ./include
src = ./src
bin = ./bin
out = ./out
lib = ./lib

$(bin)/main: $(out)/main.o $(lib)/libcommandline.a $(lib)/libcommands.a
	mkdir -p $(bin)/
	gcc $(CFLAGS) -o $@ $(out)/main.o -L$(lib)/ -lcommandline -lcommands

#_______________________________MAIN.o___________________________________________#
$(out)/main.o: $(src)/main.c $(include)/commandline.h $(include)/executecommands.h
	mkdir -p $(out)/
	gcc $(CFLAGS) -o $@ -c $(src)/main.c


#________________________________Library for command line_______________________#
$(lib)/libcommandline.a: $(out)/commandline.o $(out)/executecommands.o $(out)/externprogram.o $(out)/pipe.o $(out)/ioredirection.o
	mkdir -p $(lib)/
	ar -rc $@ $^

$(out)/commandline.o: $(src)/commandline.c
	gcc $(CFLAGS) -o $@ -c $^

$(out)/executecommands.o: $(src)/executecommands.c
	gcc $(CFLAGS) -o $@ -c $^

$(out)/externprogram.o: $(src)/externprogram.c
	gcc $(CFLAGS) -o $@ -c $^

$(out)/pipe.o: $(src)/pipe.c
	gcc $(CFLAGS) -o $@ -c $^

$(out)/ioredirection.o: $(src)/ioredirection.c
	gcc $(CFLAGS) -o $@ -c $^


#________________________________Library for commands___________________________#
$(lib)/libcommands.a: $(out)/commands/exit.o $(out)/commands/cd.o $(out)/commands/clr.o $(out)/commands/echo.o
	ar -rc $@ $^

$(out)/commands/exit.o: $(src)/commands/exit.c
	mkdir -p $(out)/commands/
	gcc $(CFLAGS) -o $@ -c $^

$(out)/commands/cd.o: $(src)/commands/cd.c
	gcc $(CFLAGS) -o $@ -c $^

$(out)/commands/clr.o: $(src)/commands/clr.c
	gcc $(CFLAGS) -o $@ -c $^

$(out)/commands/echo.o: $(src)/commands/echo.c
	gcc $(CFLAGS) -o $@ -c $^	

#_CLEAN_#
clean:
	rm -rf $(bin)/ $(lib)/ $(out)/ 
