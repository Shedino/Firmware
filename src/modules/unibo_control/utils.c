#include <stdlib.h>
#include <uORB/uORB.h>
#include <uORB/topics/vehicle_attitude.h>

#include "main_includes.h"

void utils_loadAHRSPacket(struct vehicle_attitude_s* obj){

	Model_GS_U.Attitude[0] = obj->q[0];
	Model_GS_U.Attitude[1] = obj->q[1];
	Model_GS_U.Attitude[2] = obj->q[2];
	Model_GS_U.Attitude[3] = obj->q[3];
	Model_GS_U.AngSpeed[0] = obj->rollspeed;
	Model_GS_U.AngSpeed[1] = obj->pitchspeed;
	Model_GS_U.AngSpeed[2] = obj->yawspeed;

}

#include <sys/time.h>

unsigned long utils_getCurrentTime(void){
	struct timeval now;
	gettimeofday(&now,NULL);
	unsigned long millis = now.tv_sec*10000+now.tv_usec/100;
	return millis;
}

/*
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

struct termios orig_termios;

void reset_terminal_mode()
{
    tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode()
{
    struct termios new_termios;

    // take two copies - one for now, one for later
    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(new_termios));

    // register cleanup handler, and set the new terminal mode
    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

int getch()
{
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0) {
        return r;
    } else {
        return c;
    }
}
*/
