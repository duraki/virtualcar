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

/**
 * Definition of controllers and signals
 */

/** special address description for door node */
#define NODE_SIGNAL_DOOR_MODE 0x000000100 /* door action */
#define NODE_SIGNAL_DOOR_UNLC 0x000000101 /* door unlock */
#define NODE_SIGNAL_DOOR_LOCK 0x000000102 /* door lock */
#define NODE_SIGNAL_DOOR_MIRR 0x000000103 /* door mirror */
#define NODE_SIGNAL_DOOR_WNDW 0x000000104 /* door window */

/** special address description for pump node */
#define NODE_SIGNAL_EHPS_MODE 0x000000201 /** pump action */
#define NODE_SIGNAL_EHPS_FLOW 0x000000202 /** pump flow */
#define NODE_SIGNAL_EHPS_CPCT 0x000000203 /** pump capacity */
#define NODE_SIGNAL_EHPS_RGLT 0x000000204 /** pump regulator */

/** special address for future nodes */
#define NODE_SIGNAL_INST_MODE 0x0 /** instrument cluster */
#define NODE_SIGNAL_ENGN_MODE 0x0 /** engine controller */
#define NODE_SIGNAL_MABS_MODE 0x0 /** abs controller */
#define NODE_SIGNAL_MESP_MODE 0x0 /** esp node sensor **/
#define NODE_SIGNAL_AIRB_MODE 0x0 /** airbag controller */
#define NODE_SIGNAL_NAVG_MODE 0x0 /** radio + navigation */
#define NODE_SIGNAL_TRNC_MODE 0x0 /** climatronic */

