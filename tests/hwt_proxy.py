#!/usr/bin/python
# -*- coding: utf-8; mode: python -*-


import Ice
from service_config import fpga_endpoint

Ice.loadSlice("/opt/hw_testing/tools/slices/testingService.ice")
import TestingService



class FPGA_hwtClient(Ice.Application):
    def arguments(self, addr, din):
        self.din = din
        self.addr = addr
        self.dout = None

    def result(self):
        return self.dout      

        
    def run(self, args):        
        ic = self.communicator()

        proxy = ic.stringToProxy(fpga_endpoint)
        proxy = TestingService.GCommandPrx.uncheckedCast(proxy)
        self.dout=proxy.remoteExec(self.addr, self.din)

