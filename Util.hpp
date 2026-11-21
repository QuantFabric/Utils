
#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include <string.h>
#include <dirent.h>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <mutex>
#include <iconv.h>
#include<pthread.h>

namespace Utils
{
using namespace std;

static void FormatCurrentTime(char *buffer, size_t bufferSize, time_t current,
                              const char *format, unsigned long fraction,
                              int fractionWidth)
{
    if (buffer == NULL || bufferSize == 0)
        return;

    buffer[0] = '\0';
    struct tm timeStamp = {};
    if (localtime_r(&current, &timeStamp) == NULL)
        return;

    size_t length = strftime(buffer, bufferSize, format, &timeStamp);
    if (length == 0 || length >= bufferSize || fractionWidth <= 0)
        return;

    std::snprintf(buffer + length, bufferSize - length, ".%0*lu",
                  fractionWidth, fraction);
}

/********************************
struct timespec
{
time_t tv_sec;
long int tv_nsec;
};
struct tm {
int tm_sec;
int tm_min;
int tm_hour;
int tm_mday;
int tm_mon;
int tm_year;
int tm_wday;
int tm_yday;
int tm_isdst;
};
********************************/

static unsigned long getTimeNs()
{
    struct timespec timeStamp = {0, 0};
    clock_gettime(CLOCK_REALTIME, &timeStamp);
    return static_cast<unsigned long>(timeStamp.tv_sec) * 1000000000UL +
           static_cast<unsigned long>(timeStamp.tv_nsec);
}

static unsigned long getTimeUs()
{
    return getTimeNs() / 1000UL;
}

static unsigned long getTimeMs()
{
    return getTimeNs() / 1000000UL;
}

static unsigned long getTimeSec()
{
    struct timespec timeStamp = {0, 0};
    clock_gettime(CLOCK_REALTIME, &timeStamp);
    return timeStamp.tv_sec;
}

static const char *getCurrentTimeSec()
{
    time_t current = getTimeSec();
    thread_local char szBuffer[64] = {0};
    FormatCurrentTime(szBuffer, sizeof(szBuffer), current,
                      "%Y-%m-%d %H:%M:%S", 0, 0);
    return szBuffer;
}

static int getCurrentTodaySec()
{
    time_t current = getTimeSec();
    struct tm timeStamp = {};
    if (localtime_r(&current, &timeStamp) == NULL)
        return -1;
    return timeStamp.tm_hour * 3600 + timeStamp.tm_min * 60 +
           timeStamp.tm_sec;
}

static const char *getCurrentTimeMs()
{
    unsigned long n = Utils::getTimeMs();
    time_t current = n / 1000UL;
    thread_local char szBuffer[64] = {0};
    FormatCurrentTime(szBuffer, sizeof(szBuffer), current,
                      "%Y-%m-%d %H:%M:%S", n % 1000UL, 3);
    return szBuffer;
}

static const char *getCurrentTimeUs()
{
    unsigned long n = Utils::getTimeUs();
    time_t current = n / 1000000UL;
    thread_local char szBuffer[64] = {0};
    FormatCurrentTime(szBuffer, sizeof(szBuffer), current,
                      "%Y-%m-%d %H:%M:%S", n % 1000000UL, 6);
    return szBuffer;
}

static const char *getCurrentTimeNs()
{
    unsigned long n = Utils::getTimeNs();
    time_t current = n / 1000000000UL;
    thread_local char szBuffer[64] = {0};
    FormatCurrentTime(szBuffer, sizeof(szBuffer), current,
                      "%Y-%m-%d %H:%M:%S",
                      n % 1000000000UL, 9);
    return szBuffer;
}

static const char *getCurrentDay()
{
    time_t current = Utils::getTimeSec();
    thread_local char szBuffer[64] = {0};
    FormatCurrentTime(szBuffer, sizeof(szBuffer), current,
                      "%Y-%m-%d", 0, 0);
    return szBuffer;
}

static const char *getCurrentNumberDay()
{
    time_t current = Utils::getTimeSec();
    thread_local char szBuffer[64] = {0};
    FormatCurrentTime(szBuffer, sizeof(szBuffer), current,
                      "%Y%m%d", 0, 0);
    return szBuffer;
}

static unsigned long getTimeStamp(const char *str)
{
    if (str == NULL)
        return 0;

    struct tm timeStamp = {};
    if (strptime(str, "%Y-%m-%d %H:%M:%S", &timeStamp) == NULL)
        return 0;

    return static_cast<unsigned long>(mktime(&timeStamp));
}

static long getTimeStampUs(const char *str)
{
    if (str == NULL)
        return -1;

    int hour, minute, second, microsecond;
    int n = sscanf(str, "%d:%d:%d.%d", &hour, &minute, &second, &microsecond);
    if (n != 4)
        return -1;
    int64_t totalSeconds =
        static_cast<int64_t>(hour) * 3600 + static_cast<int64_t>(minute) * 60 +
        second;
    return static_cast<long>(totalSeconds * 1000000 + microsecond);
}

static long getTimeStampMs(const char *str)
{
    if (str == NULL)
        return -1;

    int hour, minute, second, millisecond;
    int n = sscanf(str, "%d:%d:%d.%d", &hour, &minute, &second, &millisecond);
    if (n != 4)
        return -1;
    return (hour * 3600 + minute * 60 + second) * 1000 + millisecond;
}

static int64_t TimeDiffUs(const std::string& start, const std::string& end)
{
    int hour1, minute1, second1, microsecond1;
    int n1 = sscanf(start.c_str(), "%d:%d:%d.%d", &hour1, &minute1, &second1, &microsecond1);
    int hour2, minute2, second2, microsecond2;
    int n2 = sscanf(end.c_str(), "%d:%d:%d.%d", &hour2, &minute2, &second2, &microsecond2);
    if (n1 == 4 && n2 == 4)
    {
        int64_t totalSeconds =
            static_cast<int64_t>(hour2 - hour1) * 3600 +
            static_cast<int64_t>(minute2 - minute1) * 60 +
            (second2 - second1);
        return totalSeconds * 1000000 + microsecond2 - microsecond1;
    }
    else
    {
        return -1;
    }
}

static bool startWith(const std::string &src, const std::string &head)
{
    return src.compare(0, head.length(), head) == 0;
}

static bool endWith(const std::string &src, const std::string &tail)
{
    if (tail.length() > src.length())
        return false;
    return src.compare(src.length() - tail.length(), tail.length(), tail) == 0;
}

static bool equalWith(const std::string &src, const std::string &dest)
{
    return src.compare(dest) == 0;
}

static void RightFill(int totalWidth, char fill, std::string& src)
{
    if (totalWidth <= 0 || static_cast<size_t>(totalWidth) <= src.length())
        return;
    src.append(static_cast<size_t>(totalWidth) - src.length(), fill);
}

static void LeftFill(int totalWidth, char fill, std::string& src)
{
    if (totalWidth <= 0 || static_cast<size_t>(totalWidth) <= src.length())
        return;
    src.insert(0, static_cast<size_t>(totalWidth) - src.length(), fill);
}


static void Split(const std::string &src, const std::string &delimiter, std::vector<std::string> &value)
{
    value.clear();
    if (src.size() < 2)
        return;

    std::string token;
    token.reserve(src.size());
    for (char character : src)
    {
        if (delimiter.find(character) != std::string::npos)
        {
            if (!token.empty())
            {
                size_t first = token.find_first_not_of(' ');
                if (first == std::string::npos)
                    value.push_back(std::string());
                else
                {
                    size_t last = token.find_last_not_of(' ');
                    value.push_back(token.substr(first, last - first + 1));
                }
                token.clear();
            }
        }
        else
        {
            token.push_back(character);
        }
    }

    size_t first = token.find_first_not_of(' ');
    if (first == std::string::npos)
        value.push_back(std::string());
    else
    {
        size_t last = token.find_last_not_of(' ');
        value.push_back(token.substr(first, last - first + 1));
    }
}

static void CreateDirectory(const char *str)
{
    if (str == NULL)
        return;
    mkdir(str, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

static int CodeConvert(char *inbuf, size_t inlen, char* outbuf, size_t outlen, const char *from_charset, const char *to_charset)
{
    if (inbuf == NULL || outbuf == NULL || outlen == 0 ||
        from_charset == NULL || to_charset == NULL)
        return -1;

    std::memset(outbuf, 0, outlen);
    iconv_t cd = iconv_open(to_charset, from_charset);
    if (cd == (iconv_t)(-1))
        return -1;

    char *input = inbuf;
    char *output = outbuf;
    size_t inputLeft = inlen;
    size_t outputLeft = outlen - 1;
    size_t result = iconv(cd, &input, &inputLeft, &output, &outputLeft);
    *output = '\0';
    int closeResult = iconv_close(cd);

    if (result == (size_t)(-1) || closeResult != 0)
        return -1;
    return 0;
}

static bool ThreadBind(pthread_t thread, int cpuid)
{
    if (cpuid < 0 || cpuid >= CPU_SETSIZE)
        return false;

    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(cpuid, &mask);
    return pthread_setaffinity_np(thread, sizeof(mask), &mask) == 0;
}

static bool ReadDirectory(const std::string& path, std::vector<std::string>& ret)
{
    ret.clear();
    struct dirent* ptr;
    DIR* dir = opendir(path.c_str());
    if (dir == NULL)
        return false;

    while((ptr = readdir(dir)) != NULL)
    {
        if(DT_REG == ptr->d_type)
        {
            ret.push_back(ptr->d_name);
        }
    }
    closedir(dir);
    std::sort(ret.begin(), ret.end());
    return true;
}

static bool ReadFile(const std::string& path, std::vector<std::string>& ret)
{
    ret.clear();
    bool ok = true;
    FILE* fp = fopen(path.c_str(), "r");
    if (NULL != fp)
    {
        char *line = NULL;
        size_t len = 0;
        while (getline(&line, &len, fp) != -1)
        {
            ret.push_back(line);
        }
        free(line);
        fclose(fp);
    }
    else
    {
        ok = false;
    }
    return ok;
}

}

#endif // UTIL_HPP
