MAKEFLAGS	+=	-s

CXX 		=	c++

CXXFLAGS 	=	-Wall -Werror -Wextra -std=c++98 -Iinclude -MMD -MP

RM 			=	rm -rf

# TEXT RESET #
RESET		=	\033[0m

# TEXT FORMATTING #
BOLD 		=	\033[1m

# TEXT COLOR #
RED 		= 	\033[31m
GREEN 		=	\033[32m

# BACKGROUND COLOR #
RED_B		=	\033[41m
GREEN_B		=	\033[42m


NAME 		=	ircserv

# SOURCE FOLDER
SRC_FOLDER	=	src
# OBJS FOLDER
OBJ_FOLDER	=	obj

# SOURCE FILES
SRC_FILES 	=	main\
				User\
				UserList\
				Channel\
				ChannelList\
				IrcServer \
				Parse \
				ChannelModes

SRC			=	$(addprefix $(SRC_FOLDER), $(addsuffix .cpp, $(SRC_FILES)))
OBJS 		=	$(addprefix $(OBJ_FOLDER)/, $(addsuffix .o, $(SRC_FILES)))

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN_B) $(BOLD)CREATED $(RESET) $(BOLD)$(GREEN)$(NAME) CREATED$(RESET)."

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp
	@mkdir -p $(OBJ_FOLDER)
	$(CXX) $(CXXFLAGS) -c $< -o $@

valgrind:
	@valgrind --quiet --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=memcheck ./$(NAME) $(ARG)

valgrindQ:
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --tool=memcheck ./$(NAME) $(ARG)

debug: CXXFLAGS += -g
debug: re

clean:
	$(RM) $(OBJ_FOLDER)
	@echo "$(RED_B) $(BOLD)DELETED $(RESET) $(BOLD)$(RED)$(NAME) - ALL OBJS DELETED$(RESET)."

fclean: clean
	$(RM) $(NAME)
	@echo "$(RED_B) $(BOLD)DELETED $(RESET) $(BOLD)$(RED)$(NAME) - PROGRAM DELETED$(RESET)."

re: fclean all

-include $(OBJS:.o=.d)

.PHONY: all clean fclean debug re valgrind valgrindQ
