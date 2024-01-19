/************************************************************

                MCI0410.c


This file implements all the module entry points: 

int rtIdentify( P_IDENTITY_BLOCK* ppIdentityBlock );
int rtLoad(   UINT32 ScanRate, UINT32* rDirectCalls );
int rtOpen(   LPDRIVER_INST lpNet, P_ERR_PARAM lpErrors);
int rtReload( LPDRIVER_INST lpNet, P_ERR_PARAM lpErrors);
int rtOnLine( LPDRIVER_INST lpNet, P_ERR_PARAM lpErrors);
int rtInput(  LPDRIVER_INST lpNet);
int rtOutput( LPDRIVER_INST lpNet);
int rtSpecial(LPDRIVER_INST lpNet, LPSPECIAL_INST lpData);
int rtOffLine(LPDRIVER_INST lpNet, P_ERR_PARAM  lpErrors);
int rtClose(  LPDRIVER_INST lpNet, P_ERR_PARAM  lpErrors);
int rtUnload( );

**************************************************************/


#include "stdafx.h"

                 
#include <rt.h>

#include <stdlib.h>     // _MAX_PATH
#include <string.h>     // strcat()

#include "vlcport.h"
#include "CSFlat.h"     // FCoreSup
#include "DCFlat.h"     // FDriverCore
#include "driver.h"

#include "version.h"
#include "auxrut.h"
#include "task.h"
#include "card.h"
#include "pcistuff.h"
#include "8164drv.h"
#include "8164io.h"
#include "8164io.h"



//if ini file used
int SpawnLoadIni(LPDRIVER_INST pNet)
{
    int   rc=SUCCESS;
    char  Fname[ _MAX_PATH ];
    char  Pathname[ _MAX_PATH ];

    char  Para1[10];

    char* argv[7];
	Fname[0]=0;

return rc;

// no path
rc = GetPathInfo( ptVcm, pcDir, Pathname, sizeof(Pathname) );

	strcat( Fname, pNet->ConfigFile );
	sprintf(Para1,"%d\0",(pNet->PciIndex -1));
	strcat( Pathname, "LoadInit.exe" );

    argv[0] =Pathname;
	argv[1] =Para1;		// card number
	argv[2] =Fname;		// file name
	argv[3] ="1";
    argv[4] = NULL;



    rc = spawnv( P_WAIT, argv[0], argv );

	pNet->ShareMemPool = rc;	// passing of variable

	if (rc < 1 ) rc= FAILURE;
	else
	rc=SUCCESS;

    return rc;
}



int rtIdentify( P_IDENTITY_BLOCK* ppIdentityBlock )
{
    static IDENTITY_BLOCK IdentityBlock; 
    IdentityBlock.DriverId   = DriverID;
    IdentityBlock.DriverVers = DriverVERS;
    IdentityBlock.pName      = PRODUCT_NAME ", " PRODUCT_VERSION;
    *ppIdentityBlock = &IdentityBlock;
    return 0;
}

int rtLoad( UINT32 ScanRate, UINT32* rDirectCalls )
{
    // Executing the LOAD PROJECT command

    #if defined( _DEBUG )
        SetDebuggingFlag( 1 );  // Disable the VLC watchdog, so we can step through our code. 
    #endif  // _DEBUG


    // Use direct calls for very fast applications.  
    // With the appropriate bit set, Input(), Output() and/or Special()
    //  can be directly called from the engine thread, 
    //  saving the delay introduced by a task switch. 
    // Note:  Functions exectuted in the engine thread cannot call 
    //  some C stdlib APIs, like sprintf(), malloc(), ...
    
    // *rDirectCalls = ( DIRECT_INPUT | DIRECT_OUTPUT | DIRECT_SPECIAL );



    EROP( "rtLoad() ScanRate=%d, rDirectCalls=%x", ScanRate, *rDirectCalls, 0, 0 );

    return 0;
}

int rtOpen( LPDRIVER_INST pNet, P_ERR_PARAM pErrors)
{
    // Executing the LOAD PROJECT command

    int rc = SUCCESS;
    LPDEVICE_INST pDevice;
	int bn = 0;
	int cn = 0;
	short cbn =0 ;

    if( pNet->Sentinel != RT3_SENTINEL )
        rc = IDS_VLCRTERR_ALIGNMENT;

    if( rc == SUCCESS )
    {
        UINT32* pSentinel = BuildUiotPointer( pNet->ofsSentinel );
        if( *pSentinel != RT3_SENTINEL )
            rc = IDS_VLCRTERR_ALIGNMENT;
    }

    EROP( "rtOpen() pNet=%p, pErrors=%p", pNet, pErrors, 0, 0 );


if( !pNet->bSimulate )
{

       

//  for(cn=0;cn<MAX_PCI_CARDS;cn++)
//	pci_Info[cn].initFlag = FALSE;

	
	if( rc == SUCCESS )
	{
		rc = InitPCI( pNet, pErrors );  // Load the physical address of the PCI card in pNet

		bn= (pNet->PciIndex) ;
		// init Pci motion card
#if defined( _DEBUG )
	 SayOut( "found Card index, address : %d, %X ", bn,pNet->PhyAddr,0,0,0);
#endif


		cbn=(pNet->PciIndex) -1; /// use index as array offset
		// init Once
	if ( rc == SUCCESS  )
	rc=	_8164_initial(&cbn);///( &cbn,  &info  ); send card number in

	}
		
        if( rc == SUCCESS )
        {
// no physical dpr
//            pNet->pDpr = AllocateDpr( pNet->PhyAddr , DPR_TOTAL_SIZE ); // 64K
//            if( pNet->pDpr == NULL )
//                rc = IDS_VLCRTERR_CREATE_DESCRIPTOR;
        }

		
	if( rc == SUCCESS )
	{
		UINT32	OffsetAxis;

		OffsetAxis =0;

        pNet->pDeviceList = BuildUiotPointer( pNet->ofsDeviceList );

		for( pDevice = pNet->pDeviceList; pDevice->Type && ( rc == SUCCESS ) ; pDevice++ )

		{
			if( pDevice->Sentinel != RT3_SENTINEL )
				rc = IDS_VLCRTERR_ALIGNMENT;
			else
			{
                // Create UIOT pointers
                if( pDevice->Input.bUsed )
				{
                   pDevice->Input.pDst  = BuildUiotPointer( pDevice->Input.ofsUiot );
                   pDevice->Input.pSrc  = (UINT8*)pNet->pDpr +OffsetAxis;
				}

                if( pDevice->Output.bUsed )
                { 
					pDevice->Output.pSrc  = BuildUiotPointer( pDevice->Output.ofsUiot );//// (UINT8*)pNet->pDpr+OffsetAxis;
					pDevice->Output.pDst = BuildUiotPointer( pDevice->Output.ofsUiot );
				}
			}
		}
	}

	// Load default values into card
    ///    if( rc == SUCCESS ) rc=SpawnLoadIni(pNet);
	// load memory offset in io address

	}
	//no background task
   //     if( rc == SUCCESS )
   //         rc = CreateBackgroundTask(pNet);

	

    return rc;
}

int rtReload( LPDRIVER_INST pNet, P_ERR_PARAM pErrors)
{
    // Executing the LOAD PROJECT command
    EROP( "rtReload() pNet=%p, pErrors=%p", pNet, pErrors, 0, 0);
    if( !pNet->bSimulate )
    {
        InitLinkedList(&pNet->Pend);
        InitLinkedList(&pNet->Done);
    }

    // make sure pNet is in the same state as after rtOpen(). 
    return 0;
}

int rtOnLine( LPDRIVER_INST pNet, P_ERR_PARAM pErrors)
{
    int	rc = SUCCESS;
	I16 AxisNum = 0;
	I16 bn=0;

	EROP( "rtOnLine() pNet=%p, pErrors=%p", pNet, pErrors, 0, 0 );
    pNet->bFirstCycle = 1;
    pNet->bGoOffLine  = 0;

    if( !pNet->bSimulate )
    {
        /* Check all devices. If critical devices are offline,  rc = IDS_MCI0410_DEVICE_OFFLINE */

		bn= (pNet->PciIndex) -1 ;
//// set axis default
		i_software_reset( bn );

		for (;AxisNum < 4 ; AxisNum++ )
		{
		bn= (((pNet->PciIndex) -1 ) * 4)+AxisNum;

		rc=_8164_emg_stop(bn);
		rc=_8164_disable_soft_limit(bn);

		rc=_8164_set_command(bn,0.0);
		rc=_8164_set_position(bn,0.0);
		rc=_8164_set_general_counter(bn,2,0.0);
		rc=_8164_reset_error_counter(bn);
		rc=_8164_unfix_speed_range(bn); // 
		rc=_8164_backlash_comp(bn,0,0); // 
		rc=_8164_set_idle_pulse(bn,0); // 

		rc=_8164_set_pls_outmode(bn,0); // 
		rc=_8164_set_pls_iptmode(bn,0,0); // 
		rc=_8164_set_feedback_src(bn,1); ///intern cod pluse

		rc=_8164_set_home_config(bn,9,1,1,5,1);
///set_int_factor()  // not used
		rc=_8164_set_el(bn,0);
		rc=_8164_set_ltc_logic(bn,0);
		rc=_8164_set_erc(bn,0,12);
		rc=_8164_set_sd(bn,0,1,1,0);

		rc=_8164_set_servo(bn,0);

		rc=_8164_set_alm(bn,0,0);
		rc=_8164_set_inp(bn,0,0);
		rc=_8164_set_move_ratio(bn,1.0);



		}

 //       rc = TestConfig( pNet, pErrors);
    }

	EROP( "rtOnLine(). exit.", 0, 0, 0, 0 );

    return rc;

}


int rtInput( LPDRIVER_INST pNet ) 
{

    int     rc       = SUCCESS;
	int	bn =0;

	// EROP( "rtInput() pNet=%p", pNet, 0, 0, 0 );
    // This is the beginning of the VLC scan cycle
    if( !pNet->bSimulate )
    {
		// Copy new input data from the hw to the driver input image in the UIOT. 
		LPDEVICE_INST pDevice = pNet->pDeviceList;


		
		bn= (pNet->PciIndex) -1;

///	printf("rt input 8164 card %d \n", bn); 
		
		for( ; pDevice->Type ; pDevice++ )
		{
			if( pDevice->Input.bUsed )
			{
//			bn= (pNet->PciIndex) -1;
				// Start Read IO,INT,POS from adlink card
				// bn crd number 0~3
				rc= ADlinkReadIO(pDevice, bn, pDevice->Input.pDst );

			}
		}


    VerifyDoneList(&pNet->Done);    // Flush the completed background functions
    }

	EROP( "rtInput(). exit", 0, 0, 0, 0 );

    return SUCCESS;
}


int rtOutput( LPDRIVER_INST pNet)
{
	    int	rc = SUCCESS;
		U16 cRes = 0;
		I16 Cardno =0;
		I16 Ch_No=0;
		I16 value=0;


    if( !pNet->bSimulate )
    {
        // Copy new output data from the UIOT driver output image to the hw.
		LPDEVICE_INST pDevice = pNet->pDeviceList;
    
		for( ; pDevice->Type ; pDevice++ )
            if( pDevice->Output.bUsed &&( pDevice->Type == DEVICE_1W_IANDO))
			{
            U8 *pDst =   pDevice->Output.pSrc ;  // was pDst
			I16 Data = (U8) *(pDst);
			
			Cardno= (pNet->PciIndex) -1;
//			 cRes=  _8164_get_dio_status(Cardno, &Data);

			for(Ch_No=0;Ch_No<6;Ch_No++){

			value= Data && (0x01 << Ch_No) ;
			  _8164_d_output(Cardno, Ch_No, value);
			}

			}

        if( pNet->bFirstCycle )     // first Output() ?
        {
            //  Only now we have a valid output image in the DPR. 
            //    EnableOutputs(dp);  enable outputs (if our hardware lets us) 
            
            pNet->bFirstCycle = 0;
        }       
    }

 //   EROP( "rtOutput() pNet=%p", pNet, 0, 0, 0 );

    return SUCCESS;
}

int rtSpecial( LPDRIVER_INST pNet, LPSPECIAL_INST pData)
{
    // A trapeziodal block has been hit, function found in card.c

    UINT16  Result = 0;
    UINT16  Status = VLCFNCSTAT_OK;
    
	// get devicelist
	LPDEVICE_INST pDevice = pNet->pDeviceList;

    EROP( "rtSpecial() pNet=%p, pData=%p", pNet, pData, 0, 0 );

    if( !pNet->bSimulate )
    {

		////start function call into special block
       int  FunctionId = pData->User.paramHeader.FunctionId;

#if defined( _DEBUG )
	 SayOut( "Function Id : %d", FunctionId,0 ,0,0,0);
#endif


        switch( FunctionId ) 
        {
            case DRVF_MOTION:
            case DRVF_FUNCT_66:
				AdLinkInterpol( pNet, pData );
					break;
            case DRVF_MOTION_INTERP:
				AdLinkInterpol( pNet, pData );
					break;
			case DRVF_SETGET:
				AdLinkSetGet( pNet, pData );
					break;
            case DRVF_OTHERS_INT:
				AdLinkI16( pNet, pData );
				break;
            case DRVF_OTHERS_F64:
				AdLinkF64( pNet, pData );
///////7
			case DRVF_FUNCT_64:
            case DRVF_FUNCT_65:
            case DRVF_FUNCT_69:
            case DRVF_FUNCT_612:
            case DRVF_FUNCT_615:
            case DRVF_FUNCT_616:
				AdLinkF64( pNet, pData );

			default:
                    Status = VLCFNCSTAT_WRONGPARAM;
                    break;
        }
    
        EROP("Special();  FunId= %d, Status= %d, pData= %p", FunctionId, Status, pData, 0);
    }
    else
    {
		UINT16* pResult = BuildUiotPointer( pData->User.paramHeader.ofsResult );
        if( pResult )   // some functions may not have the Result param implemented
		    *pResult = (UINT32) SUCCESS;

        Status = VLCFNCSTAT_SIMULATE;
    }

    if( pData->User.paramHeader.ofsStatus )   // some functions may not have the status param implemented
	{
		UINT16* pStatus = BuildUiotPointer( pData->User.paramHeader.ofsStatus );
		*pStatus = Status;
	}
    
    return SUCCESS;
}

int rtOffLine( LPDRIVER_INST pNet, P_ERR_PARAM pErrors)
{
    // Executing the STOP PROJECT command
    int rc = SUCCESS;
	I16 AxisNum = 0;
	I16 value=0;
	I16 Cardno=0;
	I16 Ch_No=0;

    EROP( "rtOffLine() pNet=%p, pErrors=%p", pNet, pErrors, 0, 0 );

    pNet->bGoOffLine = 1;
    if( !pNet->bSimulate )
    {

	///TODO stop any task or card from running
	///stop motion card here

		for (;AxisNum < 4 ; AxisNum++ )
		{
		rc=_8164_emg_stop(AxisNum);

		}

		for(Ch_No=0;Ch_No<6;Ch_No++){

		value= 0;
			  _8164_d_output(Cardno, Ch_No, value);
		}

		rc = SUCCESS;

        rc = WaitForAllFunctionCompletion(pNet);  /* wait for the backgroung task to calm down */
        
        if( rc == SUCCESS )
        {
            /*
            DUAL_PORT far *  dp  = (DUAL_PORT far *)pNet->pDpr;
            if( pNet->StopState == 1 )
                rc = stop scanning;
    
            DisableOutputs(dp, &pNet->trans_count);
            DisableWD(dp); 
            */
        }
        
    }    

    EROP("rtOffLine(). exit  rc= %d", rc, 0, 0, 0);

    return rc;
}

/*   if Open() fails, Close() is not automatically called for this instance.
     if lpErrors == NULL, do not report any error, keep the Open()'s error code and params.  
 */ 
int rtClose( LPDRIVER_INST pNet, P_ERR_PARAM pErrors)
{
    int rc = SUCCESS;
	I16 bn=0;

		bn= (pNet->PciIndex-1);

    // Executing the UNLOAD PROJECT command
    if( !pNet->bSimulate )
    {
        EROP("rtClose(). start. pNet= %p", pNet, 0, 0, 0);

		_8164_close(bn);

	///TODO may need to stop any task or card from running
        /*
        {
            DUAL_PORT far* const dp = (DUAL_PORT far *)pNet->pDpr;     / * pointer to the dualport * /
            Reset the board;
        }
        */
        //DeleteInterruptTask( pNet );
        DeleteBackgroundTask( pNet );
    
		if( pNet->pDpr )
        {
            FreeDpr( pNet->pDpr );
            pNet->pDpr = NULL;
        }

    }

    EROP( "rtClose() pNet=%p, pErrors=%p", pNet, pErrors, 0, 0 );
    return SUCCESS;
}

int rtUnload()
{
    // Executing the UNLOAD PROJECT command
    EROP( "rtUnload()", 0,0,0,0 );
    return 0;
}




