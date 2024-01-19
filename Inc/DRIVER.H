/****************************************************************************

                            Driver.h

     Driver specfic UIOT structures and adjunct to the network node

*****************************************************************************/



#ifndef __DRIVER_H__
#define __DRIVER_H__

#define VENDOR_ID	0x144A
#define DEVICE_ID	0x8164
#define SUB_ID		0x8164  
#define BAR_ADDR_TO_READ 0x1  
#define BAR_ADDR_TO_READ2 0x2  
#define TASKNAME	"PCI8164"

#define DriverID       0x14538164L



#define DriverVERS          0x00030009L
#define NETCONFIG_ID        0x00030009L
#define NETCONFIG_VERS      0x00030009L
#define DEVCONFIG_VERS      0x00030009L     



#define DEVCONFIG_ID        0x12345678L    
#define RT3_SENTINEL        0x55667788L


// max Num of networks can be controlled by 1 PC
#define  MAX_DRV_INSTANCES          12      


#include  "errors.h"

#ifndef APSTUDIO_READONLY_SYMBOLS


#ifndef VLCPORT_H__
#include "vlcport.h"
#pragma warning( disable: 4244 )
#endif

#ifndef DATASEG_H__
#include "dataseg.h"
#endif



//************   1 byte alignment typedef structures !!!   ************

#pragma BYTE_ALIGN(_SPECIAL_INST)
typedef struct _SPECIAL_INST*  LPSPECIAL_INST_;
typedef UINT8*  LPUINT8;


typedef  selector   SEMAPHORE;

typedef  UINT32     UIOTREF2CHAR;
typedef  UINT32     UIOTREF2SINT8;
typedef  UINT32     UIOTREF2UINT8;
typedef  UINT32     UIOTREF2SINT16;
typedef  UINT32     UIOTREF2UINT16;
typedef  UINT32     UIOTREF2SINT32;
typedef  UINT32     UIOTREF2UINT32;
typedef  UINT32     UIOTREF2DOUBLE;
typedef  UINT32     UIOTREF2VOID;


#pragma BYTE_ALIGN(_LINKED_LIST)
typedef struct _LINKED_LIST 
{
    LPSPECIAL_INST_     pHead;      
    LPSPECIAL_INST_     pTail;      
    SEMAPHORE           Semaphore;  
    UINT16              uCounter;   
} LINKED_LIST, *LPLINKED_LIST; 
#pragma BYTE_NORMAL()


#pragma BYTE_ALIGN(_PTBUFFER)
typedef struct _PTBUFFER 
{
    UIOTREF2VOID    Offset;  
    UINT32          Size;           
} PTBUFFER, * LPPTBUFFER;           
#pragma BYTE_NORMAL()


#pragma BYTE_ALIGN(_TASK)
typedef struct _TASK 
{
    UINT16      hTask;          
    SEMAPHORE   Semaphore;      
    void*       pStack;         
    UINT16      bBusy;          
    UINT16      Error;          
    void*       IrqThunk;       
    UINT16      level;          
    UINT16      align;
} TASK, * LPTASK; 
#pragma BYTE_NORMAL()





#pragma BYTE_ALIGN(_DEVICE_IO)  
typedef struct _DEVICE_IO       
{
    void*        pSrc;          
    void*        pDst;          // UIOT offset/pointer for input devices || DPR  offset/pointer for output devices
    UIOTREF2VOID ofsUiot;       // ofsDst for input devices or ofsSrc for output devices
    UINT16       Size;          // device input or output size.  Never 0 !!!
    UINT16       bUsed;         // If no I/O tags defined in the UIOT, skip it
} DEVICE_IO, *LPDEVICE_IO;            
#pragma BYTE_NORMAL()


#pragma BYTE_ALIGN(_DEVICE_INST)         // 1 byte alignment
typedef struct _DEVICE_INST
{
    UIOTREF2VOID ofsName;       // UIOT offset to the device name generated at compile time
    UINT16       Address;       // device's network address
    UINT16       Type;          // DEVICE_1W_INPUT, ... Never 0 !!!
    UINT16       Spare1;	
	UINT16       Spare2;
    UINT16       bPresent;      // if 1 --> device was online when load and go
    char*        pName;         // Usable UIOT pointer to the device name generated at runtime based on ofsName.
	DEVICE_IO	 Input;			// how to handle the input image
	DEVICE_IO	 Output;		// how to handle the output image
	UINT32       Sentinel;
} DEVICE_INST, *LPDEVICE_INST;
#pragma BYTE_NORMAL()




#pragma BYTE_ALIGN(_DRIVER_INST) 
typedef struct _DRIVER_INST 
{
    NETWORK Net;

        // Compile-time Static variables.  This structure maps to UIOT

    UIOTREF2VOID    ofsDeviceList;      // Where the DEVICE_INST list starts.
    UINT32          nDevices;           // how many Devices are in the list
	UINT16			PciIndex;			// 1...max  which board 
	UINT16			PciCount;			// 0...max  how many boards expected in the system. 0--> skip test.
	UINT32          PhyAddr;            // BARx read from the PCI card
    UINT16          NumChannels;        // not used, maybe no.axis
    UINT16          bSimulate;          // =0 --> interface card must be present
    
        // Run-time Dynamic Variables
    LPDEVICE_INST   pDeviceList;        // Where the DEVICE_INST list starts.

	/// TODO if io map exist
    LPDEVICE_IO     pInputList;         // Where in the DEVICE_IO  Input list starts
    LPDEVICE_IO     pOutputList;        // Where in the DEVICE_IO Output list starts

	void* 			pDpr;               // virtual pointer built based on BARx, if supported
    UINT16          bFirstCycle;        // Set by OnLine(), reset by Output(). Read by Input() and Output()
    UINT16          bGoOffLine;         // Tell all the bkg functions to shutdown

    LINKED_LIST     Pend;               // Pointer to the linked list of pending functions
    LINKED_LIST     Done;               // Pointer to the linked list of done  functions

    TASK            BackgroundTask;     // controls for the background task
    TASK            InterruptTask;      // controls for the interrupt task
	UIOTREF2UINT8   ofsConfigFile;      // Where the config file can be found in the UIOT
    UINT32          szConfigFile;       // How many bytes in the config file
	long			ShareMemPool;		// not used
    char            ConfigFile[64];		// 28  File name for the configuration file


    UIOTREF2UINT32  ofsSentinel;        // 0x55667788 - display this value using Soft Scope to check corrct map
    UINT32          Sentinel;           // 0x55667788 - display this value using Soft Scope to check corrct map

} DRIVER_INST, *LPDRIVER_INST;    
#pragma BYTE_NORMAL() 


#pragma BYTE_ALIGN( _SPECIAL_INST_HEADER )      // Must be first block in all paremeter blocks
typedef struct _SPECIAL_INST_HEADER
{       // Compile-time Static variables.  This structure maps to .rcd descrition
                                    // off, sz, ob.sz
    UINT16          FunctionId;     //  0    2   2L   PT_CONST  --> UINT16, _SIZE 2L
    UINT16          Spare;        //  2    2		USUALLY SPARE
    UIOTREF2UINT16  ofsStatus;      //  4    4   2L   PT_REF    --> tag's offset in the UIOT
    UIOTREF2UINT16  ofsResult;      //  8    4   2L   PT_REF    --> tag's offset in the UIOT
} SPECIAL_INST_HEADER;              //      12 == sizeof( SPECIAL_INST_HEADER )

#pragma BYTE_NORMAL()
/*
    Note: beacuse all functions have an Id field and a return status, we can standardize them 
    at offsets 0 and 4. This is especially helpful when using customized parameter structures 
    to better match function particularities and to save memory. 
*/

/////// DRVF_MOTION def
#pragma BYTE_ALIGN( _SPECIAL_INST_COMMAND ) 
typedef struct _SPECIAL_INST_COMMAND
{       // Compile-time Static variables.  This structure maps to .rcd descrition
                                        // off, sz, ob.sz
    SPECIAL_INST_HEADER Header;         //  0   12        the header must always be first
    UINT16      AxisAddress;        // 12  2   2L   PT_VALUE, PT_DEVICE --> UINT32
    UINT16	    Function;		// 14    2   2L   PT_REF    --> tag's offset in the UIOT
	double		fPos;		
	double      fstVel;
	double      fmaxVel;
	double      fTAcc;
	double      fTDec;
	double      fSVAcc;
	double      fSVDec;

	double      fPosX;
	double      fPosY;
	double      fPosZ;
	double      fPosU;

	double      fCx;
	double      fCy;
	double      fEx;
	double      fEy;
	double      fOrg;
	PTBUFFER	AxisArray;
	SINT16		OptDir;
	SINT16		Spare;

	
} SPECIAL_INST_COMMAND;                 //      48 == sizeof( SPECIAL_INST_COMMAND )
#pragma BYTE_NORMAL()


/// DRVF_MOTION_INT/F64
#pragma BYTE_ALIGN( _SPECIAL_INST_OTHERS ) 
typedef struct _SPECIAL_INST_OTHERS
{       // Compile-time Static variables.  This structure maps to .rcd descrition
                                        // off, sz, ob.sz
    SPECIAL_INST_HEADER Header;         //  0   12        the header must always be first
    UINT16      AxisAddress;        // 12   2   2L   PT_VALUE, PT_DEVICE --> UINT32
    UINT16	    Function;		// 14   2   2L   PT_REF    --> tag's offset in the UIOT
UIOTREF2SINT16	iGetValue;			//16
	SINT16		iSetValue1;			//20
	SINT16		iSetValue2;			//22
	SINT16		iSetValue3;			//24
	SINT16		iSetValue4;			//26
	SINT16		iSetValue5;			//28
	SINT16		spare;			//		30

	double		fSetValue1;			//32
	double		fSetValue2;			//
	double		fSetValue3;			//
	double		fSetValue4;			//
	double		fSetValue5;			//
UIOTREF2DOUBLE  fGetValue;			//
	SINT16		spare2;			//		30


} SPECIAL_INST_OTHERS;                 //   76
#pragma BYTE_NORMAL()


#pragma BYTE_ALIGN( _SPECIAL_INST_SETGET ) 
typedef struct _SPECIAL_INST_SETGET
{       // Compile-time Static variables.  This structure maps to .rcd descrition
                                        // off, sz, ob.sz
    SPECIAL_INST_HEADER Header;         //  0   12        the header must always be first
    UINT16      AxisAddress;			// 72   2   2L   PT_VALUE, PT_DEVICE --> UINT32
    UINT16	    Function;				// 74    2   2L   PT_REF    --> tag's offset in the UIOT
	SINT32				ArraySize;		// 16	 4
    double				SetSingleValue;		// 20    8  
	PTBUFFER      SetValue;	// 24
	PTBUFFER      GetValue;	// 32

} SPECIAL_INST_SETGET;                  //     152 == sizeof( SPECIAL_INST_COMMAND )
#pragma BYTE_NORMAL()


typedef union _SPECIAL_INST_PARAM
{       // Compile-time Static variables.  This structure maps to .rcd descrition
                                         // off, sz
    SPECIAL_INST_HEADER  paramHeader;   //  0   12
    SPECIAL_INST_COMMAND paramCommand;  //  0   48
	SPECIAL_INST_SETGET  paramSetGet;
	SPECIAL_INST_OTHERS  paramOthers;

} SPECIAL_INST_PARAM;                   //      48 == sizeof(SPECIAL_INST_PARAM)

typedef struct _SPECIAL_INST
{       // Compile-time Static variables.  This structure maps to .rcd descrition
                                        // off,  sz
    SPECIAL_INST_PARAM  User;           //   0   48
    SPECIAL_INST_PARAM  Work;           //  48   48
        // generic, same for all drivers having asyncronous special functions
    UINT32                MarkTime;     //  96    4  when this s.f. must be complete
    SINT16                Status;       // 100    2
    UINT16                Busy;         // 102    2    
    struct _SPECIAL_INST* pNext;        // 104    4

} SPECIAL_INST, *LPSPECIAL_INST;        //      108 == sizeof( SPECIAL_INST )


#ifdef WINVER          // This is for MSVC compiler


#ifndef DRVRUTIL_H__
#include "drvrutil.h"   // SS_ZERO
#endif

// What we put into the database for network config

#pragma BYTE_ALIGN(_NETCONFIG)     // 1 byte alignment
typedef struct _NETCONFIG
{
    UINT32           NetcfgId;          //  0  NETCONFIG_ID
    UINT16           NetcfgVersMinor;   //  4  LOW(  NETCONFIG_VERS )
    UINT16           NetcfgVersMajor;   //  6  HIGH( NETCONFIG_VERS )
    UINT32           PciIndex;          //  8  1...8 max 8 boards in the system
    UINT16           PciCount;          // 12  0...8 if 0--> skip the count test
    UINT16           IrqLevel;          // 14  0 ... 15
//    UINT16           BaudRate;          // 16  BAUDRATE_125, BAUDRATE_250, ...
    UINT16			 NumChannels;       // 18  8 or 16 channels
    STOP_STATE_TYPES StopState;         // 18  SS_HOLD_LAST_STATE,  SS_ZERO

    UINT16           bSimulate;         // 20  =0 --> interface card must be present
    UINT16           bWatchdog;         // 22  =1 --> kick the watchdog
    UINT16           DprHWTests;        // 24  HWTEST_RW, HWTEST_OFF
    UINT16           InputRead;         // 26  INPUT_READ_CYCLIC, INPUT_READ_COS,
    UINT8            ConfigFile[64];   // 28  File name for the configuration file    
    UINT8            Reserved[128-92];  // 28  add new fields without changing NETCONFIG size
} NETCONFIG;                            // 128  == NET_CONFIG_SIZE == sizeof(NETCONFIG)
#pragma BYTE_NORMAL()


#pragma BYTE_ALIGN(_DEVCONFIG)  // 1 byte alignment
typedef struct _DEVCONFIG
{                               // Byte Offset
    UINT32  NetcfgId;           //  0 NETCONFIG_ID
    UINT32  DevcfgId;           //  4 DEVCONFIG_ID
    UINT16  DevcfgVersMinor;    //  8 LOW(  DEVCONFIG_VERS )
    UINT16  DevcfgVersMajor;    // 10 HIGH( DEVCONFIG_VERS )
    UINT16  Address;            // 12 device's address on the link
    UINT16  Reserved0;          // 14 =1 --> this device must be present on the link
	UINT16  Spare1;				// 16 Desired gain for input
	UINT16	Spare2;			// 18 TRUE if this is a bipolar channel
    UINT8   Reserved[128-20];	// 20 add new fields without changing NETCONFIG size
} DEVCONFIG;                    // 128 == DEVCONFIG_SIZE == sizeof(DEVCONFIG)
#pragma BYTE_NORMAL()
/*
    Note: The reserved fields will be used for future developpment. 
    They ensure compatibility with projects generated by older versions of this driver.
*/


#endif      // WINVER


#endif      // ! APSTUDIO_READONLY_SYMBOLS

/* 
    Defines for .rcd file 
    Arithmetic expressions are allowed to define RC and RCD constants, 
    when  ONLY using + and -.  
    It is a good idea to have them encapsulated in ( ).
    Never use * and /.  The RC compiler silently ignores them.
*/


// SPECIAL_INST offsets & sizes
#define FNC_HD_FUNCTIONID           0L 
#define FNC_HD_FUNCTIONID_SIZE          2L      
#define FNC_HD_STATUS               4L 
#define FNC_HD_STATUS_SIZE              2L  
#define FNC_HD_RESULT               8L 
#define FNC_HD_RESULT_SIZE              2L   
  
#define FNC_CM_AXISNUM               12L 
#define FNC_CM_AXISNUM_SIZE              2L    
#define FNC_CM_FUNCTIONID           14L 
#define FNC_CM_FUNCTIONID_SIZE           2L 

/////////// above always fix

#define FNC_CM_FINAL_POS             16L    
#define FNC_CM_FINAL_POS_SIZE            8L     
#define FNC_CM_ST_VEL              24L 
#define FNC_CM_ST_VEL_SIZE              8L     
#define FNC_CM_MAX_VEL               32L 
#define FNC_CM_MAX_VEL_SIZE              8L     
#define FNC_CM_ACC               40L 
#define FNC_CM_ACC_SIZE              8L     
#define FNC_CM_DEC               48L 
#define FNC_CM_DEC_SIZE              8L     
#define FNC_CM_SVACC              56L 
#define FNC_CM_SVACC_SIZE              8L    
#define FNC_CM_SVDEC              64L 
#define FNC_CM_SVDEC_SIZE              8L    

#define FNC_CM_POSX              72L 
#define FNC_CM_POSX_SIZE              8L    
#define FNC_CM_POSY              80L 
#define FNC_CM_POSY_SIZE              8L    
#define FNC_CM_POSZ              88L 
#define FNC_CM_POSZ_SIZE              8L    
#define FNC_CM_POSU              96L 
#define FNC_CM_POSU_SIZE              8L     

#define FNC_CM_CX              104L 
#define FNC_CM_CX_SIZE              8L    
#define FNC_CM_CY              112L 
#define FNC_CM_CY_SIZE              8L    
#define FNC_CM_EX              120L 
#define FNC_CM_EX_SIZE              8L    
#define FNC_CM_EY              128L 
#define FNC_CM_EY_SIZE              8L     

#define FNC_CM_ORG              136L 
#define FNC_CM_ORG_SIZE              8L     

#define FNC_CM_AXISARRY           144L 
#define FNC_CM_AXISARRY_SIZE        8L     

#define FNC_CM_OPT              152L 
#define FNC_CM_OPT_SIZE              2L //// TOTAL 144   



#define FNC_CM_ARRAYSIZE          16L    
#define FNC_CM_SET_SIZE            4L

#define FNC_CM_SET             20L    
#define FNC_CM_ARRAY_SIZE            8L

#define FNC_CM_SET_ARRAY       28L    
#define FNC_CM_GET_ARRAY       36L    




#define FNC_OT_GET             16L 
#define FNC_OT_GET_SIZE             4L      

#define FNC_OT_SET1             20L    
#define FNC_OT_SET2             22L    
#define FNC_OT_SET3             24L    
#define FNC_OT_SET4             26L   
#define FNC_OT_SET5             28L    
#define FNC_OT_SET_SIZE          2L     

#define FNC_OT_SET6             32L    
#define FNC_OT_SET7             40L    
#define FNC_OT_SET8             48L    
#define FNC_OT_SET9             56L    
#define FNC_OT_SET10            64L  
#define FNC_OT_SET_SIZE2		 8L     

#define FNC_OT_GET2             72L 
#define FNC_OT_GET_SIZE2	     8L     




#define FNC_HD_SPECIAL_INST_SIZE        12
#define FNC_CM_SPECIAL_INST_SIZE        156
#define FNC_OT_SPECIAL_INST_SIZE        88
#define FNC_SG_SPECIAL_INST_SIZE        48
#define FNC_SPECIAL_INST_SIZE           156


// NETCONFIG offsets & sizes
#define NET_ID                      0 
#define NET_ID_SIZE                     32 
#define NET_VERS                    4 
#define NET_VERS_SIZE                   32 
#define NET_PCI_INDEX               8 
#define NET_PCI_INDEX_SIZE              32 
#define NET_PCI_COUNT               12
#define NET_PCI_COUNT_SIZE              16 
#define NET_NUMCHANNELS             18 
#define NET_NUMCHANNELS_SIZE            16 
#define NET_SIMULATE                20 
#define NET_SIMULATE_SIZE               16 
#define NET_WATCHDOG                22 
#define NET_WATCHDOG_SIZE               16 
#define NET_HWTEST                  24 
#define NET_HWTEST_SIZE                 16 
#define NETCONFIG_SIZE              128 

// DEVICECONFIG offsets & sizes
#define DEV_DRVID                   0
#define DEV_DRVID_SIZE                  32
#define DEV_ID                      4
#define DEV_ID_SIZE                     32
#define DEV_VERS                    8
#define DEV_VERS_SIZE                   32
#define DEV_ADDRESS                 12 
#define DEV_ADDRESS_SIZE                16 
#define DEV_GAIN                    16 
#define DEV_GAIN_SIZE                   16 
#define DEV_BIPOLAR                 18 
#define DEV_BIPOLAR_SIZE                16 
#define DEVCONFIG_SIZE              128 


// This is for the demo only.  Replace it with the real settings. 
// Dual port ram layout
#define  DPR_CONTROL_OFF        0
#define  DPR_CONTROL_SIZE       2048
#define  DPR_INPUT_OFF          2048    // where the input image can be found in the dpr
#define  DPR_INPUT_SIZE         1024    // 1kbyte =  MAX_DEVICES * 8bytes input devices
#define  DPR_OUTPUT_OFF         3072    // where the output image can be found in the dpr
#define  DPR_OUTPUT_SIZE        1024    // 1kbyte =  MAX_DEVICES * 8bytes input devices
#define  DPR_TOTAL_SIZE         4096    // 4 kbytes
#define  MAX_DEVICES            4      // max 16 devices allowed by our didactical network


/*
#define  DPADR_MIN              0x80000L
#define  DPADR_MAX              0xef000L
#define  DPADR_STEP             0x01000L    // 4 kbytes increments
#define  DPADR_DEFAULT          0xd0000L

#define  PORT_MIN               0x100
#define  PORT_MAX               0x3fc
#define  PORT_STEP              4           // 4 bytes increments
#define  PORT_DEFAULT           0x250

#define  NO_IRQ                 0L
#define  HWTEST_RW              1
#define  HWTEST_OFF             0
#define  INPUT_READ_COS         1
#define  INPUT_READ_CYCLIC      0

#define  BAUDRATE_125           1
#define  BAUDRATE_250           2
#define  BAUDRATE_500           3
*/


#define	 DEV_NUM					10

#define  DEVICE_CARD_POS            10      

#define  DEVICE_CARD_IO_STATUS      20     
#define  DEVICE_CARD_IO_STATUS1     21  
#define  DEVICE_CARD_IO_STATUS2     22      
#define  DEVICE_CARD_IO_STATUS3     23      
#define  DEVICE_CARD_IO_STATUS4     24      

#define  DEVICE_CARD_INT_STATUS     30      
#define  DEVICE_CARD_INT_STATUS1    31     
#define  DEVICE_CARD_INT_STATUS2    32     
#define  DEVICE_CARD_INT_STATUS3    33     
#define  DEVICE_CARD_INT_STATUS4    34

#define	 DEVICE_CARD_MOTION_STATUS   40
#define DEVICE_CARD_INT_STATUS_ERROR 50
// io     
#define  DEVICE_1W_IANDO			 70

#define  DRVF_MOTION               100    
#define  DRVF_SETGET               101    
#define  DRVF_SETAXIS              102
#define  DRVF_OTHERS_INT           103    
#define  DRVF_OTHERS_F64           104    
#define  DRVF_ONFLY                105
#define	 DO_COLLECT				106
#define  DRVF_MOTION_INTERP        107    

#define	 DRVF_FUNCT_64				108  
#define	 DRVF_FUNCT_65				109 
#define	 DRVF_FUNCT_66				110  
#define	 DRVF_FUNCT_69				111  
#define	 DRVF_FUNCT_612				112  
#define	 DRVF_FUNCT_615				113  
#define	 DRVF_FUNCT_616				114  
#define	 DRVF_FUNCT_600				115  
#define	 DRVF_FUNCT_601				116  
#define	 DRVF_FUNCT_602				117  



#define  DEVICE_FUNC                110    // special device functions ids
#define  DEVF_GET_DEVSTAT           120    // functions at device level
#define  LIST_FUNCTION1				131
#define  LIST_FUNCTION2				132
#define  LIST_FUNCTION3				133
#define  LIST_FUNCTION4				134
#define	 LIST_FUNCTION_INTERP		135
#define	 LIST_FUNCTIONSETGET		136

#define  LIST_FUNCTION64			140
#define  LIST_FUNCTION65			141
#define  LIST_FUNCTION66			142
#define  LIST_FUNCTION69			143
#define  LIST_FUNCTION612			144
#define  LIST_FUNCTION615			145
#define  LIST_FUNCTION616			146



// #define  MAX_LENGTH                 400

#define	 FUNC_NUM		1000

#define	 SET_PLS_OUTMODE	 1001 //"set pls outmode\0",
#define  SET_PLS_INMODE		 1002 //"set pls ipmode\0",
#define  SET_FEEDBK_SRC		 1003 //"set feedback src\0",

#define	TV_MOVE				 1011 //"tv move\0"
#define	SV_MOVE				 1012 //"sv move\0"
#define	V_CHANGE			 1013 //"v change\0"
#define	EMG_STOP			 1014 //"emg stop\0"
#define	FIX_SPEED_RANGE		 1015 //"fix speed range\0"
#define	UNFIX_SPEED_RANGE	 1016 //"unfix speed range\0"
#define	GET_CURRENT_SPEED	 1017 //"get current speed\0"
#define	VERIFY_SPEED		 1018 //"verify speed\0"

#define	START_TR_MOVE		 1021 //"start tr move\0"
#define	START_TA_MOVE		 1022 //"start ta move\0"
#define	START_SR_MOVE		 1023 //"start sr move\0"
#define	START_SA_MOVE		 1024 //"start sa move\0"
#define	SET_MOVE_RATIO		 1025 //"set move ratio\0"
#define	P_CHANGE			 1026 //"p change\0"
#define	SET_PCS_LOGIC		 1027 //"set pcs logic\0"
#define	SET_SD_PIN			 1028 //"set sd pin\0"
#define	BACKLASH_COMP		 1029 //"backlash comp\0"
#define	SUPPRESS_VIBRATION	 1031 //"suppress vibration\0"

#define	SET_IDLE_PULSE		 1041 //"set idle pulse\0"
#define SET_LATCH_SRC		 1042

//// INTERPOLE FUNCTION 1200 ~ 1300
#define	START_SA_LINE2		 1201 //"start sa line2\0"
#define	START_SA_LINE3		 1202 //"start sa line3\0"
#define	START_SA_LINE4		 1203 //"start sa line4\0"
#define	START_TA_LINE2		 1204 //"start ta line2\0"
#define	START_TA_LINE3		 1205 //"start ta line3\0"
#define	START_TA_LINE4		 1206 //"start ta line4\0"
#define	START_SR_LINE2		 1207 //"start sr line2\0"
#define	START_SR_LINE3		 1208 //"start sr line3\0"
#define	START_SR_LINE4		 1209 //"start sr line4\0"
#define	START_TR_LINE2		 1211 //"start tr line2\0"
#define	START_TR_LINE3		 1212 //"start tr line3\0"
#define	START_TR_LINE4		 1213 //"start tr line4\0"

#define	START_TR_MOVE_XY	 1214 //"start tr move xy\0"
#define	START_TA_MOVE_XY	 1215 //"start ta move xy\0"
#define	START_SR_MOVE_XY	 1216 //"start sr move xy\0"
#define	START_SA_MOVE_XY	 1217 //"start sa move xy\0"

#define	START_TR_MOVE_ZU	 1218 //"start tr move zu\0"
#define	START_TA_MOVE_ZU	 1219 //"start ta move zu\0"
#define	START_SR_MOVE_ZU	 1221 //"start sr move zu\0"
#define	START_SA_MOVE_ZU	 1222 //"start sa move zu\0"

///circular type

#define	START_TR_ARC_XYU	 1223 //"start tr arc xyu\0"
#define	START_TA_ARC_XYU	 1224 //"start ta arc xyu\0"
#define	START_SR_ARC_XYU	 1225 //"start sr arc xyu\0"
#define	START_SA_ARC_XYU	 1226 //"start sa arc xyu\0"

#define	START_TR_ARC_XY	 1227 //"start tr arc xy\0"
#define	START_TA_ARC_XY	 1228 //"start ta arc xy\0"
#define	START_SR_ARC_XY	 1229 //"start sr arc xy\0"
#define	START_SA_ARC_XY	 1231 //"start sa arc xy\0"

#define	START_TR_ARC_ZU	 1232 //"start tr arc zu\0"
#define	START_TA_ARC_ZU	 1233 //"start ta arc zu\0"
#define	START_SR_ARC_ZU	 1234 //"start sr arc zu\0"
#define	START_SA_ARC_ZU	 1235 //"start sa arc zu\0"

#define	START_TR_ARC2	 1236 //"start tr arc2\0"
#define	START_TA_ARC2	 1237 //"start ta arc2\0"
#define	START_SR_ARC2	 1238 //"start sr arc2\0"
#define	START_SA_ARC2	 1239 //"start sa arc2\0"

#define	PULSER_R_LINE2		 1240 //"pulser r line2\0"
#define	PULSER_R_ARC2		 1241 //"pulser r arc2\0"

#define	PULSER_A_LINE2		 1242 //"pulser a line2\0"
#define	PULSER_A_ARC2		 1243 //"pulser a arc2\0"

#define	SET_TR_MOVE_ALL			1244 //"set tr move all\0"
#define	SET_TA_MOVE_ALL			1245  //"set ta move all\0"
#define	SET_SR_MOVE_ALL			1246  //"set sr move all\0"
#define	SET_SA_MOVE_ALL			1247  //"set sa move all\0"
#define	START_MOVE_ALL			1248  //"start move all\0"
#define	STOP_MOVE_ALL			1249  //"stop move all\0"


//////////////////

#define	SET_HOME_CONFIG		 1301 //"set home config\0"
#define	HOMVE_MOVE			 1302 //"home move\0"
#define	ESCAPE_HOME			 1303 //"escape home\0"
#define	HOME_SEARCH			 1304 //"home search\0"


#define	SET_PULSER_IPTMODE	 1305 //"set pulser iptmode\0"
#define	PULSER_VMODE		 1306 //"pulser vmode\0"
#define	PULSER_PMOVE		 1307 //"pulser pmode\0"
#define	PULSER_HOME_MOVE	 1308 //"pulser home_move\0"
#define	SET_PULSE_RATIO		 1309 //"set pulser ratio\0"

#define	MOTION_DONE			 1312 //"motion done\0"

#define	GET_IO_STATUS		 1313 //"get io status\0"

#define	SET_ALM		 1314 //"set alm\0"
#define	SET_INP		 1315 //"set inp\0"
#define	SET_ERC		 1316 //"set erc\0"
#define	SET_SERVO	 1317 //"set servo\0"
#define	SET_SD		 1318 //"set sd\0"
#define	SET_EL		 1319 //"set el\0"

#define	INT_CONTROL			 1360 //"int control\0"
#define	SET_INT_FACTOR		 1361 //"set INT factor\0"
#define	SET_AXIS_STOP_INT	 1362 //"set_axis stop int\0"
#define	MASK_AXIS_STOP_INT	 1363 //"mask_axis stop int\0"


#define	GET_POSITION		 1323 //"get position\0"
#define	SET_POSITION		 1324 //"set position\0"
#define	GET_COMMAND			 1325 //"get command\0"
#define	SET_COMMAND			 1326 //"set command\0"
#define	GET_ERROR_COUNTER	 1327 //"get error counter\0"
#define	RESET_ERROR_COUNTER	 1328 //"reset error counter\0"
#define	GET_GENERAL_COUNTER	 1329 //"get general counter\0"
#define	SET_GENERAL_COUNTER	 1330 //"set general counter\0"
#define	GET_TARGET_POS		 1331 //"get target pos\0"
#define	RESET_TARGET_POS	 1332 //"reset target pos\0"
#define	GET_RESET_COMMAND	 1333 //"get reset command\0"
#define	CHECK_RDP			 1334 //"check rdp\0"

#define	SET_LTC_LOGIC		1335  //"set ltc logic\0"
#define	GET_LATCH_LOGIC		1336  //"get latch logic\0"
#define	SET_SOFT_LIMIT		1337  //"set soft limit\0"
#define	ENABLE_SOFT_LIMIT	1338  //"enable soft limit\0"
#define	DISABLE_SOFT_LIMIT	1339  //"disale soft limit\0"
#define	SET_ERROR_COUNTER_CHECK	1340  //"set error counter check\0"
#define	SET_GENERAL_COMPARATOR	1341  //"set general comparator\0"
#define	SET_TRIGGER_COMPARATOR	1342  //"set trigger comparator\0"
#define	CHECK_COMPARE_DATA		1343  //"check compare data\0"
#define	CHECK_COMPARE_STATUS	1344  //"check compare status\0"
#define	SET_AUTO_COMPARE		1345  //"set auto compare\0"
#define	BUILD_COMPARE_FUNCTION	1346  //"build compare function\0"
#define	BUILD_COMPARE_TABLE		1347  //"build compare table\0"
#define	COMP_V_CHANGE			1348  //"comp v change\0"

#define	SET_CONTINUOUS_MOVE		1349  //"set continuous move\0"
#define	CHECK_CONTINUOUS_BUFFER	1350  //"check continuous buffer\0"

#define	SET_SYNC_SIG_SOURCE		1355  //"set sync option\0"
#define	SET_SYNC_MODE			1356  //"set sync option\0"
#define	SET_SYNC_OPTION			1357  //"set sync option\0"
#define	SET_SYNC_STOP_MODE		1358  //"set sync stop mode\0"

#define START_A_ARC_XY			1370
#define START_R_ARC_XY			1371
#define START_A_ARC_ZU			1372
#define START_R_ARC_ZU			1373
#define START_A_ARC2			1374
#define	START_R_ARC2			1375

#define SET_FA_SPEED			1376

#define	SET_LINE_MOVE_MODE		1380
#define	SET_AXIS_OPTION			1381
#define SET_ROTARY_COUNTER		1382	
#define	SET_AUTO_RDP			1383
#define	MASK_OUTPUT_PULSE		1384
#define SD_STOP					1385

#define SET_COMP_DATA			1390
#define SET_COMP_MODE			1391



#endif       // __DRIVER_H__ 

/*

_int error() bit
    1, SA_INPUT,   0,  "  0 - +soft limit on and stop\0"
    1, SA_INPUT,   1,  "  1 - -soft limit on and stop\0"
    1, SA_INPUT,   2,  "  2 - (reserved)\0"
    1, SA_INPUT,   3,  "  3 - general comparator on and stop \0"
    1, SA_INPUT,   4,  "  4 - (reserved)\0"
    1, SA_INPUT,   5,  "  5 - +end limit on and stop\0"
    1, SA_INPUT,   6,  "  6 - -end limit on and stop\0"
    1, SA_INPUT,   7,  "  7 - ALM happen and stop\0"
    1, SA_INPUT,   8,  "  8 - CSTP, Sync. stop on and stop\0"
    1, SA_INPUT,   9,  "  9 - CEMG, emergency on and stop\0"
    1, SA_INPUT,  10,  " 10 - SD on and slow down to stop\0"
    1, SA_INPUT,  11,  " 11 - (reserved)\0"
    1, SA_INPUT,  12,  " 12 - interpolation error and stop\0"
    1, SA_INPUT,  13,  " 13 - other axis stop on interpolation\0"
    1, SA_INPUT,  14,  " 14 - pulser input buffer overflow and stop\0"
    1, SA_INPUT,  15,  " 15 - interpolation counter overflow\0"
	1, SA_INPUT,   16, " 16 - encoder input signal error\0"
    1, SA_INPUT,   17,  " 17 - pulser input signal error\0"


    1, SA_INPUT,   0,  "  0 - normal stop\0"
    1, SA_INPUT,   1,  "  1 - next command starts\0"
    1, SA_INPUT,   2,  "  2 - command pre-reg 2 is empty\0"
    1, SA_INPUT,   4,  "  4 - acceleration start\0"
    1, SA_INPUT,   5,  "  5 - acceleration end\0"
    1, SA_INPUT,   6,  "  6 - deceleration start\0"
    1, SA_INPUT,   7,  "  7 - deceleration end\0"
    1, SA_INPUT,  11,  " 11 - general comparator compared\0"
    1, SA_INPUT,  12,  " 12 - trigger comparator compared\0"
    1, SA_INPUT,  14,  " 14 - counter latched for axis2,3\0"
    1, SA_INPUT,  15,  " 15 - ORG input and latched\0"

	1, SA_INPUT,   16, " 16 - SD on\0"
    1, SA_INPUT,   19, " 19 - CSTA, Sync. start on\0"
    1, SA_INPUT,   31, " 31 - Axis Stop Interrupt\0"



*/
/*
// done in io map
// 	MOTION_DONE		 +LONG_PAD, "motion done\0"
// 	GET_IO_STATUS	 +LONG_PAD, "get io status\0"
// 	GET_POSITION		 +LONG_PAD, "get position\0"
// 	GET_COMMAND		+LONG_PAD, "get command\0"
// 	GET_GENERAL_COUNTER	 +LONG_PAD, "get general counter\0"


    SET_AUTO_COMPARE		+LONG_PAD, "set auto compare\0"
 	BUILD_COMPARE_FUNCTION	+LONG_PAD, "build compare function\0"
 	BUILD_COMPARE_TABLE		+LONG_PAD, "build compare table\0"


*/


