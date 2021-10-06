OBJS	= main_c.cpp.o \
	  CP2DG.cpp.o \
	  Main.cpp.o \
	  GUI.cpp.o \
	  AssetLoader.cpp.o \
	  InputHandler.cpp.o \
	  GameObjects/RenderObject.cpp.o \
	  GameObjects/FunctionalGameObject.cpp.o \
	  GameObjects/GameObject.cpp.o \
	  GameObjects/Sprite.cpp.o \
	  GameObjects/ShaderObject.cpp.o \
	  GameObjects/TextObject.cpp.o \
	  GameObjects/Shapes/Shape.cpp.o \
	  GameObjects/Shapes/Rectangle.cpp.o \
	  GameObjects/Shapes/Ellipse.cpp.o \
	  GameObjects/Shapes/Polygon.cpp.o \
	  GameObjects/Shapes/Arc.cpp.o \
	  GameObjects/MusicObject.cpp.o \
	  GameObjects/Attributes/Collidable.cpp.o \
	  GameObjects/ParticlesObject.cpp.o \
	  audio.c.o \
	  CppGen.cpp.o \
	  JsonLoader/JsonLoader.cpp.o \
	  JsonLoader/JsonLoaderDefaults.cpp.o \
	  JsonLoader/JsonLoaderDefs/JsonDefaultDefs.cpp.o \
	  JsonLoader/JsonLoaderDefs/JsonLdouble.cpp.o \
	  JsonLoader/JsonLoaderDefs/JsonLfloat.cpp.o \
	  JsonLoader/JsonLoaderDefs/JsonLint.cpp.o \
	  JsonLoader/JsonLoaderDefs/JsonLoadDef.cpp.o \
	  JsonLoader/JsonLoaderDefs/JsonLstd__pair_float_float_.cpp.o \
	  JsonLoader/JsonLoaderDefs/JsonLstd__pair_int_int_.cpp.o \
	  JsonLoader/JsonLoaderDefs/JsonLstd__string.cpp.o \
	  ArguementHandler/ArgHandle.cpp.o \
	  ArguementHandler/Arguement.cpp.o\
	  SimpleCppTextFileHandler/file.cpp.o\
	  SimpleCppTextFileHandler/fileManipulation.cpp.o \
	  SimpleCppTextFileHandler/getExecutablePath.cpp.o \
	  NFont/SDL_FontCache.c.o \
	  NFont/NFont.cpp.o \
	  flextGL.c.o \

OUT	= main
WIN_OUT = main.exe
SHARED  = main.so
WIN_SHARED = main.dll
CXX	= g++
WIN_CXX = x86_64-w64-mingw32-g++
CC      = gcc
WIN_CC  = x86_64-w64-mingw32-gcc
BUILD_CXX_FLAGS	 = -std=c++20 -fPIC
WIN_BUILD_CXX_FLAGS = -std=c++20 -fPIC -ILibraries/Win/include
BULID_CC_FLAGS   = -fPIC
WIN_BUILD_CC_FLAGS = -fPIC
LINK_OPTS	 = -lpthread -ldl -lSDL2 -lSDL2_gpu -lSDL2_ttf -lGL -ltbb
WIN_LINK_OPTS = -lpthread -ltbb_static -ldl -LLibraries/Win/lib -lopengl32 -l:OpenGL32.Lib -w -Wl,-subsystem,windows -lmingw32  -lSDL2main -lSDL2 -lSDL2.dll -lSDL2_gpu_s  -lSDL2_ttf -lfreetype -lbz2 -static -static-libgcc -static-libstdc++ -lhid -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -lglu32 -lopengl32 -fno-stack-protector -fstack-protector #kinda just threw a whole bunch here and hoped that it would be good enough
OS     = Linux

all: $(OBJS)
ifeq ($(OS), Linux)
	$(CXX) -g $(OBJS) -o $(OUT) $(LINK_OPTS)
	#$(AR) rvs $(LIB) $(OBJS)
	$(CXX) -shared -g -o $(SHARED) $(OBJS) $(BUILD_CXX_FLAGS) $(LINK_OPTS)
else
	$(WIN_CXX) -g -o $(WIN_OUT) $(OBJS) $(WIN_LINK_OPTS)
	#$(AR) rvs $(LIB) $(OBJS)
	$(WIN_CXX) -shared -g -o $(WIN_SHARED) $(OBJS) $(WIN_BUILD_CXX_FLAGS) $(WIN_LINK_OPTS)

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
	rm -f $(OBJS) $(OUT) $(SHARED)
	rm -f $(WIN_OUT) $(WIN_SHARED)
	rm -rf -f DllTemp

mingw:
	$(MAKE) OS=Win

mingwj:
	$(MAKE) OS=Win -j

