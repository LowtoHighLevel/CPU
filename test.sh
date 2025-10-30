make
../ASM/target/asm ./test.S
echo "Starting test run!"
./target/emu -r -f out.bin
make clean