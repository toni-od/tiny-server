# makefile for tiny-server
# -
# usage: 
#	make       - compiles the program
#	make run   - run the program
# -

target=bin/server
objects=bin/main.o bin/ts_accept.o bin/ts_listen.o bin/ts_handle.o bin/ts_serve.o

$(target): $(objects)
	cc -o $(target) $(objects)

bin/main.o:
	cc -c src/main.c -o bin/main.o
	
bin/ts_accept.o:
	cc -c src/ts_accept.c -o bin/ts_accept.o

bin/ts_listen.o:
	cc -c src/ts_listen.c -o bin/ts_listen.o

bin/ts_handle.o:
	cc -c src/ts_handle.c -o bin/ts_handle.o

bin/ts_serve.o:
	cc -c src/ts_serve.c -o bin/ts_serve.o

# only run invoking make to produce the executable
run:
	@clear
	@./bin/server
	
clean:
	@rm -f $(target) $(objects)
	