Compiler.exe D:/comp/build/release/demo/04DoWhile.cpp
copy D:\\comp\\build\\release\\demo\\04DoWhile.cpp.asm D:\\comp\\build\\release\\Masm\\out.asm
DOSBox.exe -noconsole -c "mount c ./Masm" -c "c:" -c "masm out.asm;" -c "link out.obj;" -c "out.exe"