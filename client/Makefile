output: gthclient.o my-thello.o
		g++ gthclient.o my-thello.o -o output

gthclient.o: gthclient.c gthclient.h
	$(CC) $(CFLAGS) -c gthclient.c

my-thello.o: my-thello.cpp gthclient.h
	g++ -c my-thello.cpp

clean:
	-rm -f *.o output
