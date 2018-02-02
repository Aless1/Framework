#include <sys/stat.h>
#include <sys/types.h>

#include "Logger.h"
#include "LogFile.h"

ILogger * tcore::GetLoggerInstance() {
    static ILogger * s_logger = new Logger();
    return s_logger;
}

bool Logger::Launch() {
    mkdir("log", S_IRWXU | S_IRWXG | S_IRWXO);
    Start();
    return true;
}

bool Logger::Shutdown() {
    Terminate();
    return true;
}

void Logger::LogSyn(char * path, char * log, char * filename, int line) {
    LOGFILE_MAP::iterator iter = _logfile_map.find(path);
    if(iter == _logfile_map.end()) {
        iter = _logfile_map.insert(std::pair<const char *, LogFile *>(path, new LogFile(path))).first;
    }
    
    iter->second->WriteFormat("[%s]: {%s: %d} - %s\n", Util::Daily::GetTimeString(), filename, line, log);
    iter->second->Flush();
}

void Logger::LogAsyn(char * path, char * log, char * filename, int line) {
    if((_queue_index_write + 1) % ASYN_TEMP_QUEUE_SIZE ==  _queue_index_read) {
        return;
    }
    _queue[_queue_index_write].path = path;
    _queue[_queue_index_write].log = log;
    _queue[_queue_index_write].filename = filename;
    _queue[_queue_index_write].line = line;
    _queue_index_write = (_queue_index_write + 1) % ASYN_TEMP_QUEUE_SIZE;
}

void Logger::Run() {
    while(_queue_index_read != _queue_index_write) {

        LOGFILE_MAP::iterator iter = _logfile_map.find(_queue[_queue_index_read].path);
        if(iter == _logfile_map.end()) {
            iter = _logfile_map.insert(
                std::pair<const char *, LogFile *>(
                    _queue[_queue_index_read].path, 
                    new LogFile(_queue[_queue_index_read].path))
                ).first;
        }
        
        iter->second->WriteFormat("[%s]: {%s: %d} - %s\n", 
            Util::Daily::GetTimeString(), _queue[_queue_index_read].filename,
             _queue[_queue_index_read].line,
              _queue[_queue_index_read].log);

        iter->second->Flush();
    }
}

void Logger::Terminate() {

}