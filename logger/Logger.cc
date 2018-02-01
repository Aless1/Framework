#include "Logger.h"

ILogger * tcore::GetLoggerInstance() {
    static ILogger * s_logger = new Logger();
    return s_logger;
}

bool Logger::Launch() {
    return true;
}

bool Logger::Shutdown() {
    return true;
}

void Logger::LogSyn(char * type, char * log, char * filename, int line) {

}

void Logger::LogASyn(char * type, char * log, char * filename, int line) {
    char * path = "error.log";
    char * format = "[%s]: {%s: %d} - %s";

    FILE *stream;
    if ((stream = fopen(path, "a+")) == NULL) {
        return;
    }
    fprintf(stream, format, Tools::GetTimeString(), filename, line, log); /* 写的struct文件*/
    fclose(stream); /*关闭文件*/
}