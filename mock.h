#ifdef MOCK
#define MAXLEN_DEBUG_MSG 8192 // maximum debug message size
#define NB_LOGS 20
typedef struct logMessage {
    uint64_t Id;
    char message[MAXLEN_DEBUG_MSG];
} logMessage;
#endif

