/***************************************************************

                Card.h             

   This file contains the interface to the manufacturer code

****************************************************************/


#ifndef  __CARD_H__
#define  __CARD_H__


#define LOW_BYTE(x)         (x & 0x00FF)
#define HI_BYTE(x)          ((x & 0xFF00) >> 8)
#define PAGE(x)             ((x & 0xF000) >> 12)
#define HI_OFFSET(x)          ((x & 0x0FF0) >>4)
#define LO_OFFSET(x)          ((x & 0x000F) << 4)



int Init( void* const dp, P_ERR_PARAM const lpErrors);
int TestConfig( LPDRIVER_INST const pNet, P_ERR_PARAM const lpErrors);
int	DoCollect( LPDRIVER_INST pNet, LPSPECIAL_INST pData);

///low level read write here !

void AdLinkMotion( const LPDRIVER_INST pNet, SPECIAL_INST* const pData );
void AdLinkInterpol( const LPDRIVER_INST pNet, SPECIAL_INST* const pData );
void AdLinkF64( const LPDRIVER_INST pNet, SPECIAL_INST* const pData );
void AdLinkI16( const LPDRIVER_INST pNet, SPECIAL_INST* const pData );
int ADlinkReadIO( LPDEVICE_INST const pDevice, int bn, VOID *Dest );
void AdLinkSetGet( const LPDRIVER_INST pNet, SPECIAL_INST* const pData );





#endif      /* __CARD_H__ */

