#ifndef VECTOR_NORM_H
#define VECTOR_NORM_H

const static short HIST_SIZE=16;

float sum_hist_pow(float histIN[HIST_SIZE]);
float scale2(float sum);
void mult_hist_scale(float histAUX[HIST_SIZE], float scale, float histOUT[HIST_SIZE]);
void l2norm(float histIN[HIST_SIZE], float histOUT[HIST_SIZE]);


#ifdef POSIX
float sum_hist(float histIN[HIST_SIZE]);
float scale1(float sum);
float scale1_sqrt(float sum);
float sum_min_hist_scale(float histAUX[HIST_SIZE], float scale);

void l1norm(float histIN[HIST_SIZE], float histOUT[HIST_SIZE]);
void l1sqrt(float histIN[HIST_SIZE], float histOUT[HIST_SIZE]);
void l2hys(float histIN[HIST_SIZE], float histOUT[HIST_SIZE]);
#endif

#endif
