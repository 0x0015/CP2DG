OBJS	= main.cpp.o \
	  ArguementHandler/ArgHandle.cpp.o \
	  ArguementHandler/Arguement.cpp.o\
	  SimpleCppTextFileHandler/file.cpp.o\
	  SimpleCppTextFileHandler/fileManipulation.cpp.o \
	  SimpleCppTextFileHandler/getExecutablePath.cpp.o \

OUT	= main
WIN_OUT = main.exe
CXX	= g++
WIN_CXX = x86_64-w64-mingw32-g++
CC      = gcc
WIN_CC  = x86_64-w64-mingw32-gcc
BUILD_CXX_FLAGS	 = -std=c++20 -fPIC
WIN_BUILD_CXX_FLAGS = -std=c++20 -fPIC -ILibraries/Win/include
BULID_CC_FLAGS   = -fPIC
WIN_BUILD_CC_FLAGS = -fPIC
LINK_OPTS	 = -lpthread -ldl
WIN_LINK_OPTS = -lpthread -ltbb_static -ldl -LLibraries/Win/lib -lopengl32 -l:OpenGL32.Lib -w -Wl,-subsystem,windows -lmingw32  -lSDL2main -lSDL2 -lSDL2.dll -lSDL2_gpu_s  -lSDL2_ttf -lfreetype -lbz2 -lzip -static -static-libgcc -static-libstdc++ -lhid -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -lglu32 -lopengl32 -fno-stack-protector -fstack-protector #kinda just threw a whole bunch here and hoped that it would be good enough
OS     = Linux

all: $(OBJS)
ifeq ($(OS), Linux)
	$(CXX) -g $(OBJS) -o $(OUT) $(LINK_OPTS)
else
	$(WIN_CXX) -g -o $(WIN_OUT) $(OBJS) $(WIN_LINK_OPTS)
endif


%.cpp.o: %.cpp
ifeq ($(OS), Linux)
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_OPTS) -g -c -o $@
else
	$(WIN_CXX) $< $(WIN_BUILD_CXX_FLAGS) $(WIN_LINK_OPTS) -g -c -o $@
endif

%.c.o: %.c
ifeq ($(OS), Linux)
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_OPTS) -g -c -o $@
else
	$(WIN_CXX) $< $(WIN_BUILD_CXX_FLAGS) $(WIN_LINK_OPTS) -g -c -o $@
endif

clean:
	rm -f $(OBJS) $(OUT) $(WIN_OUT)

mingw:
	$(MAKE) OS=Win

mingwj:
	$(MAKE) OS=Win -j

