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
		$(SRCS_DIR)main/signal.c \
		$(SRCS_DIR)exec/exec.c \
		$(SRCS_DIR)exec/exec_utils.c \
		$(SRCS_DIR)exec/exec_utils2.c \
		$(SRCS_DIR)exec/env_tab.c \
		$(SRCS_DIR)exec/exec_cleanup.c \
		$(SRCS_DIR)exec/parent_builtins.c \
		$(SRCS_DIR)exec/redir.c \
		$(SRCS_DIR)exec/wait_pipeline.c \
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
		$(SRCS_DIR)built-in/export_utils.c \
		$(SRCS_DIR)built-in/pwd.c \
		$(SRCS_DIR)built-in/unset.c


OBJS = $(SRCS:%.c=build/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SUPP_FILE = valgrind_readline_leaks_ignore.supp

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

# create .supp file that suppresses leaks from the readline library
$(SUPP_FILE):
	@echo "Creating valgrind suppression file for readline library"
	@echo "{" > $(SUPP_FILE)
	@echo "   ignore_libreadline_leaks" >> $(SUPP_FILE)
	@echo "   Memcheck:Leak" >> $(SUPP_FILE)
	@echo "   ..." >> $(SUPP_FILE)
	@echo "   obj:*/libreadline.so.*" >> $(SUPP_FILE)
	@echo "}" >> $(SUPP_FILE)

# launch ./minishell with valgrind set up with the suppressed file
valgrind: $(NAME) $(SUPP_FILE)
	valgrind --suppressions=$(SUPP_FILE) --leak-check=full --track-fds=yes --show-leak-kinds=all --trace-children=yes ./$(NAME) || true


CHAT = { ignore_readline_leaks Memcheck:Leak ... obj:*/libreadline.so.* } { ignore_bin_functions Memcheck:Leak ... obj:/usr/bin/* } { ncurses_termcap Memcheck:Leak match-leak-kinds:reachable fun:rl_make_bare_keymap fun:rl_generic_bind fun:rl_parse_and_bind obj:/usr/lib/x86_64-linux-gnu/libreadline.so.8.2 fun:rl_initialize fun:readline }

ignore:
	@for i in $(CHAT); do \
	       echo $$i >> ignore.supp; \
	done

val:
	@make
	@if ! [ -f "ignore.supp" ]; then make ignore; fi
	@valgrind --suppressions=./ignore.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes -s ./minishell

.PHONY: all clean fclean re