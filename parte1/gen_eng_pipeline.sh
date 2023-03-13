#!/bin/bash

# check the number of arguments
if [ "$#" -lt 3 ]; then
  echo "Error: At least two arguments are required."
  exit 1
fi

# assign the first argument to a variable
shape=$1

# use a case statement to handle different shapes
case $shape in
  sphere)
    if [ "$#" -ne 5 ]; then
      echo "Error: Wrong number of arguments for $shape."
      exit 1
    fi
    radius=$2
    slices=$3
    stacks=$4
    filename=$5
    echo "Creating a sphere with radius $radius, $slices slices, $stacks stacks and saving to $filename..."
    ;;
  box)
    if [ "$#" -ne 4 ]; then
      echo "Error: Wrong number of arguments for $shape."
      exit 1
    fi
    length=$2
    divisions=$3
    filename=$4
    echo "Creating a box with length of $length units where each side is divided in a grid $divisions x $divisions and saving to $filename..."
    ;;
  cone)
    if [ "$#" -ne 6 ]; then
      echo "Error: Wrong number of arguments for $shape."
      exit 1
    fi
    radius=$2
    height=$3
    slices=$4
    stacks=$5
    filename=$6
    echo "Creating a cone with radius $radius, height $height, $slices slices, $stacks stacks and saving to $filename..."
    ;;
  plane)
    if [ "$#" -ne 4 ]; then
      echo "Error: Wrong number of arguments for $shape."
      exit 1
    fi
    width=$2
    divisions=$3
    filename=$4
    echo "Creating a plane with $width unit in length, $divisions along each axis and saving to $filename..."
    ;;
*)
    echo "Error: Invalid shape '$shape'."
    exit 1
    ;;
esac

# Build the change_model to change the xml file
cd data
g++ change_model.cpp -o change_model
./change_model teste.xml $filename

# Build the generator
cd ../Generator
mkdir -p build
cd build
cmake ..
make

# Run the generator with appropriate parameters based on shape
if [ "$shape" == "sphere" ]; then
    ./generator sphere $radius $slices $stacks $filename
elif [ "$shape" == "box" ]; then
    ./generator box $length $divisions $filename
elif [ "$shape" == "cone" ]; then
    ./generator cone $radius $height $slices $stacks $filename
elif [ "$shape" == "plane" ]; then
    ./generator plane $width $divisions $filename
else
    echo "Error: Invalid shape '$shape'."
    exit 1
fi

# Build the engine
cd ../../Engine
mkdir -p build
cd build
cmake ..
make

# Run the engine
./engine
  
