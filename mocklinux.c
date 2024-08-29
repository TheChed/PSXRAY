#include "PSXMSFS.h"
#include <stdint.h>
#include <stdlib.h>

void deleteFlagsPSXMSFS(FLAGS *flags){
    return;
}
int disconnectPSXMSFS(FLAGS *flags)
{
    return 0;
}
int initializePSXMSFS(FLAGS *F)
{
    return 0;
}

int connectPSXMSFS(FLAGS *f)
{
    return 0;
}

int launchPSXMSFS(FLAGS *f)
{
    return -1;
}
void cleanup(void)
{
    return;
}

typedef struct logMessage logMessage;

logMessage *getLogBuffer(int nblogs)
{
    return NULL;
}
char *getLogMessage(logMessage *D, int n)
{
    return NULL;
}
int getLogLevel(logMessage *D, int n)
{
    return -1;
}
uint64_t getLogID(logMessage *D, int n)
{
    return -1;
}

void freeLogBuffer(logMessage *D)
{
    return;
}
 FLAGS *createFlagsPSXMSFS(void)
{
    return NULL;
}
int updateFromIni(FLAGS *flags){
    return 0;
}
servers getServersInfo(FLAGS *f){
    servers S;
    return S;
}
unsigned int getSwitch(FLAGS *f){
    return 0;
}
void setLogVerbosity(FLAGS *f, LOG_LEVELS level){
}
void setOnlineHack(FLAGS *f, unsigned  int hack){}
void setElevationInject(FLAGS *f, unsigned  int elev){}
void setTCASinject(FLAGS *f, unsigned  int TCAS){}
void setCrashInhib(FLAGS *f, unsigned  int crash){}
void setPSXslave(FLAGS *f, unsigned  int slave){}

int getLogVerbosity(FLAGS *f){
    return 0;
}

ACFT getACFTInfo(void){
    ACFT A;
    return A;
}

int setServersInfo(servers *S, FLAGS *f){
    return 0;
}
