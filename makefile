all: submission

submission: assignment1.o
	g++ -g assignment1.o -o submission
	
assignment1.o: assignment1.cpp
	g++ -g -c assignment1.cpp
	
clean:
	rm -f *.o submission
