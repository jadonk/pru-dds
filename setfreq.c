#include <stdio.h>
#include <stdlib.h>
#include <prussdrv.h>
#include <pruss_intc_mapping.h>
#include "util.h"

int main (int argc, char **argv)
{
  double freqf;
  int ret;

  if (argc != 2) {
    printf("Usage %s <frequency>\n", argv[0]);
    return 0;
    }

  freqf = atof(argv[1]);

  pruinit();

  ret = setfreq(freqf);

  if (ret) {
    printf("Error setting freq %f\n", freqf);
    return(0);
    }

  // Reset PRU instruction pointer to get it to reload skiplen from DDR
  // perhaps there's a better way, but this works for me
  // prussdrv_pru_reset() blows away whatever code is in the PRU, and we don't want that.

  prussdrv_pru_disable ( 0 );
  prussdrv_pru_enable ( 0 );

  return(0);
}
