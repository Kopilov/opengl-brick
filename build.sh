#!/bin/bash
git submodule update --init
mkdir -p build
cp *.gl *.mtl *.obj build
cd build

cmake .. -DASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT=NO \
         -DASSIMP_BUILD_OBJ_IMPORTER=YES \
         -DASSIMP_NO_EXPORT=YES \
         -DASSIMP_BUILD_TESTS=OFF \
         -DBUILD_SHARED_LIBS=OFF \
  && make -j5

cd -
