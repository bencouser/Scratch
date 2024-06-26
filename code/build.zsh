#!/bin/zsh

# Turn off echo
set +x

# Make sure build dir is there
mkdir -p ../build

# Build object and exe file with debug
echo "Building..."
pushd ../build || exit

echo 'Compiling...'
clang -o MineSweeper ../code/minesweeper.c -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2 -lSDL2_image
if [[ $? -ne 0 ]]; then
    echo "Compilation failed."
    popd
    exit 1
fi

# Run script
echo "Do you want to run the ./scratch file? (y/n): "
read -r user_input

# Run script if user input is 'y'
if [[ "$user_input" == "y" ]]; then
    echo "Running..."
    ./MineSweeper
else
    echo "Skipping run."
fi

popd || exit

echo "Done."
