#These are variables
#name the compiler
CC = gcc

#eliminate a competing module with a main function
XMAINFILE=countdown.o

#name the include dir for headers
IDIR = ../include
#the gcc option for include dir
CFLAGS = -O0 -g -I $(IDIR)

#folder to put other .c files
OCDIR = ../src

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
_CCFILES = $(wildcard *.c) #current dir
_OCFILES = $(wildcard $(OCDIR)/*.c) #other dir
_CFILES = $(_CCFILES) $(_OCFILES) #all .c files
#like cmd: sed "s/.c/.o/g" <<< $(_CFILES)
#  notdir outputs strips directory path
_OBJ = $(subst .c,.o, $(notdir $(_CFILES))) 
#like cmd: sed "s|\S| somedir/&|g" <<< $(_OBJ) 
#  '\S' for nonspacewords
__OBJ = $(subst $(XMAINFILE),, $(_OBJ))
OBJ = $(patsubst %, $(ODIR)/%, $(__OBJ))

_TF= $(wildcard ../test/*.c)


#start of makefile rules
# target : prerequisites
# 	recipe...

#make object files for each C file 
#  in current and other directory
# alongside with the stated header files
$(ODIR)/%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
$(ODIR)/%.o : $(OCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#make an executable with the object files 
#$(BDIR)/countdown: $(OBJ)
#	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
$(BDIR)/tcountdown: $(OBJ)
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
