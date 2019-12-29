NAME			= scope
SHEL			= /bin/bash

CC				= gcc
CFLAGS		=	-Wall -Wextra
# CFLAGS		=	-Wall -Wextra -Werror
SRCS_DIR	=	srcs/
LIBFT_DIR	=	libft/
SRCS_LIST	=	main.c \
						utils/vector.c \
						utils/vectorial_addition.c \
						utils/vectorial_substraction.c \
						utils/vectorial_scalar_product.c \
						utils/vectorial_dot_product.c \
						loaders/obj_parser.c \

SRCS			=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS_DIR	=	objs/
OBJS_LIST	=	$(patsubst %.c, %.o, $(SRCS_LIST))
OBJS			=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))
HEADERS		=	-I./libft -I./includes
LIBS			= -lglfw -lGL -lGLEW -L./libft -lft -lm

.PHONY : all clean fclean norme $(NAME) re

all : $(NAME)

$(NAME) : $(OBJS)
	@make --no-print-directory -C $(LIBFT_DIR)
	echo "\033[32mLinking...\033[0m"
	@$(CC) $(CFLAGS) $^ $(LIBS) -o $@
	echo "\033[32mBinary \033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/utils
	@mkdir -p $(OBJS_DIR)/loaders
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	echo "\033[34mCompilation of \033[36m$(notdir $<)\033[34m done.\033[0m"

norme :
	@norminette $(SRCS)

clean :
	@make clean --no-print-directory -C $(LIBFT_DIR)
	@rm -rf $(OBJS_DIR)
	echo "\033[31mObjects files \033[1;31m$(OBJS_LIST)\033[1;0m\033[31m removed.\033[0m"

fclean : clean
	@make fclean --no-print-directory -C $(LIBFT_DIR)
	@rm -rf $(NAME)
	echo "\033[31mBin \033[1;31m$(NAME)\033[1;0m\033[31m removed.\033[0m"

re : fclean all
