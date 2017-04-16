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

#include <stdlib.h>
#include <time.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "include/lib.h"

int send_can_frame(char *sframe)
{
    int s; /* can socket */
    struct ifreq ifr;
    struct sockaddr_can addr;
    struct canfd_frame frame;
    int enable_canfd = 1;
    int required_mtu;

    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("socket");
    }
    
    memset(&ifr, 0, sizeof(struct ifreq));
    strncpy(ifr.ifr_name, "virtualcar", IFNAMSIZ - 1);
    ifr.ifr_name[IFNAMSIZ-1[ = '\0';
    ifr.ifr_ifindex = if_nametoindex(ifr.ifr_name);
    if (ioctl(sock, SIOCGIFINDEX, &ifr) < 0)
        perror("SIOCGIFINDEX");

}
