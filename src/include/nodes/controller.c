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

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>

#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/can.h>

#include "../logger.h"

#include "nodes.h"

/** nodes header */
#include "door.h"
 
void can_accept_signal(struct can_frame *frame)
{
	uint8_t i;
	Log("New frame recieved ...");

	if (frame->can_id == NODE_SIGNAL_DOOR_MODE) 
		node_door_mode();	

	if (frame->can_id == NODE_SIGNAL_DOOR_UNLC)
		node_door_unlock();

	if (frame->can_id == NODE_SIGNAL_DOOR_LOCK)
		node_door_lock();

	if (frame->can_id == NODE_SIGNAL_DOOR_WNDW)
		node_door_mirror();

	if (frame->can_id == NODE_SIGNAL_DOOR_MIRR)
		node_door_mirror();

	printf("\n");
}

void can_accept_signal_rtr(struct can_frame *frame)
{
	Log("New RTR frame recieved ...");


}