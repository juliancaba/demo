#include "unity.h"

#include "vector_norm.h"


float input[HIST_SIZE];


void setUp(void)
{
  for(int i=0; i!= HIST_SIZE; i++) 
    input[i] = i; 
}

void tearDown(void)
{
}


void
test_sum_hist()
{
  TEST_ASSERT_EQUAL_FLOAT(120.0, sum_hist(input));
}

void
test_sum_hist_pow()
{
  TEST_ASSERT_EQUAL_FLOAT(1240.0, sum_hist_pow(input));
}


void
test_scale1()
{
  TEST_ASSERT_EQUAL_FLOAT(0.00833326, scale1(120.0));
}


void
test_scale1_sqrt()
{
  TEST_ASSERT_EQUAL_FLOAT(0.0283973, scale1_sqrt(1240.0));
}


void
test_scale2()
{
  TEST_ASSERT_EQUAL_FLOAT(0.5, scale2(0.16));
  TEST_ASSERT_EQUAL_FLOAT(0.217391, scale2(9.0));
}


void
test_sum_min_hist_scale()
{
  TEST_ASSERT_EQUAL_FLOAT(0.57, sum_min_hist_scale(input, 0.1));
}


void
test_mult_hist_scale()
{
  float ref[HIST_SIZE];
  for(char i=0; i!=HIST_SIZE; i++)
    ref[i] = input[i]*0.1;

  float out[HIST_SIZE];
  mult_hist_scale(input, 0.1, out);

  for(char i = 0; i != HIST_SIZE; i++)
    TEST_ASSERT_EQUAL_FLOAT(ref[i], out[i]);
}


void
test_l1norm()
{
  const float ref_l1norm[HIST_SIZE]={0, 0.00833326, 0.0166665,
				     0.0249998, 0.0333331, 0.0416663,
				     0.0499996, 0.0583328, 0.0666661,
				     0.0749994, 0.0833326, 0.0916659,
				     0.0999992, 0.108332, 0.116666,
				     0.124999};

  float out[HIST_SIZE];

  l1norm(input, out);
  
  for(char i = 0; i != HIST_SIZE; i++)
    TEST_ASSERT_EQUAL_FLOAT(ref_l1norm[i], out[i]); 
}


void
test_l1sqrt()
{
  const float ref_l1sqrt[HIST_SIZE]={0, 0.0912788, 0.182558,
				     0.273836, 0.365115, 0.456394,
				     0.547673, 0.638951, 0.73023,
				     0.821509, 0.912788, 1.00407,
				     1.09535, 1.18662, 1.2779,
				     1.36918};
  float out[HIST_SIZE];

  l1sqrt(input, out);
  
  for(char i = 0; i != HIST_SIZE; i++)
    TEST_ASSERT_EQUAL_FLOAT(ref_l1sqrt[i], out[i]); 
}


void
test_l2norm()
{
  const float ref_l2norm[HIST_SIZE]={0, 0.0271638, 0.0543277,
				     0.0814915, 0.108655, 0.135819,
				     0.162983, 0.190147, 0.217311,
				     0.244475, 0.271638, 0.298802,
				     0.325966, 0.35313, 0.380294,
				     0.407458};
  float out[HIST_SIZE];

  l2norm(input, out);
  
  for(char i = 0; i != HIST_SIZE; i++)
    TEST_ASSERT_EQUAL_FLOAT(ref_l2norm[i], out[i]); 
}


void
test_l2hys()
{

  const float ref_l2hys[HIST_SIZE]={0, 0.0416868, 0.0833737,
				    0.125061, 0.166747, 0.208434,
				    0.250121, 0.291808, 0.306929,
				    0.306929, 0.306929, 0.306929,
				    0.306929, 0.306929, 0.306929,
				    0.306929};
  float out[HIST_SIZE];

  l2hys(input, out);
  
  for(char i = 0; i != HIST_SIZE; i++)
    TEST_ASSERT_EQUAL_FLOAT(ref_l2hys[i], out[i]); 
}
