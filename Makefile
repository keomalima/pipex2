# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/01 11:56:39 by keomalima         #+#    #+#              #
#    Updated: 2025/01/04 12:28:32 by keomalima        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC := cc
CFLAGS := -Wall -Wextra -Werror -Iincludes -I$(LIBFTDIR)/includes
RM := rm -f

SRCSDIR := src
OBJDIR := objects

LIBFTDIR := libft
LIBSRCS := $(LIBFTDIR)/src

SRCS := $(SRCSDIR)/pipex.c  $(SRCSDIR)/pipex_pipes.c  $(SRCSDIR)/pipex_utils.c \
		 $(SRCSDIR)/pipex_arg_parse.c $(SRCSDIR)/pipex_utils2.c
OBJS := $(SRCS:$(SRCSDIR)/%.c=$(OBJDIR)/%.o)

LIBFT_SRCS := $(LIBSRCS)/ft_atoi.c $(LIBSRCS)/ft_bzero.c $(LIBSRCS)/ft_calloc.c \
			$(LIBSRCS)/ft_isalnum.c $(LIBSRCS)/ft_isalpha.c $(LIBSRCS)/ft_isascii.c \
			$(LIBSRCS)/ft_isdigit.c $(LIBSRCS)/ft_isprint.c $(LIBSRCS)/ft_memchr.c \
			$(LIBSRCS)/ft_memcmp.c $(LIBSRCS)/ft_memcpy.c $(LIBSRCS)/ft_memmove.c \
			$(LIBSRCS)/ft_memset.c $(LIBSRCS)/ft_strchr.c $(LIBSRCS)/ft_strdup.c \
			$(LIBSRCS)/ft_strlcat.c $(LIBSRCS)/ft_strlcpy.c $(LIBSRCS)/ft_strlen.c \
			$(LIBSRCS)/ft_strncmp.c $(LIBSRCS)/ft_strnstr.c $(LIBSRCS)/ft_strrchr.c \
			$(LIBSRCS)/ft_tolower.c $(LIBSRCS)/ft_toupper.c $(LIBSRCS)/ft_itoa.c \
			$(LIBSRCS)/ft_putchar_fd.c $(LIBSRCS)/ft_putendl_fd.c \
			$(LIBSRCS)/ft_putnbr_fd.c $(LIBSRCS)/ft_putstr_fd.c \
			$(LIBSRCS)/ft_split.c $(LIBSRCS)/ft_striteri.c \
			$(LIBSRCS)/ft_strjoin.c $(LIBSRCS)/ft_strmapi.c \
			$(LIBSRCS)/ft_strtrim.c $(LIBSRCS)/ft_substr.c \
			$(LIBSRCS)/get_next_line.c $(LIBSRCS)/get_next_line_utils.c \
			$(LIBSRCS)/ft_printf.c $(LIBSRCS)/ft_print_char.c \
			$(LIBSRCS)/ft_print_hex.c $(LIBSRCS)/ft_print_int.c \
			$(LIBSRCS)/ft_print_ptr.c $(LIBSRCS)/ft_lstmap.c \
			$(LIBSRCS)/ft_lstadd_back.c $(LIBSRCS)/ft_lstadd_front.c \
			$(LIBSRCS)/ft_lstclear.c $(LIBSRCS)/ft_lstdelone.c \
			$(LIBSRCS)/ft_lstiter.c $(LIBSRCS)/ft_lstlast.c \
			$(LIBSRCS)/ft_lstnew.c $(LIBSRCS)/ft_lstsize.c

LIBFT_HEADERS := $(LIBFTDIR)/includes/libft.h
LIBFT := $(LIBFTDIR)/libft.a

HEADERS := includes/pipex.h $(LIBFT_HEADERS)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJDIR)/%.o: $(SRCSDIR)/%.c $(HEADERS) Makefile | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT): $(LIBFT_SRCS) $(LIBFT_HEADERS)
	$(MAKE) -C $(LIBFTDIR)

clean:
	$(RM) -rf $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re

