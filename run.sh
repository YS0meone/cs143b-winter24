root=$(pwd);
if [ ! -d "build" ]; then
  mkdir build
  echo "Build directory created."
else
  echo "Build directory found."
fi
cd build || exit
cmake ..
cmake --build .
./PRM fileInput < "$root"/input.txt > "$root"/output.txt