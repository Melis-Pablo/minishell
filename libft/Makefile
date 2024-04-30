# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 12:37:00 by pmelis            #+#    #+#              #
#    Updated: 2023/11/24 20:06:45 by pmelis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# List of source files for the library
MY_SOURCES = ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_strcmp.c \
		ft_putchr.c \
		ft_putstr.c \
		ft_putnbr.c \
		ft_putunsigned.c \
		ft_puthex.c \
		ft_printf.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstadd_back.c \
		ft_lstlast.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_atod.c \
		ft_atol.c \
		ft_get_next_line.c \

# Name of the output library
NAME = libft.a

# Flags for the C compiler
CFLAGS = -Wall -Wextra -Werror

# Object files for the main library
MY_OBJECTS = $(MY_SOURCES:.c=.o)

# Default target - builds the main library
all: $(NAME)

# Target to build the main library
$(NAME): $(MY_OBJECTS)
	@ar rc $(NAME) $(MY_OBJECTS)    # create the library archive
	@echo "$(NAME) created"
	@ranlib $(NAME)                 # index the library for faster linking
	@echo "$(NAME) indexed"

# Rule for compiling individual source files
%.o: %.c
	@cc $(CFLAGS) -c $< -o $@      # compile the source file into an object file
	
# Target to clean up object files
clean:
	@rm -f $(MY_OBJECTS)           # delete object files
	@echo "OBJ deleted"

# Target to clean up object files and the library
fclean: clean
	@rm -f $(NAME)                 # delete the library archive
	@echo "$(NAME) deleted"

# Target to rebuild the library
re: fclean all

# Declare these targets as phony, to ensure they always run
.PHONY: all, clean, fclean, re
