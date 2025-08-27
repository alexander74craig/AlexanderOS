FROM ubuntu:24.04

RUN DEBIAN_FRONTEND="noninteractive" apt-get update && apt-get -y install tzdata

RUN apt update && \
    apt install -y \
        cmake \
        make \
        git \
        build-essential \
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
        mtools \
        grub-pc-bin \
        gdb

RUN mkdir /build \
    && cd /build \
    && git clone --depth 1 --branch binutils-2_45 git://sourceware.org/git/binutils-gdb.git \
    && git clone --depth 1 --branch releases/gcc-15.2.0 git://gcc.gnu.org/git/gcc.git

RUN mkdir /build/binutils-build \
    && cd /build/binutils-build \
    && /build/binutils-gdb/configure --target="i686-elf" --prefix="/build/cross" --with-sysroot --disable-nls \
    && make -j $(nproc) \
    && make -j $(nproc) install

RUN mkdir /build/gcc-build \
    && cd /build/gcc-build \
    && /build/gcc/configure --target="i686-elf" --prefix="/build/cross" --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx  \
    && make -j $(nproc) all-gcc \
    && make -j $(nproc) all-target-libgcc \
    && make -j $(nproc) all-target-libstdc++-v3 \
    && make -j $(nproc) install-gcc \
    && make -j $(nproc) install-target-libgcc \
    && make -j $(nproc) install-target-libstdc++-v3

RUN mkdir /build/binutils-build-64 \
    && cd /build/binutils-build-64 \
    && /build/binutils-gdb/configure --target="x86_64-elf" --prefix="/build/cross" --with-sysroot --disable-nls \
    && make -j $(nproc) \
    && make -j $(nproc) install

RUN mkdir /build/gcc-build-64 \
    && cd /build/gcc-build-64 \
    && /build/gcc/configure --target="x86_64-elf" --prefix="/build/cross" --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx  \
    && make -j $(nproc) all-gcc \
    && make -j $(nproc) all-target-libgcc \
    && make -j $(nproc) all-target-libstdc++-v3 \
    && make -j $(nproc) install-gcc \
    && make -j $(nproc) install-target-libgcc \
    && make -j $(nproc) install-target-libstdc++-v3
