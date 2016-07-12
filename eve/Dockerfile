FROM tschemmer/base
MAINTAINER Thomas Schemmer

RUN sudo pip install eve

RUN sudo apt-get update && \
    sudo apt-get upgrade && \
    sudo apt-get install nodejs

# Define working directory
WORKDIR /data
VOLUME /data

COPY settings.py /eve/settings.py

EXPOSE 5000
