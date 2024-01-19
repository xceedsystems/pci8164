#ifndef _8164mcod_H

#define _8164mcod_H

#include "motion.h"
#include "pci_8164.h"
#include "pcl6045.h"

I16 _one_axis_move(I16 AxisNo, F64 Dist, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec,I16 C_Type,I16 M_Type,F64 SVacc,F64 SVdec);
I16 _two_axes_move(I16 *Axis, F64 *DistA, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec,I16 C_Type,I16 M_Tpye,F64 SVacc,F64 SVdec,I16 P_Type);
I16 _constant_speed_arc(I16 *Axis, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 MaxVel, I16 M_Type, I16 P_Type);
I16 _three_axes_move(I16 *Axis, F64 *DistA, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec,I16 C_Type, I16 M_Type,F64 SVacc,F64 SVdec);
I16 _four_axes_move(I16 CardNo, F64 *DistA, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec,I16 C_Type, I16 M_Type,F64 SVacc,F64 SVdec,I16 ChipNo);
I16 _vary_speed_arc(I16 *Axis, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, I16 C_Type, I16 M_Type, F64 SVacc, F64 SVdec);
I16 _vary_speed_arc_u(I16 *Axis, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, I16 C_Type, I16 M_Type, F64 SVacc);
#endif

