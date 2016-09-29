##
## Makefile for OCRap
## 
## Made by Juliette Malassé
## Login   <dwnut@epita.fr>
## 
## Started on  Tue Sep 27 23:51:36 2016 Juliette Malassé
## Last update Wed Sep 28 23:26:09 2016 Juliette Malassé
##

CC	= @gcc
EC	= @echo
MD	= @mkdir -p
RM	= @rm -rv

SRCDIR	= src
INCDIR	= include
OBJDIR	= obj

CFLAGS	= -Wall -Wextra -Wpadded
CFLAGS += -std=c99 -ansi -pedantic
CFLAGS += -I./$(INCDIR)

NAME	= ocr

SRCS	= main.c		\
	  BitmapReader.c

OBJS	= $(SRCS:%.c=$(OBJDIR)/%.o)

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
