# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-maga <mtmpfb@gmail.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 12:12:17 by mde-maga          #+#    #+#              #
#    Updated: 2025/03/26 12:17:39 by mde-maga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:


SRCS	= main.c
SRCS	+= ft_finish.c ft_initialize.c \
			ft_philo_utils.c ft_utils.c ft_routine.c
OBJS	= $(SRCS:.c=.o)
NAME	= philo
CC		= cc
CFLAGS = -Werror -Wall -Wextra -g -pthread
HEADER	= philo.h

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
MSG3 = @echo ${BILGreen}"✔︎ Cleaned ${NAME} executable successfully"${Color_Off}
HOWTO = @echo ${BIGreen}"To run the program write:"${BIWhite}"./${NAME} X X X X (X)"${Color_Off}

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	$(MSG1)
	${HOWTO}

clean:
	@/bin/rm -rf $(OBJS)
	$(MSG2)

fclean: clean
	@rm -f $(NAME)
	$(MSG3)

re: fclean all

.PHONY: clean fclean all re