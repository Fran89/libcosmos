int main()
{
  int packedrecords;
  int verbose = 0;
  char *msfile = "output.v0c";
  int32_t datasamples[] = {0,1,2,3,4,5,6,7,8,9,10};
  V0CRecord *v0cr;
  
  
  
  msr = msr3_init (NULL);
  /* Populate MS3Record values */
  strcpy (msr->sid, "XX_TEXT__B_H_E");
  msr->formatversion = 3;
  msr->reclen = 512;
  msr->encoding = DE_STEIM2;
  msr->starttime = ms_timestr2nstime ("2018-12-01T00:00:00.000000000");
  msr->samprate = 20.0;
  msr->datasamples = datasamples;  /* pointer to 32-bit integer data samples */
  msr->numsamples = 11;
  msr->sampletype = 'i';  /* declare data type to be 32-bit integers */
  /* Write all data in MS3Record to output file, using MSF_FLUSHDATA flag */
  packedrecords = msr3_writemseed (msr, msfile, 1, MSF_FLUSHDATA, verbose);
  ms_log (0, "Wrote %d records to %s\n", packedrecords, msfile);
  /* Disconnect datasamples pointer, otherwise msr3_free() will attempt to free() it */
  msr->datasamples = NULL;
  msr3_free (&msr);
}
