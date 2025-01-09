# makefile for tiny-server
# -
# usage: 
#	make       - compiles the program
#	make run   - run the program
# -

target=bin/server
objects=bin/main.o bin/ts_accept.o bin/ts_listen.o

$(target): $(objects)
	cc -o $(target) $(objects)

bin/main.o:
	cc -c src/main.c -o bin/main.o
	
bin/ts_accept.o:
	cc -c src/ts_accept.c -o bin/ts_accept.o

bin/ts_listen.o:
	cc -c src/ts_listen.c -o bin/ts_listen.o

# only run invoking make to produce the executable
run:
	@./bin/server
	
clean:
	@rm -f $(target) $(objects)
	