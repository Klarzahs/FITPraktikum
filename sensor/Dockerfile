FROM resin/rpi-raspbian:jessie
MAINTAINER Thomas Schemmer

# Install dependencies
RUN apt-get update && apt-get install -y \
    git-core \
    build-essential \
    gcc \
    g++ \
    make \
    vim \
    wget \
    python \
    python-dev \
    python-pip \
    python-virtualenv \
    --no-install-recommends && \
    rm -rf /var/lib/apt/lists/*

RUN sudo apt-get update && \
    sudo apt-get upgrade && \
    sudo apt-get install pkg-config

RUN wget https://github.com/mongodb/mongo-c-driver/releases/download/1.3.5/mongo-c-driver-1.3.5.tar.gz && \
    tar xzf mongo-c-driver-1.3.5.tar.gz && \
    cd mongo-c-driver-1.3.5 && \
    ./configure && \
    make && \
    sudo make install

# Define working directory
WORKDIR /data
VOLUME /data

CMD ["/bin/bash"]
