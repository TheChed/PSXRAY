CC = clang
CFLAGS = -DMOCK -std=c2x -IInclude -Wall -Wextra -pedantic -Wno-unused-parameter
OBJ = linux_link.o
DEPS = gui.h linux_link.h mock.h

all: lib linux_link

lib:
	$(CC) -fPIC -shared -o libmocklinux.so -c mocklinux.c

linux_link: $(OBJ) 
	$(CC) $(OBJ) -o linux_link -L. -lraylib -lm -lmocklinux
	cp *.{h,c} /home/stephan/NAS/TRANSFERT/SRC/PSXRAY

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf linux_link *.o *.so *.dll *.aux *.log *.pdf

