// Library for writing VXc files
#include "vXc.h"

VXCRecord* vXc_init(VXCRecord* vXc) {
	
  void   *datasamples = NULL;
  
  if (!vXc)
  {
    vXc = (VXCRecord*) malloc (sizeof (VXCRecord));
  }
  else
  {
    datasamples = vXc->datasamples;
  }

  if (vXc == NULL)
  {
    printf ("Cannot allocate memory\n");
    return NULL;
  }

  memset (vXc, 0, sizeof (VXCRecord));
  
  for (int i = 0; i < 100; i++){
    vXc->relvalues[i] = -999;
    vXc->intvalues[i] = -999.0;
  }
  
  vXc->IntHeader.numValuesIntHd = 100;
  vXc->IntHeader.numLineIntHd = 10;
  strcpy(vXc->IntHeader.formatInt, "10I8");

  vXc->RealHeader.numValuesRealHd = 90;
  vXc->RealHeader.numLineRealHd = 15;
  strcpy(vXc->RealHeader.formatReal, "6F13.6");

  vXc->CommentHeader.numComments = 2;
  
  datasamples = vXc->datasamples;

  return vXc;
} 

void v0c_create   (VXCRecord* vXc, char* Agency){
  // Set RAW
  strcpy (vXc->TextHeader.dataType,  "Raw acceleration counts");
  strcpy (vXc->DataHeader.dataParam, "raw accel.  pts");
  strcpy (vXc->DataEnd.ChanPhy, "Raw acceleration counts");
  strcpy (vXc->DataHeader.dataUnits, "counts");
  strcpy (vXc->DataHeader.dataFormat, "10I8");

  vXc->intvalues[0] = 0;
  vXc->intvalues[1] = 1;
  vXc->intvalues[2] = 50;
  vXc->DataHeader.dataCode = 50;

  // Set Version
  vXc->TextHeader.verMajor = 1;
  vXc->TextHeader.verMinor = 20;
  vXc->intvalues[3] = 120;
  vXc->intvalues[4] = 4;
  vXc->TextHeader.textHeaderSz = 13;
  strcpy(vXc->TextHeader.agency, Agency);
}

void vXc_setEqName(VXCRecord* vXc,char* name){
  strcpy(vXc->TextHeader.eqName, name);
}

void vXc_setEqInfo(VXCRecord* vXc, int yr, int mo, int day, int hr, int min, double sec, int tq, char* Tz){
  vXc->TextHeader.eqYr = yr;
  vXc->TextHeader.eqMo = mo;
  vXc->TextHeader.eqDy = day;
  vXc->TextHeader.eqHr = hr;
  vXc->TextHeader.eqMi = min;
  vXc->TextHeader.eqSe = sec;
  vXc->TextHeader.eqOrYr = yr;
  vXc->TextHeader.eqOrMo = mo;
  vXc->TextHeader.eqOrDy = day;
  vXc->TextHeader.eqOrHr = hr;
  vXc->TextHeader.eqOrMi = min;
  vXc->TextHeader.eqOrSe = sec;
  vXc->TextHeader.recYr = yr;
  vXc->TextHeader.recMo = mo;
  vXc->TextHeader.recDy = day;
  vXc->TextHeader.recHr = hr;
  vXc->TextHeader.recMi = min;
  vXc->TextHeader.recSe = sec;
  vXc->TextHeader.recQl = tq;
  strcpy(vXc->TextHeader.eqTz, Tz);
}

void vXc_setEqLocI(VXCRecord* vXc, double lat, double lon, double depth, char* Agency, char* Magnitude){
  vXc->TextHeader.eqLat = lat;
  vXc->relvalues[9] = lat;
  vXc->TextHeader.eqLon = lon;
  vXc->relvalues[10] = lon;
  vXc->TextHeader.eqDep = depth;
  vXc->relvalues[11] = depth;
  strcpy(vXc->TextHeader.eqSrc, Agency);
  strcpy(vXc->TextHeader.eqOrNote, Agency);
  strcpy(vXc->TextHeader.eqMag, Magnitude);
}

void  vXc_setEqMgAz(VXCRecord* vXc, int m, int mL, int mS, double mag, double magLoc, double magSur, double dist, double az){
  vXc->intvalues[25] = m;
  vXc->intvalues[26] = mL;
  vXc->intvalues[27] = mS;
  vXc->relvalues[12] = mag;
  vXc->relvalues[13] = magLoc;
  vXc->relvalues[14] = magSur;
  vXc->relvalues[16] = dist;
  vXc->relvalues[17] = az;
}

void vXc_setStaInf(VXCRecord* vXc, int net, int sta, char* netCode, char* code, char* netAbr, int type, char* staDesc){
   vXc->TextHeader.netNo = net;
   vXc->intvalues[10] = net;
   vXc->intvalues[11] = net;
   vXc->intvalues[13] = net;
   vXc->intvalues[24] = net;
   vXc->TextHeader.staNo = sta;
   vXc->intvalues[7] = sta;
   strcpy(vXc->TextHeader.staNet, netCode);
   strcpy(vXc->TextHeader.staCod, code);
   strcpy(vXc->TextHeader.netAbr, netAbr);
   vXc->intvalues[18] = type;
   strcpy(vXc->TextHeader.staNam, staDesc);
}

void vXc_setStaLoc(VXCRecord* vXc, double lat, double lon, double elev, double vs30, int geology, char* SiteDesc){
  vXc->TextHeader.staLat = lat;
  vXc->TextHeader.staLon = lon;
  vXc->relvalues[0] = lat;
  vXc->relvalues[1] = lon;
  vXc->relvalues[2] = elev;
  vXc->intvalues[15] = 1;
  vXc->relvalues[3] = vs30;
  vXc->intvalues[17] = geology;
  strcpy(vXc->TextHeader.staGeo, SiteDesc);
}

void vXc_setRecInf(VXCRecord* vXc, char* recorder,  int numrec, int numchan, char* sensor){
  strcpy(vXc->TextHeader.recoDes, recorder);
  vXc->TextHeader.numRChan = numrec;
  vXc->intvalues[21] = numrec;
  vXc->TextHeader.numSChan = numchan;
  vXc->intvalues[22] = numchan;
  strcpy(vXc->TextHeader.sensDes, sensor);
}

void vXc_setRecoID(VXCRecord* vXc, char* ID){
  strcpy(vXc->TextHeader.recID, ID);
}

void vXc_setRecTim(VXCRecord* vXc, int yr, int mo, int day, int hr, int min, double sec, int tq){
  vXc->TextHeader.recYr = yr;
  vXc->TextHeader.recMo = mo;
  vXc->TextHeader.recDy = day;
  vXc->TextHeader.recHr = hr;
  vXc->TextHeader.recMi = min;
  vXc->TextHeader.recSe = sec;
  vXc->TextHeader.recQl = tq;
}

char* vXc_buildTXHD(VXCRecord* vXc){
  
  char *TXHD =  (char*)malloc((100*13) * sizeof(char));
  
  
  // Build the text Header
  char *line1 = (char*)malloc(100 * sizeof(char));
  char *line2 = (char*)malloc(100 * sizeof(char));
  
  // Line 1
  sprintf(line1,
    "%-26s (Format v%02i.%02i with %2i text lines) %s\n",
    vXc->TextHeader.dataType,
    vXc->TextHeader.verMajor,
    vXc->TextHeader.verMinor,
    vXc->TextHeader.textHeaderSz,
    vXc->TextHeader.agency
  );
  strcat(TXHD, line1);
  
  // Line 2
  sprintf(line2,
    "%-40s Time: %i/%i/%i, %02i:%02i:%.3f   %s \n",
   vXc->TextHeader.eqName,
   vXc->TextHeader.eqYr,
   vXc->TextHeader.eqMo,
   vXc->TextHeader.eqDy,
   vXc->TextHeader.eqHr,
   vXc->TextHeader.eqMi,
   vXc->TextHeader.eqSe,
   vXc->TextHeader.eqTz
  );
  strcat(TXHD, line2);
  
  // Line 3
  sprintf(line1,
    "Hypocenter: %-2.3f    %-7.3f  H= %3.fkm%7s  %s\n",
    vXc->TextHeader.eqLat,
    vXc->TextHeader.eqLon,
    vXc->TextHeader.eqDep,
    vXc->TextHeader.eqSrc,
    vXc->TextHeader.eqMag
  );
  strcat(TXHD, line1);
  
  // Line 4
  sprintf(line2,
   "Origin: %02i/%02i/%4i,  %02i:%02i:%.3f   UTC %s\n",
   vXc->TextHeader.eqOrMo,
   vXc->TextHeader.eqOrDy,
   vXc->TextHeader.eqOrYr,
   vXc->TextHeader.eqOrHr,
   vXc->TextHeader.eqOrMi,
   vXc->TextHeader.eqOrSe,
   vXc->TextHeader.eqOrNote
  );
  strcat(TXHD, line2);
  
  // Line 5
  sprintf(line1,
   "Statn No: %02i- %5i Code:%s-%s %s %s\n",
   vXc->TextHeader.netNo,
   vXc->TextHeader.staNo,
   vXc->TextHeader.staNet,
   vXc->TextHeader.staCod,
   vXc->TextHeader.netAbr,
   vXc->TextHeader.staNam
  );
  strcat(TXHD, line1);
  
  // Line 6
  sprintf(line2,
   "Coords: %-2.3f  %-7.3f   Site geology: %s\n",
   vXc->TextHeader.staLat,
   vXc->TextHeader.staLon,
   vXc->TextHeader.staGeo
  );
  strcat(TXHD, line2);
  
  // Line 7
  sprintf(line1,
   "Recorder: %s (%2i Chns of %2i at Sta) Sensor:%s\n",
    vXc->TextHeader.recoDes,
    vXc->TextHeader.numRChan,
    vXc->TextHeader.numSChan,
    vXc->TextHeader.sensDes
  );
  strcat(TXHD, line1);
  
  // Line 8
  sprintf(line2,
   "Rcrd start time: %02i/%02i/%4i, %02i:%02i:%.3f UTC (Q=%1i) RcrdId: %s\n",
   vXc->TextHeader.recMo,
   vXc->TextHeader.recDy,
   vXc->TextHeader.recYr,
   vXc->TextHeader.recHr,
   vXc->TextHeader.recMi,
   vXc->TextHeader.recSe,
   vXc->TextHeader.recQl,
   vXc->TextHeader.recID
  );
  strcat(TXHD, line2);
  
  // Line 9

  // Line 10

  // Line 11

  // Line 12

  // Line 13


  return TXHD;
}

char* vXc_buildINHD(VXCRecord* vXc){
  
  // Build the Integer Header
  char *INHD =  (char*)malloc((100*11) * sizeof(char));

  char *line1 = (char*)malloc(100 * sizeof(char));
  sprintf(line1,
    "%4i  Integer-header values follow on %3i lines, Format= (%s)\n",
    vXc->IntHeader.numValuesIntHd,
    vXc->IntHeader.numLineIntHd,
    vXc->IntHeader.formatInt
  );
  strcat(INHD, line1);
  
  for (int i=0; i < vXc->IntHeader.numLineIntHd; i++) {
    int j = 10*i;
    char *line2 = (char*)malloc(100 * sizeof(char));

    sprintf(line2,
      "%8i%8i%8i%8i%8i%8i%8i%8i%8i%8i\n",
      vXc->intvalues[j],
      vXc->intvalues[j+1],
      vXc->intvalues[j+2],
      vXc->intvalues[j+3],
      vXc->intvalues[j+4],
      vXc->intvalues[j+5],
      vXc->intvalues[j+6],
      vXc->intvalues[j+7],
      vXc->intvalues[j+8],
      vXc->intvalues[j+9]
    );

    strcat(INHD, line2);
  }

  return INHD;
}

char* vXc_buildRLHD(VXCRecord* vXc){
  
  // Build the Real Header
  char *RLHD =  (char*)malloc((100*11) * sizeof(char));

  char *line1 = (char*)malloc(100 * sizeof(char));
  sprintf(line1,
    "%4i  Real-header values follow on %3i lines, Format= (%s)\n",
    vXc->RealHeader.numValuesRealHd,
    vXc->RealHeader.numLineRealHd,
    vXc->RealHeader.formatReal
  );
  strcat(RLHD, line1);
  
  for (int i=0; i < vXc->RealHeader.numLineRealHd; i++) {
    int j = 6*i;
    char *line2 = (char*)malloc(100 * sizeof(char));

    sprintf(line2,
      "%13.6f%13.6f%13.6f%13.6f%13.6f%13.6f\n",
      vXc->relvalues[j],
      vXc->relvalues[j+1],
      vXc->relvalues[j+2],
      vXc->relvalues[j+3],
      vXc->relvalues[j+4],
      vXc->relvalues[j+5]
    );

    strcat(RLHD, line2);
  }

  return RLHD;
}

char* vXc_buildCMHD(VXCRecord* vXc){
  
  // Build the Comment Header
  char *CMHD =  (char*)malloc((3*100) * sizeof(char));

  char *line1 = (char*)malloc(100 * sizeof(char));
  sprintf(line1,
    "%4i  Comment line(s) follow, each starting with a \"|\":\n",
    vXc->CommentHeader.numComments
  );
  strcat(CMHD, line1);

  sprintf(line1,
    "|     This file created by v0c.c in libcosmos\n"
  );
  strcat(CMHD, line1);
    
  sprintf(line1,
    "|     Version 0.1 Beta\n"
  );
  strcat(CMHD, line1);

  return CMHD;
}

char* vXc_buildDTHD(VXCRecord* vXc){

  // Build the Comment Header
  char *CMHD =  (char*)malloc((3*100) * sizeof(char));

  char *line1 = (char*)malloc(100 * sizeof(char));
  sprintf(line1,
    "%4i %s, approx %4i secs , unit=%s(%2i), Format = (%5s)\n",
    vXc->DataHeader.numDataPoints,
    vXc->DataHeader.dataParam,
    vXc->DataHeader.dataLength,
    vXc->DataHeader.dataUnits,
    vXc->DataHeader.dataCode,
    vXc->DataHeader.dataFormat
  );
  strcat(CMHD, line1);

  return CMHD;
}

char* vXc_buildEDHD(VXCRecord* vXc){
  vXc->DataEnd.ChanNum = 0;

  // Build the Comment Header
  char *EDHD =  (char*)malloc((3*100) * sizeof(char));

  char *line1 = (char*)malloc(100 * sizeof(char));
  sprintf(line1,
    "End-of-data for Chan%4i %s\n",
    vXc->DataEnd.ChanNum,
    vXc->DataEnd.ChanPhy
  );
  strcat(EDHD, line1);

  return EDHD;
}

void  vXc_print(VXCRecord* vXc){
  char *TX, *IN, *RL, *CM, *DT, *ED, *file;
  int size = 0;

  TX = vXc_buildTXHD(vXc);
  size += strlen(TX);
  IN = vXc_buildINHD(vXc);
  size += strlen(IN);
  RL = vXc_buildRLHD(vXc);
  size += strlen(RL);
  CM = vXc_buildCMHD(vXc);
  size += strlen(CM);
  DT = vXc_buildDTHD(vXc);
  size += strlen(DT);
  ED = vXc_buildEDHD(vXc);
  size += strlen(ED);

  file = (char*) malloc(size * sizeof(char));
  strcat(file, TX);
  strcat(file, IN);
  strcat(file, RL);
  strcat(file, CM);
  strcat(file, DT);
  strcat(file, ED);
  printf(file);
}

void vXc_free (VXCRecord **ppvXc) {
	// I really must write this at some point.
  
}