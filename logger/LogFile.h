#ifndef __FRAMEWORK_LOGFILE__
#define __FRAMEWORK_LOGFILE__

#include <stdio.h>

#define LOG_CUT_TIME_SED 3600

class LogFile {
public:
    LogFile(const char * path);
    ~LogFile();
    void Write(const char * str);
    
    void Flush();
    void Close();

    template<typename... Args>
    void WriteFormat(const char * format, Args ...args) {
        fprintf(GetStream(), format, args...);
    }

    static LogFile * GetFile();
private:
    FILE * GetStream();

private:
    const char * _path;
    const int _cut_time;

    FILE * _file;
    long long _tick;
};

#endif // __FRAMEWORK_LOGFILE__