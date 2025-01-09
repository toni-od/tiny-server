

objects=bin/main.o bin/accept.o
target=bin/server

$(target): $(objects)
	cc -o $(target) $(objects)

bin/main.o:
	cc -c src/main.c -o bin/main.o
bin/accept.o:
	cc -c src/accept.c -o bin/accept.o
	
clean:
	rm -f $(target) $(objects)
	
