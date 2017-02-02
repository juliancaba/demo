#CC = arm-xilinx-linux-gnueabi-gcc
#CC = /opt/Xilinx/SDK/2015.4/gnu/arm/lin/arm-xilinx-linux-gnueabi/bin/gcc

UNITY_ROOT=/opt/utFrameworks/Unity

VERSION = POSIX

CC = g++
CFLAGS = -g

INC_DIRS +=-I.
INC_DIRS +=-I $(UNITY_ROOT)/src

PRJ=testNorm

RUNNER=$(UNITY_ROOT)/auto/generate_test_runner.rb

TEST_SUITE=ut_vector_norm
TEST_FILES = $(UNITY_ROOT)/src/unity.c
TEST_FILES += $(TEST_SUITE).c 
TEST_FILES += $(TEST_SUITE)_Runner.c

SRCS = vector_norm.cc


ALL_SRCS = ${TEST_FILES} $(SRCS)



all: runner ${TEST_SUITE} run


runner:
	ruby $(RUNNER) ${TEST_SUITE}.c ${TEST_SUITE}_Runner.c

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIRS)  -D $(VERSION) -c $^

${TEST_SUITE}: $(ALL_SRCS)
	${CC} $(CFLAGS) $(INC_DIRS) $^ -D $(VERSION) -o $@

run:
	./${TEST_SUITE}


clean:
	$(RM) -rf ${BUILD_DIR} *~ ${TEST_SUITE} ${TEST_SUITE}_Runner.c *.o

.PHONY: clean run verbose runner
