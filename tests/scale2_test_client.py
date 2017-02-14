#!/usr/bin/python -u
# -*- mode: python; coding: utf-8 -*-

import sys
import Ice

Ice.loadSlice("/opt/hw_testing/tools/slices/testingService.ice")
import TestingService


class Client(Ice.Application):
    def run(self, args):
        if len(args) < 2:
            print ("USAGE: {} <proxy>".format(args[0]))
            return 1

        ic = self.communicator()

        proxy = ic.stringToProxy(args[1])
        proxy = TestingService.GCommandPrx.uncheckedCast(proxy)

        din=[]
        din.append(0x00010104)
        din.append(0x00000001)
        din.append(0x449b0000)
        print (din)
        dout = proxy.remoteExec(0x42000000, din)
        dout = reversed(dout)
        for it in dout:
            #print hex(it)
            print (hex(it))
            


if __name__ == '__main__':
    Client().main(sys.argv)
