/*
 * BRLTTY - A background process providing access to the console screen (when in
 *          text mode) for a blind person using a refreshable braille display.
 *
 * Copyright (C) 1995-2021 by The BRLTTY Developers.
 *
 * BRLTTY comes with ABSOLUTELY NO WARRANTY.
 *
 * This is free software, placed under the terms of the
 * GNU Lesser General Public License, as published by the Free Software
 * Foundation; either version 2.1 of the License, or (at your option) any
 * later version. Please see the file LICENSE-LGPL for details.
 *
 * Web Page: http://brltty.app/
 *
 * This software is maintained by Dave Mielke <dave@mielke.cc>.
 */

/* Dot combinations mapped more than once:
 *    Dots     Bytes
 *    0        0X00 0X20
 *    12345678 0XDB 0XFF
 *    1234568  0XC0 0XE1
 *    12346    0X2B 0X98
 *    123468   0X26 0XE0
 *    1246     0X8D 0X95
 *    126      0X3C 0XA1
 *    1456     0X25 0XA2
 *    156      0X3E 0X8C
 *    16       0X86 0XA0
 *    167      0X8F 0XA4
 *    1678     0XEB 0XF8
 *    235678   0XF6 0XFA
 *    23568    0XB7 0XBD
 *    2358     0X21 0X9E
 *    2368     0XB8 0XE8
 *    2578     0XC6 0XFC
 *    267      0XBA 0XC5
 *    346      0X5F 0XF7
 *    3578     0X9D 0XDE
 *    358      0X9B 0XEA
 *    38       0XA8 0XBB
 *    4        0X40 0X60
 *    457      0X5E 0XBE
 *    467      0XB6 0XF4
 *    5        0X27 0XB2
 *    58       0X87 0XAD
 *    7        0XF2 0XFD
 *    8        0XB9 0XFE
 */

/* Unmapped dot combinations:
 *    1234567
 *    123567
 *    12467
 *    12568
 *    134568
 *    13458
 *    1358
 *    1467
 *    1468
 *    234567
 *    234568
 *    235
 *    2367
 *    237
 *    2468
 *    256
 *    25678
 *    28
 *    34568
 *    3468
 *    347
 *    348
 *    357
 *    37
 *    45
 *    4578
 *    458
 *    57
 *    67
 */

MAP(0X00, 0),
MAP(0X01, BRL_DOT1|BRL_DOT7|BRL_DOT8),
MAP(0X02, BRL_DOT1|BRL_DOT2|BRL_DOT7|BRL_DOT8),
MAP(0X03, BRL_DOT1|BRL_DOT4|BRL_DOT7|BRL_DOT8),
MAP(0X04, BRL_DOT1|BRL_DOT4|BRL_DOT5|BRL_DOT7|BRL_DOT8),
MAP(0X05, BRL_DOT1|BRL_DOT5|BRL_DOT7|BRL_DOT8),
MAP(0X06, BRL_DOT1|BRL_DOT2|BRL_DOT4|BRL_DOT7|BRL_DOT8),
MAP(0X07, BRL_DOT1|BRL_DOT2|BRL_DOT4|BRL_DOT5|BRL_DOT7|BRL_DOT8),
MAP(0X08, BRL_DOT1|BRL_DOT2|BRL_DOT5|BRL_DOT7|BRL_DOT8),
MAP(0X09, BRL_DOT2|BRL_DOT4|BRL_DOT7|BRL_DOT8),
MAP(0X0A, BRL_DOT2|BRL_DOT4|BRL_DOT5|BRL_DOT7|BRL_DOT8),
MAP(0X0B, BRL_DOT1|BRL_DOT3|BRL_DOT7|BRL_DOT8),
MAP(0X0C, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT7|BRL_DOT8),
MAP(0X0D, BRL_DOT1|BRL_DOT3|BRL_DOT4|BRL_DOT7|BRL_DOT8),
MAP(0X0E, BRL_DOT1|BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT7|BRL_DOT8),
MAP(0X0F, BRL_DOT1|BRL_DOT3|BRL_DOT5|BRL_DOT7|BRL_DOT8),
MAP(0X10, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT7|BRL_DOT8),
MAP(0X11, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT7|BRL_DOT8),
MAP(0X12, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT5|BRL_DOT7|BRL_DOT8),
MAP(0X13, BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT7|BRL_DOT8),
MAP(0X14, BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT7|BRL_DOT8),
MAP(0X15, BRL_DOT1|BRL_DOT3|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0X16, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0X17, BRL_DOT2|BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0X18, BRL_DOT1|BRL_DOT3|BRL_DOT4|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0X19, BRL_DOT1|BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0X1A, BRL_DOT1|BRL_DOT3|BRL_DOT5|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0X1B, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT5|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0X1C, BRL_DOT3|BRL_DOT4|BRL_DOT7|BRL_DOT8),
MAP(0X1D, BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0X1E, BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0X1F, BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0X20, 0),
MAP(0X21, BRL_DOT2|BRL_DOT3|BRL_DOT5|BRL_DOT8),
MAP(0X22, BRL_DOT5|BRL_DOT6),
MAP(0X23, BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT6),
MAP(0X24, BRL_DOT4|BRL_DOT6),
MAP(0X25, BRL_DOT1|BRL_DOT4|BRL_DOT5|BRL_DOT6),
MAP(0X26, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT6|BRL_DOT8),
MAP(0X27, BRL_DOT5),
MAP(0X28, BRL_DOT2|BRL_DOT3|BRL_DOT6),
MAP(0X29, BRL_DOT3|BRL_DOT5|BRL_DOT6),
MAP(0X2A, BRL_DOT3|BRL_DOT5),
MAP(0X2B, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT6),
MAP(0X2C, BRL_DOT2),
MAP(0X2D, BRL_DOT3|BRL_DOT6),
MAP(0X2E, BRL_DOT3),
MAP(0X2F, BRL_DOT3|BRL_DOT4),
MAP(0X30, BRL_DOT2|BRL_DOT4|BRL_DOT5|BRL_DOT8),
MAP(0X31, BRL_DOT1|BRL_DOT8),
MAP(0X32, BRL_DOT1|BRL_DOT2|BRL_DOT8),
MAP(0X33, BRL_DOT1|BRL_DOT4|BRL_DOT8),
MAP(0X34, BRL_DOT1|BRL_DOT4|BRL_DOT5|BRL_DOT8),
MAP(0X35, BRL_DOT1|BRL_DOT5|BRL_DOT8),
MAP(0X36, BRL_DOT1|BRL_DOT2|BRL_DOT4|BRL_DOT8),
MAP(0X37, BRL_DOT1|BRL_DOT2|BRL_DOT4|BRL_DOT5|BRL_DOT8),
MAP(0X38, BRL_DOT1|BRL_DOT2|BRL_DOT5|BRL_DOT8),
MAP(0X39, BRL_DOT2|BRL_DOT4|BRL_DOT8),
MAP(0X3A, BRL_DOT2|BRL_DOT5),
MAP(0X3B, BRL_DOT2|BRL_DOT3),
MAP(0X3C, BRL_DOT1|BRL_DOT2|BRL_DOT6),
MAP(0X3D, BRL_DOT2|BRL_DOT3|BRL_DOT5|BRL_DOT6),
MAP(0X3E, BRL_DOT1|BRL_DOT5|BRL_DOT6),
MAP(0X3F, BRL_DOT2|BRL_DOT6),
MAP(0X40, BRL_DOT4),
MAP(0X41, BRL_DOT1|BRL_DOT7),
MAP(0X42, BRL_DOT1|BRL_DOT2|BRL_DOT7),
MAP(0X43, BRL_DOT1|BRL_DOT4|BRL_DOT7),
MAP(0X44, BRL_DOT1|BRL_DOT4|BRL_DOT5|BRL_DOT7),
MAP(0X45, BRL_DOT1|BRL_DOT5|BRL_DOT7),
MAP(0X46, BRL_DOT1|BRL_DOT2|BRL_DOT4|BRL_DOT7),
MAP(0X47, BRL_DOT1|BRL_DOT2|BRL_DOT4|BRL_DOT5|BRL_DOT7),
MAP(0X48, BRL_DOT1|BRL_DOT2|BRL_DOT5|BRL_DOT7),
MAP(0X49, BRL_DOT2|BRL_DOT4|BRL_DOT7),
MAP(0X4A, BRL_DOT2|BRL_DOT4|BRL_DOT5|BRL_DOT7),
MAP(0X4B, BRL_DOT1|BRL_DOT3|BRL_DOT7),
MAP(0X4C, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT7),
MAP(0X4D, BRL_DOT1|BRL_DOT3|BRL_DOT4|BRL_DOT7),
MAP(0X4E, BRL_DOT1|BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT7),
MAP(0X4F, BRL_DOT1|BRL_DOT3|BRL_DOT5|BRL_DOT7),
MAP(0X50, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT7),
MAP(0X51, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT7),
MAP(0X52, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT5|BRL_DOT7),
MAP(0X53, BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT7),
MAP(0X54, BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT7),
MAP(0X55, BRL_DOT1|BRL_DOT3|BRL_DOT6|BRL_DOT7),
MAP(0X56, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT6|BRL_DOT7),
MAP(0X57, BRL_DOT2|BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT7),
MAP(0X58, BRL_DOT1|BRL_DOT3|BRL_DOT4|BRL_DOT6|BRL_DOT7),
MAP(0X59, BRL_DOT1|BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT7),
MAP(0X5A, BRL_DOT1|BRL_DOT3|BRL_DOT5|BRL_DOT6|BRL_DOT7),
MAP(0X5B, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT5|BRL_DOT6),
MAP(0X5C, BRL_DOT1|BRL_DOT4|BRL_DOT6),
MAP(0X5D, BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT6),
MAP(0X5E, BRL_DOT4|BRL_DOT5|BRL_DOT7),
MAP(0X5F, BRL_DOT3|BRL_DOT4|BRL_DOT6),
MAP(0X60, BRL_DOT4),
MAP(0X61, BRL_DOT1),
MAP(0X62, BRL_DOT1|BRL_DOT2),
MAP(0X63, BRL_DOT1|BRL_DOT4),
MAP(0X64, BRL_DOT1|BRL_DOT4|BRL_DOT5),
MAP(0X65, BRL_DOT1|BRL_DOT5),
MAP(0X66, BRL_DOT1|BRL_DOT2|BRL_DOT4),
MAP(0X67, BRL_DOT1|BRL_DOT2|BRL_DOT4|BRL_DOT5),
MAP(0X68, BRL_DOT1|BRL_DOT2|BRL_DOT5),
MAP(0X69, BRL_DOT2|BRL_DOT4),
MAP(0X6A, BRL_DOT2|BRL_DOT4|BRL_DOT5),
MAP(0X6B, BRL_DOT1|BRL_DOT3),
MAP(0X6C, BRL_DOT1|BRL_DOT2|BRL_DOT3),
MAP(0X6D, BRL_DOT1|BRL_DOT3|BRL_DOT4),
MAP(0X6E, BRL_DOT1|BRL_DOT3|BRL_DOT4|BRL_DOT5),
MAP(0X6F, BRL_DOT1|BRL_DOT3|BRL_DOT5),
MAP(0X70, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT4),
MAP(0X71, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT5),
MAP(0X72, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT5),
MAP(0X73, BRL_DOT2|BRL_DOT3|BRL_DOT4),
MAP(0X74, BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT5),
MAP(0X75, BRL_DOT1|BRL_DOT3|BRL_DOT6),
MAP(0X76, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT6),
MAP(0X77, BRL_DOT2|BRL_DOT4|BRL_DOT5|BRL_DOT6),
MAP(0X78, BRL_DOT1|BRL_DOT3|BRL_DOT4|BRL_DOT6),
MAP(0X79, BRL_DOT1|BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT6),
MAP(0X7A, BRL_DOT1|BRL_DOT3|BRL_DOT5|BRL_DOT6),
MAP(0X7B, BRL_DOT2|BRL_DOT3|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0X7C, BRL_DOT4|BRL_DOT5|BRL_DOT6),
MAP(0X7D, BRL_DOT3|BRL_DOT5|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0X7E, BRL_DOT6),
MAP(0X7F, BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT8),
MAP(0X80, BRL_DOT5|BRL_DOT7|BRL_DOT8),
MAP(0X81, BRL_DOT1|BRL_DOT2|BRL_DOT5|BRL_DOT6),
MAP(0X82, BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT6),
MAP(0X83, BRL_DOT1|BRL_DOT6|BRL_DOT8),
MAP(0X84, BRL_DOT3|BRL_DOT4|BRL_DOT5),
MAP(0X85, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT5|BRL_DOT6|BRL_DOT8),
MAP(0X86, BRL_DOT1|BRL_DOT6),
MAP(0X87, BRL_DOT5|BRL_DOT8),
MAP(0X88, BRL_DOT1|BRL_DOT2|BRL_DOT6|BRL_DOT8),
MAP(0X89, BRL_DOT1|BRL_DOT2|BRL_DOT4|BRL_DOT6|BRL_DOT8),
MAP(0X8A, BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT6|BRL_DOT8),
MAP(0X8B, BRL_DOT1|BRL_DOT5|BRL_DOT6|BRL_DOT7),
MAP(0X8C, BRL_DOT1|BRL_DOT5|BRL_DOT6),
MAP(0X8D, BRL_DOT1|BRL_DOT2|BRL_DOT4|BRL_DOT6),
MAP(0X8E, BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT7),
MAP(0X8F, BRL_DOT1|BRL_DOT6|BRL_DOT7),
MAP(0X90, BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT6|BRL_DOT7),
MAP(0X91, BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT8),
MAP(0X92, BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT7|BRL_DOT8),
MAP(0X93, BRL_DOT1|BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT8),
MAP(0X94, BRL_DOT2|BRL_DOT4|BRL_DOT6),
MAP(0X95, BRL_DOT1|BRL_DOT2|BRL_DOT4|BRL_DOT6),
MAP(0X96, BRL_DOT1|BRL_DOT5|BRL_DOT6|BRL_DOT8),
MAP(0X97, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT6|BRL_DOT7),
MAP(0X98, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT6),
MAP(0X99, BRL_DOT2|BRL_DOT4|BRL_DOT6|BRL_DOT7),
MAP(0X9A, BRL_DOT1|BRL_DOT2|BRL_DOT5|BRL_DOT6|BRL_DOT7),
MAP(0X9B, BRL_DOT3|BRL_DOT5|BRL_DOT8),
MAP(0X9C, BRL_DOT5|BRL_DOT6|BRL_DOT8),
MAP(0X9D, BRL_DOT3|BRL_DOT5|BRL_DOT7|BRL_DOT8),
MAP(0X9E, BRL_DOT2|BRL_DOT3|BRL_DOT5|BRL_DOT8),
MAP(0X9F, BRL_DOT2|BRL_DOT3|BRL_DOT5|BRL_DOT7),
MAP(0XA0, BRL_DOT1|BRL_DOT6),
MAP(0XA1, BRL_DOT1|BRL_DOT2|BRL_DOT6),
MAP(0XA2, BRL_DOT1|BRL_DOT4|BRL_DOT5|BRL_DOT6),
MAP(0XA3, BRL_DOT1|BRL_DOT2|BRL_DOT4|BRL_DOT5|BRL_DOT6),
MAP(0XA4, BRL_DOT1|BRL_DOT6|BRL_DOT7),
MAP(0XA5, BRL_DOT1|BRL_DOT2|BRL_DOT6|BRL_DOT7),
MAP(0XA6, BRL_DOT1|BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT7),
MAP(0XA7, BRL_DOT1|BRL_DOT2|BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT7),
MAP(0XA8, BRL_DOT3|BRL_DOT8),
MAP(0XA9, BRL_DOT3|BRL_DOT6|BRL_DOT7),
MAP(0XAA, BRL_DOT3|BRL_DOT6|BRL_DOT8),
MAP(0XAB, BRL_DOT2|BRL_DOT3|BRL_DOT8),
MAP(0XAC, BRL_DOT2|BRL_DOT5|BRL_DOT6|BRL_DOT8),
MAP(0XAD, BRL_DOT5|BRL_DOT8),
MAP(0XAE, BRL_DOT4|BRL_DOT8),
MAP(0XAF, BRL_DOT4|BRL_DOT7),
MAP(0XB0, BRL_DOT3|BRL_DOT4|BRL_DOT6|BRL_DOT7),
MAP(0XB1, BRL_DOT4|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XB2, BRL_DOT5),
MAP(0XB3, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT6),
MAP(0XB4, BRL_DOT2|BRL_DOT7),
MAP(0XB5, BRL_DOT2|BRL_DOT5|BRL_DOT7),
MAP(0XB6, BRL_DOT4|BRL_DOT6|BRL_DOT7),
MAP(0XB7, BRL_DOT2|BRL_DOT3|BRL_DOT5|BRL_DOT6|BRL_DOT8),
MAP(0XB8, BRL_DOT2|BRL_DOT3|BRL_DOT6|BRL_DOT8),
MAP(0XB9, BRL_DOT8),
MAP(0XBA, BRL_DOT2|BRL_DOT6|BRL_DOT7),
MAP(0XBB, BRL_DOT3|BRL_DOT8),
MAP(0XBC, BRL_DOT5|BRL_DOT6|BRL_DOT7),
MAP(0XBD, BRL_DOT2|BRL_DOT3|BRL_DOT5|BRL_DOT6|BRL_DOT8),
MAP(0XBE, BRL_DOT4|BRL_DOT5|BRL_DOT7),
MAP(0XBF, BRL_DOT2|BRL_DOT6|BRL_DOT8),
MAP(0XC0, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT8),
MAP(0XC1, BRL_DOT3|BRL_DOT7|BRL_DOT8),
MAP(0XC2, BRL_DOT1|BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XC3, BRL_DOT2|BRL_DOT4|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XC4, BRL_DOT2|BRL_DOT5|BRL_DOT6|BRL_DOT7),
MAP(0XC5, BRL_DOT2|BRL_DOT6|BRL_DOT7),
MAP(0XC6, BRL_DOT2|BRL_DOT5|BRL_DOT7|BRL_DOT8),
MAP(0XC7, BRL_DOT2|BRL_DOT3|BRL_DOT5|BRL_DOT6|BRL_DOT7),
MAP(0XC8, BRL_DOT7|BRL_DOT8),
MAP(0XC9, BRL_DOT2|BRL_DOT5|BRL_DOT8),
MAP(0XCA, BRL_DOT3|BRL_DOT5|BRL_DOT6|BRL_DOT7),
MAP(0XCB, BRL_DOT1|BRL_DOT3|BRL_DOT8),
MAP(0XCC, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT8),
MAP(0XCD, BRL_DOT1|BRL_DOT3|BRL_DOT4|BRL_DOT8),
MAP(0XCE, BRL_DOT4|BRL_DOT7|BRL_DOT8),
MAP(0XCF, BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XD0, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT8),
MAP(0XD1, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT8),
MAP(0XD2, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT5|BRL_DOT8),
MAP(0XD3, BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT8),
MAP(0XD4, BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT8),
MAP(0XD5, BRL_DOT1|BRL_DOT3|BRL_DOT6|BRL_DOT8),
MAP(0XD6, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT6|BRL_DOT8),
MAP(0XD7, BRL_DOT2|BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT8),
MAP(0XD8, BRL_DOT1|BRL_DOT3|BRL_DOT4|BRL_DOT6|BRL_DOT8),
MAP(0XD9, BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XDA, BRL_DOT1|BRL_DOT3|BRL_DOT5|BRL_DOT6|BRL_DOT8),
MAP(0XDB, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XDC, BRL_DOT3|BRL_DOT4|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XDD, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XDE, BRL_DOT3|BRL_DOT5|BRL_DOT7|BRL_DOT8),
MAP(0XDF, BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT7),
MAP(0XE0, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT6|BRL_DOT8),
MAP(0XE1, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT8),
MAP(0XE2, BRL_DOT2|BRL_DOT3|BRL_DOT5|BRL_DOT7|BRL_DOT8),
MAP(0XE3, BRL_DOT1|BRL_DOT2|BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT8),
MAP(0XE4, BRL_DOT4|BRL_DOT6|BRL_DOT8),
MAP(0XE5, BRL_DOT2|BRL_DOT7|BRL_DOT8),
MAP(0XE6, BRL_DOT3|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XE7, BRL_DOT6|BRL_DOT8),
MAP(0XE8, BRL_DOT2|BRL_DOT3|BRL_DOT6|BRL_DOT8),
MAP(0XE9, BRL_DOT3|BRL_DOT5|BRL_DOT6|BRL_DOT8),
MAP(0XEA, BRL_DOT3|BRL_DOT5|BRL_DOT8),
MAP(0XEB, BRL_DOT1|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XEC, BRL_DOT1|BRL_DOT2|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XED, BRL_DOT1|BRL_DOT4|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XEE, BRL_DOT1|BRL_DOT5|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XEF, BRL_DOT1|BRL_DOT2|BRL_DOT4|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XF0, BRL_DOT1|BRL_DOT2|BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XF1, BRL_DOT1|BRL_DOT2|BRL_DOT5|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XF2, BRL_DOT7),
MAP(0XF3, BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT7),
MAP(0XF4, BRL_DOT4|BRL_DOT6|BRL_DOT7),
MAP(0XF5, BRL_DOT2|BRL_DOT3|BRL_DOT7|BRL_DOT8),
MAP(0XF6, BRL_DOT2|BRL_DOT3|BRL_DOT5|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XF7, BRL_DOT3|BRL_DOT4|BRL_DOT6),
MAP(0XF8, BRL_DOT1|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XF9, BRL_DOT5|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XFA, BRL_DOT2|BRL_DOT3|BRL_DOT5|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XFB, BRL_DOT2|BRL_DOT6|BRL_DOT7|BRL_DOT8),
MAP(0XFC, BRL_DOT2|BRL_DOT5|BRL_DOT7|BRL_DOT8),
MAP(0XFD, BRL_DOT7),
MAP(0XFE, BRL_DOT8),
MAP(0XFF, BRL_DOT1|BRL_DOT2|BRL_DOT3|BRL_DOT4|BRL_DOT5|BRL_DOT6|BRL_DOT7|BRL_DOT8)
