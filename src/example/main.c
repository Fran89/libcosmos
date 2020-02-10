#include <stdio.h>
#include "vXc.h"
int main()

{
  int verbose = 0;
  char *v0cfile = "output.v0c";
  int32_t datasamples[] = {0,1,2,3,4,5,6,7,8,9,
                       0,1,2,3,4,5,6,7,8,9,
                       0,1,2,3,4,5,6,7,8,9,
                       0,1,2,3,4,5,6,7,8,9,
                       0,1,2,3,4,5,6,7,8,9,
                       0,1,2,3,4,5,6,7,8,9,
                       0,1,2,3,4,5,6,7,8,9,
                       0,1,2,3,4,5,6,7,8,9,
                       0,1,2,3,4,5,6,7,8,9,
                       0,1,2,3,4
                      };
  VXCRecord *v0cr;

  v0cr = vXc_init(NULL);

  v0cr->datasamples = datasamples;
  v0cr->datasize = sizeof(datasamples)/sizeof(datasamples[0]);

  // Create v0c file with origin "Test.evt" **Req**
  v0c_create(v0cr, "Test.evt");

  /* Populate v0crRecord values */
  // Set Eq & Origin name **Req**
  vXc_setEqName(v0cr, "Northridge Earthquake");
  // Set Eq & Origin & Record time (if different, must change values manually, see header) **Req**
  vXc_setEqInfo(v0cr, 1994, 01, 17, 12, 30, 55.400, 2, "UTC");
  // Set Eq & Origin info **Req**
  vXc_setEqLocI(v0cr, 34.215, -118.531,28, "(SCSN)",  "ML=6.6");
  // Set Eq & Origin Mag **Opt**
  vXc_setEqMgAz(v0cr, 1, 1, 1, 6.6, 6.7, 6.7, -999.0, -999.0);

  // Set Station Name **Req**
  vXc_setStaInf(v0cr, 01, 24236, "CE", "J236", "CDMG", 10, "Los Angeles - Hollywood Storage Bldg");
  // Set Station Info **Req**
  vXc_setStaLoc(v0cr, 24.09, -118.3390, -999.0, -999.0, 1, "Shallow Alluvium over Granite");

  // Set Recorder & Sensor Info **Req**
  vXc_setRecInf(v0cr, "SSA-2 s/n 908",  3, 12, "FBA-11 s/n 123456");
  // Set Record ID **Req**
  vXc_setRecoID(v0cr, "24236-F0900-94017.04");
  vXc_setRecTim(v0cr, 1994, 01, 17, 12, 30, 52.900, 2);
  vXc_setChanIn(v0cr, 1, 360, 4, "8th Floor : Center");

  // Set Timing Info **Req**
  vXc_setTiming(v0cr, 10 , 1000);

  vXc_print(v0cr);


  //msr->datasamples = datasamples;  /* pointer to 32-bit integer data samples */
  //msr->numsamples = 11;
  //msr->sampletype = 'i';  /* declare data type to be 32-bit integers */
  ///* Write all data in MS3Record to output file, using MSF_FLUSHDATA flag */
  //packedrecords = msr3_writemseed (msr, msfile, 1, MSF_FLUSHDATA, verbose);
  //ms_log (0, "Wrote %d records to %s\n", packedrecords, msfile);
  ///* Disconnect datasamples pointer, otherwise msr3_free() will attempt to free() it */
  //msr->datasamples = NULL;
  //msr3_free (&msr);
}
