#!/bin/sh
JOBS=$1
# docker run -itd --name=llvm --net=host -v`pwd`:/data0 -w /data0 ubuntu:18.04 bash
# 准备环境：
# apt-get update
# apt-get install -y git vim build-essential gcc-6 g++-6 cmake swig python-swiglpk libxml2 libxml2-dev libncurses5 libncurses5-dev libedit-dev libpython-dev

# git clone https://github.com/llvm/llvm-project.git
# git clone --depth 1 https://github.com/llvm-mirror/llvm llvm 
# git clone --depth 1 https://github.com/llvm-mirror/clang llvm/tools/clang 
# git clone --depth 1 https://github.com/llvm-mirror/clang-tools-extra llvm/tools/clang/tools/extra 
# git clone --depth 1 https://github.com/llvm-mirror/compiler-rt llvm/projects/compiler-rt 
# git clone --depth 1 https://github.com/llvm-mirror/libcxx llvm/projects/libcxx 
# git clone --depth 1 https://github.com/llvm-mirror/libcxxabi llvm/projects/libcxxabi 
# git clone --depth 1 https://github.com/llvm-mirror/lld llvm/tools/lld


# mkdir build
cd build
# cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/opt/llvm ../llvm
# cmake -G "Unix Makefiles" -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE="Debug" -DCMAKE_INSTALL_PREFIX=/opt/llvm ../llvm-project/llvm/
# cmake -G "Unix Makefiles" -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE="Release" -DCMAKE_INSTALL_PREFIX=/opt/llvm ../llvm-project/llvm/
# cmake -G "Unix Makefiles" -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE="Release" -DLLVM_BUILD_EXAMPLES=ON -DCLANG_BUILD_EXAMPLES=ON -DCMAKE_INSTALL_PREFIX=/opt/llvm ../llvm-project/llvm/

make -j $JOBS 1>>../clangBuild.log 2>>../clangBuildError.log
# 测试：
# make check-llvm-unit 1>>../clangBuild.log 2>>../clangBuildError.log
# make check-llvm 1>>../clangBuild.log 2>>../clangBuildError.log
# make check-clang-unit 1>>../clangBuild.log 2>>../clangBuildError.log
# make check-clang 1>>../clangBuild.log 2>>../clangBuildError.log

make check-all 1>>../clangBuild.log 2>>../clangBuildError.log

make install 1>>../clangBuild.log 2>>../clangBuildError.log