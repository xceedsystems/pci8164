/***************************************************************

                PciStuff.h             

   This file contains the interface to the Pcilib.lib

****************************************************************/


#ifndef  __PCISTUFF_H__
#define  __PCISTUFF_H__



int InitPCI( LPDRIVER_INST pNet, P_ERR_PARAM pErrors );
int SearchPCIBoard( UINT16 CardNo);



#endif      /* __PCISTUFF_H__ */

