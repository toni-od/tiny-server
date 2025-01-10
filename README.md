#tiny-server

## description

A tiny server written in the C programming language.

## usage

```bash
git clone https://github.com/toni-od/tiny-server.git
cd tiny-server
make clean
make
./bin/server 9000 10
```

The arguments are

+ port:     listening port number
+ backlog:  number of clients to accept at a go

alternatively, you can use the commands

```
make clean
make
make run
```

although they will use the default port to run the server
