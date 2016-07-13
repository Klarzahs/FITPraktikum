FROM tschemmer/base
MAINTAINER Thomas Schemmer

#install apache server
#https://medium.com/dev-tricks/apache-and-php-on-docker-44faef716150#.fqgne5p0t

RUN sudo apt-get update && sudo apt-get upgrade && \
    EBIAN_FRONTEND=noninteractive apt-get -y install apache2

# Enable apache mods.
RUN a2enmod rewrite

# Manually set up the apache environment variables
ENV APACHE_RUN_USER www-data
ENV APACHE_RUN_GROUP www-data
ENV APACHE_LOG_DIR /var/log/apache2
ENV APACHE_LOCK_DIR /var/lock/apache2
ENV APACHE_PID_FILE /var/run/apache2.pid

COPY display /var/www/

# Expose apache.
EXPOSE 80

# By default start up apache in the foreground, override with /bin/bash for interative.
CMD /usr/sbin/apache2ctl -D FOREGROUND
