FROM tschemmer/base
MAINTAINER Thomas Schemmer

#install mongodb c driver

RUN wget https://github.com/mongodb/mongo-c-driver/releases/download/1.3.5/mongo-c-driver-1.3.5.tar.gz && \
    tar xzf mongo-c-driver-1.3.5.tar.gz && \
    cd mongo-c-driver-1.3.5 && \
    ./configure && \
    make && \
    sudo make install
	

#install rf24 lib
COPY ./install.sh /data

RUN cd /data && \
    chmod +x install.sh  && \
    sudo ./install.sh 


# build the ./rbpi
COPY ./rbpi.cpp /data

RUN cp -r /usr/local/lib/* /usr/lib/ && \
    cp -r /usr/local/include/lib* /usr/include/ && \
    g++ -I/usr/local/include/libbson-1.0 -I/usr/local/include/libmongoc-1.0 -lmongoc-1.0 -lbson-1.0 -I/usr/include -I/usr/include/c++/4.9/ -IRaspberry/librf24/rf24libs/RF24/ -L../librf24/ -lrf24 -o rbpi rbpi.cpp



# Define working directory
WORKDIR /data

CMD ["/bin/bash"]
