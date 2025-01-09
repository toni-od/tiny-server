# makefile for tiny-server
# usage: make


objects=bin/main.o bin/accept.o bin/listen.o
target=bin/server

$(target): $(objects)
	cc -o $(target) $(objects)

bin/main.o:
	cc -c src/main.c -o bin/main.o
bin/accept.o:
	cc -c src/accept.c -o bin/accept.o

bin/listen.o:
	cc -c src/listen.c -o bin/listen.o

# only run invoking make to produce the executable
run:
	@./bin/server
	
clean:
	rm -f $(target) $(objects)
	