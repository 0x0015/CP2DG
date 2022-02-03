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
	  src/JsonLoader/JsonLoaderDefs/JsonLstd__vector_std__shared_ptr_GameObject__.cpp.o \
	  src/ArguementHandler/ArgHandle.cpp.o \
	  src/ArguementHandler/Arguement.cpp.o\
	  src/SimpleCppTextFileHandler/file.cpp.o\
	  src/SimpleCppTextFileHandler/fileManipulation.cpp.o \
	  src/SimpleCppTextFileHandler/getExecutablePath.cpp.o \
	  src/NFont/SDL_FontCache.c.o \
	  src/NFont/NFont.cpp.o \
	  src/flextGL.c.o 
RUNTIMELOADER_OBJS = src/RuntimeLoader/RuntimeLoader.cpp.o \
	  src/RuntimeLoader/zip.cpp.o 

OUT	= bin/main.exe
SHARED  = bin/main.dll
CXX	= x86_64-w64-mingw32-g++
CC      = x86_64-w64-mingw32-gcc
BUILD_CXX_FLAGS	 = -Wall -std=c++20 -fPIC -ILibraries/Win/include -Iinclude
BULID_CC_FLAGS   = -fPIC
LINK_OPTS	 = -lpthread -ltbb_static -ldl -LLibraries/Win/lib -lopengl32 -l:OpenGL32.Lib -w -Wl,-subsystem,windows -lmingw32  -lSDL2main -lSDL2 -lSDL2.dll -lSDL2_gpu_s  -lSDL2_ttf -lfreetype -lbz2 -lzip.dll -static -static-libgcc -static-libstdc++ -lhid -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lsetupapi -lversion -luuid -lglu32 -lopengl32 -fno-stack-protector -fstack-protector

all: $(OBJS) $(RUNTIMELOADER_OBJS)
	mkdir -p bin
	$(CXX) -g $(OBJS) $(RUNTIMELOADER_OBJS) -o $(OUT) $(LINK_OPTS)
	#$(AR) rvs $(LIB) $(OBJS)
	$(CXX) -shared -g -o $(SHARED) $(OBJS) $(RUNTIMELOADER_OBJS) $(BUILD_CXX_FLAGS) $(LINK_OPTS)
	cp -a Content/. bin/Content/
	cp -a include/. bin/include/


%.cpp.o: %.cpp
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_OPTS) -g -c -o $@

%.c.o: %.c
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_OPTS) -g -c -o $@

clean:
	rm -f $(OBJS) $(OUT) $(RUNTIMELOADER_OBJS) $(SHARED)
	rm -rf -f DllTemp
	rm -rf -f bin
