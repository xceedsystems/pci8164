#include "stdafx.h"

                 
#include <rt.h>

#include <stdlib.h>     // _MAX_PATH
#include <string.h>     // strcat()

#include "vlcport.h"
#include "CSFlat.h"     // FCoreSup
#include "DCFlat.h"     // FDriverCore



//#include <windows.h>
//#include <stdio.h>
#include "pcibios.h"
#define CARRY_FLAG 0x01 	/* 80x86 Flags Register Carry Flag bit */

struct DWORDREGS
{
    DWORD   eax, ebx, ecx, edx, esi, edi;
};

struct WORDREGS
{
    WORD            ax,hax,
		            bx,hbx,
					cx,hcx,
					dx,hdx,
					si,hsi,
					di,hdi,flags;
};


struct BYTEREGS
{
    BYTE            al, ah,hal,hah,
		            bl, bh,hbl,hbh,
					cl, ch,hcl,hch,
					dl, dh,hdl,hdh;
};

union  REGS
{   
	struct  DWORDREGS ex;
    struct  WORDREGS x;
    struct  BYTEREGS h;
};


int pci_bios_present(BYTE *hardware_mechanism,
			    WORD *interface_level_version,
			    BYTE *last_pci_bus_number)
{
//   char buf[255]; 
   int ret_status;	    //* Function Return Status. 
   union REGS regs;

   memset(&regs,0,sizeof(regs)); // add by simon 8/19

   regs.x.ax=0xb101;
   regs.x.si=0;
   DeviceIoControl(hCVxD1, 1/*CVXD_APIFUNC_0*/,
                   &regs,sizeof(regs),
                   &regs,sizeof(regs),
                   NULL, NULL);
/*   
   sprintf(buf,"eax=%lx ebx=%lx ecx=%lx edx=%lx"
	           " esi=%lx edi=%lx flag=%x",regs.ex.eax,
			                     regs.ex.ebx,
			                     regs.ex.ecx,
			                     regs.ex.edx,
			                     regs.ex.esi,
			                     regs.ex.edi,
			                     regs.x.flags);
   MessageBox(0,buf,"",MB_OK);
*/
   //* Next, must check that AH (BIOS Present Status) == 0 
    if (regs.h.ah==0) 
	{
	   if(regs.ex.edx == 0x20494350 )
	   {
	     ret_status = 0x00; //SUCCESSFUL

         //* Extract calling parameters from saved registers 
         if (hardware_mechanism != NULL) 
		     *hardware_mechanism = regs.h.al;

		 if( interface_level_version != NULL)
			 *interface_level_version = regs.x.bx;

		 if (last_pci_bus_number != NULL) 
        	 *last_pci_bus_number = regs.h.cl;

       }
       else 
		   ret_status =0x01;// NOT_SUCCESSFUL;      //no '$pci'
    }
    else 
       ret_status =0x01; // NOT_SUCCESSFUL;          //no install
   return (ret_status);
}

int find_pci_device(WORD device_id,
		    WORD vendor_id,
		    WORD index,
		    BYTE *bus_number,
		    BYTE *device_and_function)
{
  
//   char buf[255]; 
   int ret_status;	    //* Function Return Status. 
   union REGS regs;

   memset(&regs,0,sizeof(regs)); // add by simon 8/19
   regs.x.ax=0xb102;
   regs.x.cx=device_id;
   regs.x.dx=vendor_id;
   regs.x.si=index;
   DeviceIoControl(hCVxD1,2, &regs,sizeof(regs),&regs,sizeof(regs),  NULL , NULL);
  
//   sprintf(buf,"eax=%lx ebx=%lx ecx=%lx edx=%lx"
//	           " esi=%lx edi=%lx flag=%x",regs.ex.eax,
//			                     regs.ex.ebx,
//								 regs.ex.ecx,
//								 regs.ex.edx,
//								 regs.ex.esi,
//								 regs.ex.edi,
//								 regs.x.flags & CARRY_FLAG);
// MessageBox(0,buf,"message",MB_OK);

   if ((regs.x.flags & CARRY_FLAG) == 0) 
   {
      ret_status = regs.h.ah;
      if (ret_status == SUCCESSFUL) 
	  {

      	 if (bus_number != NULL) 
		     *bus_number = regs.h.bh;
	 	 if (device_and_function != NULL) 
		     *device_and_function = regs.h.bl;
	  }
   }
   else 
     ret_status = NOT_SUCCESSFUL;
   return (ret_status);
}

int read_configuration_area(BYTE function,
				   BYTE bus_number,
				   BYTE device_and_function,
				   BYTE register_number,
				   DWORD *data)
{
   int ret_status; /* Function Return Status */
   union REGS regs;

   memset(&regs,0,sizeof(regs)); // add by simon 8/19

   regs.h.al=0x8+function;   //08:byte 09:word 0a:dword
   regs.h.ah=0xb1;
   regs.h.bl=device_and_function;
   regs.h.bh=bus_number;
   regs.x.di=register_number;
   DeviceIoControl(hCVxD1,1, &regs,sizeof(regs) , &regs,sizeof(regs),  NULL , NULL);

   if ((regs.x.flags & CARRY_FLAG) == 0)
   {
      ret_status = regs.h.ah;
      if (ret_status == SUCCESSFUL) 
	     *data = regs.ex.ecx;
   }
   else 
	  ret_status = NOT_SUCCESSFUL;

   return (ret_status);
}


int write_configuration_area(BYTE function,
				    BYTE bus_number,
				    BYTE device_and_function,
				    BYTE register_number,
				    DWORD value)
{
   int ret_status; /* Function Return Status */
   union REGS regs;

   memset(&regs,0,sizeof(regs)); // add by simon 8/19
   
   regs.h.al=0xb+function;   //0b:byte 0c:word 0d:dword
   regs.h.ah=0xb1;
   regs.h.bl=device_and_function;
   regs.h.bh=bus_number;
   regs.x.di=register_number;
   regs.ex.ecx=value;
   DeviceIoControl(hCVxD1,1, &regs,sizeof(regs) , &regs,sizeof(regs),  NULL , NULL);

   if ((regs.x.flags & CARRY_FLAG) == 0) 
       ret_status = regs.h.ah;
   else 
	   ret_status = NOT_SUCCESSFUL;
   return (ret_status);
}
