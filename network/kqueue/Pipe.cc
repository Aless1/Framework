#include "Pipe.h"

void Pipe::send(void * data, int len) {
   
}

void Pipe::close() {
   ::close(sock);
   delete this;
}