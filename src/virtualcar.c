/**
 *
 *  This file is part of virtualcar.
 *
 *  virtualcar is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3 of the License.
 *
 *  virtualcar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with virtualcar.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  virtualcar is a vehicle computer-powered system engine written in C to 
 *  help you research and learn more about vehicle devices and CAN protocol.
 *  This project represents a central unit or the CAN Bus, along with several
 *  different nodes that transmit and analyze signals.
 *
 *  The purpose of this code and the project is to replace paid alternatives
 *  and allow others to learn more about vehicle embedded systems.
 *
 *  The project is developed in C and it's based on a SocketCAN which is 
 *  available in any modern Linux kernel.
 *
 *  (c) Halis Duraki <duraki.halis@nsoft.ba>
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>	

#include <linux/if_packet.h>
#include <linux/if_ether.h>	
#include <linux/can.h>		

#include "include/nodes/controller.c"

#include "car.c"
#include "bus.c"

unsigned char virtualcar_intro[] = {
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5f, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x5f, 0x5f, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5f, 0x5f, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x0a, 0x20, 0x5f, 0x20, 0x20, 0x20, 0x5f, 0x5f, 0x28, 0x5f, 0x29, 0x5f,
  0x5f, 0x5f, 0x5f, 0x2f, 0x20, 0x2f, 0x5f, 0x5f, 0x5f, 0x20, 0x20, 0x5f,
  0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x20, 0x5f, 0x2f, 0x20, 0x2f, 0x5f, 0x5f,
  0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x20, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f,
  0x5f, 0x0a, 0x7c, 0x20, 0x7c, 0x20, 0x2f, 0x20, 0x2f, 0x20, 0x2f, 0x20,
  0x5f, 0x5f, 0x5f, 0x2f, 0x20, 0x5f, 0x5f, 0x2f, 0x20, 0x2f, 0x20, 0x2f,
  0x20, 0x2f, 0x20, 0x5f, 0x5f, 0x20, 0x60, 0x2f, 0x20, 0x2f, 0x20, 0x5f,
  0x5f, 0x5f, 0x2f, 0x20, 0x5f, 0x5f, 0x20, 0x60, 0x2f, 0x20, 0x5f, 0x5f,
  0x5f, 0x2f, 0x0a, 0x7c, 0x20, 0x7c, 0x2f, 0x20, 0x2f, 0x20, 0x2f, 0x20,
  0x2f, 0x20, 0x20, 0x2f, 0x20, 0x2f, 0x5f, 0x2f, 0x20, 0x2f, 0x5f, 0x2f,
  0x20, 0x2f, 0x20, 0x2f, 0x5f, 0x2f, 0x20, 0x2f, 0x20, 0x2f, 0x20, 0x2f,
  0x5f, 0x5f, 0x2f, 0x20, 0x2f, 0x5f, 0x2f, 0x20, 0x2f, 0x20, 0x2f, 0x20,
  0x20, 0x20, 0x20, 0x0a, 0x7c, 0x5f, 0x5f, 0x5f, 0x2f, 0x5f, 0x2f, 0x5f,
  0x2f, 0x20, 0x20, 0x20, 0x5c, 0x5f, 0x5f, 0x2f, 0x5c, 0x5f, 0x5f, 0x2c,
  0x5f, 0x2f, 0x5c, 0x5f, 0x5f, 0x2c, 0x5f, 0x2f, 0x5f, 0x2f, 0x5c, 0x5f,
  0x5f, 0x5f, 0x2f, 0x5c, 0x5f, 0x5f, 0x2c, 0x5f, 0x2f, 0x5f, 0x2f, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20
};

pthread_t ntpump;

void print_head()
{
	printf("\n%s\n", virtualcar_intro);
	printf("%s", "virtualcar is a CAN-based wrapper written in C, that acts as a virtual car.\n");
	printf("%s", "The core is listening to the virtual CAN device and parse, analyze and transmit\n");
	printf("%s", "signal from nodes to nodes, or in other way manipulate with the request.\n\n");
	printf("%s", "This software is licensed under GNU General Public V3 license. The project is\n");
	printf("%s", "developed on top of SocketCAN module and therefore requires Linux based system.\n");
	printf("%s", "--\n\n");
	printf("%s", "https://github.com/dn5/virtualcar\n");
    printf("%s", "Halis Duraki / @dn5 / <duraki.halis@nsoft.ba>\n\n");
}

/** Create a virtual CAN device that acts as a vehicle CANBus */
void create_car() 
{
	const char *virtualcar = "virtualcar"; /* Use the const in future */

	print_head(); // Call info function

	system("modprobe vcan");
	system("sudo ip link add dev virtualcar type vcan");
	system("sudo ip link set up virtualcar");
}

int main(int argc, char *argv[])
{

	int 	s;							/* socket */
	struct 	can_frame frame;			/* frame  */
	int 	size, i;					/* data size */
	static 	struct ifreq ifr;			/* ifr as an instance*/
	static 	struct sockaddr_ll sl;		/* prefs */	
	char 	*instance = "virtualcar";	/* our virtual device */			
	int 	ifindex;					/* car socket # */											
	char 	current[8];					/* current operation received */
	int 	tid;						/* thread id */

	if (argv[1] && strcmp(argv[1], "k") == 0) { 
		/* kill using k argument */
		car_kill();
	}

	/** Bring up main controller and gateway */
	create_car();

	/** Check thread */
	tid = pthread_create(&(ntpump), NULL, &check_pump_flow, NULL);

	if (tid != 0)
		printf("\ncan't create thread :[%s]", strerror(tid));
	else
		printf("\nThread created successfully\n");

	s = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_CAN));
	if (s < 0) {
		// Can't connect to socket?!
		perror("socket");
		//return 1;
	}

	if (strcmp(instance, "any") == 0)
		ifindex = 0; // Debug; listen to index 0
	else {
		strcpy(ifr.ifr_name, instance);
		ioctl(s, SIOCGIFINDEX, &ifr);
		ifindex = ifr.ifr_ifindex;
	}

	sl.sll_family = AF_PACKET;
	sl.sll_ifindex = ifindex;
	sl.sll_protocol = htons(ETH_P_CAN);

	if (bind(s, (struct sockaddr *)&sl, sizeof(sl)) < 0) {
		perror("bind"); // please avoid!
		return 1;
	}

	while (1) {

		if ((size = read(s, &frame, sizeof(struct can_frame))) < 0) {
			// invalid frame
			perror("read");
			return 1;
		} else if (size < sizeof(struct can_frame)) {
			// invalid frame
			fprintf(stderr, "CAN frame is wrong! Are you trying to hack me?!\n");
			return 1;
		} else {
			if (frame.can_id & CAN_EFF_FLAG)
				printf("%8X  ", frame.can_id & CAN_EFF_MASK); // 8 bytes
				can_accept_signal(&frame);
			if (frame.can_id & CAN_RTR_FLAG)
				printf("%8X  ", frame.can_id & CAN_EFF_MASK); // 8 bytes
				can_accept_signal_rtr(&frame);

			printf("%3X  ", frame.can_id & CAN_SFF_MASK); // SFF (3)
	    
			printf("[%d] ", frame.can_dlc);
			printf("[%8X] ", frame.can_id);
			strcpy(current, frame.data);
			
			int len;
			len = frame.can_dlc;
					
			printf("%zu", strlen(current)); 	        /* Size of the data */

			for (i = 0; i < frame.can_dlc; i++) {
				printf("%02X ", frame.data[i]); 		/* Print frame data */
			}

			fflush(stdout);
		}
	}

	close(s);

	return 0;

}
