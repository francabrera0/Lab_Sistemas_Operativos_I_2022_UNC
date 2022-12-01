CFLAGS = -Wall -Werror -pedantic 
include = ./include/
src = ./src/
out = ./out/
lib = ./lib/
bin = ./bin/

$(bin)Main: $(out)Main.o $(lib)libfunctions.a $(lib)libfilesystems.so
	mkdir -p $(bin)
	gcc $(CFLAGS) -o $@ $(out)Main.o -L$(lib) -lfunctions -lfilesystems -ldl

$(out)Main.o: $(src)Main.c $(include)getprocinfo.h $(include)getversioninfo.h 
	mkdir -p $(out)
	gcc $(CFLAGS) -o $@ -c $(src)Main.c

$(out)getversioninfo.o: $(src)getversioninfo.c $(include)getversioninfo.h
	gcc $(CFLAGS) -o $@ -c $(src)getversioninfo.c
	
$(out)getprocinfo.o: $(src)getprocinfo.c $(include)getprocinfo.h
	gcc $(CFLAGS) -o $@ -c $(src)getprocinfo.c

$(out)cJSON.o: $(src)cJSON.c $(include)cJSON.h
	gcc $(CFLAGS) -o $@ -c $(src)cJSON.c

$(out)filesystems.o: $(src)filesystems.c $(include)filesystems.h
	gcc $(CFLAGS) -o $@ -c $(src)filesystems.c

$(lib)libfunctions.a: $(out)getprocinfo.o $(out)getversioninfo.o $(out)cJSON.o
	mkdir -p $(lib)
	ar -rc $@ $^

$(lib)libfilesystems.so: $(out)filesystems.o $(out)cJSON.o
	gcc $(CFLAGS) -shared -fPIC -o $@ $^

clean:
	rm -rf $(out) $(lib) $(bin) 