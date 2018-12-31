#include <Engine.h>

#ifndef MAX_LOG_SIZE
#define MAX_LOG_SIZE 1000
#endif

#ifndef DISPLAYED_LOG_LEVEL
#define DISPLAYED_LOG_LEVEL LOG_NOTICE
#endif

#define LOG_ERROR(msg) \
    log(LOG_ERROR, msg);

typedef enum {
    LOG_ERROR,
    LOG_WARNING,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG
} LogLevel_t;

bool log(LogLevel_t level, const char* msg);

typedef struct sLoggerComponent {
    uint32_t message_bytes_left = MAX_LOG_SIZE;
    char message[MAX_LOG_SIZE+1] = {};
} LoggerComponent;

typedef struct sLoggerConfig {
    char* log_file_path;
} LoggerConfig_t;

class Logger_System : public System {
public:
    Logger_System();
    void init();
    void update();
    void shutdown();
    virtual void config();
protected:
    LoggerConfig_t config;
private:
    ofstream log_file;
}

/* Example logger class */
class Sample_Logger : public Logger_System {
public:
    void config();
protected:
    LoggerConfig_t config;
}

Sample_Logger::config() {
    config.log_file_path = strdup("game.log");
}
