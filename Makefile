# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgueugno <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/21 14:58:12 by pgueugno          #+#    #+#              #
#    Updated: 2021/03/09 20:25:56 by pgueugno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                               Filename output                                #
################################################################################

NAME_CHECKER		=	checker
NAME_SWAP			=	push_swap

################################################################################
#                         Sources and objects directories                      #
################################################################################

HEADERS_DIR	=	header
SRCS_DIR	=	srcs
OBJS_DIR	=	objs
LIBS_DIR	=	libs
LIBFT_DIR	=	libft
LIBFT_MAKE	=	Makefile
LIB_LIBFT_DIR	= $(LIBS_DIR)/libft.a

################################################################################
#                               Sources filenames                              #
################################################################################

SRCS_SWAP		=	main_swap.c sort_arg.c list_management.c exec_cmd.c\
					parse_arg.c error.c sort_small_stack.c sort_big_stack.c \
					quicksort_get_pivot.c evaluate_stack.c
SRCS_CHECKER	=	main_checker.c parse_cmd.c list_management.c error.c \
					parse_arg.c exec_cmd.c sort_arg.c \
					evaluate_stack.c 

################################################################################
#                              Commands and arguments                          #
################################################################################

CC			=	@gcc
CFLAGS		=	-Wall -Wextra -Werror -g3 -I$(HEADERS_DIR) -fsanitize=address
LDFLAGS 	=	-L . $(LIB_LIBFT_DIR) -fsanitize=address
RM			=	@rm -f

################################################################################
#                                 Defining colors                              #
################################################################################

_RED		=	\033[31m
_GREEN		=	\033[32m
_YELLOW		=	\033[33m
_CYAN		=	\033[96m

################################################################################
#                                  Compiling                                   #
################################################################################

OBJS_SWAP		=	$(addprefix $(OBJS_DIR)/, $(SRCS_SWAP:.c=.o))
OBJS_CHECKER	=	$(addprefix $(OBJS_DIR)/, $(SRCS_CHECKER:.c=.o))

all:	init_libft init_1 init_2 $(NAME_CHECKER) $(NAME_SWAP)

init_1:
		@ if test -f $(NAME_CHECKER);\
		then echo "$(_CYAN)[checker program already created]";\
		else echo "$(_YELLOW)[Initialize checker program]";\
		fi

init_2:
		@ if test -f $(NAME_SWAP);\
		then echo "$(_CYAN)[push_swap program already created]";\
		else echo "$(_YELLOW)[Initialize push_swap program]";\
		fi

init_libft:
			if test -f $(LIB_LIBFT_DIR); \
			then echo "$(_CYAN)[libft.a already created]";\
			else make -j -C $(LIBFT_DIR) -f $(LIBFT_MAKE);\
			fi

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
				@ echo "\t$(_YELLOW) compiling... $*.c"
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME_CHECKER):	$(OBJS_CHECKER)
					@ echo "\t$(_YELLOW)[Creating checker program]"
					$(CC) $(OBJS_CHECKER) -o $(NAME_CHECKER) $(LDFLAGS)
					@ echo "$(_GREEN)[checker program created & ready]"

$(NAME_SWAP):	$(OBJS_SWAP)
				@ echo "\t$(_YELLOW)[Creating push_swap program]"
				$(CC) $(OBJS_SWAP) -o $(NAME_SWAP) $(LDFLAGS)
				@ echo "$(_GREEN)[push_swap program created & ready]"

clean:
		@ echo "$(_RED)[cleaning up .out & objects files]"
		$(RM) $(OBJS_SWAP) $(OBJS_CHECKER)
		@ make -C $(LIBFT_DIR) -f $(LIBFT_MAKE) clean

fclean: clean
		@ echo "$(_RED)[cleaning up .out, objects & library files]"
		$(RM) $(NAME_CHECKER) $(NAME_SWAP)
		@ make -C $(LIBFT_DIR) -f $(LIBFT_MAKE) fclean

re:	fclean all

.SILENT:
		all
.PHONY: all clean fclean re bonus
