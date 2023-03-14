#!/bin/bash

# check the number of arguments
if [ "$#" -lt 1 ]; then
  echo "Error: One argument is required."
  exit 1
fi

xmlFile=$1

# Get the model names from the xml file
cd data
regex='file="([^"]+)"'

xmlContent=$(cat "$xmlFile")
models=$(echo "$xmlContent" | grep -oE "$regex" | sed 's/file="//' | sed 's/"//' | sed -E 's/^(sphere|plane|box|cone)_([0-9]+)_([0-9]+)(_([0-9]+))?(_([0-9]+))?\.3d$/\1 \2 \3 \5 \7 \1\_\2_\3\4\6.3d/' | sed 's/\<0*\([1-9]\)/\1/g' | paste -sd "," - | tr -s ' ' | tr -d '\n')

echo "The model names are: $models"

# Build the generator
echo "Building the generator..."
cd ../Generator
mkdir -p build
cd build
cmake ..
make

# Split model names into an array
IFS=',' read -ra modelNames <<< "$models"

# Loop over the array of model names and run the generator for each one
for name in "${modelNames[@]}"
do
    echo "Running the generator for $name ..."
    read -ra params <<< "$name"
    if [ "${params[0]}" == "sphere" ] || [ "${params[0]}" == "plane" ] || [ "${params[0]}" == "box" ] || [ "${params[0]}" == "cone" ]; then
    ./generator $name
else
    echo "Error: Invalid shape '${params[0]}'."
    exit 1
fi

done

# Build the engine
echo "Building the engine..."
cd ../../Engine
mkdir -p build
cd build
cmake ..
make

# Run the engine
echo "Running the engine..."
./engine $xmlFile
