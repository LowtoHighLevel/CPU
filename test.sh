make
../ASM/target/asm ./test.S
cp out.bin a.out
echo "Starting test run!"
./target/emu -r
make clean
rm a.out