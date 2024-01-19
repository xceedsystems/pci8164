#ifndef _8164IO_H
#define _8164IO_H

#include "motion.h"
#include "pcl6045.h"

I16 i_set_s_rdp_virtual(I16 AxisNo, F64 VChg_Dist, F64 V_FH, F64 V_DR, F64 *V_DP,I16 Cont_Index);
I16 i_set_t_rdp_virtual(I16 AxisNo, F64 VChg_Dist, F64 V_FH, F64 V_DR, F64 *V_DP,I16 Cont_Index);
I16 i_set_t_cmp_rdp_virtual(I16 AxisNo, F64 Res_Dist, F64 VChg_Dist, F64 V_FH, F64 V_DR, F64 *V_DP);
I16 i_set_s_cmp_rdp_virtual(I16 AxisNo, F64 Res_Dist, F64 VChg_Dist, F64 V_FH, F64 V_DR, F64 *V_DP);
I16 i_clear_rdp(I16 AxisNo,I16 Pre);
I16 i_clear_rspeed(I16 AxisNo,I16 Pre);
I16 i_set_rdp_ex(I16 AxisNo,U32 RDP_Value, I16 Pre);
U32 i_get_rdp_ex(I16 AxisNo);
I16 i_set_to_control_axis(I16 MasterAxisNo,I16 ControlAxisNo, I16 Pre);
I16 i_set_rci(I16 AxisNo, F64 Dist, I16 Pre);
I16 i_set_run_mode(pAXIS_INFO pAxis,I16 MOD,I16 C_Type, I16 SDP_Type, I16 FH_Type);
I16 i_get_position(I16 AxisNo, F64 *pos);
I16 i_set_compare_data(I16 AxisNo, I16 CompNo, F64 Pos);
I16 i_set_compare_mode(I16 AxisNo, I16 CompNo, I16 CmpSrc, I16 CmpMethod, I16 CmpAction);
I16 i_get_compare_data(I16 AxisNo, I16 CompNo, F64 *Pos);
I16 i_check_arc_compensate(pAXIS_INFO pAxis, I16 MOD,F64 *CCx,F64 *CCy,F64 Ex,F64 Ey);
I16 i_set_auto_mode_rdp(I16 AxisNo, I16 Pre);

#endif
