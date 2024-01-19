#ifndef _P8164_1_H

#define _P8164_1_H

#include "motion.h"
#include "type_def.h"

// #define _WIN32_WINNT 0x0400
// #include <windows.h>

#define MAX_PCI_CARDS   (I16)12
#define MAX_MPC_CARDS	(I16)4
#define MAX_EVENTA		(I16)6
#define AXIS_PER_CARD 	(I16)4

#define CARD0 (I16)0
#define CARD1 (I16)1
#define CARD2 (I16)2
#define CARD3 (I16)3
#define CARD4 (I16)4
#define CARD5 (I16)5
#define CARD6 (I16)6
#define CARD7 (I16)7
#define CARD8 (I16)8
#define CARD9 (I16)9
#define CARD10 (I16)10
#define CARD11 (I16)11

#ifdef __cplusplus
extern "C" {
#endif

int _8164_initial(I16 *existCards);

I16 _8164_int_control(U16 cardNo, U16 intFlag );
I16 _8164_set_int_factor(I16 AxisNo, U32 int_factor );
I16 _8164_close(I16 CardNo);
I16 _8164_get_irq_channel(I16 cardNo, U16 *irq_no );
I16 _8164_get_base_addr(I16 cardNo, U16 *base_addr );
I16 _8164_get_io_status(I16 AxisNo, U16 *io_sts);
I16 _8164_motion_done(I16 AxisNo);
I16 _8164_get_position(I16 AxisNo, F64 *pos);
I16 _8164_get_encoder(I16 AxisNo, I32 *pos) ;
I16 _8164_set_position(I16 AxisNo, F64 pos);
I16 _8164_get_command(I16 AxisNo, I32 *cmd);
I16 _8164_set_command(I16 AxisNo, I32 cmd);
I16 _8164_get_error_counter(I16 AxisNo, I32 *error);
I16 _8164_reset_error_counter(I16 AxisNo);
I16 _8164_get_target_pos(I16 AxisNo, F64 *pos);
I16 _8164_reset_target_pos(I16 AxisNo, F64 pos);
I16 _8164_get_current_speed(I16 AxisNo, F64 *speed);
I16 _8164_get_rest_command(I16 AxisNo, I32 *rest_command);
I16 _8164_get_latch_data(I16 AxisNo, I16 LatchNo, F64 *Pos);
I16 _8164_check_rdp(I16 AxisNo, I32 *rdp_command);
I16 _8164_set_servo(I16 AxisNo, I16 on_off);
I16 _8164_set_pls_outmode(I16 AxisNo, I16 pls_outmode);
I16 _8164_set_pls_iptmode(I16 AxisNo, I16 pls_iptmode, I16 pls_logic);
I16 _8164_set_feedback_src(I16 AxisNo, I16 Src);
I16 _8164_set_general_counter(I16 AxisNo,I16 CntSrc, F64 CntValue);
I16 _8164_get_general_counter(I16 AxisNo, F64 *CntValue);

I16 _8164_d_output(I16 CardNo, I16 Ch_No, I16 value);
I16 _8164_get_dio_status(I16 CardNo, U16 *dio_sts);

I16 _8164_set_alm(I16 AxisNo, I16 alm_logic, I16 alm_mode);
I16 _8164_set_inp(I16 AxisNo, I16 inp_enable, I16 inp_logic);
I16 _8164_set_ltc_logic(I16 AxisNo, I16 ltc_logic);
I16 _8164_set_pcs_logic(I16 AxisNo, I16 pcs_logic);
I16 _8164_set_erc(I16 AxisNo, I16 erc_logic, I16 erc_on_time);
I16 _8164_set_sd(I16 AxisNo, I16 enable, I16 sd_logic, I16 sd_latch, I16 sd_mode);
I16 _8164_set_el(I16 AxisNo, I16 el_mode);
I16 _8164_set_move_ratio(I16 AxisNo, F64 move_ratio);
I16 _8164_set_sd_pin(I16 AxisNo, I16 Type);

I16 _8164_set_home_config(I16 AxisNo, I16 home_mode, I16 org_logic, I16 ez_logic, I16 ez_count, I16 erc_out);
I16 _8164_home_move(I16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc);

I16 _8164_pulser_vmove(I16 AxisNo,F64 SpeedLimit);
I16 _8164_pulser_pmove(I16 AxisNo, F64 Dist,F64 SpeedLimit);
I16 _8164_pulser_home_move(I16 AxisNo, I16 HomeType,F64 SpeedLimit);
I16 _8164_set_pulser_iptmode(I16 AxisNo,I16 InputMode, I16 Inverse);
I16 _8164_backlash_comp(I16 AxisNo, I16 BCompPulse, I16 Mode);
I16 _8164_suppress_vibration(I16 AxisNo, U16 ReverseTime, U16 ForwardTime);

I16 _8164_tv_move(I16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc);
I16 _8164_sv_move(I16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc, F64 SVacc);
I16 _8164_emg_stop(I16 AxisNo);
I16 _8164_sd_stop(I16 AxisNo,F64 Tdec);
I16 _8164_v_change(I16 AxisNo, F64 NewVel, F64 Time);
I16 _8164_cmp_v_change(I16 AxisNo, F64 Res_Dist, F64 OldVel, F64 NewVel, F64 Time);
I16 _8164_p_change(I16 AxisNo, F64 NewPos);
I16 _8164_fix_speed_range(I16 AxisNo, F64 MaxVel);
I16 _8164_unfix_speed_range(I16 AxisNo);
I16 _8164_set_continuous_move(I16 AxisNo, I16 conti_logic);

I16 _8164_set_soft_limit(I16 AxisNo, I32 PLimit, I32 NLimit);
I16 _8164_disable_soft_limit(I16 AxisNo);
I16 _8164_enable_soft_limit(I16 AxisNo, I16 Action);

I16 _8164_set_error_counter_check(I16 AxisNo, I16 Tolerance, I16 On_Off);
I16 _8164_set_general_comparator(I16 AxisNo, I16 CmpSrc, I16 CmpMethod, I16 CmpAction, F64 Data);
I16 _8164_set_trigger_comparator(I16 AxisNo, I16 CmpSrc, I16 CmpMethod, F64 Data);

I16 _8164_check_compare_data(I16 AxisNo, I16 CompType, F64 *Pos);

I16 _8164_start_tr_move(I16 AxisNo, F64 Dist, F64 StrVel, F64 MaxVel, F64 Tacc,F64 Tdec);
I16 _8164_start_ta_move(I16 AxisNo, F64 Pos, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 _8164_start_sr_move(I16 AxisNo, F64 Dist, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 _8164_start_sa_move(I16 AxisNo, F64 Pos, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);

I16 _8164_start_tr_move_xy(I16 CardNo, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 _8164_start_ta_move_xy(I16 CardNo, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 _8164_start_sr_move_xy(I16 CardNo, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 _8164_start_sa_move_xy(I16 CardNo, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);

I16 _8164_start_tr_move_zu(I16 CardNo, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 _8164_start_ta_move_zu(I16 CardNo, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 _8164_start_sr_move_zu(I16 CardNo, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 _8164_start_sa_move_zu(I16 CardNo, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);

I16 _8164_start_a_arc_xy(I16 CardNo, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 MaxVel);
I16 _8164_start_r_arc_xy(I16 CardNo, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR,F64 MaxVel);
I16 _8164_start_a_arc_zu(I16 CardNo, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 MaxVel);
I16 _8164_start_r_arc_zu(I16 CardNo, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 MaxVel );

I16 _8164_start_tr_line2(I16 CardNo, I16 *AxisArray, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 _8164_start_ta_line2(I16 CardNo, I16 *AxisArray, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 _8164_start_sr_line2(I16 CardNo, I16 *AxisArray, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 _8164_start_sa_line2(I16 CardNo, I16 *AxisArray, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);

I16 _8164_start_r_arc2(I16 CardNo, I16 *AxisArray, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 MaxVel);
I16 _8164_start_a_arc2(I16 CardNo, I16 *AxisArray, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 MaxVel);

I16 _8164_start_tr_line3(I16 CardNo, I16 *AxisArray, F64 DistX, F64 DistY, F64 DistZ, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 _8164_start_ta_line3(I16 CardNo, I16 *AxisArray, F64 PosX, F64 PosY, F64 PosZ, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 _8164_start_sr_line3(I16 CardNo, I16 *AxisArray, F64 DistX, F64 DistY, F64 DistZ, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 _8164_start_sa_line3(I16 CardNo, I16 *AxisArray, F64 PosX, F64 PosY, F64 PosZ, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);

I16 _8164_start_tr_line4(I16 CardNo, F64 DistX, F64 DistY, F64 DistZ, F64 DistU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 _8164_start_ta_line4(I16 CardNo, F64 PosX, F64 PosY, F64 PosZ, F64 PosU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 _8164_start_sr_line4(I16 CardNo, F64 DistX, F64 DistY, F64 DistZ, F64 DistU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 _8164_start_sa_line4(I16 CardNo, F64 PosX, F64 PosY, F64 PosZ, F64 PosU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);

I16 _8164_set_tr_move_all(I16 TotalAxes, I16 *AxisArray, F64 *DistA, F64 *StrVelA, F64 *MaxVelA, F64 *TaccA, F64 *TdecA);
I16 _8164_start_move_all(I16 FirstAxisNo);
I16 _8164_stop_move_all(I16 FirstAxisNo);

I16 _8164_config_from_file(char *file_name);

I16 _8164_set_fa_speed(I16 AxisNo, F64 FA_Speed);
I16 _8164_check_compare_status(I16 AxisNo, U16 *cmp_sts);
I16 _8164_check_continuous_buffer(I16 AxisNo);

I16 _8164_set_sa_move_all(I16 TotalAx, I16 *AxisArray, F64 *PosA, F64 *StrVelA, F64 *MaxVelA, F64 *TaccA, F64 *TdecA, F64 *SVaccA, F64 *SVdecA);
I16 _8164_set_ta_move_all(I16 TotalAx, I16 *AxisArray, F64 *PosA, F64 *StrVelA, F64 *MaxVelA, F64 *TaccA, F64 *TdecA);
I16 _8164_set_sr_move_all(I16 TotalAx, I16 *AxisArray, F64 *DistA, F64 *StrVelA, F64 *MaxVelA, F64 *TaccA, F64 *TdecA, F64 *SVaccA, F64 *SVdecA);
I16 _8164_set_latch_source(I16 AxisNo, I16 ltc_src);
I16 _8164_set_idle_pulse(I16 AxisNo, I16 idl_pulse);
I16 _8164_delay_time(I16 AxisNo,F64 miniSecond);
I16 _8164_set_pulser_ratio(I16 AxisNo,I16 PDV, I16 PMG);
I16 _8164_pulser_r_line2(I16 CardNo,I16 *AxisArray, F64 DistX, F64 DistY, F64 SpeedLimit);
I16 _8164_pulser_r_arc2(I16 CardNo, I16 *AxisArray, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 MaxVel);
I16 _8164_pulser_a_line2(I16 CardNo,I16 *AxisArray, F64 PosX, F64 PosY, F64 SpeedLimit);
I16 _8164_pulser_a_arc2(I16 CardNo, I16 *AxisArray, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 MaxVel);

I16 _8164_escape_home(I16 AxisNo, F64 SrVel,F64 MaxVel,F64 Tacc);
I16 _8164_home_search(I16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc, F64 ORGOffset);
I16 _8164_set_line_move_mode(I16 AxisNo, I16 Mode);

F64 _8164_verify_speed(F64 StrVel,F64 MaxVel,F64 *minAccT,F64 *maxAccT, F64 MaxSpeed);

I16 _8164_start_tr_arc2(I16 CardNo, I16 *AxisArray, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 StrVel,F64 MaxVel, F64 Tacc,F64 Tdec);
I16 _8164_start_ta_arc2(I16 CardNo, I16 *AxisArray, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc,F64 Tdec);
I16 _8164_start_sr_arc2(I16 CardNo, I16 *AxisArray, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 StrVel,F64 MaxVel, F64 Tacc,F64 Tdec,F64 SVacc,F64 SVdec);
I16 _8164_start_sa_arc2(I16 CardNo, I16 *AxisArray, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc,F64 Tdec,F64 SVacc,F64 SVdec);

I16 _8164_start_tr_arc_xy(I16 CardNo, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 StrVel,F64 MaxVel,F64 Tacc,F64 Tdec);
I16 _8164_start_ta_arc_xy(I16 CardNo, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 StrVel,F64 MaxVel,F64 Tacc,F64 Tdec);
I16 _8164_start_tr_arc_zu(I16 CardNo, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 StrVel,F64 MaxVel,F64 Tacc,F64 Tdec);
I16 _8164_start_ta_arc_zu(I16 CardNo, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 StrVel,F64 MaxVel,F64 Tacc,F64 Tdec);

I16 _8164_start_sr_arc_xy(I16 CardNo, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 StrVel,F64 MaxVel, F64 Tacc,F64 Tdec,F64 SVacc,F64 SVdec);
I16 _8164_start_sa_arc_xy(I16 CardNo, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 StrVel,F64 MaxVel, F64 Tacc,F64 Tdec,F64 SVacc,F64 SVdec);
I16 _8164_start_sr_arc_zu(I16 CardNo, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 StrVel,F64 MaxVel, F64 Tacc,F64 Tdec,F64 SVacc,F64 SVdec);
I16 _8164_start_sa_arc_zu(I16 CardNo, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 StrVel,F64 MaxVel, F64 Tacc,F64 Tdec,F64 SVacc,F64 SVdec);

I16 _8164_set_sync_option(I16 AxisNo, I16 sync_stop_on, I16 cstop_output_on, I16 sync_option1, I16 sync_option2);
I16 _8164_mask_axis_stop_int(I16 AxisNo, I16 int_disable);
I16 _8164_set_axis_option(I16 AxisNo, I16 option);
I16 _8164_set_axis_stop_int(I16 AxisNo, I16 axis_stop_int);
I16 _8164_set_sync_stop_mode(I16 AxisNo, I16 stop_mode);

I16 _8164_mask_output_pulse(I16 AxisNo,I16 Mask);
I16 _8164_set_sync_signal_source(I16 AxisNo, I16 sync_axis);
I16 _8164_set_sync_signal_mode(I16 AxisNo, I16 mode);

I16 _8164_set_auto_rdp(I16 CardNo,I16 on_off);

I16 _8164_set_rotary_counter(I16 AxisNo, I16 reset_src);

//// added
I16 _8164_get_inter_status(I16 AxisNo, U32 *inter_sts) ;
I16 _8164_get_sts(I16 AxisNo, U32 *sts);
I16 _8164_set_compare_data(I16 AxisNo, I16 CompNo, F64 Pos);
I16 _8164_set_compare_mode(I16 AxisNo, I16 CompNo, I16 CmpSrc, I16 CmpMethod, I16 CmpAction);
///did not have 
/// set auto mode
/// build function
/// build table



#ifdef __cplusplus
}
#endif

#endif
