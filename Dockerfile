FROM debian:latest

MAINTAINER Julian Caba <julian.caba@uclm.es>

WORKDIR /test
VOLUME /opt

RUN apt-get update && apt-get install -y make libx11-6 libc6-dev python3.4 python3-jinja2 python3-zeroc-ice

COPY src /test/src
COPY run.sh /test
COPY tests /test/tests

