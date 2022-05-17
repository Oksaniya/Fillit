NAME = fillit

CC = gcc
FLAG = -glldb -g3
INC = -I ./inc -I ./my_stdlib
LIB = ./my_stdlib/my_stdlib.a
LIBDIR = ./my_stdlib

all: obj
	make -C $(LIBDIR)
	$(CC) obj/main.o \
	obj/io.o \
	obj/validator.o \
	obj/maping.o \
	obj/fitting.o \
	 -o fillit -glldb -fsanitize=address -g3 $(LIB)
	@echo "\033[0;32mFillit compiled : \033[0m\033[31m$(NAME)\033[0m"	

obj:
	mkdir obj
	$(CC) $(FLAG) -c src/main.c -o obj/main.o $(INC)
	$(CC) $(FLAG) -c src/io.c -o obj/io.o $(INC)
	$(CC) $(FLAG) -c src/validator.c -o obj/validator.o $(INC)
	$(CC) $(FLAG) -c src/maping.c -o obj/maping.o $(INC)
	$(CC) $(FLAG) -c src/fitting.c -o obj/fitting.o $(INC)

clean:
	rm -fr obj/*.o
	rm -fr obj

fclean: clean
	rm -fr $(NAME)

re: fclean all

run: re
	./$(NAME) ./Sample1

debug: re
	lldb -- ./$(NAME) ./Sample1