### Source: https://www.youtube.com/watch?v=DtGrdB8wQ_8&t

EXEC			:= loupe
SOURCE_DIRECTORIES	:= ./src ./OGLT/src ./OGLT/src/BufferObject ./OGLT/src/Texture ./OGLT/src/Handler ./OGLT/src/Camera ./OGLT/glad
HEADER_DIRECTORIES	:= ./OGLT/header ./OGLT/header/BufferObject ./OGLT/header/Texture ./OGLT/header/Handler ./OGLT/header/Camera ./OGLT/

CC                      := gcc
CXX			:= g++
OPT			:= -O0
# Generate files that encode make rules for the .h and .hpp dependencies
DEPFLAGS		:= -MP -MD
DEBUG_FLAG              := -g -ggdb
# Automatically add -I flag to include directory
INC_FLAG		:= $(foreach D, $(HEADER_DIRECTORIES), -I$(D))
LIBRARY_FLAGS		:= -lOpenGL -lX11 -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm

CXXFLAGS		:= -Wall -Werror -Wextra $(INC_FLAG) $(OPT) $(DEPFLAGS) $(DEBUG_FLAG)
CFLAGS                  := $(CXXFLAGS) -lstdc++

CPP_FILES		:= $(foreach D, $(SOURCE_DIRECTORIES), $(wildcard $(D)/*.cpp))
C_FILES                 := $(foreach D, $(SOURCE_DIRECTORIES), $(wildcard $(D)/*.c))
OBJ_FILES		:= $(patsubst %.cpp, %.o, $(CPP_FILES)) $(patsubst %.c, %.o, $(C_FILES))
DEP_FILES		:= $(patsubst %.cpp, %.d, $(CPP_FILES)) $(patsubst %.c, %.d, $(C_FILES))

all : $(EXEC)

$(EXEC) : $(OBJ_FILES)
	$(CXX) -o $@ $^ $(LIBRARY_FLAGS)

%.o : %.c %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(EXEC) $(OBJ_FILES) $(DEP_FILES)
