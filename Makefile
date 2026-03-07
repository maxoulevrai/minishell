NAME = minishell

RED				= \e[31m
GREEN			= \e[32m
YELLOW			= \e[33m
BLUE			= \e[34m
MAGENTA			= \e[35m
CYAN			= \e[36m
RESET			= \e[m

SRCS_DIR = srcs/
INC = includes/minishell.h
LIB = lib/libft.a
SRCS =	srcs/main/main.c \
		srcs/main/env.c \
		srcs/parsing/parsing.c \
		srcs/parsing/token.c \
		srcs/parsing/token_utils.c \
		srcs/parsing/quote_handler.c \
		srcs/parsing/parse_cmd.c \
		srcs/parsing/parse_utils.c \
		srcs/parsing/expand.c \
		srcs/parsing/expand_word.c \
		srcs/parsing/expand_av.c \
		srcs/parsing/expand_utils.c


OBJS = $(SRCS:%.c=build/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	@echo "$(GREEN)Linking $@$(NO_COLOR)"
	@$(CC) $(CFLAGS) -o $@ $^ 
	@echo "$(GREEN)Build complete$(NO_COLOR)"

$(LIB):
	@$(MAKE) -C lib lib

$(OBJS): | build

build:
	@mkdir -p build

build/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<$(NO_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files$(NO_COLOR)"
	@rm -rf build
	@$(MAKE) -C lib lib_clean

fclean: clean
	@echo "$(RED)Cleaning executable$(NO_COLOR)"
	@rm -f $(NAME)
	@rm -f $(BONUS_NAME)
	@$(MAKE) -C lib lib_fclean

re: fclean all

.PHONY: all clean fclean re