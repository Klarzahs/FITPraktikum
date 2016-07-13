FROM tschemmer/base
MAINTAINER Thomas Schemmer

RUN sudo pip install eve

RUN mkdir /eve

COPY settings.py /eve/settings.py
COPY run.py /eve/run.py

# Define working directory
WORKDIR /data
VOLUME /data


EXPOSE 5000

CMD ["python","/eve/run.py"]