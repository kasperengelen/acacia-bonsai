FROM debian:trixie

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y wget cmake autoconf time python3-dev gpg

## Add the LRDE key for SPOT 
RUN     mkdir -p /etc/apt/keyrings && \
        wget https://www.lrde.epita.fr/repo/debian.gpg && \
        gpg --no-default-keyring --keyring ./tmp-kr.gpg --import debian.gpg && \
        gpg --no-default-keyring --keyring ./tmp-kr.gpg --export --output /etc/apt/keyrings/lrde.gpg && \
        rm tmp-kr.gpg && \
        echo 'deb [signed-by=/etc/apt/keyrings/lrde.gpg] http://www.lrde.epita.fr/repo/debian/ stable/' >> /etc/apt/sources.list

RUN apt-get update && \
    apt-get install -y spot libspot-dev spot-doc

COPY binaries/* /usr/bin/

RUN apt-get install -y zsh meson git gcc python-is-python3 \
                    ninja-build gnupg wget python3-pip \
                    pkg-config libglib2.0-dev libffi-dev libboost-dev \
                    autoconf automake libtool bison flex valgrind

RUN git clone --recurse-submodules https://github.com/gaperez64/acacia-bonsai

RUN cd acacia-bonsai && \
    ./self-benchmark.sh -f -b ab/syntcomp21/0s-20s -t 1

ENTRYPOINT ["/bin/bash"]
