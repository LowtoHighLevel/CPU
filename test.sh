make COPTS="-DLTHLV2_TYPE=32"
../ASM/target/asm.exe ./test.S
echo "Starting test run!"
./target/emu.exe -r -f out.bin
make clean