This is the complete repo for the MagicMirror final project for the Master Workshop at Fraunhofer FIT.
It contains all docker builds (so called Dockerfiles) as well as source code for receiving data (c++) and sending data (arduino).

*_trans are the different codes for each sensor type, we have bmp, dht and tsl.
Functioning Sender is a debug arduino application.

Base: Docker base image, everything builds up onto this
Sensor: Receive data from all 3 data types, uses RF24 lib
MongoDB: Data is stored here
Eve: Create a REST Api for the mongodb
Server: Apache server for displaying data
	Note: the display is made by Khanh

How To Build:
Install docker and build:
1) docker build -t tschemmer/base ./base/
2) docker build -t tschemmer/mongodb ./mongodb/
3) docker build -t tschemmer/sensor ./sensor/
4) docker build -t tschemmer/eve ./eve/
5) docker build -t tschemmer/server ./server/

Now with the included .sh files in this order:
1) sh ./mongodb/run.sh
   docker exec -ti mongodb 
   => sh adduser.sh

2) sh ./sensor/run.sh

3) sh ./eve/run.sh

4) docker run -ti tschemmer/server /bin/bash