#include "PSXMSFS.h"
#include <stdint.h>
#include <stdlib.h>

int initialize(FLAGS *)
{
    return 0;
}

int connectPSXMSFS(FLAGS *f)
{
    return 0;
}

int main_launch(void)
{
    return -1;
}
int cleanup(void)
{
    return -1;
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
 FLAGS *initFlags(void)
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

int getLogVerbosity(FLAGS *f){
    return 0;
}

ACFT getACFTInfo(void){
    ACFT A;
    return A;
}

void setServersInfo(servers *S){
}
