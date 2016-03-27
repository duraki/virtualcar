/**
 * 
 * @author		Halis Duraki <halis_duraki@outlook.com>
 * @project		car.c (Virtual car)
 * @package 	dn5/vircar@github
 * @website		http://dn5.ljuska.org
 *
 * This file consist of all function one car can make.
 * Vircar is hackable, so any functions you may want to
 * sniff and hack can be located here. Please, understand
 * that the engine codes shall be 4 chars long otherwise
 * you are breaking the car. Don't break the car. Think
 * of this as an various ECUs.
 *
 * Contribution is welcome.
 */

#define  ENON = "454E4F4E" 		/* Start a car engine 	*/
#define  ENOF = "454E4F46"		/* Stop the car engine 	*/
#define  LOCK = "4C4F434B"		/* Lock the doors 		*/
#define  DOCK = "444F434B"		/* Unlock the doors 	*/
 
#define  KILL = "4B494C4C"		/* Don't do this, the car will explode */

int car_do_something(char *what) {
	printf(" %s", what);
}

int car_start_engine() { 		/* ENON */
	car_do_something("vircar engine is turned on.");

	return 1;
}

int car_stop_engine() { 		/* ENOF */
	car_do_something("vircar engine is turned off.");

	return 1;
}

int car_lock_doors() { 			/* LOCK */
	car_do_something("vircar doors are locked.");

	return 1;
}

int car_unlock_doors() { 		/* DOCK */
	car_do_something("vircar ulocked the doors.");

	return 1;
}

int car_kill() {				/* KILL */
	car_do_something("ka-boom, pfw, aaa, ts\n");
	car_do_something("*car exploded*\n");
	/* I'll be back ... */

	system("sudo ip link delete vircar");
	exit(1);
}