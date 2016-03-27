/**
 * 
 * @author		Halis Duraki <halis_duraki@outlook.com>
 * @project		vircar.c (Virtual car)
 * @package 	dn5/vircar@github
 * @website		http://dn5.ljuska.org
 *
 * This is a car. Yes, a virtual car connected on your 
 * machine. Please, do not drive fast, you may want to 
 * consult with your car dealer first.
 *
 * The future will bring:
 * 	- Revs
 * 	- Top speed / Current speed
 * 	- Error debug
 * 	- Chip & tuning
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>	

#include <linux/if_packet.h>
#include <linux/if_ether.h>	
#include <linux/can.h>		

#include "car.c" // The car requires some functions, right?!

#define  VIRCAR const

int print_head()
{
	printf("%s", "Welcome to vir(tual) car.\n");
	printf("%s", "~\n");
	printf("%s", "vircar is an open-source project\n");
	printf("%s", "coded by Halis Duraki as a solo \n");
	printf("%s", "paper on vehicle hacking and \n");
	printf("%s", "reverse engineering.\n");
	printf("%s", "=========================================\n");
	printf("%s", "https://github.com/dn5/vircar\n\n");
}

int create_car() 
{
	VIRCAR vircar = "vircar"; /* Use the const in future */

	/**
	 * Create a car, because no car is bad car.
	 * Also, who doesn't love cars?!
	 * 
	 * Use: $ sudo ip link delete vircar to remove
	 * your car. You can also send a KILL signal to
	 * the car and it will remove itself from the 
	 * protocol.
	 */

	print_head(); // Call info function

	system("modprobe vcan");
	system("sudo ip link add dev vircar type vcan");
	system("sudo ip link set up vircar");
}

int main(int argc, char *argv[])
{
	// Debug no args: printf("%d", argc);

	int 	s;							/* socket */
	struct 	can_frame frame;			/* frame  */
	int 	size, i;					/* data size */
	static 	struct ifreq ifr;			/* ifr as an instance*/
	static 	struct sockaddr_ll sl;		/* prefs */	
	char 	*instance = "vircar";		/* our virtual device */			
	int 	ifindex;					/* car socket # */											
	char 	current[8];					/* current operation received */

	if (argv[1] && strcmp(argv[1], "k") == 0) { /* kill using k argument */
		car_kill();
	}

	create_car();

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
			perror("read");
			return 1;
		} else if (size < sizeof(struct can_frame)) {
			fprintf(stderr, "CAN frame is wrong! Are you trying to hack me?!\n");
			return 1;
		} else {
			if (frame.can_id & CAN_EFF_FLAG)
				printf("%8X  ", frame.can_id & CAN_EFF_MASK); // 8 bytes
			else
				printf("%3X  ", frame.can_id & CAN_SFF_MASK); // SFF (3)
	    
			printf("[%d] ", frame.can_dlc);
			printf("[%s] ", frame.data);
			strcpy(current, frame.data);
			
			int len;
			len = frame.can_dlc;
					
			printf("%d", strlen(current)); 				/* Size of the data */

			// aka car_do_something();
			if (strcmp(current, "ENON") == 0) {
				car_start_engine();
			} else if (strcmp(current, "ENOF") == 0) {
				car_stop_engine();
			} else if (strcmp(current, "LOCK") == 0) {
				car_lock_doors();
			} else if (strcmp(current, "DOCK") == 0) {
				car_unlock_doors();
			} else if (strcmp(current, "KILL") == 0) {
				car_kill(); /* no you didn't */
			}


			for (i = 0; i < frame.can_dlc; i++) {
				// printf("%02X ", frame.data[i]); 		/* Print frame data */
			}

			if (frame.can_id & CAN_RTR_FLAG)
				printf("Request error, check your privs. Do you have a driving license?");
			printf("\n");
			fflush(stdout);
		}
	}

	close(s);

	return 0;

}