#!/usr/bin/env bash

# Install git & wget
sudo yum -y install git 
sudo yum -y install wget

# Install figlet
sudo rpm -Uvh https://dl.fedoraproject.org/pub/epel/epel-release-latest-6.noarch.rpm
wget http://ftp.altlinux.org/pub/distributions/ALTLinux/Sisyphus/x86_64/RPMS.classic//figlet-2.2.5-alt1.x86_64.rpm
sudo rpm -Uvh figlet-2.2.5-alt1.x86_64.rpm

# Add bash startup script
echo figlet "virtualcar" -f smslant >> /home/vagrant/.bashrc


# Install latest Ruby 2.0.0> supported
sudo yum -y install ruby

# Install ifconfig and such natives
sudo yum -y install net-tools

# Install devtool group
sudo yum -y group install "Development Tools"

# ripl is cool
sudo gem install ripl

# terminal table
sudo gem install terminal-table

# clone can-utils
git clone https://github.com/linux-can/can-utils

# compile can-utils
cd can-utils && make

# copy all elfs to /usr/bin 
for i in `find -type f`; do [ -x $i ] && echo "$i is can-utils executable;
 moving the copy " && sudo cp $i /usr/bin/; done

