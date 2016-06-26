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
    sudo apt-get install mongodb-server

RUN sudo mkdir /data && \
    sudo mkdir /data/db

# Define working directory
WORKDIR /data
VOLUME /data

EXPOSE 27017

ENTRYPOINT ["/usr/bin/mongod"]
