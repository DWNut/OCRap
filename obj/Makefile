CC       = @gcc
EC 	 = @echo
MD 	 = @mkdir -p
RM	 = @rm -rv

SRCDIR 	 = src
INCDIR	 = include
OBJDIR 	 = obj

CPPFLAGS = `pkg-config --cflags sdl`
CFLAGS	 = -Wall -Wextra -Werror -std=c99 -pedantic 
CFLAGS  += -I./$(INCDIR)
LDLIBS	 = `pkg-config --libs sdl` -lSDL_image -lm

NAME 	 = OCR

SRCS	 = main.c

OBJS	 = ${SRCS:%.c=$(OBJDIR)/%.o}

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(MD) $(OBJDIR)
	$(EC) Compilation de $<...
	$(CC) -o $@ -c $< $(CFLAGS)

$(NAME): $(OBJS)
	$(EC) Linking de $(NAME)...
	$(CC) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re


