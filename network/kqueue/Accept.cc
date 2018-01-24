#include "Accept.h"

void Accept::close() {
   ::close(sock);
   delete this;
}

