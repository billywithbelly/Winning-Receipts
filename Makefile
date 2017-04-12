CC = g++ -lm -std=c++11 -Wall

SRCS = ./*.cpp
OBS = ./*.o

# The following line means that do SRC first.
Receipt: SRC
	$(CC) -o $@ *.o

SRC: $(SRCS)
	$(CC) -c $(SRCS)
	
.PHONY :
	clean
clean: 
	rm Receipt *.o 
