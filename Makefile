all:
	gcc -g regicide.c deque.c utility.c -o regicide

clean:
	rm -rf *.o
	rm -rf regicide