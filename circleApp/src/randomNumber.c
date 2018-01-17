/*
 * randomNumber.c
 *
 *	taken from https://github.com/mdavidsaver/epics-doc/blob/master/code-listings/prngApp/src/devprng.c
 *
 *  Created on: Jan 16, 2018
 *      Author: dale
 */

#include <stdlib.h>
#include <dbAccess.h>
#include <devSup.h>
#include <recGbl.h>
#include <alarm.h>
#include <math.h>

#include <aiRecord.h>

#include <epicsExport.h>

struct prngState {
  unsigned int seed;
};

static long init_record(aiRecord *prec)
{
  struct prngState* priv;
  unsigned long start;

  priv=malloc(sizeof(struct prngState));
  if(!priv){
    recGblRecordError(S_db_noMemory, (void*)prec,
      "devAoTimebase failed to allocate private struct");
    return S_db_noMemory;
  }

  recGblInitConstantLink(&prec->inp,DBF_ULONG,&start);

  priv->seed=start;
  prec->dpvt=priv;

  return 0;
}

static long read_ai(aiRecord *prec)
{
  struct prngState* priv=prec->dpvt;
  if(!priv) {
    (void)recGblSetSevr(prec, COMM_ALARM, INVALID_ALARM);
    return 0;
  }

  float r = rand_r(&priv->seed)*1.0;
  float rMax = RAND_MAX*1.0;
  double x = (double)random() / RAND_MAX,
           y = (double)random() / RAND_MAX,
           z = sqrt(-2 * log(x)) * cos(2 * M_PI * y);

  prec->val=z;

  return 2;
}

struct {
  long num;
  DEVSUPFUN  report;
  DEVSUPFUN  init;
  DEVSUPFUN  init_record;
  DEVSUPFUN  get_ioint_info;
  DEVSUPFUN  read_ai;
  DEVSUPFUN  special_linconv;
} randomAi = {
  6, /* space for 6 functions */
  NULL,
  NULL,
  init_record,
  NULL,
  read_ai,
  NULL
};
epicsExportAddress(dset,randomAi);
