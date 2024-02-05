CC = clang
CFLAGS = -DMOCK -std=c2x -IInclude -Wall -Wextra -pedantic -Wno-unused-parameter
OBJ = linux_link.o
DEPS = gui.h linux_link.h mock.h

all: lib linux_link

lib:
	$(CC) -fPIC -shared -o libmocklinux.so -c mocklinux.c

linux_link: $(OBJ) 
	$(CC) $(OBJ) -o linux_link -L. -lraylib -lm -lmocklinux

%.o : %.c $(DEPS)
	$(CC) $(CFLAGS) -c $<
	cp  $< /home/stephan/NAS/TRANSFERT/PSXMSFS/SRC/RAY

clean:
	rm -rf linux_link *.o *.so *.dll *.aux *.log *.pdf

