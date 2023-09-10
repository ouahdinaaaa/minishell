# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayael-ou <ayael-ou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/28 23:46:21 by ayael-ou          #+#    #+#              #
#    Updated: 2023/07/28 23:46:21 by ayael-ou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell
INCLUDE     = ./includes/minishell.h
LIBFT       = ./libft/libft.so
LINK        = -I./includes -I./libft/includes
SRC_DIR     = ./srcs/
OBJ_DIR     = ./objs/
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3
LDFLAGS     = -L./libft -lft -lreadline
RM          = rm -f
SMAKE       = make --no-print-directory

# Colors
END         = \033[0m
BOLD        = \033[1m
YELLOW      = \033[0;93m
GREEN       = \033[0;92m
BLUE        = \033[0;94m
CYAN        = \033[0;96m

# Sources
SRC_FILES   = minishell \
			  loop \
				./utils/utils1 \
				./utils/utils_parse \
				./signal/signo \
				./exec/here_doc \
				./exec/path_bonus \
				./exec/child_bonus \
				./exec/files_bonus \
				./exec/pipex_bonus \
				./exec/replace_cmd \
				./exec/redirection \
				./exec/form_replace \
				./exec/utils_form \
				./exec/replace_dollars_here_doc \
				./exec/fonction_write \
				./exec/utils_of_replace \
				./exec/get_next_line \
				./builtins/builtins\
				./builtins/utils\
				./builtins/cmd_cd\
				./builtins/cmd_pwd\
				./builtins/cmd_env\
				./builtins/cmd_exit\
				./builtins/cmd_echo\
				./builtins/cmd_unset\
				./builtins/cmd_export\
				./builtins/export_fake_env\
				./builtins/export\
				./kamel/initfree\
                ./kamel/parsing\
                ./kamel/parseCommand\
                ./kamel/parseInfile\
                ./kamel/parseInfileHeredoc\
                ./kamel/parseOutfile\
                ./kamel/parseOutfileAppend\
                ./kamel/builtins\
                ./kamel/builtinsUnset\
                ./kamel/builtinsPwd\
                ./kamel/builtinsExport\
                ./kamel/builtinsExit\
                ./kamel/builtinsEnv\
                ./kamel/builtinsEcho\
                ./kamel/builtinsCd\
                ./kamel/sqdq\
                ./kamel/sqdq-utils1\
                ./kamel/sqdq-utils2\
                ./kamel/splitPipes\
                ./kamel/utils1\
                ./kamel/utils2\
                ./kamel/utils3\
                ./kamel/utils4\
                ./kamel/utils5\
                ./kamel/utils6\
                ./kamel/utils7\
                ./kamel/utils8\

SRC         = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ         = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LDFLAGS) -o $@
	@echo "$(GREEN)$(BOLD)minishell compiled!$(END)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling: $<$(END)"
	$(CC) $(CFLAGS) $(LINK) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	$(SMAKE) -C ./libft

clean:
	$(RM) -r $(OBJ_DIR)
	@echo "$(BLUE)minishell object files cleaned!$(END)"
	$(SMAKE) -C ./libft clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	@echo "$(CYAN)minishell executable files cleaned!$(END)"
	$(SMAKE) -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
