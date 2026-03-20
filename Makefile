NAME = minishell

RED				= \e[31m
GREEN			= \e[32m
YELLOW			= \e[33m
BLUE			= \e[34m
MAGENTA			= \e[35m
CYAN			= \e[36m
RESET			= \e[m

SRCS_DIR = src/
INC = includes/minishell.h \
		includes/execution.h \
		includes/parsing.h \
		includes/builtins.h 

LIBFT_COMPAT = lib/libft.h
LIB = lib/libft.a
SRCS = $(SRCS_DIR)main/main.c \
		$(SRCS_DIR)main/env.c \
		$(SRCS_DIR)main/env_utils.c \
		$(SRCS_DIR)exec/exec.c \
		$(SRCS_DIR)exec/exec_utils.c \
		$(SRCS_DIR)parsing/parsing.c \
		$(SRCS_DIR)parsing/token.c \
		$(SRCS_DIR)parsing/token_utils.c \
		$(SRCS_DIR)parsing/parse_cmd.c \
		$(SRCS_DIR)parsing/parse_utils.c \
		$(SRCS_DIR)parsing/expand.c \
		$(SRCS_DIR)parsing/expand_word.c \
		$(SRCS_DIR)parsing/expand_av.c \
		$(SRCS_DIR)parsing/expand_utils.c \
		$(SRCS_DIR)parsing/quote_handler.c \
		$(SRCS_DIR)built-in/builtins_check_dispatch.c \
		$(SRCS_DIR)built-in/cd.c \
		$(SRCS_DIR)built-in/echo.c \
		$(SRCS_DIR)built-in/env.c \
		$(SRCS_DIR)built-in/exit.c \
		$(SRCS_DIR)built-in/export.c \
		$(SRCS_DIR)built-in/pwd.c \
		$(SRCS_DIR)built-in/unset.c


OBJS = $(SRCS:%.c=build/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	@echo "$(GREEN)Linking $@$(NO_COLOR)"
	@$(CC) $(CFLAGS) -o $@ $^ -lreadline
	@echo "$(GREEN)Build complete$(NO_COLOR)"

$(LIB):
	@$(MAKE) -C lib lib

$(LIBFT_COMPAT): lib/includes/libft.h
	@ln -sf includes/libft.h $(LIBFT_COMPAT)

$(OBJS): | build

$(OBJS): $(INC) $(LIBFT_COMPAT)

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
	@$(MAKE) -C lib lib_fclean

re: fclean all

.PHONY: all clean fclean re