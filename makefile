NAME        := main

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# SRC_DIR   source directory
# OBJ_DIR   object directory
# SRCS      source files
# OBJS      object files
#
# CC        compiler
# CXXFLAGS  compiler flags (for C++)
# CPPFLAGS  preprocessor flags

SRC_DIR     := src
OBJ_DIR     := obj
SRCS        := \
	../main.cpp			\
	CommunicationSystem.cpp \
	Actuator.cpp		\
	Clock.cpp	        \
	FlightLogger.cpp    \
	IMU.cpp 		    \
	Rocket.cpp		    \
	RocketModule.cpp    \
	Sensor.cpp		    \
	TextDataSaver.cpp

SRCS        := $(SRCS:%=$(SRC_DIR)/%)
OBJS        := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CC          := g++
CXXFLAGS    := -Wall
CPPFLAGS    := -I include/

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove
# MAKEFLAGS make flags
# DIR_DUP   duplicate directory tree

RM          := rm -f
MAKEFLAGS   += --no-print-directory
DIR_DUP     = mkdir -p $(@D)

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# $(NAME)   linking .o -> binary
# %.o       compilation .cpp -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal

all: $(NAME)

$(NAME): $(OBJS)
	echo $(CC) $(OBJS) -o $(NAME) $(CPPFLAGS)
	$(CC) $(OBJS) -o $(NAME) $(CPPFLAGS)
	$(info CREATED $(NAME))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(DIR_DUP)
	echo $(CC) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

clean:
	echo $(RM) $(OBJS)
	$(RM) $(OBJS)
	echo $(RM) $(NAME)
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

run:
	echo ./$(NAME)
	./$(NAME)

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: clean fclean re
.SILENT: