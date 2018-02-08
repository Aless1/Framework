#include "LogFile.h"
#include <string.h>

#include "Daily.h"
#include "Tools.h"

LogFile::LogFile(const char * path) : 
_path(path), _tick(Util::Daily::GetCurrentTime()), _cut_time(LOG_CUT_TIME_SED), _file(NULL) {}

LogFile::~LogFile() {
    Close();
}

FILE * LogFile::GetStream() {
    long long now = Util::Daily::GetCurrentTime();
    if(now - _tick > _cut_time * 1000) {
        _tick = now;
        Close();
    }

    if(!_file) {
        char path[128];
        SafeSprintf(path, 128, "log/%s-%s.log", _path, Util::Daily::GetTimeString(_tick));
        _file = fopen(path, "a+");
    }

    return _file;
}

void LogFile::Write(const char * str) {
    printf(str);
    fwrite(str, strlen(str), 1, GetStream());
}

void LogFile::Flush() {
    fflush(_file);
}

void LogFile::Close() {
    if(_file) {
        fclose(_file);
        _file = NULL;
    }
}

