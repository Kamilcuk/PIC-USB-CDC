/*
 File: usbpic_defs.h

 Copyright (c) 2010,2013 Kustaa Nyholm / SpareTimeLabs

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


 Version 1.1     Compatible with SDCC 3.x
 Respond to GET_LINE_CODING to work with overzealous
 Windows software (like Hyperterminal)
 */
#ifndef USBPIC_DEFS_H
#define USBPIC_DEFS_H

// Version 1.1     Compatible with SDCC 3.x

// Buffer Descriptor bit masks (from PIC datasheet)
#define UOWN   0x80 // USB Own Bit
#define DTS    0x40 // Data Toggle Synchronization Bit
#define KEN    0x20 // BD Keep Enable Bit
#define INCDIS 0x10 // Address Increment Disable Bit
#define DTSEN  0x08 // Data Toggle Synchronization Enable Bit
#define BSTALL 0x04 // Buffer Stall Enable Bit
#define BC9    0x02 // Byte count bit 9
#define BC8    0x01 // Byte count bit 8

typedef struct _BDT
{
    unsigned char STAT;
    unsigned char CNT;
    unsigned int ADDR;
} BDT; //Buffer Descriptor Table

// Every device request starts with an 8 unsigned char setup packet (USB 2.0, chap 9.3)
// with a standard layout.  The meaning of wValue and wIndex will
// vary depending on the request type and specific request.
typedef struct _setup_packet_struct
{
    unsigned char bmrequesttype; // D7: Direction, D6..5: Type, D4..0: Recipient
    unsigned char brequest;      // Specific request
    unsigned char wvalue0;       // LSB of wValue
    unsigned char wvalue1;       // MSB of wValue
    unsigned char windex0;       // LSB of wIndex
    unsigned char windex1;       // MSB of wIndex
    unsigned short wlength;       // Number of unsigned chars to transfer if there's a data stage
    unsigned char extra[56];     // Fill out to same size as Endpoint 0 max buffer
} setup_packet_struct;

#define USTAT_IN (0x04)
#define USTAT_OUT (0x00)

//endpoints
volatile BDT __at (0x0400+0*8) ep0_o;
volatile BDT __at (0x0404+0*8) ep0_i;
volatile BDT __at (0x0400+1*8) ep1_o;
volatile BDT __at (0x0404+1*8) ep1_i;
volatile BDT __at (0x0400+2*8) ep2_o;
volatile BDT __at (0x0404+2*8) ep2_i;
volatile BDT __at (0x0400+3*8) ep3_o;
volatile BDT __at (0x0404+3*8) ep3_i;

#endif
