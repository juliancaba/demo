#!/usr/bin/python
# -*- coding: utf-8; mode: python -*-

from vector_norm import scale2, mult_hist_scale, sum_hist_pow
import unittest
import time

class TestL2Norm(unittest.TestCase):

    def test_scale2(self):
        self.assertEqual(0.21739131212234497, scale2(9.0))
        

    def test_sum_hist_pow(self):
        din = []
        for i in range(0,16):
            din.append(float(i))
        self.assertEqual(1242.0, sum_hist_pow(din))

    def test_mult_hist_scale(self):
        din = []
        dout = []
        ref = []
        for i in range(0,16):
            din.append(float(i))
            ref.append(float(i)*0.1)
        
        mult_hist_scale(din, 0.1, dout)

        for o,r in zip(dout,ref):
            self.assertEqual(r,o)

# if __name__ == '__main__':
#     unittest.main()
    
