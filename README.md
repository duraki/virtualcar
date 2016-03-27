## vircar
**vircar** (**vir**tual-**car**) is a car written in C that opens a CAN Bus network on your computer and register operations that should be sent to the ECU, just like a real car. This software is licensed under GNU General Public V3 license. Please, keep the software open source and contribute to the project if you want. It works over CAN interface that linux kernel have in itself. I wrote this software for educational and pro-bon purpose only.  
  
## a car? really?
Yes! A fully, functional car. Well, not really no. It does represent a car but in a limited spirit and form. I was writing a post about [cyber-attacks](http://dn5.ljuska.org/napadi-na-auto-sistem-1.html) on a vehicle systems and didn't have necessary (hardware) equipment to test security, so I wrote a script to let me test and experiment with a fuzzing technique on a virtual car. You may want to implement other functions and options which you can do over **car.c** file.  
  
## functionality
Currently, **vircar** offers several operations that are registered at ECU. These are: **ENON** (Engine on), **ENOF** (Engine off), **LOCK** (Lock doors), **DOCK** (Unlock doors), and **KILL** (destroy the car, remove virtual bus). As I said, you may want to implement other functions in the car, so be free to tune it however you like it. Also, if you've made a NOS or something cool make a pull request, I would be glad to see contributors to the project.  
  
## requirements
I love to write pure native scripts. The only requirement for now is that you are running under **GNU Linux** and have **can-utils** installed on your system.  

* gcc
* linux kernel (can.h)
* can-utils
  
## compile & running

To clone the repo and compile it from source: 

	$ git clone https://github.com/dn5/vircar.git
	$ cd vircar
	$ sudo ./make
	$ chmod 777 vircar

To run vircar use or appropriate sudo (need to create a car)	

	$ ./vircar
	Welcome to vir(tual) car.
	~
	vircar is an open-source project
	coded by Halis Duraki as a solo 
	paper on vehicle hacking and 
	reverse engineering.
	=========================================
	https://github.com/dn5/vircar

	# waiting for operation

To **exit** vircar use Ctrl+C.  
To **kill** a car and remove protocol use:
	
	$ ./vircar k
	ka-boom, pfw, aaa, ts
	*car exploded*

## outro
If you are interested in car hacking, write me on [twitter](https://twitter.com/dn5__). Any additional options and ECU operations shall me transfered to pull requests. Please, keep the code and project with clean lines of code. Ugly code won't be commited to master. I would like to thank my family and supporters who have been there when I need them and who could continue to live with me without killing me :-).  