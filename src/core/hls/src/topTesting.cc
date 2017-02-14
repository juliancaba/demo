#include "topTesting.h"
#include "wrapperOBJ.h"


// union typeHead{
//   unsigned int words32;
//   unsigned char words8[4];  
// }byteHeader[2];



void
inputBuffer_OBJ(hls::stream<unsigned int> &src)
{
  unsigned int aux;
  aux = src.read();
  bufferIN_OBJ.write(aux);
}


void
outputBuffer_OBJ(hls::stream<unsigned int> &dst)
{
  unsigned int aux;
  aux = bufferOUT_OBJ.read();
  dst.write(aux);
}


void
forward_OBJ(short size)
{
  short it=0;
  while(it != size){
    bufferIN_OBJ.read();
    it += 1;
  }
}


void
buildResponseHead_OBJ(hls::stream<unsigned int> &dst,
		  unsigned short objID, unsigned short size,
		  unsigned char flags)
{
  int words32;

  words32 = (header_OBJ.cb<<16) | (header_OBJ.methodID<<8) | flags;
  dst.write(words32);
  if(flags & FLAG_HAS_PAYLOAD){
    words32 = (objID<<16) | size;
    dst.write(words32);
  }
}


void
buildResponse_OBJ(unsigned short objID, unsigned short size,
	      unsigned char flags)
{
  if (!bufferRESP_OBJ.empty()){
    buildResponseHead_OBJ(bufferOUT_OBJ, objID, size, flags);
    while (!bufferRESP_OBJ.empty())
      bufferOUT_OBJ.write(bufferRESP_OBJ.read());
  }
}


void
getRequestHead_OBJ()
{
  int words32[2];

  for(int it=0; it != 2; it++)
    words32[it] = bufferIN_OBJ.read();
  //byteHeader[it].words32 = bufferIN.read();

  header_OBJ.nodeID = (words32[0] >> 24) & 0xFF;
  header_OBJ.objectID = (words32[0] >> 16) & 0xFF;
  header_OBJ.methodID = (words32[0] >> 8) & 0xFF;
  header_OBJ.flags = words32[0] & 0xFF;
  header_OBJ.cb = (words32[1] >> 16) & 0xFFFF;
  header_OBJ.size = words32[1] & 0xFFFF;

  /*
  header.nodeID = byteHeader[0].words8[3];
  header.objectID = byteHeader[0].words8[2];
  header.methodID_flags = to_short(byteHeader[0].words8[1], byteHeader[0].words8[0]);
  header.cb = to_short(byteHeader[1].words8[3], byteHeader[1].words8[2]);
  header.size = to_short(byteHeader[1].words8[1], byteHeader[1].words8[0]);
  */
}


void
manager_OBJ()
{
  getRequestHead_OBJ();

  if (ID_OBJ == header_OBJ.objectID)
    if (ID_OBJ_scale2 == header_OBJ.methodID){
      testing_OBJ_scale2(bufferIN_OBJ, bufferRESP_OBJ);
      buildResponse_OBJ(ID_OBJ, sizeof(ret_OBJ_scale2)/OBJ_BUS_WIDTH_BYTES,
		    FLAG_HAS_PAYLOAD|FLAG_RESPONSE|FLAG_OK);
    }
    // else if (ID_OBJ_l2norm == header_OBJ.methodID){
    //   testing_OBJ_l2norm(bufferIN_OBJ, bufferRESP_OBJ);
    //   buildResponse_OBJ(ID_OBJ, sizeof(ret_OBJ_l2norm)/OBJ_BUS_WIDTH_BYTES,
    // 			FLAG_HAS_PAYLOAD|FLAG_RESPONSE|FLAG_OK);
    // }
    else if (ID_OBJ_sum_hist_pow == header_OBJ.methodID){
      testing_OBJ_sum_hist_pow(bufferIN_OBJ, bufferRESP_OBJ);
      buildResponse_OBJ(ID_OBJ, sizeof(ret_OBJ_sum_hist_pow)/OBJ_BUS_WIDTH_BYTES,
			FLAG_HAS_PAYLOAD|FLAG_RESPONSE|FLAG_OK);
    }
    else if (ID_OBJ_mult_hist_scale == header_OBJ.methodID){
      testing_OBJ_mult_hist_scale(bufferIN_OBJ, bufferRESP_OBJ);
      buildResponse_OBJ(ID_OBJ, sizeof(ret_OBJ_mult_hist_scale)/OBJ_BUS_WIDTH_BYTES,
			FLAG_HAS_PAYLOAD|FLAG_RESPONSE|FLAG_OK);
    }
    else{
      forward_OBJ(header_OBJ.size);
      buildResponseHead_OBJ(bufferOUT_OBJ, ID_OBJ, 0, 
			    FLAG_RESPONSE|FLAG_FAIL);
    }
  else{
    forward_OBJ(header_OBJ.size);
    buildResponseHead_OBJ(bufferOUT_OBJ, NULL_OBJ, 0,
			  FLAG_RESPONSE|FLAG_FAIL);
  }
}


void
topTesting(hls::stream<unsigned int> din, hls::stream<unsigned int> dout)
{
  inputBuffer_OBJ(din);
  manager_OBJ();
  outputBuffer_OBJ(dout);
}


