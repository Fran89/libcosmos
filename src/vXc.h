 // Header files describes data that may be availible in a VXc File.
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "vc_defs.h"


 typedef struct _VXcTextHeader {
    // I. Text Header
    
    // Meta Info 1 (1)
   char   dataType[25]; // Type of physical parameter of the data that follows: "Raw acceleration counts"
   int    verMajor;     // Mayor VXc Version
   int    verMinor;     // Minor VXc Version
   int    textHeaderSz; // Number of lines in text header (including this one).
   char   agency[19];   // Field reserved for use by preparing agency

   // Eq Info 1 (2)
   char   eqName[40];   // Earthquake name
   int    eqYr;         // Earthquake Year
   int    eqMo;         // Earthquake Month
   int    eqDy;         // Earthquake Day
   int    eqHr;         // Earthquake Hour
   int    eqMi;         // Earthquake Minute
   double eqSe;         // Earthquake Second
   char   eqTz[3];      // Earthquake Timezone

   // Eq Info 2 (3)
   double eqLat;        // Latitude (positive North)
   double eqLon;        // Longitude (positive East)
   double eqDep;        // Depth (km)
   char   eqSrc[8];     // Source agency for hypocenter information.
   char   eqMag[34];    // Magnitude(s), including source agency for values

   // Eq Info 3 (4)
   int    eqOrYr;       // Earthquake Year
   int    eqOrMo;       // Earthquake Month
   int    eqOrDy;       // Earthquake Day
   int    eqOrHr;       // Earthquake Hour
   int    eqOrMi;       // Earthquake Minute
   double eqOrSe;       // Earthquake Second
   char   eqOrNote[38]; // For use by preparing agency; may include note

   // Station Info 1 (5)
   int    netNo;        // Network number
   int    staNo;        // Station number
   char   staNet[3];    // Network code
   char   staCod[6];    // Station alphanumeric code (left justified)
   char   netAbr[5];    // Network abbreviation
   char   staNam[40];   // Station name

   // Station Info 2 (6)
   double staLat;       // Latitude (positive North)
   double staLon;       // Longitude (positive East)
   char   staGeo[40];   // Site geology description.

   // Recorder and sensor info 1 (7)
   char  recoDes[15];   // Recorder type and serial number.
   int   numRChan;      // Number of channels in recorder
   int   numSChan;      // Number of channels at station.
   char  sensDes[22];   // Sensor type and serial number.

   // Record information 1 (8)
   int    recYr;        // Record Year
   int    recMo;        // Record Month
   int    recDy;        // Record Day
   int    recHr;        // Record Hour
   int    recMi;        // Record Minute-
   double recSe;        // Earthquake Second
   int    recQl;        // Time quality(0 through 5 correspond to lowest through highest quality)
   char   recID[21];    // Record identification, assigned by preparing agency.

   // Record information 2 (9)
   int    chaNum;       // Station channel number for this sensor
   int    chaAzm;       // Sensing direction
   int    recNum;       // Recorder channel number, if different.
   char   chaDes[33];   // Location of sensor (for structural or other arrays).

   // Record information 3 (10)
   double recLen;       // Length of raw record, as recorded (seconds)
   double maxRaw;       // Maximum of raw (uncorrected) record in g (or other units);
   double maxTimR;      // Time max occurs in raw record (secs after start).

   // Record information 4 (11)
   char   procInfo[29]; // Processing/release date, time and agency.
   double maxProc;      // Maximum of data series in file, units
   double maxTimP;      // Time of maximum (seconds after start).

   // Record information 5 (12)
   double filtBanHzL;   // Filter band used in processing in Hz;
   double filtBanSc;    // Expressed as period, in seconds; 
   double filtBanHzH;   // High frequency frequency, in Hz.

   // Record information 6 (13)
   int    emptyValInt;  // Value used in file to indicate a parameter or data value is unknown or not specified:
   double emptyValDbl;  // Value for reals.

 } VXcTextHeader;
 
 typedef struct _VXcIntHeader {
   // II. Integer Header
   int  numValuesIntHd; // Number of values in Integer Header.
   int  numLineIntHd;   // Number of lines of Integer Header values that follow.
   char formatInt[24];  // Format by which the Integer Header values are written.

 } VXcIntHeader;

 typedef struct _VXcRealHeader {
   // III. Real Header
   int  numValuesRealHd; // Number of values in Real Header.
   int  numLineRealHd;   // Number of lines of Real Header values that follow.
   char formatReal[24];  // Format by which the RealHeader values are written.

 } VXcRealHeader;

 typedef struct _VXcCommentHeader {
   // IV. Comments
   int numComments; // Number of comment lines that follow, each starting with “|”; may be zero.

 } VXcCommentHeader;

 typedef struct _VXcDataHeader {
   // V. DATA VALUES SECTION
   int numDataPoints;  // Number of data points following;
   char dataParam[15]; // Physical parameter of the data.
   int  dataLength;    // Approximate length of record (rounded to nearest sec; see Rhdr(66) for precise value).
   char dataUnits[7];  // Units of the data values (e.g., cm/sec2);
   int  dataCode;      // Index code for units (see Table 2).
   char dataFormat[7]; // Format of the data values written on the following lines.

 } VXcDataHeader;

 typedef struct _VXcDataEnd {
   // End-of-Data Flag Line:
   int  ChanNum;     // Station channel number
   char ChanPhy[20]; // physical parameter of data

 } VXcDataEnd;

 typedef struct _VXCRecord {

   // Headers
   VXcTextHeader    TextHeader;
   VXcIntHeader     IntHeader;
   VXcRealHeader    RealHeader;
   VXcCommentHeader CommentHeader;
   VXcDataHeader    DataHeader;
   VXcDataEnd       DataEnd;

   // Data
   void             *datasamples;
   double           relvalues[100];
   int              intvalues[100];

   // Data Size
   int              datasize;

 } VXCRecord;
 
 extern VXCRecord* vXc_init(VXCRecord *vXc);
 extern void  vXc_setEqName(VXCRecord* ,char*);
 extern void  vXc_setEqInfo(VXCRecord* , int, int, int, int, int, double, int, char*);
 extern void  vXc_setEqMgAz(VXCRecord* , int, int, int, double, double, double, double, double);
 extern void  vXc_setEqLocI(VXCRecord* , double, double , double , char*, char*);
 extern void  vXc_setStaInf(VXCRecord* , int ,int ,char* ,char* , char*, int, char*);
 extern void  vXc_setStaLoc(VXCRecord* , double , double , double, double, int, char*);
 extern void  vXc_setRecInf(VXCRecord* , char* ,  int, int, char*);
 extern void  vXc_setRecoID(VXCRecord* , char*);
 extern void  vXc_setRecTim(VXCRecord* , int , int , int , int , int , double , int );
 extern char* vXc_build(VXCRecord *vXc);
 extern void  vXc_print(VXCRecord *vXc);
 extern void  vXc_free(VXCRecord **ppvXc);
 
 extern void  v0c_create(VXCRecord *vXc, char* Agency);
