NAME = pipex
BONUS_NAME = pipex_bonus

RED				= \e[31m
GREEN			= \e[32m
YELLOW			= \e[33m
BLUE			= \e[34m
MAGENTA			= \e[35m
CYAN			= \e[36m
RESET			= \e[m

SRCS_DIR = src/
INC = includes/pipex.h
LIB = lib/libft.a
SRCS = $(SRCS_DIR)pipex.c \
		$(SRCS_DIR)pipex_utils.c

BONUS_SRC = $(SRCS_DIR)pipex_bonus.c \
			$(SRCS_DIR)pipex_utils.c \
			$(SRCS_DIR)bonus_utils.c \


OBJS = $(SRCS:%.c=build/%.o)
BONUS_OBJS = $(BONUS_SRC:%.c=build/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	@echo "$(GREEN)Linking $@$(NO_COLOR)"
	@$(CC) $(CFLAGS) -o $@ $^ 
	@echo "$(GREEN)Build complete$(NO_COLOR)"

bonus: $(BONUS_NAME)
	
$(BONUS_NAME): $(BONUS_OBJS) $(LIB)
	@echo "$(GREEN)Linking bonus$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "$(GREEN)Bonus build complete$(RESET)"
	@echo "$(GREEN)Build complete$(NO_COLOR)"

$(LIB):
	@$(MAKE) -C lib lib

$(OBJS) $(BONUS_OBJS): $(INC) | build

$(OBJS): | build

$(BONUS_OBJS): | build

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

.PHONY: all clean fclean re bonus