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
        qemu-system \
        grub-efi-amd64 \
        xorriso \
        mtools

RUN mkdir /build

RUN cd /build \
    && git clone --depth 1 --branch binutils-2_45 git://sourceware.org/git/binutils-gdb.git \
    && git clone --depth 1 --branch releases/gcc-15.2.0 git://gcc.gnu.org/git/gcc.git

RUN mkdir /build/binutils-build \
    && cd /build/binutils-build \
    && /build/binutils-gdb/configure --target="i686-elf" --prefix="/build/cross" --with-sysroot --disable-nls \
    && make \
    && make install

RUN mkdir /build/gcc-build \
    && cd /build/gcc-build \
    && /build/gcc/configure --target="i686-elf" --prefix="/build/cross" --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx  \
    && make all-gcc \
    && make all-target-libgcc \
    && make all-target-libstdc++-v3 \
    && make install-gcc \
    && make install-target-libgcc \
    && make install-target-libstdc++-v3


RUN apt update && \
    apt install -y grub-pc-bin