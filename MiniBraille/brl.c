/*
 * BRLTTY - A background process providing access to the Linux console (when in
 *          text mode) for a blind person using a refreshable braille display.
 *
 * Copyright (C) 1995-2001 by The BRLTTY Team. All rights reserved.
 *
 * BRLTTY comes with ABSOLUTELY NO WARRANTY.
 *
 * This is free software, placed under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation.  Please see the file COPYING for details.
 *
 * Web Page: http://mielke.cc/brltty/
 *
 * This software is maintained by Dave Mielke <dave@mielke.cc>.
 */

/* MiniBraille/brl.c - Braille display library
 * the following Tieman B.V. braille terminals are supported
 *
 * - MiniBraille v 1.5 (20 braille cells + 2 status)
 *   (probably other versions too)
 *
 * Brailcom o.p.s. <technik@brailcom.cz>
 *
 * Thanks to Tieman B.V., which gives me protocol information. Author.
 */


#define __EXTENSIONS__  /* for termios.h */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
// #include <sys/termios.h>
#include <string.h>
#include <termios.h>

#include "../brl.h"
#include "../misc.h"
#include "brlconf.h"
#include "../brl_driver.h"
#include "../message.h"
#include "minibraille.h"

/* types */
enum mode_t { NORMAL_MODE, F1_MODE, F2_MODE, MANAGE_MODE, CLOCK_MODE };

/* global variables */
static int brl_fd = -1;
static struct termios oldtermios;
static unsigned char xtbl[256];
unsigned char xlated[20]; // translated content of display
unsigned char status[2]; // xlated content of status area
enum mode_t mode = NORMAL_MODE;

/* #defines */
// delay this time after command - better: use CTS, DTR, CTR or find other signal which means "ready for next command"
#define AFTER_CMD_DELAY_TIME 10000
#define AFTER_CMD_DELAY do { usleep(AFTER_CMD_DELAY_TIME); } while (0)

static void beep(void)
{
	AFTER_CMD_DELAY;
	write(brl_fd, "\eB\r", 3);
	AFTER_CMD_DELAY;
};

/* interface */
static void identbrl(void)
{
	LogAndStderr(LOG_NOTICE, "Tieman B.V. MiniBraille driver");
	LogAndStderr(LOG_INFO, "   Copyright (C) 2000 by Brailcom o.p.s. <technik@brailcom.cz>"); 
}

static void initbrl(brldim *brl, const char *brldev)
{
	__label__ __errexit;
	struct termios newtermios;
	unsigned char standard[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	unsigned char Tieman[8] = { 0, 7, 1, 6, 2, 5, 3, 4 };
	int n, i; /* counters */
	
	// init geometry
	brl->x = 20;
	brl->y = 1;
	brl->disp = malloc(brl->x * brl->y + 1);
	if (brl->disp == NULL) goto __errexit;

	// open device
	if (brldev == NULL)  goto __errexit;
	brl_fd = open(brldev, O_RDWR | O_SYNC | O_NOCTTY);
	if (brl_fd == -1) goto __errexit;
	if (!isatty(brl_fd)) goto __errexit;
	tcgetattr(brl_fd, &oldtermios); // save old terminal setting
	tcgetattr(brl_fd, &newtermios);
	cfmakeraw(&newtermios);
	//newtermios.c_iflag |= CRTSCTS;
	newtermios.c_cc[VMIN] = 0; // non-blocking read
	newtermios.c_cc[VTIME] = 0;
	cfsetspeed(&newtermios, B9600);
	tcflush(brl_fd, TCIFLUSH);
	tcsetattr(brl_fd, TCSANOW, &newtermios);
	/* hm, how to switch to 38400 ? 
	write(brl_fd, "\eV\r", 3);
	tcflush(brl_fd, TCIFLUSH);
	cfsetspeed(&newtermios, B38400);
	tcsetattr(brl_fd, TCSANOW, &newtermios);
	*/

	memset(xtbl, 0, 256); // fill xlatetable
	for (n = 0; n < 256; n++)
		for (i = 0; i < 8; i++)
			if (n & 1 << standard[i])
				xtbl[n] |= 1 << Tieman[i];
	message("BRLTTY Ready", 0);
	beep();
	return;

__errexit:
	LogAndStderr(LOG_ERR, "Cannot initialize MiniBraille");
	brl->x = brl->y = -1;
	if (brl->disp) free(brl->disp);
	return;
}

static void closebrl(brldim *brl)
{
	free(brl->disp); // handles NULL
	tcsetattr(brl_fd, TCSANOW, &oldtermios);
	close(brl_fd);
}

static void refresh(void)
{
	unsigned char datab[] = { 27, 'Z', '1' };
	unsigned char datae[] = { 13 };
	write(brl_fd, datab, sizeof datab);
	write(brl_fd, status, sizeof status);
	write(brl_fd, xlated, sizeof xlated);
	write(brl_fd, datae, sizeof datae);
};

static void writebrl(brldim *brl)
{
	int i;
	for (i = 0; i < 20; i++) xlated[i] = xtbl[brl->disp[i]];
	refresh();
}


static int readbrl(DriverCommandContext cmds)
{
	unsigned char znak;
	int rv;
	if (cmds == CMDS_MESSAGE)
	  return EOF;
	rv = read(brl_fd, &znak, 1);
	switch (mode) {
	case NORMAL_MODE:
		if (rv == -1) return EOF;
		if (rv == 0) return EOF;
		switch (znak) {
		case KEY_F1:
			mode = F1_MODE;
			message("F1 mode active", 0);
			return CMD_NOOP;
		case KEY_F2:
			mode = F2_MODE;
			message("F2 mode active", 0);
			return CMD_NOOP;
		case KEY_UP:
			return CMD_LNUP;
		case KEY_DOWN:
			return CMD_LNDN;
		case KEY_C:
			return CMD_HOME;
		case KEY_LEFT:
			return CMD_FWINLT;
		case KEY_RIGHT:
			return CMD_FWINRT;
		};
		beep();
		return EOF; // cannot do anythink
	case F1_MODE:
		if (rv == 0) { usleep(20000); return CMD_NOOP; };
		mode = NORMAL_MODE;
		if (rv == -1) return CMD_NOOP;
		switch (znak) {
		case KEY_F1:
			mode = MANAGE_MODE; // F1-F1 prechod na management
			message("Management mode", 0);
			return CMD_NOOP;
		case KEY_F2:
			return CMD_CSRVIS;
		case KEY_LEFT:
			return CMD_LNBEG;
		case KEY_RIGHT:
			return CMD_LNEND;
		case KEY_UP:
			return CMD_TOP_LEFT;
		case KEY_DOWN:
			return CMD_BOT_LEFT;
		case KEY_C:
			return CMD_CAPBLINK;
		};
		beep();
		return EOF;
	case F2_MODE:
		if (rv == 0) { usleep(20000); return CMD_NOOP; };
		mode = NORMAL_MODE;
		if (rv == -1) return CMD_NOOP;
		switch (znak) {
		case KEY_F1:
			return CMD_CSRSIZE;
		case KEY_F2:
			return CMD_SKPIDLNS;
		case KEY_C:
			return CMD_CSRTRK;
		case KEY_RIGHT:
			return CMD_SIXDOTS;
		case KEY_DOWN:
			return CMD_DISPMD;
		case KEY_LEFT:
			return CMD_INFO;
		case KEY_UP: // stepmode (by melo byt)
			return CMD_FREEZE;
		};
		beep();
		return EOF;
	case CLOCK_MODE: {
			char t[200];
			struct tm* c;
			time_t cas;
			cas = time(NULL);
			c = localtime(&cas);
			strftime(t, sizeof t, "%e.%m %Y %H:%M:%S", c);
			message(t, 0);
		};
		if (rv == 0) { usleep(500000); return CMD_NOOP; };
		if (rv == -1) return CMD_NOOP;
		mode = NORMAL_MODE;
		break;
	case MANAGE_MODE:
		if (rv == 0) { usleep(50000); return CMD_NOOP; };
		mode =  NORMAL_MODE;
		if (rv == -1) return CMD_NOOP;
		switch (znak) {
		case KEY_F1:
			return CMD_HELP;
		case KEY_F2:
			return CMD_INFO;
		case KEY_C:
			return CMD_RESET;
		case KEY_LEFT:
			return CMD_RESTARTBRL;
		case KEY_RIGHT:
			mode = CLOCK_MODE;
			return CMD_NOOP;
		case KEY_UP:
			return CMD_CONFMENU;
		case KEY_DOWN:
			return CMD_SAVECONF;
		};
	};
	return EOF; // never should reach this
}

static void setbrlstat(const unsigned char *s)
{
	status[0] = xtbl[s[0]];
	status[1] = xtbl[s[1]];
	//refresh();
}

