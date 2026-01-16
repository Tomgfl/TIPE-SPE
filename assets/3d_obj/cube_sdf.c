#include "cube_sdf.h"

float SDF_cube(vector pts, vector c) { 
   vector C_1 = { 1.000000,1.000000,-1.000000 };
   vector C_2 = { 1.000000,-1.000000,-1.000000 };
   vector C_3 = { 1.000000,1.000000,1.000000 };
   vector C_4 = { 1.000000,-1.000000,1.000000 };
   vector C_5 = { -1.000000,1.000000,-1.000000 };
   vector C_6 = { -1.000000,-1.000000,-1.000000 };
   vector C_7 = { -1.000000,1.000000,1.000000 };
   vector C_8 = { -1.000000,-1.000000,1.000000 };
   float trig_0 = SDF_triangle(pts,C_5,C_3,C_1);
   float trig_1 = SDF_triangle(pts,C_3,C_8,C_4);
   float trig_2 = SDF_triangle(pts,C_7,C_6,C_8);
   float trig_3 = SDF_triangle(pts,C_2,C_8,C_6);
   float trig_4 = SDF_triangle(pts,C_1,C_4,C_2);
   float trig_5 = SDF_triangle(pts,C_5,C_2,C_6);
   float trig_6 = SDF_triangle(pts,C_5,C_7,C_3);
   float trig_7 = SDF_triangle(pts,C_3,C_7,C_8);
   float trig_8 = SDF_triangle(pts,C_7,C_5,C_6);
   float trig_9 = SDF_triangle(pts,C_2,C_4,C_8);
   float trig_10 = SDF_triangle(pts,C_1,C_3,C_4);
   float trig_11 = SDF_triangle(pts,C_5,C_1,C_2);
   int nb = 12;
   float all_sdf[12]; 
   all_sdf[0] = trig_0; 
   all_sdf[1] = trig_1; 
   all_sdf[2] = trig_2; 
   all_sdf[3] = trig_3; 
   all_sdf[4] = trig_4; 
   all_sdf[5] = trig_5; 
   all_sdf[6] = trig_6; 
   all_sdf[7] = trig_7; 
   all_sdf[8] = trig_8; 
   all_sdf[9] = trig_9; 
   all_sdf[10] = trig_10; 
   all_sdf[11] = trig_11; 
   return min_lst(all_sdf,12);
}