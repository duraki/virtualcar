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

#include <time.h>
#include <stdio.h>

#define LOGFILE	"virtualcar.log"     // all Log(); messages will be appended to this file

/**
 * Log message to a logfile
 * 
 */
int Log (char *str, ...)
{
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	FILE * fp = fopen(LOGFILE, "a");

	if (fp == NULL)
		return -1;

	fprintf(fp, "\n[%i/%i/%i %i:%i:%i] LOG: %s", 
				timeinfo->tm_mday, 
				timeinfo->tm_mon + 1, 
				timeinfo->tm_year + 1900, 
				timeinfo->tm_hour + 2, 
				timeinfo->tm_min, 
				timeinfo->tm_sec, str);

	fclose(fp);

	return 1;
}