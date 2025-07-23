# Compiler + flags
CC      := cc
CFLAGS  := -Wall -Wextra -Werror -I include 

# Source & objects
SRC := src/main.c src/utils.c src/parsing.c src/errors.c
NAME  := philo
OBJDIR  := obj
OBJ := $(SRC:src/%.c=$(OBJDIR)/%.o)

# Main target
all: $(NAME)

# Link server
$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) \
	      -o $(NAME)

# Compile .c → .o
$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Ensure obj dir
$(OBJDIR):
	@mkdir -p $(OBJDIR)

VG_FLAGS  := --leak-check=full \
             --show-leak-kinds=all \
             --track-origins=yes \
             --error-exitcode=1

valgrind: all
	@$(MAKE) CFLAGS="$(CFLAGS) -g"

# Clean rules
clean:
	rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)
	
re: fclean all

# san: CFLAGS += -fsanitize=address -fno-omit-frame-pointer -g
san: CFLAGS += -fsanitize=address -g -static-libsan  -Wunused
san: fclean all

.PHONY: all clean fclean re