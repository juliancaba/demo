// -*- coding: utf-8; mode: c++; tab-width: 4 -*-

#include "vector_norm.h"
#include <cmath>

#ifndef POSIX
#include "hls_math.h"
#endif


static float histAUX_1 [HIST_SIZE];
#ifdef POSIX
static float histAUX_2 [HIST_SIZE];
#endif



float
sum_hist_pow(float histIN[HIST_SIZE])
{
#pragma HLS STREAM variable=histAUX_1 dim=1
  float sum = 0.f;
  float inAUX;

  inAUX = histIN[0];
 loop1:for(int i = 0; i != HIST_SIZE; i++){
	sum += inAUX*inAUX;	  
	histAUX_1[i] = inAUX;
    if (i < HIST_SIZE-1)
      inAUX = histIN[i+1];
  }
  return sum;
}


float
scale2(float sum)
{
#pragma HLS STREAM variable=histAUX_1 dim=1
#ifndef POSIX
  return hls::recipf(sqrtf(sum)+1.6f);
#else
  return 1.f/(sqrtf(sum)+1.6f);
#endif
}



void
mult_hist_scale(float histAUX[HIST_SIZE], float scale, float histOUT[HIST_SIZE])
{
  //#pragma HLS STREAM variable=histAUX dim=1
  //#pragma HLS STREAM variable=histAUX_2 dim=1
#pragma HLS STREAM variable=histAUX_1 dim=1
 loop2:for(int i = 0; i != HIST_SIZE; i++)
    histOUT[i] = histAUX[i]*scale;
}


void
l2norm(float histIN[HIST_SIZE], float histOUT[HIST_SIZE])
{
#pragma HLS STREAM variable=histAUX_1 dim=1
  float scale = 0.f;
  float sum = 0.f;
  
  sum = sum_hist_pow(histIN);
  scale = scale2(sum);
  mult_hist_scale(histAUX_1, scale, histOUT);
}



#ifdef POSIX
float
sum_hist(float histIN[HIST_SIZE])
{
#pragma HLS STREAM variable=histAUX_1 dim=1
  float sum = 0.f;
  float inAUX;

  inAUX = histIN[0];
 loop1:for(int i = 0; i != HIST_SIZE; i++){
	sum += inAUX;	  
	histAUX_1[i] = inAUX;
    if (i < HIST_SIZE-1)
      inAUX = histIN[i+1];
  }
  return sum;
}



float
scale1(float sum)
{
#pragma HLS STREAM variable=histAUX_1 dim=1
#ifndef POSIX
  return hls::recipf(sum+1.e-3f);
#else
  return 1.f/(sum+1e-3f);
#endif
}


float
scale1_sqrt(float sum)
{
#pragma HLS STREAM variable=histAUX_2 dim=1
#pragma HLS STREAM variable=histAUX_1 dim=1
#ifndef POSIX
  return hls::recipf(sqrt(sum)+1.e-3f);
#else
  return 1.f/(sqrtf(sum)+1e-3f);
#endif
}


float
sum_min_hist_scale(float histAUX[HIST_SIZE], float scale)
{
  //#pragma HLS STREAM variable=histAUX dim=1
#pragma HLS STREAM variable=histAUX_2 dim=1
#pragma HLS STREAM variable=histAUX_1 dim=1
  float thres = 0.2f;
  float sum = 0.f;
  float inAUX;

 loop3:for(int i = 0; i != HIST_SIZE; i++){
	inAUX = fmin(histAUX[i]*scale, thres);
	histAUX_2[i] = inAUX;
	sum += inAUX*inAUX;
  }
   
  return sum;
}


void
l1norm(float histIN[HIST_SIZE], float histOUT[HIST_SIZE])
{
#pragma HLS STREAM variable=histAUX_1 dim=1
  float scale = 0.f;
  float sum = 0.f;

  sum = sum_hist(histIN);
  scale = scale1(sum);
  mult_hist_scale(histAUX_1, scale, histOUT);
}


void
l1sqrt(float histIN[HIST_SIZE], float histOUT[HIST_SIZE])
{
#pragma HLS STREAM variable=histAUX_1 dim=1
  float scale = 0.f;
  float sum = 0.f;

  sum = sum_hist(histIN);
  scale = scale1_sqrt(sum);
  mult_hist_scale(histAUX_1, scale, histOUT);
}


void
l2hys(float histIN[HIST_SIZE], float histOUT[HIST_SIZE])
{
#pragma HLS STREAM variable=histAUX_2 dim=1
#pragma HLS STREAM variable=histAUX_1 dim=1
  float scale = 0.f;
  float sum = 0.f;

  sum = sum_hist_pow(histIN);
  scale = scale2(sum);
  sum = sum_min_hist_scale(histAUX_1, scale);
  scale = scale1_sqrt(sum);
  mult_hist_scale(histAUX_2, scale, histOUT);  
}
#endif

