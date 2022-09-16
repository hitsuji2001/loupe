#!/bin/bash

CXX="${CXX:-g++}"
SRC_APP="src/*.cpp ./OGLT/src/*.cpp ./OGLT/src/BufferObject/*.cpp ./OGLT/src/Texture/*.cpp ./OGLT/src/Handler/*.cpp ./OGLT/src/Camera/*.cpp ./OGLT/glad/glad.c"
FLAGS="-Wall -Werror -Wextra -pedantic"
LIBS="-lX11 -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm"
OUT="loupe"

if [[ -z "$LIBS" ]]
then
    $($CXX $SRC_APP $FLAGS -o $OUT)
else
    $($CXX $SRC_APP $FLAGS $LIBS -o $OUT)
fi

if [[ $? -ne 0 ]]
then
    echo "ERROR: Compile failed!"
    exit 1
else
    echo "Compile succesfully!"
    exit 0
fi
