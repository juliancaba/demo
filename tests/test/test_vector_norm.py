#!/usr/bin/python
# -*- coding: utf-8; mode: python -*-



import unittest
from unittest_time import TimeTestCase

from vector_norm import scale2, mult_hist_scale, sum_hist_pow


class TestL2Norm(TimeTestCase):

    def test_scale2(self):
        self.UNITTEST_TIME_RESET()
        self.CONFIGURE_UNITTEST_TIME_HW_ADDR(0x41000000)
        self.CONFIGURE_UNITTEST_TIME_INPUT_32BIT_WORDS(3)
        self.CONFIGURE_UNITTEST_TIME_OUTPUT_32BIT_WORDS(1)
        self.CONFIGURE_UNITTEST_TIME_ENABLE_CYCLES(2000000)

        self.UNITTEST_TIME_CONFIGURE();
        self.assertEqual(0.21739131212234497, scale2(19.0))
        self.assertTimeLT(40)
        self.assertTimeGT(35)
        

    def test_sum_hist_pow(self):
        din = []
        for i in range(0,16):
            din.append(float(i))
            
        self.UNITTEST_TIME_RESET()
        self.CONFIGURE_UNITTEST_TIME_HW_ADDR(0x41000000)
        self.CONFIGURE_UNITTEST_TIME_INPUT_32BIT_WORDS(18)
        self.CONFIGURE_UNITTEST_TIME_OUTPUT_32BIT_WORDS(1)
        self.CONFIGURE_UNITTEST_TIME_ENABLE_CYCLES(2000000)

        self.UNITTEST_TIME_CONFIGURE();
        self.assertEqual(1240.0, sum_hist_pow(din))
        self.assertTimeGT(50)

    def test_mult_hist_scale(self):
        din = []
        dout = []
        ref = []
        for i in range(0,16):
            din.append(float(i))
            ref.append(float(i)*0.1)

        self.UNITTEST_TIME_RESET();
        self.CONFIGURE_UNITTEST_TIME_HW_ADDR(0x41000000)
        self.CONFIGURE_UNITTEST_TIME_INPUT_32BIT_WORDS(18)
        self.CONFIGURE_UNITTEST_TIME_OUTPUT_32BIT_WORDS(1)
        self.CONFIGURE_UNITTEST_TIME_ENABLE_CYCLES(2000000)

        self.UNITTEST_TIME_CONFIGURE();
        mult_hist_scale(din, 0.1, dout)
        
        self.assertTimeLT(350)
        self.assertTimeGT(200)
        
        for o,r in zip(dout,ref):
            self.assertEqual(r,o)

# if __name__ == '__main__':
#     unittest.main()
    
