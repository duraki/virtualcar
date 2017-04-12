#!/usr/bin/env bash

# Install git
sudo yum -y install git 

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

