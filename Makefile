# Project settings
NAME := ft_retro


# Basic definitions
SRC_PATH := srcs
OBJ_PATH := .bin
INC_PATH := includes


# Compiler flags
CPPFLAGS :=	-Wall -Wextra -Werror
CPPFLAGS += -iquote$(INC_PATH)
LDFLAGS :=	-lncurses

# Commands
CC := clang++
RM := rm -f
RMDIR := rmdir -p
MKDIR := mkdir -p
PRINT := printf
NORM := norminette

SRCS_NAMES :=	main.cpp						\
				Renderer.cpp					\
				AEntity.cpp						\
				ASpaceShip.cpp					\
				Meteorite.cpp					\
				Rocket.cpp						\
				Player.cpp						\
				EntityList.cpp					\
				Invader.cpp						\
				RetroEngine.cpp					\
				Bomber.cpp						\
				Bomb.cpp						\
				TimeLapse.cpp					\
				Boss.cpp


SRCS := $(addprefix $(SRC_PATH)/,$(SRCS_NAMES))
OBJS := $(addprefix $(OBJ_PATH)/,$(SRCS_NAMES:.cpp=.o))

OBJ_DIRS := $(sort $(dir $(OBJS)))

INCS :=	Renderer.hpp			\
		IEntity.hpp				\
		AEntity.hpp				\
		ASpaceShip.hpp			\
		Meteorite.hpp			\
		Rocket.hpp				\
		Player.hpp				\
		EntityList.hpp			\
		Invader.hpp				\
		Coord.hpp				\
		KeyEvent.hpp			\
		RetroEngine.hpp			\
		TimeLapse.hpp			\
		Bomber.hpp				\
		Bomb.hpp				\
		ft_retro.hpp			\
		Boss.hpp


# THE NORM IS REAL
NORM_LOG := norm.log
NORM_FILES := $(SRCS) $(addprefix $(INC_PATH)/,$(INCS))

# Cosmetic features
DETAILED = 1
RESET := \033[0m
GREY := \033[90m
GREEN := \033[32m
YELLOW := \033[93m
DYELLOW := \033[33m
UNDERLINE := \033[4m

all: $(NAME)

$(NAME): $(OBJ_DIRS) $(OBJS)
ifeq ($(DETAILED), 1)
	@tput dl; tput el1; tput cub 100; $(PRINT) "$(GREY)Creating object files: $(GREEN)done!$(RESET)"
endif
	@$(PRINT) "\n$(GREY)Compiling $(RESET)$(NAME)$(GREY): $(RESET)"
	@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
	@$(PRINT) "$(GREEN)done!$(RESET)\n"


$(OBJ_DIRS):
	@$(MKDIR) $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(addprefix $(INC_PATH)/,$(INCS))
ifeq ($(DETAILED), 1)
	@tput dl; tput el1; tput cub 100; $(PRINT) "$(GREY)Creating object files: $(RESET)$(notdir $@)"
endif
	@$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@$(RM) $(NORM_LOG)
	@$(RM) -r *.dSYM
	@$(RM) $(OBJS) 2> /dev/null || true
	@$(RMDIR) $(OBJ_DIRS) 2> /dev/null || true
	@$(PRINT) "$(DYELLOW)Removed $(YELLOW)object files!$(RESET)\n"

fclean: clean
	@$(RM) $(NAME) 2> /dev/null || true
	@$(RM) $(TEST_NAME) 2> /dev/null || true
	@$(PRINT) "$(DYELLOW)Removed $(YELLOW)$(NAME) executable!$(RESET)\n\n"

re: fclean all

norm:
	@$(PRINT) "$(GREY)Checking $(RESET)The Norm$(GREY)...$(RESET)\n"
	@$(PRINT) "Found $(GREEN)$(words $(NORM_FILES))$(RESET) files!\n"
	@$(RM) $(NORM_LOG)
	@$(NORM) $(NORM_FILES) > $(NORM_LOG)
	@$(PRINT) "Norm Errors: "
	@cat $(NORM_LOG) | grep Error | wc -l | bc
	@$(PRINT) "See $(UNDERLINE)$(NORM_LOG)$(RESET) for details.\n"

.PHONY: all clean fclean re norm
