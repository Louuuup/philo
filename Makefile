
MUTE = @
NAME = philo
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>#
#----------------------------------SOURCES-------------------------------------#
#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<#
SRC := \
	main.c parse.c utils.c tmp.c time.c printer.c actions.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJS = $(addprefix $(BIN_DIR)/, $(SRC:.c=.o))
#==============================================================================#
SRC_DIR     := src
BIN_DIR     := bin
INC_DIR     := include
LIB_DIR     := lib
LIBFT       = $(LIBFT_DIR)/libft.a
LIBFT_DIR   := $(LIB_DIR)/libft
#Shell cmd

CC := gcc
CFLAGS := -Wall -Werror -Wextra -Wunreachable-code -Ofast -g #-fsanitize=address
MKDIRP := mkdir -p
DELETE := rm -rf
# headers to include
INCLUDES := -I$(LIBFT_DIR) -I$(INC_DIR)
# things to link
#
#==============================================================================#
LFLAGS :=  $(LIBFT) $(LIBRL) #librl to re-see

#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>#
#----------------------------------MAIN RULES----------------------------------#
#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<#
all: libft $(NAME)
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(MUTE)echo "$(BLUE)$(BOLD)✅Compiling $(PURPLE)PHILO $(BLUE)→ $(RESET)$(CYAN)$(notdir $<)        $(RESET)"
	$(MUTE)$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	$(MUTE)printf	$(UP)$(CUT)
$(NAME): $(BIN_DIR) $(OBJS) $(READLINE_DEPENDENCIES)
	$(MUTE)$(CC) $(CFLAGS) -o $@ $(OBJS) $(LFLAGS)
	$(MUTE)echo "$(GREEN)$(BOLD)✅ Successfully compiled $(PURPLE)PHILO         $(RESET)"
$(BIN_DIR):
	$(MUTE)$(MKDIRP) $(BIN_DIR)
libft:
	$(MUTE)$(MAKE) -C $(LIBFT_DIR)
bonus: all
	$(MUTE)echo "\n🤯No bonus🤯\n"
clean:
	$(MUTE)$(DELETE) $(OBJS)
	$(MUTE)$(DELETE) $(BIN_DIR)
	$(MUTE)$(MAKE) -C $(LIBFT_DIR) clean
	$(MUTE)echo "$(GREEN)$(BOLD)✅ Cleaned $(PURPLE)PHILO$(RESET)"
fclean: clean
	$(MUTE)$(DELETE) $(NAME)
	$(MUTE)$(MAKE) -C $(LIBFT_DIR) fclean
	$(MUTE)echo "$(GREEN)$(BOLD)✅ Fully cleaned $(PURPLE)PHILO$(RESET)"
rclean:
	$(MUTE)$(DELETE) $(READLINE_DIR)
ffclean: fclean rclean
	$(MUTE)echo "$(GREEN)$(BOLD)✅ Fully Fully cleaned $(PURPLE)PHILO$(RESET)"
OS		:= $(shell uname -s)
re: fclean all
.PHONY: all clean fclean re libft bonus
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>#
#-------------------------------------RUN--------------------------------------#
#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<#
run: all
	./philo 5 60 60 60 60 
val: all
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes ./project
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>#
#------------------------------------NORM--------------------------------------#
#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<#
norm: all
	@norminette lib/libft
	@norminette include/
	@norminette src
#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>#
#-------------------------------------HELP-------------------------------------#
#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<#
help man:
	$(MUTE)echo "$(BOLD)$(GREEN)---------------------------------------------------------------$(RESET)"
	$(MUTE)echo "$(BOLD)$(YELLOW)                    Welcome to $(PURPLE)$(BOLD)PHILO                         $(RESET)"
	$(MUTE)echo "$(BOLD)$(GREEN)---------------------------------------------------------------$(RESET)"
	$(MUTE)echo ""
	$(MUTE)echo "$(BOLD)$(CYAN) Available Options:$(RESET)"
	$(MUTE)echo ""
	$(MUTE)echo "$(BOLD)  make (all)$(RESET)    - Compile the main program and dependencies"
	$(MUTE)echo "$(BOLD)  make run$(RESET)      - Compiles and runs the ./minishel program"
	$(MUTE)echo "$(BOLD)  make clean$(RESET)    - Remove compiled object files"
	$(MUTE)echo "$(BOLD)  make fclean$(RESET)   - Remove compiled files and executable"
	$(MUTE)echo "$(BOLD)  make rclean$(RESET)   - Remove the local readline library"
	$(MUTE)echo "$(BOLD)  make re$(RESET)       - Remove all compiled files and recompile"
	$(MUTE)echo "$(BOLD)  make norm$(RESET)     - Run norminette for coding style"
	$(MUTE)echo ""
	$(MUTE)echo "$(BOLD)$(CYAN) Debug Options:$(RESET)"
	$(MUTE)echo ""
	$(MUTE)echo "$(BOLD)  make libft$(RESET)    - Compile only the library"
	$(MUTE)echo "$(BOLD)  make val$(RESET)      - $(BOLD)make run $(RESET)but with a flagged Valgrind"
	$(MUTE)echo ""
	$(MUTE)echo "$(BOLD)$(GREEN)---------------------------------------------------------------$(RESET)"

#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>#
#----------------------------------COLOR CODES---------------------------------#
#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<#
# Colors
BLACK		=\033[30m
RED			=\033[31m
GREEN       =\033[32m
YELLOW      =\033[33m
BLUE        =\033[34m
PURPLE      =\033[35m
CYAN        =\033[36m
WHITE       =\033[37m
# Text
ERASE       =\033[2K
RESET       =\033[0m
BOLD        =\033[1m
FAINT       =\033[2m
ITALIC      =\033[3m
UNDERLINE   =\033[4m
INVERT      =\033[7m
STRIKE      =\033[9m
# Background
BG_BLACK    =\033[40m
BG_RED      =\033[41m
BG_GREEN    =\033[42m
BG_YELLOW   =\033[43m
BG_BLUE     =\033[44m
BG_PURPLE   =\033[45m
BG_CYAN     =\033[46m
BG_WHITE    =\033[47m
# Others
UP    ="\033[A" # cursor up
CUT   ="\033[K" # cut line
#==============================================================================#
