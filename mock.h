#ifdef MOCK
#define MAXLEN_DEBUG_MSG 8192 // maximum debug message size
typedef struct logMessage {
    uint64_t Id;
    char message[MAXLEN_DEBUG_MSG];
} logMessage;
#endif

