#!/usr/bin/python
# -*- coding: utf-8; mode: python -*-



import unittest
from rc_unittest_remote import RCUnittestTestCase

from vector_norm import scale2, mult_hist_scale, sum_hist_pow


class TestL2Norm(RCUnittestTestCase):

    def test_scale2(self):
        self.TEST_RESET()
        self.CONFIGURE_HW_ADDR(0x41000000)
        self.CONFIGURE_SKIP_INPUT(3)
        self.CONFIGURE_SKIP_OUTPUT(1)
        self.CONFIGURE_ENABLE_CYCLES(2000000)

        self.TEST_CONFIGURE();
        self.assertEqual(0.21739131212234497, scale2(9.0))
        self.assertTimeLT(40)
        self.assertTimeGT(20)
        

    def test_sum_hist_pow(self):
        din = []
        for i in range(0,16):
            din.append(float(i))
            
        self.TEST_RESET()
        self.CONFIGURE_HW_ADDR(0x41000000)
        self.CONFIGURE_SKIP_INPUT(18)
        self.CONFIGURE_SKIP_OUTPUT(1)
        self.CONFIGURE_ENABLE_CYCLES(2000000)

        self.TEST_CONFIGURE();
        self.assertEqual(1240.0, sum_hist_pow(din))
        self.assertTimeGT(20)

    def test_mult_hist_scale(self):
        din = []
        dout = []
        ref = []
        for i in range(0,16):
            din.append(float(i))
            ref.append(float(i)*0.1)

        self.TEST_RESET();
        self.CONFIGURE_HW_ADDR(0x41000000)
        self.CONFIGURE_SKIP_INPUT(18)
        self.CONFIGURE_SKIP_OUTPUT(1)
        self.CONFIGURE_ENABLE_CYCLES(2000000)

        self.TEST_CONFIGURE();
        mult_hist_scale(din, 0.1, dout)
        
        self.assertTimeLT(350)
        self.assertTimeGT(200)
        
        for o,r in zip(dout,ref):
            self.assertTrue(abs(r-o)<0.0001)

# if __name__ == '__main__':
#     unittest.main()
    
