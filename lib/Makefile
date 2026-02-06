LIB = libft.a

RED				= \033[31m
GREEN			= \033[32m
YELLOW			= \033[33m
BLUE			= \033[34m
MAGENTA			= \033[35m
CYAN			= \033[36m
RESET			= \033[0m

GNL_DIR = srcs/get_next_line/
PRINTF_DIR = srcs/printf/
LIB_DIR = srcs/libft/
BUILD_DIR = build/

GNL_SRCS = $(GNL_DIR)get_next_line_utils.c \
			$(GNL_DIR)get_next_line.c

PRINTF_SRCS = $(PRINTF_DIR)ft_printf.c \
			$(PRINTF_DIR)utils/ft_putaddyf.c \
			$(PRINTF_DIR)utils/ft_putcharf.c \
			$(PRINTF_DIR)utils/ft_putnbr_basef.c \
			$(PRINTF_DIR)utils/ft_putnbrf.c \
			$(PRINTF_DIR)utils/ft_putstrf.c

LIB_SRCS = $(LIB_DIR)ft_abs.c \
			$(LIB_DIR)ft_isalpha.c \
			$(LIB_DIR)ft_isdigit.c \
			$(LIB_DIR)ft_isalnum.c \
			$(LIB_DIR)ft_isascii.c \
			$(LIB_DIR)ft_isprint.c \
			$(LIB_DIR)ft_strlen.c \
			$(LIB_DIR)ft_memset.c \
			$(LIB_DIR)ft_bzero.c \
			$(LIB_DIR)ft_memcpy.c \
			$(LIB_DIR)ft_memmove.c \
			$(LIB_DIR)ft_strcmp.c \
			$(LIB_DIR)ft_strlcpy.c \
			$(LIB_DIR)ft_strlcat.c \
			$(LIB_DIR)ft_toupper.c \
			$(LIB_DIR)ft_tolower.c \
			$(LIB_DIR)ft_strchr.c \
			$(LIB_DIR)ft_strrchr.c \
			$(LIB_DIR)ft_strncmp.c \
			$(LIB_DIR)ft_memchr.c \
			$(LIB_DIR)ft_memcmp.c \
			$(LIB_DIR)ft_strnstr.c \
			$(LIB_DIR)ft_atoi.c \
			$(LIB_DIR)ft_atol.c \
			$(LIB_DIR)ft_calloc.c \
			$(LIB_DIR)ft_strdup.c \
			$(LIB_DIR)ft_substr.c \
			$(LIB_DIR)ft_strjoin.c \
			$(LIB_DIR)ft_strtrim.c \
			$(LIB_DIR)ft_split.c \
			$(LIB_DIR)ft_itoa.c \
			$(LIB_DIR)ft_strmapi.c \
			$(LIB_DIR)ft_striteri.c \
			$(LIB_DIR)ft_putchar_fd.c \
			$(LIB_DIR)ft_putstr_fd.c \
			$(LIB_DIR)ft_putendl_fd.c \
			$(LIB_DIR)ft_putnbr_fd.c \
			$(LIB_DIR)word_count.c \
			$(LIB_DIR)free_dtab.c \
			$(LIB_DIR)ft_strcat.c \
			$(LIB_DIR)get_dtab_len.c \
			$(LIB_DIR)word_len.c \
			$(LIB_DIR)ft_lstnew.c \
			$(LIB_DIR)ft_lstadd_front.c \
			$(LIB_DIR)ft_lstsize.c \
			$(LIB_DIR)ft_lstlast.c \
			$(LIB_DIR)ft_lstadd_back.c \
			$(LIB_DIR)ft_lstdelone.c \
			$(LIB_DIR)ft_lstclear.c \
			$(LIB_DIR)ft_lstiter.c \
			$(LIB_DIR)ft_lstmap.c 

ALL_SRCS = $(LIB_SRCS) $(GNL_SRCS) $(PRINTF_SRCS)
LIB_OBJS = $(ALL_SRCS:%.c=$(BUILD_DIR)%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
AR = ar rcs
RM = rm -rf

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)%.o: %.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
# 	@echo "$(YELLOW)Compiling $<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

lib: $(LIB)

$(LIB): $(LIB_OBJS)
	@echo "$(GREEN)Archiving $@$(RESET)"
	@$(AR) $@ $^
	@echo "$(GREEN)Archive complete$(RESET)"

lib_clean:
	@echo "$(RED)Cleaning library object files$(RESET)"
	@$(RM) $(BUILD_DIR)
	
lib_fclean: lib_clean
	@echo "$(RED)Cleaning library archive$(RESET)"
	@$(RM) $(LIB)

re_lib: lib_fclean lib

.PHONY: lib lib_clean lib_fclean re_lib