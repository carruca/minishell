# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsierra- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 17:05:33 by tsierra-          #+#    #+#              #
#    Updated: 2021/03/02 15:45:36 by tsierra-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft

LNAME = libft.a

CFLAGS = -Wall -Werror -Wextra

LFLAGS = -c

LSOURCE = ft_memset.c \
		  ft_bzero.c \
		  ft_memcpy.c \
		  ft_memccpy.c \
		  ft_memmove.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_strlen.c \
		  ft_isalpha.c \
		  ft_isdigit.c \
		  ft_isalnum.c \
		  ft_isascii.c \
		  ft_isprint.c \
		  ft_toupper.c \
		  ft_tolower.c \
		  ft_strchr.c \
		  ft_strrchr.c \
		  ft_strncmp.c \
		  ft_strlcpy.c \
		  ft_strlcat.c \
		  ft_strnstr.c \
		  ft_atoi.c \
		  ft_calloc.c \
		  ft_strdup.c \
		  ft_substr.c \
		  ft_strjoin.c \
		  ft_strtrim.c \
		  ft_strncpy.c \
		  ft_split.c \
		  ft_itoa.c \
		  ft_strmapi.c \
		  ft_putchar_fd.c \
		  ft_putstr_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c \
		  ft_strndup.c \
		  get_next_line.c \
		  ft_nbrlen.c \
		  ft_strcmp.c \
		  free_2d.c \
		  ft_is_str_digit.c \
		  ft_file_format_cmp.c \
		  ft_count_char_in_str.c \
		  ft_is_color_range.c \
		  ft_only_spaces_line.c \
		  ft_str_tab_remove.c \
		  ft_is_valid_file.c \
		  ft_lstnew.c \
		  ft_lstadd_front.c \
		  ft_lstadd_back.c \
		  ft_lstclear.c \
		  ft_lstdelone.c \
		  ft_lstiter.c \
		  ft_lstlast.c \
		  ft_lstmap.c \
		  ft_lstsize.c

OBJS = $(LSOURCE:.c=.o)

all: $(NAME)

$(NAME):
	gcc $(CFLAGS) $(LFLAGS) $(LSOURCE)
	ar rc $(LNAME) $(OBJS) 

clean:
	rm -f $(OBJS)
fclean:	clean
	rm -f $(LNAME)

re: fclean all

.PHONY: clean fclean all re
