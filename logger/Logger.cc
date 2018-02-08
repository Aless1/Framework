#include <sys/stat.h>
#include <sys/types.h>

#include "Logger.h"
#include "LogFile.h"

#include "Tools.h"

ILogger * tcore::GetLoggerInstance() {
    static ILogger * s_logger = new Logger();
    return s_logger;
}

bool Logger::Launch() {
    tools::file::MakeDir("log");
    Start(1);
    return true;
}

bool Logger::Shutdown() {
    Terminate();
    return true;
}

void Logger::LogSyn(const char * log) {
    LOGFILE_MAP::iterator iter = _logfile_map.find("synlog");
    if(iter == _logfile_map.end()) {
        iter = _logfile_map.insert(std::pair<const char *, LogFile *>("synlog", new LogFile("synlog"))).first;
    }

    iter->second->Write(Util::Daily::GetCurrentTimeString());
    iter->second->Write(log);
    iter->second->Write("\n");
    iter->second->Flush();
}

void Logger::LogAsyn(const char * log) {
    if((_queue_index_write + 1) % ASYN_TEMP_QUEUE_SIZE ==  _queue_index_read) {
        return;
    }

    tools::SafeMemcpy(_queue[_queue_index_write].log, LOG_TEMP_SIZE_MAX, log, strlen(log) + 1);

    _queue[_queue_index_write].tick = Util::Daily::GetCurrentTime();
    _queue_index_write = (_queue_index_write + 1) % ASYN_TEMP_QUEUE_SIZE;
}

void Logger::Run() {
    while(_status != Lib::THREAD_STOPING) {
        if(_queue_index_read == _queue_index_write) {
            CSLEEP(50);
            continue;
        }
        LOGFILE_MAP::iterator iter = _logfile_map.find("asynlog");
        if(iter == _logfile_map.end()) {
            iter = _logfile_map.insert(std::pair<const char *, LogFile *>("asynlog", new LogFile("asynlog"))).first;
        }
        
        iter->second->Write(Util::Daily::GetTimeString(_queue[_queue_index_read].tick));
        iter->second->Write(_queue[_queue_index_read].log);
        iter->second->Write("\n");
        iter->second->Flush();

        _queue_index_read = (_queue_index_read + 1) % ASYN_TEMP_QUEUE_SIZE;
    }
}