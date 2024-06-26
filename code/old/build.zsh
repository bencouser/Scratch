#!/bin/zsh

# Turn off echo
set +x

# Make sure build dir is there
mkdir -p ../build

# Build object and exe file with debug
echo "Building..."
pushd ../build || exit

clang++ -c ../code/scratch.mm -o scratch.o
if [[ $? -ne 0 ]]; then
    echo "Compilation failed."
    popd
    exit 1
fi

clang++ -o scratch scratch.o -framework Cocoa
if [[ $? -ne 0 ]]; then
    echo "Linking failed."
    popd
    exit 1
fi

# Run script
echo "Do you want to run the ./scratch file? (y/n): "
read -r user_input

# Run script if user input is 'y'
if [[ "$user_input" == "y" ]]; then
    echo "Running..."
    ./scratch
else
    echo "Skipping run."
fi

popd || exit

echo "Done."
