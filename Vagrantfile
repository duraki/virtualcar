# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
    
  # Using Centos 7 since the kernel includes SocketCAN drivers
  config.vm.box = "centos/7"

  # Share current directory and sync the data
  config.vm.synced_folder ".", "/virtualcar"

  config.vm.provider "virtualbox" do |vb|

      # Customize the amount of memory on the VM:
      vb.memory = "2048"
      
  end

  # Configure neccessary development and testing environment
  
  # + Devtools provision
  config.vm.provision :shell, path: "./provision/dev.sh"

  # + Show readme
  config.vm.provision :shell, inline: "cat /virtualcar/README.md", run:
  "always"

  # + Compile
  config.vm.provision :shell, inline: "cd /virtualcar && make"

end
