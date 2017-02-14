#ifndef TOPTESTING_H
#define TOPTESTING_H

#include "header.h"

#include <hls_stream.h>


static struct headerStruct header_OBJ;

static hls::stream<unsigned int> bufferIN_OBJ;
static hls::stream<unsigned int> bufferOUT_OBJ;
static hls::stream<unsigned int> bufferRESP_OBJ;

void inputBuffer_OBJ(hls::stream<unsigned int> &src);
void outputBuffer_OBJ(hls::stream<unsigned int> &dst);
void forward_OBJ(short size);

void getRequestHead_OBJ();
void buildResponseHead_OBJ(hls::stream<unsigned int> &dst,
		       unsigned short objID, unsigned short size, 
		       unsigned char flags);
void
buildResponse_OBJ(unsigned short objID, unsigned short size,
		  unsigned char flags);

void topTesting(hls::stream<unsigned int> din, hls::stream<unsigned int> dout);
void manager_OBJ();

#endif
