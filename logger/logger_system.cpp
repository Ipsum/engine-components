#include <iostream>
#include <fstream>
#include "logger_system.h"

using namespace std;

bool log(LogLevel_t level, const char* msg) {
    log_comp = Engine::get_component<Engine::LoggerComponent>;
    /* TODO: check compontent exists */
    /* TODO: handle out of bytes */
    if(level > DISPLAYED_LOG_LEVEL) {
        /* This log level is not critical enough to be printed */
        return true;
    }
    if(log_comp->message_bytes_left == 0) {
        return false;
    }
    char* level_str;
    switch(level) {
    case LOG_ERROR:
        level_str = "ERROR";
        break;
    case LOG_WARNING:
        level_str = "WARNING";
        break;
    case LOG_NOTICE:
        level_str = "NOTICE";
        break;
    case LOG_INFO:
        level_str = "INFO";
        break;
    case LOG_DEBUG:
        level_str = "DEBUG";
        break;
    default:
        level_str = "UNKNOWN";
        break;
    }
    log_comp->message_bytes_left -= snprintf(&log_comp->message[MAX_LOG_SIZE-log_comp->message_bytes_left], 
                                             log_comp->message_bytes_left,
                                             "%s %s - %s - %s\n", 
                                             ts, level_str, entity_type, 
                                             entity_id, msg);
    return true;
}

void Logger_System::Logger_System() {
    name = "Logger_System";
    add_component<LoggerComponent>();
}

void Logger_System::init() {
    log_file.open(config.log_file_path);
}
void Logger_System::shutdown() {
    log_file.close(config.log_file_path);
}
void Logger_System::update() {
    std::vector<Logger_Component*>* logs = get_data_vec<LoggerComponet>();
    LoggerComponent* log;

    for(uint32_t ii=0; ii<entity_count; ++ii) {
        log = logs->at(ii);
        if(log->message_bytes_left != MAX_LOG_SIZE) {
            log_file<<log->message<<endl; 
            log->message[0] = '\0';
            log->message_bytes_left = MAX_LOG_SIZE;
        }
    }
}
    
