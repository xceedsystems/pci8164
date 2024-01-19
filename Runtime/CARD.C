/********************************************************************

                                Card.c

    Interface specific code. 
    This file only should touch the hardware.

*********************************************************************/

#include "stdafx.h"

#include <rt.h>
#include <string.h>     // strlen()
#include <stdio.h>      // sprintf()
#include <stdlib.h>


#include "vlcport.h"
#include "dcflat.h"     // EROP()
#include "driver.h"     /* SEMAPHORE */
#include "errors.h"     /* IDS_RT_DP_RW_TEST                     */
#include "auxrut.h"     /* StartTimeout(), IsTimeout(), EROP     */
#include "card.h"       /* Init()                                */
#include "type_def.h"
#include "8164drv.h"
#include "8164IO.h"

//#include "8164io.h"
//#include "8164io.h"



/*   not use yet can used to read file data from win side
int FileLoad(char *fname)
{
FILE *fp;
char txt[30];
	fp=fopen(fname,"r");
	if(fp==NULL) return(-1);	
	fscanf(fp,"%s\n",txt);	
	fscanf(fp,"%s\n",txt);
	strcpy(m_BoardName,txt);
	fscanf(fp,"%d:%s\n",&m_BoardType,txt);
	fscanf(fp,"%d:%s\n",&m_IrqNo,txt);
	fscanf(fp,"%lx:%s\n",&m_Address,txt);
	fscanf(fp,"%d:%s\n",&m_PciIndex,txt);
	fscanf(fp,"%d:%s\n",&m_Sys.EsLog,txt);
	for(int axis=0;axis<4;axis++){
		fscanf(fp,"%d:%s\n",&m_Sys.SpdMode[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.AlmLog[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.NearLog[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.ZLog[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.OverLog[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.InpLog[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.PlsLog[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.ForDir[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.ClkType[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.MotType[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.HomeSeq[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.ZCnt[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.EncdMul[axis],txt);
		//S----- Add by CKTan-----
		fscanf(fp,"%d:%s\n",&m_Sys.HomeMode[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.Encoder[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.Deviation[axis],txt);
		//E----- Add by CKTan-----
		fscanf(fp,"%f:%s\n",&m_Sys.PlsUnit[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.SType[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.SCRes[axis],txt);
		fscanf(fp,"%d:%s\n",&m_Sys.MaxSpd[axis],txt);
	}
	fclose(fp);
	return(0); // ok
} */

/******************* Card specific  Functions  *******************************/


/******************* Initialization  *******************************/


static int TestAndFill(UINT8* pc, const int Size, const int test, const int fill)   /* test == 1  --> no test */
{
    int i  = 0;
    for(; i < Size;  *pc++ = fill, i++)
    {
        int c = *pc & 255;
        if(test != 1  &&  test != c)
        {
            EROP("Ram Error.  Address %p, is 0x%02x, and should be 0x%02x", pc, c, test, 0);
            return IDS_HWCARD_HW_TEST;
        }
    }
    return SUCCESS;
}


int  Init( LPDRIVER_INST pNet, P_ERR_PARAM const lpErrors)
{
    int rc = SUCCESS;

    return rc;
}



/****************************************************************************************
    IN:     pName   --> pointer to the device user name
            Address --> device's network address
            pBuf    --> pointer to the destination buffer
            szBuf   --> size of the destination buffer

    OUT:    *pBuf   <-- "Address xx (usr_name)".  
    Note:   The device user name may be truncated!
*/
static void LoadDeviceName( char* pName, UINT16 Address, char* pBuf, size_t szBuf )
{
    if( szBuf && (pBuf != NULL) )
    {
        char* format = "Address %d";

        *pBuf = '\0';

        if( szBuf > (strlen(format)+3) )    /* Address may need more digits */
        {
            size_t  len;

            sprintf(pBuf, format, Address & 0xffff);

            len = strlen( pBuf ); 

            if( pName && ((szBuf - len) > 10) )     /* if we still have 10 free bytes  */
            {
                strcat(pBuf, " (");
                len += 2;
                strncat( pBuf, pName, szBuf-len-2 );
                *(pBuf + szBuf - 2) = '\0';
                strcat( pBuf, ")" );
            }
        }
    }
}



int  TestConfig( LPDRIVER_INST const pNet, P_ERR_PARAM const lpErrors )
{
    int rc = SUCCESS;

    return rc;
}


/********************* runtime specific card access functions ********************/

///not used
int	DoCollect( LPDRIVER_INST pNet, LPSPECIAL_INST pData)
{
    int     rc       = SUCCESS;
//	int		channel;
//	UINT16	*ChanBuff[16];
//	UINT16	NumSamples = pData->Work.paramCommand.NumSamps;
	UINT16* pResult = BuildUiotPointer( pData->Work.paramHeader.ofsResult );
   
//	for (channel = 0; (channel < 16) && (rc == SUCCESS); channel++)
//	{
//		LPPTBUFFER pRBuffer = &pData->Work.paramCommand.Buffers[channel];

//		printf("Channel %d  Length %d  Offset %d\n", 
//			channel, pRBuffer->Size, pRBuffer->Offset);

//		ChanBuff[channel] = BuildUiotPointer( pRBuffer->Offset );
//		if( pRBuffer->Size > NumSamples)
//		{
//			rc = IDS_MCI0410_READ_SIZE;
//		}
//	}

	// At this time, ChanBuf[i] is a pointer to the buffer area for channel i.
	// Insert your code here.
	*pResult = rc;
	return  (rc);
}


void AdLinkMotion( const LPDRIVER_INST pNet, SPECIAL_INST* const pData )
{
    int rc = SUCCESS ;

	UINT16 bn;
		
	I16 iret=0;
    SPECIAL_INST_COMMAND* const pUser = &pData->User.paramCommand;

    UINT16* pResult = BuildUiotPointer( pUser->Header.ofsResult );
    UINT16* pStatus = BuildUiotPointer( pUser->Header.ofsStatus );

	 	*pResult=rc;	
		*pStatus=rc;


	bn=(((pNet->PciIndex) -1) *4) + pUser->AxisAddress; // axis number

	iret= ERR_FunctionCall_Missing;

 switch(pUser->Function  ) 
    {
	
	case	EMG_STOP:
	*pResult= _8164_emg_stop(bn);

	break;
	
	}
  	*pResult=iret;


}



void AdLinkSetGet( const LPDRIVER_INST pNet, SPECIAL_INST* const pData )
{
	    int rc = SUCCESS ;

	UINT16 AxisNo;
	I16 iret=0;


    SPECIAL_INST_SETGET* const pUser = &pData->User.paramSetGet;
    const LPPTBUFFER pGBuffer = &pUser->GetValue ;
    const LPPTBUFFER pSBuffer = &pUser->SetValue ;


    UINT16* pResult = BuildUiotPointer( pUser->Header.ofsResult );
    UINT16* pStatus = BuildUiotPointer( pUser->Header.ofsStatus );
 

    double* pGetValue = BuildUiotPointer( pGBuffer->Offset);
    double* pSetValue = BuildUiotPointer( pSBuffer->Offset);



	F64 minAccT =0;
	F64 maxAccT =0;
	F64 StrVel = pSetValue[0];
	F64 MaxVel = pSetValue[1];
	F64 MaxSpeed = pSetValue[2];


	I16 CardNo = (pNet->PciIndex -1);
	SINT32 ArraySize = pUser->ArraySize ;
	AxisNo=(CardNo *4) + pUser->AxisAddress; // axis number

	*pResult=rc;
	*pStatus=rc;


	iret= ERR_FunctionCall_Missing;

	switch(pUser->Function  ) 
    {

	case	VERIFY_SPEED	 :

		iret=_8164_verify_speed( StrVel, MaxVel,&minAccT, &maxAccT, MaxSpeed);
		pGetValue[0] = minAccT;
		pGetValue[1] = maxAccT; 
	break;
	}


	*pResult=iret;


}
//////

void AdLinkF64( const LPDRIVER_INST pNet, SPECIAL_INST* const pData )
{
	    int rc = SUCCESS ;

	UINT16 AxisNo;
	I16 iret=0;

	I16 iSet1,iSet2,iSet3,iSet4,iSet5;
	F64 fSet1,fSet2,fSet3,fSet4,fSet5;


    SPECIAL_INST_OTHERS* const pUser = &pData->User.paramOthers  ;

    UINT16* pResult = BuildUiotPointer( pUser->Header.ofsResult );
    UINT16* pStatus = BuildUiotPointer( pUser->Header.ofsStatus );
 
    double* pGetValue = BuildUiotPointer( pUser->fGetValue  );

	F64 pGet64 =0;
	I32 pGetI32=0 ;
	U16 pGetU16=0 ;

	I16 CardNo = (pNet->PciIndex -1);

 	*pResult=rc;
	*pStatus=rc;

	AxisNo=(CardNo *4) + pUser->AxisAddress; // axis number

//	*pResult=iret;

	
	iSet1=pUser->iSetValue1 ;
	iSet2=pUser->iSetValue2;
	iSet3=pUser->iSetValue3 ;
	iSet4=pUser->iSetValue4 ;
	iSet5=pUser->iSetValue5 ;

	fSet1=pUser->fSetValue1  ;
	fSet2=pUser->fSetValue2  ;
	fSet3=pUser->fSetValue3  ;
	fSet4=pUser->fSetValue4  ;
	fSet5=pUser->fSetValue5  ;

#if defined( _DEBUG )
	 SayOut( "AdLinkF64 int : %d,%d,%d,%d,%d", iSet1, iSet2, iSet3,iSet4,iSet5 );
	 SayOut( "AdLinkF64 float : %f,%f,%f,%f,%f", fSet1, fSet2, fSet3,fSet4,fSet5 );
#endif

		iret= ERR_FunctionCall_Missing;

	switch(pUser->Function  ) 
    {

	case	SET_GENERAL_COMPARATOR	 :
	iret=_8164_set_general_comparator( AxisNo,iSet1,iSet2,iSet3, fSet1);
	break;
	case	SET_TRIGGER_COMPARATOR :
	iret= _8164_set_trigger_comparator(AxisNo,iSet1,iSet2, fSet1);
	break;
	case	SET_GENERAL_COUNTER	 :
	iret=_8164_set_general_counter( AxisNo,iSet1, fSet1);
	break;
	case	PULSER_HOME_MOVE	 :
	iret=_8164_pulser_home_move( AxisNo,iSet1, fSet1);

	break;
	case	SET_MOVE_RATIO	 :
	iret= _8164_set_move_ratio( AxisNo, fSet1);
	break;
	case	SET_POSITION	 :
	iret=_8164_set_position( AxisNo, fSet1);
	break;
	case	RESET_TARGET_POS :
	iret=_8164_reset_target_pos( AxisNo, fSet1);
	break;
	case	PULSER_VMODE :
	iret=_8164_pulser_vmove( AxisNo, fSet1);
	break;
	case	P_CHANGE :
	iret=_8164_p_change( AxisNo, fSet1);
	break;

	case	PULSER_PMOVE :
	iret= _8164_pulser_pmove( AxisNo,fSet1,fSet2);
	break;
	case	FIX_SPEED_RANGE :
	iret=_8164_fix_speed_range( AxisNo, fSet1);
	break;
	case	SET_COMMAND :
	iret=_8164_set_command( AxisNo, (I32)fSet1);
	break;
	case	SET_SOFT_LIMIT	 :
	iret=_8164_set_soft_limit( AxisNo, (I32)fSet1, (I32)fSet2);
	break;
	case	ESCAPE_HOME :
	iret= _8164_escape_home	( AxisNo,fSet1, fSet2, fSet3);
	break;
	case	COMP_V_CHANGE	 :
	iret=_8164_cmp_v_change	( AxisNo,fSet1, fSet2, fSet3,fSet4);
	break;

	case SD_STOP	 :
	iret= _8164_sd_stop( AxisNo, fSet1);
	break;
	case	SET_FA_SPEED :
	iret=_8164_set_fa_speed( AxisNo, fSet1);
	break;

///gets float value here	
	case	CHECK_COMPARE_DATA :
	iret=_8164_check_compare_data( AxisNo,iSet1,&pGet64);
	*pGetValue = pGet64;

	break;

	case	CHECK_COMPARE_STATUS :
	iret=_8164_check_compare_status	( AxisNo,&pGetU16);
	*pGetValue = (double) pGetU16;
	iret =  pGetU16;
	break;
	case	GET_LATCH_LOGIC	 :
	iret=_8164_get_latch_data( AxisNo,iSet1,&pGet64);
	*pGetValue = pGet64;
	break;
	case	GET_TARGET_POS :
	iret=_8164_get_target_pos( AxisNo,&pGet64);
	*pGetValue = pGet64;
	break;
	case	GET_CURRENT_SPEED :
	iret=_8164_get_current_speed( AxisNo,&pGet64);
	*pGetValue = pGet64;
	break;
//	case	 :
//	iret=_8164_get_general_counter(I16 AxisNo, F64 *CntValue);
//	break;
	case	GET_RESET_COMMAND	 :
	iret=_8164_get_rest_command	( AxisNo, &pGetI32);
	*pGetValue = (double) pGetI32;

	break;
	case	CHECK_RDP	 :
	iret=_8164_check_rdp( AxisNo, &pGetI32); 
	*pGetValue = (double) pGetI32;
	break;

	case	CHECK_CONTINUOUS_BUFFER :
	iret=_8164_check_continuous_buffer(AxisNo);
	*pGetValue = (double) iret;
	break;

	case	EMG_STOP :
	iret= _8164_emg_stop( AxisNo);
	break;
	case	UNFIX_SPEED_RANGE :
	iret= _8164_unfix_speed_range( AxisNo);
	break;
	case	DISABLE_SOFT_LIMIT	 :
	iret= _8164_disable_soft_limit(AxisNo);
	break;
	case  RESET_ERROR_COUNTER	 :
	iret= _8164_reset_error_counter( AxisNo);
	break;

	case	SET_SD_PIN	 :
	iret= _8164_set_sd_pin( AxisNo, iSet1);
	break;
	case	SET_SERVO	 :
	iret= _8164_set_servo( AxisNo, iSet1);
	break;
	case	SET_PLS_OUTMODE :
	iret= _8164_set_pls_outmode( AxisNo, iSet1);
	break;
	case	SET_FEEDBK_SRC :
	iret= _8164_set_feedback_src( AxisNo, iSet1);
	break;


	case	SET_LTC_LOGIC		 :
	iret= _8164_set_ltc_logic( AxisNo,  iSet1);
	break;
	case	SET_PCS_LOGIC :
	iret= _8164_set_pcs_logic( AxisNo,  iSet1);
	break;
	case	SET_EL	 :
	iret=_8164_set_el( AxisNo,  iSet1);
	break;

	case ENABLE_SOFT_LIMIT	 :
	iret=_8164_enable_soft_limit( AxisNo, iSet1);
	break;
	case	SET_CONTINUOUS_MOVE	 :
	iret=_8164_set_continuous_move( AxisNo,iSet1);
	break;
	case	SET_IDLE_PULSE	 :
	iret=_8164_set_idle_pulse( AxisNo, iSet1);
	break;
	case	SET_SYNC_STOP_MODE	 :
	iret=_8164_set_sync_stop_mode( AxisNo, iSet1);
	break;

	case	SET_AXIS_STOP_INT	 :
	iret=_8164_set_axis_stop_int( AxisNo, iSet1);
	break;
	case	MASK_AXIS_STOP_INT	 :
	iret=_8164_mask_axis_stop_int( AxisNo, iSet1);
	break;
	case	SET_LATCH_SRC	 :
	iret= _8164_set_latch_source( AxisNo, iSet1);
	break;

	case	SUPPRESS_VIBRATION	 :
	iret= _8164_suppress_vibration( AxisNo, iSet1,iSet2);
	break;
	case	SET_PLS_INMODE :
	iret=_8164_set_pls_iptmode( AxisNo, iSet1,iSet2);
	break;
	case	SET_ALM	 :
	iret=_8164_set_alm( AxisNo, iSet1,iSet2);
	break;
	case	SET_INP :
	iret=_8164_set_inp( AxisNo, iSet1,iSet2);
	break;
	case	SET_ERC	 :
	iret= _8164_set_erc( AxisNo, iSet1,iSet2);
	break;
	case	BACKLASH_COMP :
	iret=_8164_backlash_comp( AxisNo, iSet1,iSet2);
	break;
	case	SET_PULSER_IPTMODE :
	iret= _8164_set_pulser_iptmode( AxisNo, iSet1,iSet2);
	break;
	case	SET_SD :
	iret=_8164_set_sd( AxisNo, iSet1,iSet2,iSet3,iSet4);
	break;
	case	SET_HOME_CONFIG :
	iret=_8164_set_home_config( AxisNo,iSet1,iSet2,iSet3,iSet4,iSet5);
	break;
	case	SET_SYNC_OPTION	 :
	iret= _8164_set_sync_option( AxisNo, iSet1,iSet2,iSet3,iSet4);
	break;
		case	SET_PULSE_RATIO	 :
	iret=_8164_set_pulser_ratio( AxisNo, iSet1,iSet2);
	break;

	case	 SET_ERROR_COUNTER_CHECK:
	iret=_8164_set_error_counter_check(AxisNo, iSet1,iSet2);
	break;

	case	 INT_CONTROL:
	iret=_8164_int_control(CardNo, (U16) iSet1);
	break;

	case	SET_LINE_MOVE_MODE	 :
	iret=_8164_set_line_move_mode( AxisNo,  iSet1);
	break;
	case	SET_AXIS_OPTION :
	iret=_8164_set_axis_option( AxisNo,  iSet1);
	break;
	case	SET_ROTARY_COUNTER :
	iret=_8164_set_rotary_counter( AxisNo,  iSet1);
	break;
	case	SET_AUTO_RDP	 :
	iret=_8164_set_auto_rdp	(CardNo, iSet1);
	break;
	case	MASK_OUTPUT_PULSE :
	iret=_8164_mask_output_pulse( AxisNo,  iSet1);
	break;
	case	SET_SYNC_MODE	 :
	iret=_8164_set_sync_signal_mode( AxisNo,  iSet1);
	break;
	case	SET_SYNC_SIG_SOURCE : ///????
	iret=_8164_set_sync_signal_source( AxisNo,  iSet1);
	break;
	case	SET_INT_FACTOR : 
	iret=_8164_set_int_factor(AxisNo, iSet1);
	break;

	case	SET_COMP_DATA : 
	iret=_8164_set_compare_data(AxisNo, iSet1,fSet1);
	break;

	case	SET_COMP_MODE :
	iret= _8164_set_compare_mode(AxisNo, iSet1,iSet2,iSet3,iSet4);
	break;

//// not possible
//    case SET_AUTO_COMPARE	:   ///// "set auto compare\0"
///	iret= _8164_set_compare_mode(AxisNo, iSet1,iSet2,iSet3,iSet4);

//	break;
 //	BUILD_COMPARE_FUNCTION	+LONG_PAD, "build compare function\0"
 //	BUILD_COMPARE_TABLE		+LONG_PAD, "build compare table\0"


	}

	*pResult=iret;




}




void AdLinkI16( const LPDRIVER_INST pNet, SPECIAL_INST* const pData )
{
	    int rc = SUCCESS ;

	UINT16 AxisNo,CardNo;
	I16 iret=0;

	I16 iSet1,iSet2,iSet3,iSet4,iSet5;

	

    SPECIAL_INST_OTHERS* const pUser = &pData->User.paramOthers   ;

    UINT16* pResult = BuildUiotPointer( pUser->Header.ofsResult );
    UINT16* pStatus = BuildUiotPointer( pUser->Header.ofsStatus );
 
    int* pGetValue = BuildUiotPointer( pUser->iGetValue );

 	*pResult=rc;	
	*pStatus=rc;

	CardNo = (pNet->PciIndex -1);
	AxisNo=(CardNo *4) + pUser->AxisAddress; // axis number
	
	iSet1=pUser->iSetValue1 ;
	iSet2=pUser->iSetValue2;
	iSet3=pUser->iSetValue3 ;
	iSet4=pUser->iSetValue4 ;
	iSet5=pUser->iSetValue5 ;

#if defined( _DEBUG )
 SayOut( "AdLink int : %d,%d,%d,%d,%d", iSet1, iSet2, iSet3,iSet4,iSet5 );
#endif
		iret= ERR_FunctionCall_Missing;

	switch(pUser->Function  ) 
    {

	case	EMG_STOP :
	iret= _8164_emg_stop( AxisNo);
	break;
	case	UNFIX_SPEED_RANGE :
	iret= _8164_unfix_speed_range( AxisNo);
	break;
	case	DISABLE_SOFT_LIMIT	 :
	iret= _8164_disable_soft_limit(AxisNo);
	break;
	case  RESET_ERROR_COUNTER	 :
	iret= _8164_reset_error_counter( AxisNo);
	break;

	case	SET_SD_PIN	 :
	iret= _8164_set_sd_pin( AxisNo, iSet1);
	break;
	case	SET_SERVO	 :
	iret= _8164_set_servo( AxisNo, iSet1);
	break;
	case	SET_PLS_OUTMODE :
	iret= _8164_set_pls_outmode( AxisNo, iSet1);
	break;
	case	SET_FEEDBK_SRC :
	iret= _8164_set_feedback_src( AxisNo, iSet1);
	break;


	case	SET_LTC_LOGIC		 :
	iret= _8164_set_ltc_logic( AxisNo,  iSet1);
	break;
	case	SET_PCS_LOGIC :
	iret= _8164_set_pcs_logic( AxisNo,  iSet1);
	break;
	case	SET_EL	 :
	iret=_8164_set_el( AxisNo,  iSet1);
	break;

	case ENABLE_SOFT_LIMIT	 :
	iret=_8164_enable_soft_limit( AxisNo, iSet1);
	break;
	case	SET_CONTINUOUS_MOVE	 :
	iret=_8164_set_continuous_move( AxisNo,iSet1);
	break;
	case	SET_IDLE_PULSE	 :
	iret=_8164_set_idle_pulse( AxisNo, iSet1);
	break;
	case	SET_SYNC_STOP_MODE	 :
	iret=_8164_set_sync_stop_mode( AxisNo, iSet1);
	break;

	case	SET_AXIS_STOP_INT	 :
	iret=_8164_set_axis_stop_int( AxisNo, iSet1);
	break;
	case	MASK_AXIS_STOP_INT	 :
	iret=_8164_mask_axis_stop_int( AxisNo, iSet1);
	break;
	case	SET_LATCH_SRC	 :
	iret= _8164_set_latch_source( AxisNo, iSet1);
	break;

	case	SUPPRESS_VIBRATION	 :
	iret= _8164_suppress_vibration( AxisNo, iSet1,iSet2);
	break;
	case	SET_PLS_INMODE :
	iret=_8164_set_pls_iptmode( AxisNo, iSet1,iSet2);
	break;
	case	SET_ALM	 :
	iret=_8164_set_alm( AxisNo, iSet1,iSet2);
	break;
	case	SET_INP :
	iret=_8164_set_inp( AxisNo, iSet1,iSet2);
	break;
	case	SET_ERC	 :
	iret= _8164_set_erc( AxisNo, iSet1,iSet2);
	break;
	case	BACKLASH_COMP :
	iret=_8164_backlash_comp( AxisNo, iSet1,iSet2);
	break;
	case	SET_PULSER_IPTMODE :
	iret= _8164_set_pulser_iptmode( AxisNo, iSet1,iSet2);
	break;
	case	SET_SD :
	iret=_8164_set_sd( AxisNo, iSet1,iSet2,iSet3,iSet4);
	break;
	case	SET_HOME_CONFIG :
	iret=_8164_set_home_config( AxisNo,iSet1,iSet2,iSet3,iSet4,iSet5);
	break;
	case	SET_SYNC_OPTION	 :
	iret= _8164_set_sync_option( AxisNo, iSet1,iSet2,iSet3,iSet4);
	break;
		case	SET_PULSE_RATIO	 :
	iret=_8164_set_pulser_ratio( AxisNo, iSet1,iSet2);
	break;

	case	 SET_ERROR_COUNTER_CHECK:
	iret=_8164_set_error_counter_check(AxisNo, iSet1,iSet2);
	break;

	case	 INT_CONTROL:
	iret=_8164_int_control(CardNo, (U16) iSet1);
	break;

	case	SET_LINE_MOVE_MODE	 :
	iret=_8164_set_line_move_mode( AxisNo,  iSet1);
	break;
	case	SET_AXIS_OPTION :
	iret=_8164_set_axis_option( AxisNo,  iSet1);
	break;
	case	SET_ROTARY_COUNTER :
	iret=_8164_set_rotary_counter( AxisNo,  iSet1);
	break;
	case	SET_AUTO_RDP	 :
	iret=_8164_set_auto_rdp	(CardNo, iSet1);
	break;
	case	MASK_OUTPUT_PULSE :
	iret=_8164_mask_output_pulse( AxisNo,  iSet1);
	break;
	case	SET_SYNC_MODE	 :
	iret=_8164_set_sync_signal_mode( AxisNo,  iSet1);
	break;
	case	SET_SYNC_SIG_SOURCE : ///????
	iret=_8164_set_sync_signal_source( AxisNo,  iSet1);
	break;
	case	SET_INT_FACTOR : 
	iret=_8164_set_int_factor(AxisNo, iSet1);
	break;




	}

	*pResult=iret;




}


void AdLinkInterpol( const LPDRIVER_INST pNet, SPECIAL_INST* const pData )
{
    int rc = SUCCESS ;

	UINT16 AxisNo;
	I16 FirstAxisNo,CardNo,DIR;
	F64 Pos, DistX,  DistY, DistZ,  DistU, StrVel,  MaxVel,  Tacc,  Tdec,  SVacc,  SVdec;
	F64 PosX, PosY,PosZ,PosU,ORG, SpeedLimit,Time;
	F64 Cx,Cy,Ex,Ey,OffsetCx,OffsetCy,OffsetEx,OffsetEy;
	I16 iret=0;
	I16 sze=0;
	
    SPECIAL_INST_COMMAND* const pUser = &pData->User.paramCommand;
    const LPPTBUFFER pRBuffer = &pUser->AxisArray ;

    I16* AxisArray = BuildUiotPointer( pRBuffer->Offset );

    UINT16* pResult = BuildUiotPointer( pUser->Header.ofsResult );
    UINT16* pStatus = BuildUiotPointer( pUser->Header.ofsStatus );
	*pStatus=rc;
 	*pResult=rc;	


	sze= pRBuffer->Size ;



	CardNo = (pNet->PciIndex -1);
	AxisNo=(CardNo *4) + pUser->AxisAddress; // axis number

	Pos= pUser->fPos ;
	DistX= pUser->fPosX;
	DistY= pUser->fPosY;
	DistZ= pUser->fPosZ;
	DistU= pUser->fPosU;
	PosX= pUser->fPosX;
	PosY= pUser->fPosY;
	PosZ= pUser->fPosZ;
	PosU= pUser->fPosU;

	StrVel=pUser->fstVel ;
	MaxVel=pUser->fmaxVel ;
	Tacc=pUser->fTAcc ;
	Tdec=pUser->fTDec;
	SVacc=pUser->fSVAcc ;
	SVdec=pUser->fSVDec;

	Cx = pUser->fCx ;
	Cy = pUser->fCy ;
	Ex = pUser->fEx ;
	Ey = pUser->fEy ;
	OffsetCx = pUser->fCx ;
	OffsetCy = pUser->fCy ;
	OffsetEx = pUser->fEx ;
	OffsetEy = pUser->fEy ;
	DIR=pUser->OptDir ;
	ORG=pUser->fOrg ;
	SpeedLimit=pUser->fOrg;
	Time=pUser->fOrg;

	FirstAxisNo=pUser->AxisAddress ;
#if defined( _DEBUG )
	 SayOut( "Axis Id : %d",pUser->AxisAddress ,0,0,0,0);
	 SayOut( "interpole float vel : %f,%f,%f,%f",pUser->fstVel , pUser->fmaxVel , pUser->fTAcc,pUser->fTDec,0);
 	SayOut( "interpole float pos x,y,z,u : %f,%f,%f,%f,%f",pUser->fPos , pUser->fPosX, pUser->fPosY,pUser->fPosZ,pUser->fPosU );
	 SayOut( "interpole float cx,cy,ex,ey : %f,%f,%f,%f",pUser->fCx , pUser->fCy, pUser->fEx,pUser->fEy,0);
	 SayOut( "User Function Id : %d",pUser->Function ,0,0,0,0);

#endif

	iret= ERR_FunctionCall_Missing;

	switch(pUser->Function  ) 
    {

	case	START_MOVE_ALL 	 :
	iret= _8164_start_move_all( FirstAxisNo);
	break;
	case	STOP_MOVE_ALL :
	iret= _8164_stop_move_all( FirstAxisNo);
	break;
	
	case	 START_SR_LINE2 :
	iret=  _8164_start_sr_line2( CardNo,  AxisArray,  DistX,  DistY,  StrVel,  MaxVel,  Tacc,  Tdec,  SVacc,  SVdec);
	break;
	case	 START_TR_LINE2	 :
	iret=  _8164_start_tr_line2( CardNo,  AxisArray,  DistX,  DistY,  StrVel,  MaxVel,  Tacc,  Tdec);
	break;
	case	 START_SA_LINE2	 :
	iret=  _8164_start_sa_line2( CardNo,  AxisArray,  PosX,  PosY,  StrVel,  MaxVel,  Tacc,  Tdec,  SVacc,  SVdec);
	break;
	case	 START_TA_LINE2	 :
	iret= _8164_start_ta_line2( CardNo,  AxisArray,  PosX,  PosY,  StrVel,  MaxVel,  Tacc,  Tdec);
	break;

	case	 START_SR_LINE3 :
	iret= _8164_start_sr_line3	( CardNo,  AxisArray,  DistX,  DistY,  DistZ,  StrVel,  MaxVel,  Tacc,  Tdec,  SVacc,  SVdec);
	break;
	case	 START_TR_LINE3	 :
	iret=  _8164_start_tr_line3	( CardNo,  AxisArray,  DistX,  DistY,  DistZ,  StrVel,  MaxVel,  Tacc,  Tdec);
	break;
	case	 START_SA_LINE3	 :
	iret= _8164_start_sa_line3	( CardNo,  AxisArray,  PosX,  PosY,  PosZ,  StrVel,  MaxVel,  Tacc,  Tdec,  SVacc,  SVdec);
	break;
	case	 START_TA_LINE3	 :
	iret= _8164_start_ta_line3	( CardNo,  AxisArray,  PosX,  PosY,  PosZ,  StrVel,  MaxVel,  Tacc,  Tdec);
	break;

	case	 START_SR_LINE4 :
	iret= _8164_start_sr_line4	( CardNo,   DistX,  DistY,  DistZ, DistU, StrVel,  MaxVel,  Tacc,  Tdec,  SVacc,  SVdec);
	break;
	case	 START_TR_LINE4	 :
	iret=  _8164_start_tr_line4	( CardNo,   DistX,  DistY,  DistZ, DistU,  StrVel,  MaxVel,  Tacc,  Tdec);
	break;
	case	 START_SA_LINE4	 :
	iret= _8164_start_sa_line4	( CardNo,   PosX,  PosY,  PosZ, PosU,   StrVel,  MaxVel,  Tacc,  Tdec,  SVacc,  SVdec);
	break;
	case	 START_TA_LINE4	 :
	iret= _8164_start_ta_line4	( CardNo,   PosX,  PosY,  PosZ, PosU,   StrVel,  MaxVel,  Tacc,  Tdec);
	break;
///
	case	START_SR_MOVE 	 :
	iret= _8164_start_sr_move( AxisNo,  Pos,  StrVel,  MaxVel,  Tacc,  Tdec,  SVacc,  SVdec);
	break;
	case	START_TR_MOVE 	 :
	iret= _8164_start_tr_move( AxisNo,  Pos,  StrVel,  MaxVel,  Tacc,  Tdec);
	break;
	case	START_SA_MOVE 	 :
	iret= _8164_start_sa_move( AxisNo,  Pos,  StrVel,  MaxVel,   Tacc,  Tdec,  SVacc,  SVdec);
	break;
	case	START_TA_MOVE 	 :
	iret= _8164_start_ta_move( AxisNo,  Pos,  StrVel,  MaxVel,   Tacc,  Tdec);
	break;

////
/*	case	 SET_SR_MOVE_ALL	 :
	iret= _8164_set_sr_move_all( TotalAx,  AxisArray,  DistA,  StrVelA,  MaxVelA,  TaccA,  TdecA,  SVaccA,  SVdecA);
	break;
	case	 SET_TR_MOVE_ALL	 :
	iret= _8164_set_tr_move_all( TotalAx, AxisArray,  DistA,  StrVelA,  MaxVelA,  TaccA,  TdecA);
	break;
	case	 SET_SA_MOVE_ALL	 :
	iret= _8164_set_sa_move_all( TotalAx,  AxisArray,  PosA,  StrVelA,  MaxVelA,  TaccA,  TdecA,  SVaccA,  SVdecA);
	break;
	case	 SET_TA_MOVE_ALL	 :
	iret= _8164_set_ta_move_all( TotalAx,  AxisArray,  PosA,  StrVelA,  MaxVelA,  TaccA,  TdecA);
	break;
*/
///
	case	 START_TR_ARC2	 :
	iret= _8164_start_tr_arc2	( CardNo,  AxisArray,  OffsetCx,  OffsetCy,  OffsetEx,  OffsetEy,  DIR,  StrVel,  MaxVel,  Tacc,  Tdec);
	break;

	case	 START_TA_ARC2	 :
	iret= _8164_start_ta_arc2	( CardNo,  AxisArray,  Cx,  Cy,  Ex,  Ey,  DIR,  StrVel,  MaxVel,  Tacc,  Tdec);
	break;

	case	 START_SR_ARC2	 :
	iret= _8164_start_sr_arc2	( CardNo,  AxisArray,  OffsetCx,  OffsetCy,  OffsetEx,  OffsetEy,  DIR,  StrVel,  MaxVel,  Tacc,  Tdec,  SVacc,  SVdec);
	break;

	case	 START_SA_ARC2	 :
	iret= _8164_start_sa_arc2	( CardNo,  AxisArray,  Cx,  Cy,  Ex,  Ey,  DIR,  StrVel,  MaxVel,  Tacc,  Tdec,  SVacc,  SVdec);
	break;

	case	START_TR_MOVE_XY	:
	iret= _8164_start_tr_move_xy( CardNo,  DistX,  DistY,  StrVel,  MaxVel,  Tacc,  Tdec);
	break;

	case	START_TA_MOVE_XY 	 :
	iret= _8164_start_ta_move_xy( CardNo,  PosX,  PosY,  StrVel,  MaxVel,  Tacc,  Tdec);
	break;
	case	START_SR_MOVE_XY 	 :
	iret= _8164_start_sr_move_xy( CardNo,  DistX,  DistY,  StrVel,  MaxVel,  Tacc,  Tdec,  SVacc,  SVdec);
	break;
	case	START_SA_MOVE_XY 	 :
	iret= _8164_start_sa_move_xy( CardNo,  PosX,  PosY,  StrVel,  MaxVel,  Tacc,  Tdec,  SVacc,  SVdec);
	break;
	case	START_TR_MOVE_ZU 	 :
	iret= _8164_start_tr_move_zu( CardNo,  DistU,  DistZ,  StrVel,  MaxVel,  Tacc,  Tdec);
	break;
	case	START_TA_MOVE_ZU 	 :
	iret= _8164_start_ta_move_zu( CardNo,  PosU,  PosZ,  StrVel,  MaxVel,  Tacc,  Tdec);
	break;
	case	START_SR_MOVE_ZU 	 :
	iret= _8164_start_sr_move_zu( CardNo,  DistU,  DistZ,  StrVel,  MaxVel,  Tacc,  Tdec,  SVacc,  SVdec);
	break;
	case	START_SA_MOVE_ZU 	 :
	iret= _8164_start_sa_move_zu( CardNo,  PosU,  PosZ,  StrVel,  MaxVel,  Tacc,  Tdec,  SVacc,  SVdec);
	break;

	case	 START_TR_ARC_XY	 :
	iret= _8164_start_tr_arc_xy( CardNo,  OffsetCx,  OffsetCy,  OffsetEx,  OffsetEy,  DIR,  StrVel,  MaxVel,  Tacc,  Tdec);
		break;
	case	 START_TA_ARC_XY	 :
	iret=_8164_start_ta_arc_xy( CardNo,  Cx,  Cy,  Ex,  Ey,  DIR,  StrVel,  MaxVel,  Tacc,  Tdec);
		break;
	case	 START_SR_ARC_XY	 :
	iret=_8164_start_sr_arc_xy( CardNo,  OffsetCx,  OffsetCy,  OffsetEx,  OffsetEy,  DIR,  StrVel,  MaxVel,  Tacc,  Tdec,  SVacc,  SVdec);
		break;
	case	 START_SA_ARC_XY	 :
	iret=_8164_start_sa_arc_xy( CardNo,  Cx,  Cy,  Ex,  Ey,  DIR,  StrVel,  MaxVel,  Tacc,  Tdec,  SVacc,  SVdec);
		break;

	case	 START_TR_ARC_ZU	 :
	iret= _8164_start_tr_arc_zu( CardNo,  OffsetCx,  OffsetCy,  OffsetEx,  OffsetEy,  DIR,  StrVel,  MaxVel,  Tacc,  Tdec);
		break;
	case	 START_TA_ARC_ZU	 :
	iret=_8164_start_ta_arc_zu( CardNo,  Cx,  Cy,  Ex,  Ey,  DIR,  StrVel,  MaxVel,  Tacc,  Tdec);
		break;
	case	 START_SR_ARC_ZU	 :
	iret= _8164_start_sr_arc_zu( CardNo,  OffsetCx,  OffsetCy,  OffsetEx,  OffsetEy,  DIR,  StrVel,  MaxVel,  Tacc,  Tdec,  SVacc,  SVdec);
		break;
	case	 START_SA_ARC_ZU	 :
	iret= _8164_start_sa_arc_zu( CardNo,  Cx,  Cy,  Ex,  Ey,  DIR,  StrVel,  MaxVel,  Tacc,  Tdec,  SVacc,  SVdec);
		break;


	case	 PULSER_R_LINE2	 :
	iret= _8164_pulser_r_line2 	( CardNo, AxisArray,  DistX,  DistY,  SpeedLimit);
		break;
	case	 PULSER_R_ARC2	 :
	iret= _8164_pulser_a_line2	( CardNo,  AxisArray,  PosX,  PosY,   SpeedLimit);
		break;
	case	 PULSER_A_LINE2	 :
	iret= _8164_pulser_r_arc2	( CardNo,  AxisArray,  OffsetCx,  OffsetCy,  OffsetEx,  OffsetEy,  DIR,  MaxVel);
		break;
	case	 PULSER_A_ARC2	 :
	iret=_8164_pulser_a_arc2	( CardNo,  AxisArray,  Cx,  Cy,  Ex,  Ey,  DIR,  MaxVel);
		break;

	case	V_CHANGE	 :
	iret=_8164_v_change( AxisNo, MaxVel, Time);

	break;
	case	HOMVE_MOVE	 :
	iret=_8164_home_move( AxisNo,  StrVel,  MaxVel,  Tacc);
	break;
	case	TV_MOVE	 :
	iret=_8164_tv_move( AxisNo,  StrVel,  MaxVel,  Tacc);
	break;
	case	SV_MOVE	 :
	iret=_8164_sv_move( AxisNo,  StrVel,  MaxVel,  Tacc,  SVacc);
	break;
	case	HOME_SEARCH	 :
	iret=_8164_home_search( AxisNo,  StrVel,  MaxVel,  Tacc, ORG);
	break;
	case	ESCAPE_HOME :
	iret= _8164_escape_home	( AxisNo,StrVel,  MaxVel,  Tacc);
	break;

/*
		
_8164_start_r_arc2	(I16 CardNo, I16 *AxisArray, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 MaxVel);
_8164_start_a_arc2	(I16 CardNo, I16 *AxisArray, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 MaxVel);

_8164_start_r_arc_xy 	(I16 CardNo, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 MaxVel);
_8164_start_r_arc_zu 	(I16 CardNo, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 MaxVel );

_8164_start_a_arc_xy 	(I16 CardNo, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 MaxVel);
 
_8164_start_a_arc_zu 	(I16 CardNo, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 MaxVel);
*/


	}

	*pResult=iret;
}

int ADlinkReadIO( LPDEVICE_INST const pDevice, int bn, VOID *Dest )
{

    int     rc       = SUCCESS;
	UINT16 ValueGet16;
	UINT16	AxisNum; //	IntAxisNum;
	I32	ValuePos ;
	int cardno =0;
	float	ValuePos32=0;
	double ValuePosF64 = 0;
	I16	 ValueI16=0;
	U32 ValueU32=0;

	I16 AxisNo=0;

///	printf("adlink 8164 read io,motion"); 

	switch(pDevice->Type ) 

    {

        case DEVICE_CARD_POS:   /// pos, enc, error cnt, g cnt
		//0~3
		AxisNum =0;

		for (;AxisNum < 4 ; AxisNum++ )
		{
		AxisNo= (bn * 4)+AxisNum;

		rc= _8164_get_command(AxisNo, &ValuePos);  /// current pos
		*((UINT32  volatile*)Dest+(AxisNum * 4)+0) = (UINT32)ValuePos;
	
		rc= _8164_get_position(AxisNo, &ValuePosF64); ///feedback encoder
		ValuePos32=ValuePosF64;	// convert to 32 bits
		*((UINT32  volatile*)Dest+(AxisNum*4)+1) = (UINT32)ValuePos32;
	//		_8164_get_encoder(AxisNo, &ValuePos);
	//	*((UINT32  volatile*)Dest+(AxisNum*4)+1) = (UINT32)ValuePos;


		rc= _8164_get_error_counter(AxisNo,&ValuePos); ///error cnt
		*((UINT32  volatile*)Dest+(AxisNum*4)+2) = (UINT32)ValuePos;

		rc= _8164_get_general_counter(AxisNo, &ValuePosF64); ///general cnt
		ValuePos32=ValuePosF64;	// convert to 32 bits
		*((UINT32  volatile*)Dest+(AxisNum*4)+3) = (UINT32)ValuePos32;
		}


		break;

		case DEVICE_CARD_INT_STATUS:   //event and error on int int_stat0-3,sts0-3
		AxisNum =0;
		for (;AxisNum < 4 ; AxisNum++ )
		{
		AxisNo= (bn * 4)+AxisNum;
		rc = _8164_get_inter_status(AxisNo,&ValueU32); ///event 
		*((UINT32  volatile*)Dest+AxisNum) = ValueU32;

		rc= _8164_get_sts(AxisNo,&ValueU32); 
		*((UINT32  volatile*)Dest+AxisNum+4) = ValueU32;
		}
			
		break;

		case DEVICE_CARD_MOTION_STATUS:

		AxisNum =0;
		for (;AxisNum < 4 ; AxisNum++ )
		{
		AxisNo= (bn * 4)+AxisNum;
		rc= _8164_get_io_status(AxisNo, &ValueGet16); 
		*((UINT16  volatile*)Dest+AxisNum) = (UINT16) ValueGet16;

		ValueI16 = _8164_motion_done(AxisNo);  
		*((UINT16  volatile*)Dest+AxisNum+4) = (UINT16) ValueI16;

////	iret=_8164_check_compare_status	( AxisNo,&pGetU16);

		}

		break;            
    }




	return  (rc);

}
