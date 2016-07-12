FROM tschemmer/base
MAINTAINER Thomas Schemmer

RUN sudo pip install eve

# Define working directory
WORKDIR /data
VOLUME /data

COPY settings.py /eve/settings.py

EXPOSE 5000