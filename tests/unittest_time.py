#!/usr/bin/python
# -*- coding: utf-8; mode: python -*-

import sys
import operator
from hwt_proxy import FPGA_hwtClient
from arm_casting_ieee754 import *
from unittest import TestCase


_time_valid = 0
_time_value = 0

class TimeTestCase(TestCase):
    def __init__(self, *args, **kwargs):
      super(TimeTestCase, self).__init__(*args, **kwargs)
      self._time_hw_addr = 0x41000000
      self._inputWords = 0x0001
      self._outputWords = 0x0001
      self._enableCycles = 0x00001000


    def _unittest_TimeReset(self):
      self._inputWords = 0x0001
      self._outputWords = 0x0001
      self._time_hw_addr = 0x41000000
      self._enableCycles = 0x00001000

      din = []
      din.extend(int_to_byte(0x00010100))
      din.extend(int_to_byte(0x00000000))

      testCli = FPGA_hwtClient()
      testCli.arguments(self._time_hw_addr, din)
      testCli.main([None])
      dout = testCli.result()
      idout = charSeq_to_intSeq(dout)

      head1 = idout[0]

      del testCli
      del idout


    def CONFIGURE_UNITTEST_TIME_HW_ADDR(self, addr):
      self._time_hw_addr = addr

    def CONFIGURE_UNITTEST_TIME_ENABLE_CYCLES(self, n):
      self._enableCycles = n
      
    def CONFIGURE_UNITTEST_TIME_INPUT_32BIT_WORDS(self, n):
      self._inputWords = n
    
    def CONFIGURE_UNITTEST_TIME_OUTPUT_32BIT_WORDS(self, n):
      self._outputWords = n

    def UNITTEST_TIME_RESET(self):
        self._unittest_TimeReset()

    def UNITTEST_TIME_START(self):
      global _time_value
      global _time_valid
      _time_value = 0
      _time_valid = 0
      din = []
      din.extend(int_to_byte(0x00010204))
      din.extend(int_to_byte(0x00000001))
      din.extend(int_to_byte((self._inputWords << 16) | self._outputWords))

      testCli = FPGA_hwtClient()
      testCli.arguments(self._time_hw_addr, din)
      testCli.main([None])
      dout = testCli.result()
      idout = charSeq_to_intSeq(dout)

      head1 = idout[0]

      del testCli
      del idout

    def UNITTEST_TIME_CONFIGURE(self):
      global _time_value
      global _time_valid
      _time_value = 0
      _time_valid = 0
      din = []
      din.extend(int_to_byte(0x00010204))
      din.extend(int_to_byte(0x00000002))
      din.extend(int_to_byte(self._enableCycles))
      din.extend(int_to_byte((self._inputWords << 16) | self._outputWords))

      testCli = FPGA_hwtClient()
      testCli.arguments(self._time_hw_addr, din)
      testCli.main([None])
      dout = testCli.result()
      idout = charSeq_to_intSeq(dout)

      head1 = idout[0]

      del testCli
      del idout

    
    def unittest_TimeGetTime(self):
      global _time_valid
      global _time_value
      if _time_valid == 1:
        return _time_value

      din = []
      din.extend(int_to_byte(0x00010300))
      din.extend(int_to_byte(0x00020000))
    
      testCli = FPGA_hwtClient()
      testCli.arguments(self._time_hw_addr, din)
      testCli.main([None])
      dout = testCli.result()
      idout = charSeq_to_intSeq(dout)

      head1 = idout[0]
      head2 = idout[1]
      time = idout[2]

      del testCli
      del idout

      self._unittest_TimeReset()
      _time_valid = 1
      _time_value = time

      return time


    def assertGeneral(self, func, expected):
      timeExecution = int(str(self.unittest_TimeGetTime()),16)
      evaluation = func(timeExecution, expected, msg=("TIME FAIL!!!"))


    def assertTimeEQ(self, expected):
      self.assertGeneral(self.assertEqual, expected)

    def assertTimeGT(self, expected):
      self.assertGeneral(self.assertGreater, expected)

    def assertTimeLT(self, expected):
      self.assertGeneral(self.assertLess, expected)

    def assertTimeGE(self, expected):
      self.assertGeneral(self.assertGreaterEqual, expected)

    def assertTimeLE(self, expected):
      self.assertGeneral(self.assertLessEqual, expected)


