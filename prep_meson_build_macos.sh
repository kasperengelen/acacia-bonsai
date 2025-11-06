#! /bin/zsh

export CXX="/opt/homebrew/bin/g++-15"
export CC="/opt/homebrew/bin/gcc-15"
export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:/opt/homebrew/Cellar/boost/1.89.0/include
export LIBRARY_PATH=$LIBRARY_PATH:/opt/homebrew/Cellar/boost/1.89.0/lib

meson setup builddir
