FROM ubuntu:24.04

RUN DEBIAN_FRONTEND="noninteractive" apt-get update && apt-get -y install tzdata

RUN apt update && \
    apt install -y \
        cmake \
        make \
        git \
        build-essential\
        bison\
        flex\
        libgmp3-dev\
        libmpc-dev\
        libmpfr-dev\
        texinfo\
        libisl-dev \
        qemu-system

RUN cd $HOME \
    && git clone --depth 1 --branch binutils-2_45 git://sourceware.org/git/binutils-gdb.git \
    && git clone --depth 1 --branch releases/gcc-15.2.0 git://gcc.gnu.org/git/gcc.git

RUN mkdir $HOME/binutils-build \
    && cd $HOME/binutils-build \
    && $HOME/binutils-gdb/configure --target="i686-elf" --prefix="$HOME/cross" --with-sysroot --disable-nls \
    && make \
    && make install

RUN mkdir $HOME/gcc-build \
    && cd $HOME/gcc-build \
    && $HOME/gcc/configure --target="i686-elf" --prefix="$HOME/cross" --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx  \
    && make all-gcc \
    && make all-target-libgcc \
    && make all-target-libstdc++-v3 \
    && make install-gcc \
    && make install-target-libgcc \
    && make install-target-libstdc++-v3

RUN apt update && apt install -y grub-efi-amd64 xorriso mtools