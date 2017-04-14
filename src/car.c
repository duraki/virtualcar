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

#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "include/lib.h"

#define randnum(min, max) \
        ((rand() % (int)(((max) + 1) - (min))) + (min))

#define	VIRTUALCAR "virtualcar"

int can_gateway_check_mtu(struct ifreq *ifr)
{
	if (ifr->ifr_mtu != CANFD_MTU) {
		Log("CAN interface does not support FD");
		return 0;
	}

	return 1;
}

int send_can_frame(char *sframe)
{
	int s; /* can raw socket */
	struct ifreq ifr;
	struct sockaddr_can addr;
	struct canfd_frame frame;
	int enable_canfd = 1;
	int required_mtu;

	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		Log("Couldn't create a socket to send frame to node ...");
		return 0;
	}

	required_mtu = parse_canframe(&sframe, &frame);

	/**
	 * Copy CAN interface name to ifr_name m/nb
	 */
	strncpy(ifr.ifr_name, VIRTUALCAR, IFNAMSIZ - 1);
	ifr.ifr_name[IFNAMSIZ - 1] = '\0';
	ifr.ifr_ifindex = if_nametoindex(ifr.ifr_name);

	if (!ifr.ifr_ifindex) {
		Log("Couldn't convert ifr_name to if_index ...");
		return 0;
	}

	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	/* Frame size = CAN netdevice space */
	if (ioctl(s, SIOCGIFMTU, &ifr) < 0) {
		Log("Couldn't fit can_frame in netdevice ...");
		return 0;
	}	

	/** Frame is MTU but interface does not support it */
	if (can_gateway_check_mtu(&ifr) != 1) {
		return 0;
	}

	if (setsockopt(s, SOL_CAN_RAW, CAN_RAW_FD_FRAMES,
				&enable_canfd, sizeof(enable_canfd))){
		Log("Couldn't enable CAN FD support ...");
		return 0;
	}

	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		Log("Couldn't bind to the interface address ...");
	}

	if (write(s, &frame, required_mtu) != required_mtu) {
		Log("Couldn't write through socket ...");
		return 0;
	}

	close(s);
	return 1;
}

void* check_pump_flow()
{
	pthread_t id = pthread_self();

	// Check if (pthread_equal(id, tid[0])) first thread?

	srand(time(NULL));

	while (1)
	{
		int r = randnum(1, 13);
		Log("Thread #pump_flow# exec ..");

		sleep(r);
	}
}

/**
 * Destroy car/vehicle bus device and gateway
 *
 * @return int
 */
void car_kill() 
{				
	printf("%s", "ka-boom, pfw, aaa, tsss\n");
	system("sudo ip link delete virtualcar");
	printf("%s", "*car exploded*\n");

	exit(1);
}