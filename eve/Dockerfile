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

RUN sudo pip install eve

# Define working directory
WORKDIR /data
VOLUME /data

CMD["/bin/bash"]
