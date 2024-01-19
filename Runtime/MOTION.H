// PCI8164/MPC8164
#ifndef _MOTION
#define _MOTION

#define SOFT_VERSION 12345

#define LCR_BASE 0XC400			// For example
#define MOTION_BASE 0xC800      // For example
#define IRQ_CH	11				// For example

//#define FNTYPE PASCAL
#define _OUTPORTB _outp
#define _OUTPORTW _outpw
#define _OUTPORTD outword
#define _INPORTB _inp
#define _INPORTW _inpw
#define _INPORTD inword
#define _outpd	outword
#define _inpd	inword
//#define _SLEEP Sleep



#endif
