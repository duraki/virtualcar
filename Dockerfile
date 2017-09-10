FROM ubuntu:17.04
MAINTAINER Halis Duraki <duraki@linuxmail.org>

ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update && apt-get install -y apt-transport-https
RUN sudo apt-get install -y git net-tools vim gcc build-essential libncurses-dev make wget git iproute

#RUN modprobe vcan
#RUN ip link add dev vcan0 type vcan
#RUN ip link set up vcan0

# Set default command
CMD ["/bin/bash"]

