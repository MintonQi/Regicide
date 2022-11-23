all:
	gcc -g regicide.c utility.c deque.c -o regicide

clean:
	rm -rf *.o
	rm -rf regicide