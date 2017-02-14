#!/bin/bash --
# -*- coding: utf-8; mode: shell-script; tab-width: 4 -*-

HW_SOURCES=src/hw_src
TEST_DIR=tests

echo "[INFO] Setup testing environment"
source /opt/Xilinx/Vivado/2015.4/settings64.sh
cp -r /opt/hw_testing/platform/ .
mkdir logs
mkdir output

echo "[INFO] Getting HW sources"
cd src
make >> logs/hls_synth.log
cd -

echo "[INFO] Synthesis design - Partial bitstream"
#python3 /opt/hw_testing/tools/hwt_genTCLDesignConfiguration.py $HW_SOURCES platform
cd platform
#make buildPartial >> ../logs/synth.log
cd -

/opt/hw_testing/tools/write_factory_bitstreams platform/Bitstreams/reference_pblock_topTesting_dpr_partial.bit output/partial.bit

echo "[INFO] Send partial bitstream to FPGA"
#python3 /opt/hw_testing/tools/remoteDPR.py output/partial.bit

echo "[INFO] Running tests"
cd $TEST_DIR
make tests
cd -
