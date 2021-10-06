all:
	g++ main.cpp tinyfiledialogs/tinyfiledialogs.c -o main -lSDL2 -lSDL2_image -g
clean:
	rm main
win:
	x86_64-w64-mingw32-g++ main.cpp tinyfiledialogs/tinyfiledialogs.c -g -o main.exe -lSDL2 -lSDL2_image -Wl,-subsystem,windows -municode -lcomctl32 -Wl,-emain -lComdlg32.lib -lOle32.lib
clean_win:
	rm main.exe
