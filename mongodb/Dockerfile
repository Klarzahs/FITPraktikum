FROM tschemmer/base
MAINTAINER Thomas Schemmer

RUN sudo apt-get update && \
    sudo apt-get upgrade && \
    sudo apt-get install mongodb-server

RUN sudo mkdir /data && \
    sudo mkdir /data/db

RUN echo 'db.addUser("<username>", "<password>");' | mongo weather_station

# Define working directory
WORKDIR /data
VOLUME /data

EXPOSE 27017

ENTRYPOINT ["/usr/bin/mongod"]
