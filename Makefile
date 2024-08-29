CC = clang
CFLAGS = -DMOCK -std=c2x -IInclude -Wall -Wextra -pedantic -Wno-unused-parameter
OBJ = PSXRAY.o
DEPS = gui.h PSXRAY.h mock.h

all: lib PSXRAY

lib:
	$(CC) -fPIC -shared -o libmocklinux.so -c mocklinux.c

PSXRAY: $(OBJ) 
	$(CC) $(OBJ) -o PSXRAY -L. -lraylib -lm -lmocklinux
	cp *.{h,c} /home/stephan/NAS/TRANSFERT/SRC/PSXRAY

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf PSXRAY *.o *.so *.dll *.aux *.log *.pdf

