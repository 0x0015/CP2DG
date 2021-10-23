OBJS	= src/main_c.cpp.o \
	  src/CP2DG.cpp.o \
	  src/Main.cpp.o \
	  src/GUI.cpp.o \
	  src/AssetLoader.cpp.o \
	  src/InputHandler.cpp.o \
	  src/GameObjects/RenderObject.cpp.o \
	  src/GameObjects/FunctionalGameObject.cpp.o \
	  src/GameObjects/GameObject.cpp.o \
	  src/GameObjects/Sprite.cpp.o \
	  src/GameObjects/ShaderObject.cpp.o \
	  src/GameObjects/TextObject.cpp.o \
	  src/GameObjects/Shapes/Shape.cpp.o \
	  src/GameObjects/Shapes/Rectangle.cpp.o \
	  src/GameObjects/Shapes/Ellipse.cpp.o \
	  src/GameObjects/Shapes/Polygon.cpp.o \
	  src/GameObjects/Shapes/Arc.cpp.o \
	  src/GameObjects/MusicObject.cpp.o \
	  src/GameObjects/Attributes/Collidable.cpp.o \
	  src/GameObjects/ParticlesObject.cpp.o \
	  src/audio.c.o \
	  src/ComputeShader.cpp.o \
	  src/JsonLoader/JsonLoader.cpp.o \
	  src/JsonLoader/JsonLoaderDefaults.cpp.o \
	  src/JsonLoader/JsonLoaderDefs/JsonDefaultDefs.cpp.o \
	  src/JsonLoader/JsonLoaderDefs/JsonLdouble.cpp.o \
	  src/JsonLoader/JsonLoaderDefs/JsonLfloat.cpp.o \
	  src/JsonLoader/JsonLoaderDefs/JsonLint.cpp.o \
	  src/JsonLoader/JsonLoaderDefs/JsonLoadDef.cpp.o \
	  src/JsonLoader/JsonLoaderDefs/JsonLstd__pair_float_float_.cpp.o \
	  src/JsonLoader/JsonLoaderDefs/JsonLstd__pair_int_int_.cpp.o \
	  src/JsonLoader/JsonLoaderDefs/JsonLstd__string.cpp.o \
	  src/RuntimeLoader/RuntimeLoader.cpp.o \
	  src/RuntimeLoader/zip.cpp.o \
	  src/ArguementHandler/ArgHandle.cpp.o \
	  src/ArguementHandler/Arguement.cpp.o\
	  src/SimpleCppTextFileHandler/file.cpp.o\
	  src/SimpleCppTextFileHandler/fileManipulation.cpp.o \
	  src/SimpleCppTextFileHandler/getExecutablePath.cpp.o \
	  src/NFont/SDL_FontCache.c.o \
	  src/NFont/NFont.cpp.o \
	  src/flextGL.c.o \

OUT	= bin/main
WIN_OUT = bin/main.exe
SHARED  = bin/main.so
WIN_SHARED = bin/main.dll
CXX	= g++
WIN_CXX = x86_64-w64-mingw32-g++
CC      = gcc
WIN_CC  = x86_64-w64-mingw32-gcc
BUILD_CXX_FLAGS	 = -std=c++20 -fPIC -Iinclude
WIN_BUILD_CXX_FLAGS = -std=c++20 -fPIC -ILibraries/Win/include -Iinclude
BULID_CC_FLAGS   = -fPIC
WIN_BUILD_CC_FLAGS = -fPIC
LINK_OPTS	 = -lpthread -ldl -lSDL2 -lSDL2_gpu -lSDL2_ttf -lGL -ltbb -lzip
WIN_LINK_OPTS = -lpthread -ltbb_static -ldl -LLibraries/Win/lib -lopengl32 -l:OpenGL32.Lib -w -Wl,-subsystem,windows -lmingw32  -lSDL2main -lSDL2 -lSDL2.dll -lSDL2_gpu_s  -lSDL2_ttf -lfreetype -lbz2 -lzip -static -static-libgcc -static-libstdc++ -lhid -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -lglu32 -lopengl32 -fno-stack-protector -fstack-protector #kinda just threw a whole bunch here and hoped that it would be good enough
OS     = Linux

all: $(OBJS)
	mkdir -p bin
ifeq ($(OS), Linux)
	$(CXX) -g $(OBJS) -o $(OUT) $(LINK_OPTS)
	#$(AR) rvs $(LIB) $(OBJS)
	$(CXX) -shared -g -o $(SHARED) $(OBJS) $(BUILD_CXX_FLAGS) $(LINK_OPTS)
else
	$(WIN_CXX) -g -o $(WIN_OUT) $(OBJS) $(WIN_LINK_OPTS)
	#$(AR) rvs $(LIB) $(OBJS)
	$(WIN_CXX) -shared -g -o $(WIN_SHARED) $(OBJS) $(WIN_BUILD_CXX_FLAGS) $(WIN_LINK_OPTS)
endif
	cp -R Content bin/Content
	cp -R include bin/include


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
	rm -f $(OBJS) $(OUT) $(SHARED)
	rm -f $(WIN_OUT) $(WIN_SHARED)
	rm -rf -f DllTemp
	rm -rf -f bin

mingw:
	$(MAKE) OS=Win

mingwj:
	$(MAKE) OS=Win -j

