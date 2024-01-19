#ifndef _8164DRV_H

#define _8164DRV_H

#include "motion.h"
#include "pci_8164.h"
#include "pcl6045.h"

#define OS_Unknow		(I16)0
#define OS_MSDOS		(I16)1
#define OS_WIN_31		(I16)2
#define OS_WIN_95		(I16)3
#define OS_WIN_98		(I16)4
#define OS_WIN_351		(I16)5
#define OS_WIN_40		(I16)6
#define OS_WIN_2K		(I16)7
#define OS_WIN_XP		(I16)8
#define OS_LINUX		(I16)9
#define OS_WIN_CE		(I16)10

//#define VENDOR_ID       (U16)0x144a
//#define DEVICE_ID       (U16)0x8164

//	#include <windows.h>
//    #include "pcibios.h"   // Win9x
#include "type_def.h"


typedef union
{
  U32 Full;
  U16 Half[2];
} DATA32;

typedef struct
{
  I16 Counts;	  // Interpolation Axes Counts
  U16 AxesIndex;  // Bit 8,9,10,11
} INTERPOLATION;

typedef struct
{
	F64 RefPos;
	F64 StrPos;
	I16 Conti;
	I16 Conti_Index;
	I16 FIX_SPEED;
	I16 LineMoveMode;
	F64 FA_SPEED;
	I16 INP_Enable;
	I16 PCS_ON;
	I16 SD_ON;
	I16 CSTP_ON;
	I16 CSTPOut_ON;
	I16 Sync_Option1;
	I16 Sync_Option2;
	I16 INT_Stop;
	I16 MIPF_ON;
	I16 MIPE_ON;

	F64 Tdec[3];
	F64 Speed_Ratio[3];
	I16 Master_Axis[3];
	
    F64 M_RATIO;
	F64 ORG_Offset;
  
	DATA32 ENV1;
	DATA32 ENV2;
	DATA32 ENV3;
	DATA32 ENV4;
	DATA32 ENV5;
	DATA32 ENV6;
	DATA32 ENV7;
	DATA32 RMD;
	DATA32 INTF;
	DATA32  RMV;
	DATA32  RFL;
	DATA32  RFH;
	DATA32  RUR;
	DATA32  RDR;
	DATA32  RMG;
	DATA32  RDP;
	DATA32  RIP;
	DATA32  RUS;
	DATA32  RDS;
	DATA32  RFA;
	DATA32	RCI;

	INTERPOLATION IPL_Check;
	I16 FbkSrc;

} AXIS_INFO,*pAXIS_INFO;

typedef struct
{

	U16    initFlag;
	U16    lcrBase;
	U16    baseAddr;
	U16    irqNo;
	U16    CPLD_Ctrl;

	AXIS_INFO AXIS[AXIS_PER_CHIP];

	I16 AutoRDP;

} PCI_Info;


typedef struct
{
    U16 baseAddr[MAX_PCI_CARDS];
	U16 lcrAddr[MAX_PCI_CARDS];
	U16 irqNo   [MAX_PCI_CARDS];
} PCI_INFO;


I16 i_check_os_version(void);
///void i_do_events(void);
I16 i_wdm_get_card_info(I16 cn);

I32 i_usleep(I32 uSecond);
I16 i_cpld_ctrl(I16 CardNo, U16 Data);

I16 i_get_sub_status(I16 AxisNo, U16 *sub_sts);
I16 i_get_main_status(I16 AxisNo, U16 *main_sts);
I16 i_set_cmd(I16 AxisNo, U16 cmd);
I16 i_set_gpio(I16 AxisNo, U16 gpio);
I16 i_set_pci_info(I16 AxisNo);
I16 i_software_reset(I16 cardNo);
I16 i_write_reg(I16 AxisNo, U16 CmdNo, U16 Low, U16 High);
I16 i_read_reg(I16 AxisNo, U16 CmdNo, U16 *Low, U16 *High);
F64  i_set_speed(I16 AxisNo,F64 StrVel,F64 MaxVel,I16 Pre);
I16 i_set_fa_speed(I16 AxisNo, F64 FaVel);
I16 i_set_s_accel(I16 AxisNo, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec,I16 Pre);
I16 i_set_t_accel(I16 AxisNo, F64 Tacc, F64 Tdec,I16 Pre);
I16 i_check_s_rmv(I16 AxisNo, I16 Pre);
I16 i_set_s_rdp(I16 AxisNo,I16 Pre,I16 HasRDP);
I16 i_set_rmv(I16 AxisNo, F64 Dist,I16 Pre);
I16 i_set_rip(I16 AxisNo, F64 Rip,I16 Pre);
I16 i_check_t_rmv(I16 AxisNo, I16 Pre);
I16 i_set_t_rdp(I16 AxisNo,I16 Pre, I16 HasRDP);

I16 i_6045_reset(I16 AxisNo);
I16 i_set_user_io_pin3( I16 CardNo ,I16 On_Off );
I16  i_cpld_version(I16 CardNo);
I16  i_get_plx_usr(I16 CardNo);
I16 i_hardware_int_control(I16 CardNo,I16 CH0, I16 CH0_CTRL, I16 CH1, I16 CH1_CTRL);
void  i_pause_for_stable(I16 CardNo);

I16 i_get_rcic(I16 AxisNo, I32 *Dist);


extern PCI_Info pci_Info[MAX_PCI_CARDS];
extern I16 OSVer;
extern U16 PLX_USR[MAX_PCI_CARDS][2];
extern I16 TotalAxes;
extern I16 TotalCard;


#define SayOut(Format, Arg1, Arg2, Arg3, Arg4, Arg5)                    \
            {                                                       \
                printf(Format, Arg1, Arg2, Arg3, Arg4, Arg5);             \
                printf("\n");                                       \
            }



#endif
