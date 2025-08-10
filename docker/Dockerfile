FROM ubuntu:24.04

RUN DEBIAN_FRONTEND="noninteractive" apt-get update && apt-get -y install tzdata

RUN apt update && \
    apt install -y \
        cmake \
        make

