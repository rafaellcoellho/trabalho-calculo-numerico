# Name of the project
PROJ_NAME=trabalho-calculo-numerico

# .c files
C_SOURCE=$(wildcard ./src/*.c)

# .h files
H_SOURCE=$(wildcard ./src/*.h)

# Folders
H_FOLDER:=inc

# Object files
OBJ=$(subst .c,.o,$(subst src,build,$(C_SOURCE)))


# Compiler and linker
CC=gcc

# Flags for compiler
CC_FLAGS=-c         \
	 	 -g	   		\
         -W         \
         -Wall      \
         -std=c99   \
         -pedantic

#
## Compilation and linking
#
all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $^ -lm -o $@
	@ echo 'Finished building binary: $@'
	@ echo ' '

./build/%.o: ./src/%.c ./src/%.h
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

./build/main.o: ./src/main.c $(H_SOURCE)
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

clean:
	@ rm -f build/*.o $(PROJ_NAME)
