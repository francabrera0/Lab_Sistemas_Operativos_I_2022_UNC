CFLAGS = -Wall -Werror -pedantic
include = ./include
src = ./src
bin = ./bin
out = ./out

$(bin)/main: $(out)/main.o $(out)/radarMeasurement.o
	mkdir -p $(bin)/
	gcc $(CFLAGS) -o $@ $^

$(out)/main.o: $(src)/main.c  
	mkdir -p $(out)/
	gcc $(CFLAGS) -o $@ -c $^

$(out)/radarMeasurement.o: $(src)/radarMeasurement.c
	gcc $(CFLAGS) -o $@ -c $^

clean:
	rm -rf $(bin)/ $(out)/