# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-maga <mde-maga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/28 16:30:39 by mde-maga          #+#    #+#              #
#    Updated: 2025/03/28 17:28:03 by mde-maga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = src
SRC = $(SRC_DIR)/main.c \
		$(SRC_DIR)/parser.c \
		$(SRC_DIR)/utils.c \
		$(SRC_DIR)/mutex_init.c \
		$(SRC_DIR)/routine.c \
		$(SRC_DIR)/monitor.c \
		$(SRC_DIR)/fork_picker.c \
		$(SRC_DIR)/extra_utils.c

CC = @cc
CFLAGS = -Wall -Wextra -Werror -g -pthread #-fsanitize=thread

OBJ_DIR = obj
OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Bold High Intensity
BIBlack='\033[1;90m'      # Black
BIRed='\033[1;91m'        # Red
BIGreen='\033[1;92m'      # Green
BIYellow='\033[1;93m'     # Yellow
BIBlue='\033[1;94m'       # Blue
BIPurple='\033[1;95m'     # Purple
BICyan='\033[1;96m'       # Cyan
BIWhite='\033[1;97m'      # White
BILGreen='\033[1;38;2;147;196;125m'  # Bold Custom Color (#93c47d)

MSG1 = @echo ${BILGreen}"✔︎ Compiled successfully"${Color_Off}
MSG2 = @echo ${BILGreen}"✔︎ Cleaned successfully"${Color_Off}
MSG3 = @echo ${BILGreen}"✔︎ Cleaned ./${NAME} executable successfully"${Color_Off}
HOWTO = @echo ${BIGreen}"To run the program write:"${BIWhite}"./${NAME} X X X X (X)"${Color_Off}

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^
	$(MSG1)
	${HOWTO}

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -rf $(OBJS) $(NAME)
	$(MSG2)

fclean: clean
	@rm -f $(NAME)
	$(MSG3)

re: fclean all

.PHONY: clean fclean all re
