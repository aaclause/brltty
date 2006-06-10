/*
 * BRLTTY - A background process providing access to the console screen (when in
 *          text mode) for a blind person using a refreshable braille display.
 *
 * Copyright (C) 1995-2006 by The BRLTTY Developers.
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

/* EuroBraille/braille.c - Braille display library for the EuroBraille family.
 * Copyright (C) 1997-2006 by Yannick Plassiard <yan@mistigri.org>
 *                        and Nicolas Pitre <nico@cam.org>
 * See the GNU General Public License for details in the ../../COPYING file
 * See the README file for details about copyrights and version informations
 */

#include "prologue.h"

#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include "Programs/message.h"
#include "Programs/misc.h"

/*
** For debugging only
*/
// #define		LOG_IO

#define BRL_HAVE_PACKET_IO
#define BRL_HAVE_VISUAL_DISPLAY
#include "Programs/brl_driver.h"
#include "braille.h"
#include "Programs/io_serial.h"

/*
** For debugging only
** #define		LOG_IO
*/

static t_key	num_keys[27] = {
  {1, '1', 0},
  {2, '2', 0},
  {3, '3', 0},
  {4, '4', 0},
  {5, '5', 0},
  {6, '6', 0},
  {7, '7', 0},
  {8, '8', 0},
  {9, '9', 0},
  {10, '*', 0},
  {30, '0', 0},
  {11, '#', 0},
  {12, 'A', 0},
  {13, 'B', 0},
  {14, 'C', 0},
  {15, 'D', 0},
  {16, 'E', 0},
  {17, 'F', 0},
  {18, 'G', 0},
  {19, 'H', 0},
  {20, 'I', 0},
  {21, 'J', 0},
  {22, 'K', 0},
  {23, 'L', 0},
  {24, 'M', 0},
  {25, 'Z', 0},
  {0, 0, 0}
};

/*
** next tables define assigmenss bitween keys and HLLTTY commands depending on
** the terminal type (Scriba, Clio)NoteBraille, or AzerBraille).
**
** If you make changes to those tables I'd like to be informed in order to
** update the driver for next releases.
*/

static t_key	scriba_keys[17] = {		
  {BRL_BLK_PASSKEY | BRL_KEY_CURSOR_UP, 2, 0},
  {BRL_BLK_PASSKEY | BRL_KEY_CURSOR_LEFT, 4, 0},
  {BRL_BLK_PASSKEY | BRL_KEY_CURSOR_RIGHT, 6, 0},
  {BRL_BLK_PASSKEY | BRL_KEY_CURSOR_DOWN, 8, 0},
  {0, 10, Program},
  {0, 11, ViewOn},
  {0, 13, 0},
  {BRL_CMD_FWINLT, 16, 0},
  {BRL_CMD_LNUP, 17, 0},
  {BRL_CMD_PRPROMPT, 18, 0},
  {BRL_CMD_PRSEARCH, 19, 0},
  {BRL_CMD_INFO, 20, 0},
  {BRL_CMD_NXSEARCH, 21, 0},
  {BRL_CMD_NXPROMPT, 22, 0},
  {BRL_CMD_LNDN, 23, 0},
  {BRL_CMD_FWINRT, 24, 0},
  {0, 0, 0}
};

static t_key	pscriba_keys[7] = {
  {BRL_CMD_PREFMENU, 2, 0},
  {BRL_CMD_TUNES, 6, 0},
  {BRL_CMD_CSRTRK, 8, 0},
  {0, 16, begblk},
  {BRL_CMD_PASTE, 23, 0},
  {0, 24, endblk},
  {0, 0, 0}
};

static t_key	azer40_keys[8] = {
  {BRL_CMD_FWINLT, 16, 0},
  {BRL_CMD_LNUP, 17, 0},
  {BRL_CMD_PRPROMPT, 18, 0},
  {BRL_CMD_INFO, 20, 0},
  {BRL_CMD_NXPROMPT, 22, 0},
  {BRL_CMD_LNDN, 23, 0},
  {BRL_CMD_FWINRT, 24, 0},
  {0, 0, 0}
};

static t_key	*pazer40_keys = pscriba_keys;

static t_key	azer80_keys[23] = {
  {BRL_CMD_TOP_LEFT, 1, 0},
  {BRL_BLK_PASSKEY | BRL_KEY_CURSOR_UP, 2, 0},
  {BRL_CMD_PRDIFLN, 3, 0},
  {BRL_BLK_PASSKEY | BRL_KEY_CURSOR_LEFT, 4, 0},
  {BRL_CMD_HOME, 5, 0},
  {BRL_BLK_PASSKEY | BRL_KEY_CURSOR_RIGHT, 6, 0},
  {BRL_CMD_BOT_LEFT, 7, 0},
  {BRL_BLK_PASSKEY | BRL_KEY_CURSOR_DOWN, 8, 0},
  {BRL_CMD_NXDIFLN, 9, 0},
  {0, 10, Program},
  {BRL_CMD_CSRTRK, 30, 0},
  {0, 11, ViewOn},
  {BRL_CMD_FREEZE, 12, 0},
  {BRL_CMD_FWINLT, 16, 0},
  {BRL_CMD_LNUP, 17, 0},
  {BRL_CMD_PRPROMPT, 18, 0},
  {BRL_CMD_PRSEARCH, 19, 0},
  {BRL_CMD_INFO, 20, 0},
  {BRL_CMD_NXSEARCH, 21, 0},
  {BRL_CMD_NXPROMPT, 22, 0},
  {BRL_CMD_LNDN, 23, 0},
  {BRL_CMD_FWINRT, 24, 0},
  {0, 0, 0}
};
static t_key	*pazer80_keys = pscriba_keys;

static t_key	*clio_keys = azer80_keys;
static t_key	*pclio_keys = pscriba_keys;

static t_key	*nb_keys = azer80_keys;
static t_key	*pnb_keys = pscriba_keys;

static t_key	iris_keys[16] = {
  {BRL_BLK_PASSKEY | BRL_KEY_CURSOR_UP, 2, 0},
  {BRL_BLK_PASSKEY | BRL_KEY_CURSOR_LEFT, 4, 0},
  {BRL_BLK_PASSKEY | BRL_KEY_CURSOR_RIGHT, 6, 0},
  {BRL_BLK_PASSKEY | BRL_KEY_CURSOR_DOWN, 8, 0},
  {BRL_CMD_NOOP, 10, Program},
  {BRL_CMD_NOOP, 11, ViewOn},
  {BRL_CMD_FWINLT, 16, 0},
  {BRL_CMD_LNUP, 17, 0},
  {BRL_CMD_CSRVIS, 18, 0},
  {BRL_CMD_PREFMENU, 19, 0},
  {BRL_CMD_NOOP, 20, 0},
  {BRL_CMD_NOOP, 21, enter_routing},
  {BRL_CMD_TUNES, 22, 0},
  {BRL_CMD_LNDN, 23, 0},
  {BRL_CMD_FWINRT, 24, 0},
  {0, 0, 0}
};

static t_key	*piris_keys = pscriba_keys;

/*
** Next bindings are keys that must be explicitly listed to allow function
** keys, escape, page-down, enter, backspace ...
** The first part is a 10-bits code representing the key. Format is :
**
** Braille -> decimal value
** 1		1
** 2		2
** 3		4
** 4		8
** 5		16
** 6		32
** 7		64
** 8		128
** bkspace	256
** space	512
*/

static t_alias	brl_key[] = {
  {0x100,	BRL_BLK_PASSKEY + BRL_KEY_BACKSPACE},
  {0x300,	BRL_BLK_PASSKEY + BRL_KEY_ENTER},
  {0x232,	BRL_BLK_PASSKEY + BRL_KEY_TAB},
  {0x208,	BRL_BLK_PASSKEY + BRL_KEY_CURSOR_UP},
  {0x220,	BRL_BLK_PASSKEY + BRL_KEY_CURSOR_DOWN},
  {0x210,	BRL_BLK_PASSKEY + BRL_KEY_CURSOR_RIGHT},
  {0x202,	BRL_BLK_PASSKEY + BRL_KEY_CURSOR_LEFT},
  {0x205,	BRL_BLK_PASSKEY + BRL_KEY_PAGE_UP},
  {0x228,	BRL_BLK_PASSKEY + BRL_KEY_PAGE_DOWN},
  {0x207,	BRL_BLK_PASSKEY + BRL_KEY_HOME},
  {0x238,	BRL_BLK_PASSKEY + BRL_KEY_END},
  {0x224,	BRL_BLK_PASSKEY + BRL_KEY_DELETE},
  {0x21b,	BRL_BLK_PASSKEY + BRL_KEY_ESCAPE},
  {0x215,	BRL_BLK_PASSKEY + BRL_KEY_INSERT},
  {0x101,	BRL_BLK_PASSKEY + BRL_KEY_FUNCTION},
  {0x103,	BRL_BLK_PASSKEY + BRL_KEY_FUNCTION + 1},
  {0x109,	BRL_BLK_PASSKEY + BRL_KEY_FUNCTION + 2},
  {0x119,	BRL_BLK_PASSKEY + BRL_KEY_FUNCTION + 3},
  {0x111,	BRL_BLK_PASSKEY + BRL_KEY_FUNCTION + 4},
  {0x10b,	BRL_BLK_PASSKEY + BRL_KEY_FUNCTION + 5},
  {0x11b,	BRL_BLK_PASSKEY + BRL_KEY_FUNCTION + 6},
  {0x113,	BRL_BLK_PASSKEY + BRL_KEY_FUNCTION + 7},
  {0x10a,	BRL_BLK_PASSKEY + BRL_KEY_FUNCTION + 8},
  {0x11a,	BRL_BLK_PASSKEY + BRL_KEY_FUNCTION + 9},
  {0x105,	BRL_BLK_PASSKEY + BRL_KEY_FUNCTION + 10},
  {0x107,	BRL_BLK_PASSKEY + BRL_KEY_FUNCTION + 11},
  {0,		0}
};

static int model_ID = 0;
/* model identification string. possible values :
** 0 - Unknown model name
** 1 - NoteBRAILLE
** 2 - Clio-NoteBRAILLE
** 3 - SCRIBA
** 4 - AzerBRAILLE
** 5 - Iris (not defined yet, will come soon...)
*/

static char version_ID[21] = "Unknown";
/* This is where the driver will store the internal ROM version of the
** terminal. It is used when the user asks the version of BRLTTY and his
** terminal.
*/

#define BRLROWS		1
#define MAX_STCELLS	5	/* hiest number of status cells */

/* This is the brltty braille mapping standard to Eurobraille's mapping table.
 */
static TranslationTable outputTable;

/* Global variables */

static int	JustIdentified = 0;
static int		chars_per_sec;
static SerialDevice *	serialDevice;			/* file descriptor for Braille display */
static unsigned char	*rawdata = NULL;		/* translated data to send to Braille */
static unsigned char	*prevdata = NULL;	/* previously sent raw data */
static unsigned char	*lcd_data = NULL;	/* previously sent to LCD */
static int		NbCols = 0;			/* number of cells available */
static short	ReWrite = 0;		/* 1 if display need to be rewritten */
static short	ReWrite_LCD = 0;		/* same as rewrite, for LCD */
static int	OffsetType = BRL_BLK_ROUTE;
static int	PktNbr = 127; /* 127 at first time */
static int	context = 0;   /* Input type test-value */
static int	control = 0;
static int	alt = 0;


/* Communication codes */

#define SOH     0x01
#define EOT     0x04
#define ACK     0x06
#define DLE     0x10
#define NACK    0x15

#define PRT_E_PAR 0x01		/* parity error */
#define PRT_E_NUM 0x02		/* frame numver error */
#define PRT_E_ING 0x03		/* length error */
#define PRT_E_COM 0x04		/* command error */
#define PRT_E_DON 0x05		/* data error */
#define PRT_E_SYN 0x06		/* syntax error */

#define DIM_INBUFSZ 256

static int readbrlkey(BrailleDisplay *brl);

static int begblk(BrailleDisplay *brl)
{
  OffsetType = BRL_BLK_CUTBEGIN;
  return (EOF);
}

static int endblk(BrailleDisplay *brl)
{
  OffsetType = BRL_BLK_CUTLINE;
  return (EOF);
}

static int sendbyte(unsigned char c)
{
  return (serialWriteData(serialDevice, &c, 1));
}

static int WriteToBrlDisplay (BrailleDisplay *brl, int len, const unsigned char *data)
{
  static const unsigned char needsEscape[0X100] = {
    [SOH] = 1, [EOT] = 1, [DLE] = 1, [ACK] = 1, [NACK] = 1
  };
  unsigned char	buf[1024];
  unsigned char		*p = buf;
  unsigned char parity = 0;
#ifdef	LOG_IO
  int		logfd;
#endif

   if (!len)
     return 1;

   *p++ = SOH;
   while (len--)
     {
	if (needsEscape[*data]) *p++ = DLE;
        *p++ = *data;
	parity ^= *data++;
     }
   *p++ = PktNbr; /* Doesn't need to be prefixed since greater than 128 */
   parity ^= PktNbr;
   if (++PktNbr >= 256)
     PktNbr = 128;
   if (needsEscape[parity]) *p++ = DLE;
   *p++ = parity;
   *p++ = EOT;
   brl->writeDelay += ((p - buf) * 1000 / chars_per_sec) + 1;
#ifdef		LOG_IO
   logfd = open("/tmp/eb-log.out", O_CREAT | O_APPEND | O_WRONLY, 0600);
   write(logfd, "WritePacket: ", 13);
   write(logfd, buf, p - buf);
   write(logfd, "\n", 1);
   close(logfd);
#endif
   return (serialWriteData(serialDevice, buf, p - buf) == p - buf);
}

static ssize_t brl_writePacket(BrailleDisplay *brl, const void *p, size_t sz)
{
  if (!p)
    return 0;
  return (WriteToBrlDisplay(brl, sz, p));
}

static int brl_reset(BrailleDisplay *brl)
{
  static const unsigned char packet[] = {0X02, 'S', 'I'};
  LogPrint(LOG_INFO, "EuroBraille: Reset hardware asked.\n");
  return (brl_writePacket(brl, packet, sizeof(packet)) == sizeof(packet));
}

static int brl_open (BrailleDisplay *brl, char **parameters, const char *device)
{
   {
     static const DotsTable dots = {0X01, 0X02, 0X04, 0X08, 0X10, 0X20, 0X40, 0X80};
     makeOutputTable(dots, outputTable);
   }

   if (!isSerialDevice(&device)) {
     unsupportedDevice(device);
     return 0;
   }

   rawdata = prevdata = lcd_data = NULL;		/* clear pointers */

  /* Open the Braille display device for random access */
   if (!(serialDevice = serialOpenDevice(device))) return 0;
   serialSetParity(serialDevice, SERIAL_PARITY_EVEN);

  /* set speed */
   chars_per_sec = BAUDRATE / 11;
   serialRestartDevice(serialDevice, BAUDRATE);

  /* Set model params... */
   brl->helpPage = 0;
   brl->y = BRLROWS;
   while (!NbCols)
     {
	int i = 0;
	unsigned char AskIdent[] = "\x2SI";
	WriteToBrlDisplay (brl, sizeof(AskIdent), AskIdent);
	while (!NbCols)
	  {
	     drainBrailleOutput (brl, 100);
	     brl_readCommand (brl, BRL_CTX_SCREEN);       /* to get the answer */
	     if (++i >= 10)
	       break;
	  }
     }

   ReWrite = 1;  /* To write whole display at first time */
   ReWrite_LCD = 1;
   LogPrint(LOG_INFO, "EuroBraille Display detection successfull, cols=%d", NbCols);
   return 1;
}

static void brl_close (BrailleDisplay *brl)
{
   if (rawdata)
     {
       free (rawdata);
       rawdata = NULL;
     }
   if (prevdata)
     {
       free (prevdata);
       prevdata = NULL;
     }
   if (lcd_data)
     {
       free (lcd_data);
       lcd_data = NULL;
     }
   if (serialDevice)
     {
       serialCloseDevice (serialDevice);
       serialDevice = NULL;
     }
   NbCols = 0;
   strcpy(version_ID, "Unknown");
}

static void brl_writeWindow (BrailleDisplay *brl)
{
   int i, j;

   if (context) 
     return ;
   if (!ReWrite)
     {
      /* We update the display only if it has changed */
	if (memcmp(brl->buffer, prevdata, NbCols) != 0)
	  ReWrite = 1;
     }
   if (ReWrite)
     {
      /* right end cells don't have to be transmitted if all dots down */
	i = NbCols;

	  {
	     unsigned char OutBuf[2 * i + 6];
	     unsigned char *p = OutBuf;

	     *p++ = i + 2;
	     *p++ = 'D';
	     *p++ = 'P';
	     for (j = 0;
		  j < i;
		  *p++ = outputTable[(prevdata[j++] = brl->buffer[j])]);
	     WriteToBrlDisplay (brl, p - OutBuf, OutBuf);
	     ReWrite = 0;
	  }
     }
}

/*
** If defined, the next routine will print informations on the LCD screen
*/

#ifdef		BRL_HAVE_VISUAL_DISPLAY

static void	brl_writeVisual(BrailleDisplay *brl)
{
  int		i = NbCols;
  unsigned char OutBuf[2 * NbCols + 6];
  unsigned char *p = OutBuf;
  int		j;

  if (ReWrite_LCD == 0)
    if (memcmp(brl->buffer, lcd_data, NbCols) != 0)
      {
	ReWrite_LCD = 1;
	memcpy(lcd_data, brl->buffer, NbCols);
      }
  if (ReWrite_LCD)
    {
      memset(OutBuf, 0, NbCols + 2);
      *p++ = i + 2;
      *p++ = 'D';
      *p++ = 'L';
      for (j = 0; j < i; j++)
	*p++ = brl->buffer[j];
      WriteToBrlDisplay(brl, p - OutBuf, OutBuf);
      ReWrite_LCD = 0;
    }
}

#endif

static void brl_writeStatus (BrailleDisplay *brl, const unsigned char *st)
{
  
}

static int Program(BrailleDisplay *brl)
{
  int		key;
  t_key		*p = 0;
  short		i;

  switch (model_ID)
    {
    case 1:
      message("P PROGRAMMING      x", MSG_NODELAY);
      p = pnb_keys;
      break;
    case 2:
      message("P PROGRAMMING      x", MSG_NODELAY);
      p = pclio_keys;
      break;
    case 3:
      message("Beta level ...",MSG_NODELAY);
      p = pscriba_keys;
      break;
    case 4:
      message("P PROGRAMMING      x", MSG_NODELAY);
      if (NbCols == 40)
	p = pazer40_keys;
      else
	p = pazer80_keys;
      break;
    case 5:
      message("Level 2 ...", MSG_NODELAY);
      p = piris_keys;
      break;
    default:
      message("P Unimplemented yet!", MSG_WAITKEY);
      break;
    }
  if (p)
    {
      while ((key = readbrlkey(brl)) != 10)
	{
	  for (i = 0; p[i].brl_key; i++)
	    if (key == p[i].brl_key)
	      {
		if (p[i].f)
		  return (p[i].f(brl));
		else
		  return (p[i].res);
	      }
	}
    }
  return (BRL_CMD_NOOP);
}


int ViewOn(BrailleDisplay *brl)
{
   int touche;
   static int res2 = 0;
   static int exitviewon = 0;
   switch (model_ID)
     {
      case 3:
	message("Alpha level ...", MSG_NODELAY);
	break;
      default:
	message("V VIEW ON          x", MSG_NODELAY);
	break;
     }
   exitviewon=0;
   while (!exitviewon)
     {
	touche=readbrlkey(0);
	switch(touche)
	  {
	   case 1:
	     exitviewon=1;
	     break;
	   case 3:
	     res2 = BRL_CMD_TOP_LEFT;
	     exitviewon=1;
	     break;
	   case 9:
	     res2 = BRL_CMD_BOT_LEFT;
	     exitviewon=1;
	     break;
	   case 11:
	     exitviewon=1;
	     break;
	   case 12:
	     res2 = BRL_CMD_DISPMD;
	     exitviewon=1;
	     break;
	  case 16:
	  case 17:
	  case 18:
	  case 19:
	  case 20:
	  case 21:
	  case 22:
	    res2 = BRL_BLK_SWITCHVT + touche - 16;
	    exitviewon = 1;
	    break;
	   case 24:
	     res2 = BRL_CMD_LEARN;
	     exitviewon=1;
	     break;

	  }
     }
   return res2;
}

static int brl_readCommand(BrailleDisplay *brl, BRL_DriverCommandContext context)
{
  int		res;
  int		i;
  t_key		*p;
  int		key;

  res = 0;
  key = readbrlkey(brl);
  p = 0;
  if (model_ID == 1)
    p = nb_keys;
  else if (model_ID == 2)
    p = clio_keys;
  else if (model_ID == 3)
    p = scriba_keys;
  else if (model_ID == 4 && NbCols == 40)
    p = azer40_keys;
  else if (model_ID == 4 && NbCols == 80)
    p = azer80_keys;
  else if (model_ID == 5)
    p = iris_keys;
  if (p)
    {
      for (i = 0; p[i].brl_key; i++)
	if (p[i].brl_key == key)
	  {
	    if (p[i].f)
	      res = p[i].f(brl);
	    else
	      res = p[i].res;
	  }
    }
  if (res)
    return (res);
  else
    return (key);
}

static int enter_routing(BrailleDisplay *brl)
{
  return (routing(brl, 0x83));
}

static int routing(BrailleDisplay *brl, int routekey)
{
   int res = EOF;
   int	flag = 0;

   switch (context)
     {
       case 1:
	switch (routekey)
	  {
	   case 0x02: /* exit menu */
	     ReWrite = 1;
	     context = 0;
	     res = BRL_CMD_NOOP;
	     break;
	   case 0x06: /* Console Switching */
 	     context = 0;
	     if (NbCols == 20)
	       message("switch:1 2 3 4 5 6 t", MSG_NODELAY);
	     else
	       message("switch:1 2 3 4 5 6 7 t", MSG_NODELAY);
	     context = 2;
	     ReWrite = 0;
	     res = BRL_CMD_NOOP;
	     break;
	   case 0x0A: /* Help */
	     context = 0;
	     ReWrite = 1;
	     res = BRL_CMD_LEARN;
	     break;
	  case 0x0F: /* version information */
	    context = 0;
	    message(version_ID, MSG_WAITKEY);
	    res = BRL_CMD_NOOP;
	    break;
	  }
	break;
      case 2:
	switch(routekey)
	  {
	   case 0x07: /* exit */
	     context = 0;
	     ReWrite = 1;
	     res = BRL_CMD_NOOP;
	     break;
	   case 0x09: /* switch to console 1 */
	     res = BRL_BLK_SWITCHVT;   /* BRL_BLK_WITCHVT + 0 */
	     context = 0;
	     ReWrite = 1;
	     break;
	   case 0x0B: /* switch to console 2 */
	     res = BRL_BLK_SWITCHVT + 1;
	     ReWrite = 1;
	     context = 0;
	     break;
	   case 0x0D: /* switch to console 3 */
	     res = BRL_BLK_SWITCHVT + 2;
	     context = 0;
	     ReWrite = 1;
	     break;
	   case 0x0F: /* switch to console 4 */
	     res = BRL_BLK_SWITCHVT + 3;
	     ReWrite = 1;
	     context = 0;
	     break;
	   case 0x11: /* switch to console 5 */
	     res = BRL_BLK_SWITCHVT + 4;
	     context = 0;
	     ReWrite = 1;
	     break;
	   case 0x13: /* switch to console 6 */
	     res = BRL_BLK_SWITCHVT + 5;
	     context = 0;
	     ReWrite = 1;
	     break;
	   case 0x15: /* switch to console 6 */
	     res = BRL_BLK_SWITCHVT + 6;
	     context = 0;
	     ReWrite = 1;
	     break;
	  }
	break;
      case 0:
	switch (routekey)
	  {
	  case 0x29:
	    if (model_ID == 5)
	      flag = 1;
	    /* no break */
	  case 0x57:
	  case 0x83: /* Entering in menu-mode */
	    flag = 1;
	    break;
	  default:
	    res = OffsetType + routekey - 1;
	    OffsetType = BRL_BLK_ROUTE;
	    break;
	  }
	if (flag == 1)
	  {
	    message("-:tty hlp info t", MSG_NODELAY);
	    context = 1;
	    res = BRL_CMD_NOOP;
	  }
	break;
     }
   return res;
}

static int	convert(int keys)
{
  int		res;

  res = 0;
  res = (keys & 128) ? BRL_DOT8 : 0;
  res += (keys & 64) ? BRL_DOT7 : 0;
  res += (keys & 32) ? BRL_DOT6 : 0;
  res += (keys & 16) ? BRL_DOT5 : 0;
  res += (keys & 8) ? BRL_DOT4 : 0;
  res += (keys & 4) ? BRL_DOT3 : 0;
  res += (keys & 2) ? BRL_DOT2 : 0;
  res += (keys & 1) ? BRL_DOT1 : 0;
  return (res);
}



static int	key_handle(BrailleDisplay *brl, unsigned char *buf)
{
  int	res = EOF;
  /* here the braille keys are bitmapped into an int with
   * dots 1 through 8, left thumb and right thumb
   * respectively.  It makes up to 1023 possible
   * combinations! Here's some of them.
   */
  unsigned int keys = (buf[0] & 0x3F) |
    ((buf[1] & 0x03) << 6) |
    ((int) (buf[0] & 0xC0) << 2);
  if (keys >= 0xff && keys != 0x280 && keys != 0x2c0
      && keys != 0x200)
    {
      /*
      ** keys that must be explicitly listed
      */
      int	h;
      for (h = 0; brl_key[h].brl; h++)
	if (brl_key[h].brl == keys)
	  res = brl_key[h].key;
      if (control || alt)
	{
	  control = 0;
	  alt = 0;
	  context = 0;
	  ReWrite = 1;
	}
    }
  if (keys == 0x280 && alt)
    {
      context = 0;
      alt = 0;
      ReWrite = 1;
      res = BRL_CMD_NOOP;
    }
  if (keys == 0x280 && !alt && !control) /* alt */
    {
      message("! alt", MSG_NODELAY);
      context = 4;
      ReWrite = 0;
      alt = 1;
      res = BRL_CMD_NOOP;
    }
  if (alt && control)
    {
      context = 0;
      message("! alt control", MSG_NODELAY);
      context = 4;
    }
  if (keys == 0x2c0 && control)
    {
      context = 0;
      ReWrite = 1;
      res = BRL_CMD_NOOP;
      control = 0;
    }
  if (keys == 0x2c0 && !control) /* control */
    {
      control = 1;
      message("! control ", MSG_NODELAY);
      context = 4;
      ReWrite = 0;
      res = BRL_CMD_NOOP;
    }
  if (keys <= 0xff || keys == 0x200)
    {
      /*
      ** we pass a char
      */
      res = (BRL_BLK_PASSDOTS | convert(keys));
      if (control)
	{
	  res |= BRL_FLG_CHAR_CONTROL;
	  control = 0;
	  context = 0;
	}
      if (alt)
	{
	  res |= BRL_FLG_CHAR_META;
	  context = 0;
	  alt = 0;
	}
    }
  return (res);
}

#ifdef		BRL_HAVE_PACKET_IO

static ssize_t brl_readPacket(BrailleDisplay *brl, void *packet, size_t size)
{
  unsigned char *bp = packet;
  static int		i = 0; /* cpt to build the received packet */
  size_t		offset = 0; /* offset to use serialReadChunk */
  static char		apacket = 0;  /* =1 when packet starts */
  static unsigned char	par = 0; /* parity */
  int			j = 0; /* cpt to parse the read buffer */
  int			k = 0; /* cpt to build the returned buffer (bp) */
  unsigned char		c; /* the read char */
  static unsigned char	buf[512];  /* buffer to store read chars */
  static unsigned char	end = 0; /* = 1 when end of packet */
  static unsigned char prefix = 0; /* =1 when escape code detected */

  if ((bp==NULL) || (size<2) || (size>512))
    return 0;
  while (serialReadChunk(serialDevice, &c, &offset, 1, 0, 0))
    {
      if (!apacket && c == SOH)
	{
	  end = 0;
	  apacket = 1;
	  i = 0;
	  buf[i++] = SOH;
	  par = 0;
	}
      else if (apacket)
	{
	  if (c == EOT && !prefix)
	    {
	      apacket = 0;
	      buf[i++] = EOT;
	      end = 1;
	      break;
	    }
	  if (c == DLE && !prefix)
	    prefix = 1;
	  else
	    prefix = 0;
	  buf[i++] = c;
	}
      offset = 0;
    }
  if (!end) /* either nothing read or not end of packet */
    return 0;
  for (j = 1, k = 0; j < i - 2 && k < size ; j++) {
    if (buf[j] != DLE || (buf[j - 1] == DLE))
      {
	par ^= buf[j];
	bp[k] = buf[j];
	k++;
      }
  }
  end = 0;
  if (par == buf[i - 2])
    {
      sendbyte(ACK);
      serialDiscardInput(serialDevice);
      return k - 1;
    }
  /* if bad parity */
  serialDiscardInput(serialDevice);
  sendbyte(NACK);
  sendbyte(PRT_E_PAR); /* error code of a parity error */
  return 0;
}

#endif

static int readbrlkey(BrailleDisplay *brl)
{
  int res = EOF;
#ifdef		LOG_IO
  int		logfd;
#endif
  unsigned char c;
  static int DLEflag = 0, ErrFlag = 0, old_pktnbr = 128; /* at first time */
  static unsigned char buf[DIM_INBUFSZ];
  static int pos = 0, p = 0, pktready = 0;
  
  /* here we process incoming data */
  while (!pktready && (serialReadData (serialDevice, &c, 1, 0, 0) == 1))
    {
#ifdef		LOG_IO
      logfd = open("/tmp/eb-log.in", O_CREAT |  O_APPEND | O_WRONLY, 0600);
      write(logfd, &c, 1);
      close(logfd);
#endif
      if (DLEflag)
	{
	  DLEflag = 0;
	  if (pos < DIM_INBUFSZ) buf[pos++] = c;
	}
      else if (ErrFlag)
	{
	  ErrFlag = 0;
	  /* Maybe should we check error code in c here? */
	  ReWrite = 1;
	}
      else
	switch (c)
	  {
	  case NACK:
	    ErrFlag = 1;
	    /* no break */
	  case ACK:
	  case SOH:
	    pos = 0;
	    break;
	  case DLE:
	    DLEflag = 1;
	    break;
	  case EOT:
	    {
	      /* end of packet, let's read it */
	      int i;
	      unsigned char parity = 0;
	      if (pos < 4)
		break;		/* packets can't be shorter */
	      for (i = 0; i < pos - 1; i++)
		parity ^= buf[i];
	      if (parity != buf[pos - 1])
		{
		  sendbyte (NACK);
		  sendbyte (PRT_E_PAR);
		}
	      else if (buf[pos - 2] == old_pktnbr)
		{
		  sendbyte(ACK);
		  pktready = 0;
		  pos = 0;
		  return (EOF);
		}
	      else
		{
		  /* packet is OK */
		  sendbyte (ACK);
		  old_pktnbr = buf[pos - 2];
		  pos -= 2;	/* now forget about packet number and parity */
		  p = 0;
		  pktready = 1;
		}
	      break;
	    }
	  default:
	    if (pos < DIM_INBUFSZ)
	      buf[pos++] = c;
	    break;
	  }
    }
  
  /* Packet is OK, we go inside */
  if (pktready)
    {
      int lg;
      for (lg = 0; res == EOF; )
	{
	  /* let's look at the next message */
	  lg = buf[p++];
	  if (lg >= 0x80 || p + lg > pos)
	    {
	      pktready = 0;	/* we are done with this packet */
	      break;
	    }
	  if (buf[p] == 'K' && buf[p + 1] != 'B' && context == 4)
	    {
	      context = 0;
	      alt = 0;
	      control = 0;
	    }
	  switch (buf[p])
	    {
	    case 'R': /* Mode checking */
	      switch(buf[p + 1])
		{
		case 'B': /* PC-BRAILLE mode */
		  if (JustIdentified == 0)
		  {
		    unsigned char AskIdent[] = {2, 'S', 'I'};

		    LogPrint(LOG_INFO, "EuroBraille terminal came in PC mode.");
		    WriteToBrlDisplay(brl, sizeof(AskIdent), AskIdent);
		    JustIdentified = 0;
		    ReWrite = 1; /* to refresh display */
		    context = 0;
		  
		    res = BRL_CMD_NOOP;
		  }
		  else
		    JustIdentified = 0;
		  break;
		case 'K': /* Leaving PC-Braille mode */
		  LogPrint(LOG_INFO, "EuroBraille terminal is quitting PC mode.");
		  break;
		case 'V': /* Braille and Speech mode */
		  message("! Speech unavailable", MSG_WAITKEY);
		  break;
		}
	      break;
	    case 'K':      /* Keyboard -- here are the key bindings */
	      switch (buf[p + 1])
		{
		case 'T':
		  {
		    int	p2;
		    
		   for (p2 = 0; num_keys[p2].brl_key; p2++)
		      if (buf[p + 2] == num_keys[p2].brl_key)
			res = num_keys[p2].res;
		  }
		  break;
		case 'I':	/* Routing Key */
		  res = routing(brl, buf[p + 2]);
		  break;
		case 'B':	/* Braille keyboard */
		  res = key_handle(brl, buf + p + 2);
		  break;
		}
	      break;
	    case 'S':		/* status information */
	      if (buf[p + 1] == 'I')
		{
		  /* we take the third letter from the model identification
		   * string as the amount of cells available and the two first letters
		   * for the model name in order to optimize the key configuration.
		   */
		  JustIdentified = 1;
		  if (buf[p + 2] == 'N' && buf[p + 3] == 'B')
		    model_ID = 1;
		  else if (buf[p + 2] == 'C' && buf[p + 3] == 'N')
		    model_ID = 2;
		  else if (buf[p + 2] == 'S' && 
			   ((buf[p + 3] == 'C') || (buf[p + 3] == 'B')))
		    model_ID = 3;
		  else if (buf[p + 2] == 'C' && (buf[p + 3] == 'Z' || buf[p + 3] == 'P'))
		    model_ID = 4;
		  else if (buf[p + 2] == 'I' &&
			   (buf[p + 3] == 'R' || buf[p + 3] == 'S'))
		    model_ID = 5;
		  else
		    model_ID = 0;
		  //		  if (strncmp(version_ID, (char *)(buf + p + 2), 3))
		    {
		      strncpy(version_ID, (char *)(buf + p + 2), 20);
		      NbCols = (buf[p + 4] - '0') * 10;
		      if (model_ID == 5 && NbCols == 30)
			NbCols += 2;
		      LogPrint(LOG_INFO, "Detected EuroBraille version %s: %d columns",
			       version_ID, NbCols);
		      brl->x = NbCols;
		      rawdata = realloc(rawdata, brl->y * brl->x);
		      prevdata = realloc(prevdata, brl->x * brl->y);
		      lcd_data = realloc(lcd_data, brl->x * brl->y);
		      brl->resizeRequired = 1;
		    }
		}
	      ReWrite = 1;
	    }
	  break;
	}
      p += lg;
    }
  return (res);
}
