#These are variables
#name the compiler
CC = gcc

#name the include dir for headers
IDIR = ../include
#the gcc option for include dir
CFLAGS = -I $(IDIR)

#folder to put object files
ODIR = ../obj

#folder to put binary files
BDIR = ../bin

#folder for library files
LDIR=../lib
LIBS=-lm

#put name of header files here
_DEPS = 
#suffixes the directory name to files
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

#the C files needed, listed as objects
_CFILES = $(wildcard *.c)
#like cmd: sed "s/.c/.o/g" <<< $(_CFILES)
_OBJ = $(subst .c,.o, $(_CFILES)) 
#like cmd: sed "s|\S| somedir/&|g" <<< $(_OBJ) 
#  '\S' for nonspacewords
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

_TF= $(wildcard ../test/*.c)


#start of makefile rules
# target : prerequisites
# 	recipe...

#make object files for each C file 
# alongside with the stated header files
$(ODIR)/%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#make an executable with the object files 
#$(BDIR)/countdown: $(OBJ)
#	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
$(BDIR)/countdown: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

#declares not to make a file
.PHONY: clean

#delecte object files
#	make clean
clean:
	rm -vf $(ODIR)/*.o 

#print variables
#usage:  make print-VARIABLE
print-%  : ; @echo $* = $($*)
