# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcavadas <jcavadas@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/21 11:10:41 by jcavadas          #+#    #+#              #
#    Updated: 2025/07/21 12:51:52 by jcavadas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C++ = c++
C++FLAGS = -Wall -Wextra -Werror -std=c++98
SRC = main.cpp Bureaucrat.cpp AForm.cpp ShrubberyCreationForm.cpp RobotomyRequestForm.cpp PresidentialPardonForm.cpp

OBJS = $(SRC:.cpp=.o)

NAME = Forms

all: $(NAME)

$(NAME):$(OBJS)
	@$(C++) $(C++FLAGS) $(OBJS) -o $(NAME)
	@echo "\033[0;32m [✔] \033[0m Built $(NAME)"

%.o: %.cpp
	$(C++) $(C++FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "\033[0;31m [✗] \033[0m Cleaned object files"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;31m [✗] \033[0m Removed $(NAME)"

re: fclean all

.PHONY: all clean fclean re

.SILENT:
