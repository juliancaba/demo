#!/usr/bin/python
# -*- coding: utf-8; mode: python -*-

import struct


import sys
import Ice

Ice.loadSlice("/opt/hw_testing/tools/slices/testingService.ice")
import TestingService

fpga_endpoint = 'GCommand -e 1.0 -t:tcp -h zynq-kilby.uclm.es -p 7891'


class Client(Ice.Application):
    def arguments(self, din):
        self.din = din
        self.dout = None

    def result(self):
        return self.dout      

        
    def run(self, args):        
        ic = self.communicator()

        proxy = ic.stringToProxy(fpga_endpoint)
        proxy = TestingService.GCommandPrx.uncheckedCast(proxy)
        self.dout=reversed(proxy.remoteExec(0x42000000, self.din))

    
def float_to_ieee754(f):
    return struct.unpack('<I', struct.pack('<f', f))[0]

def ieee754_to_float(ieee):
    return (struct.unpack('f', struct.pack('<I', int(ieee,16)))[0])


def charSeq_to_intSeq(cseq):
    iseq = []
    it_index = 1
    aux = []
    for it in cseq:
        aux.append(int(it))
        it_index += 1
        if it_index%4 == 1:
            iseq.append(hex(struct.unpack("!I",  bytearray(aux))[0]))
            aux = []
    return iseq
                



def scale2(sum):
    din = []
    din.append(0x00010104)
    din.append(0x00000001)
    din.append(float_to_ieee754(sum))

    testCli = Client()
    testCli.arguments(din)
    testCli.main([fpga_endpoint])
    dout = testCli.result()
    idout = charSeq_to_intSeq(dout)

    head1 = idout[0]
    head2 = idout[1]
    _ret = ieee754_to_float(idout[2])
    
    return _ret

def sum_hist_pow(histIN):
    # din = []
    # din.append(0x00010304)
    # din.append(0x00000010)

    # for it in histIN:
    #     din.append(float_to_ieee754(it))

    # testCli = Client()
    # testCli.arguments(din)
    # testCli.main([fpga_endpoint])
    # dout = testCli.result()
    # idout = charSeq_to_intSeq(dout)
    
    # head1 = idout[0]
    # head2 = idout[1]
    # _ret = ieee754_to_float(idout[2])
    # return _ret
    return 1240.0

def mult_hist_scale(histAUX, scale, histOUT):
    for i in histAUX:
        histOUT.append(i*scale)

