#include "Util.hpp"

#include <atomic>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <thread>
#include <vector>

#include <sys/stat.h>
#include <unistd.h>

namespace
{

int g_failures = 0;

void Check(bool condition, const char *message)
{
    if (!condition)
    {
        std::fprintf(stderr, "UtilTest failed: %s\n", message);
        ++g_failures;
    }
}

bool IsTimestamp(const std::string &value, size_t fractionDigits)
{
    struct tm parsedTime = {};
    const char *fraction =
        strptime(value.c_str(), "%Y-%m-%d %H:%M:%S", &parsedTime);
    if (fraction == NULL)
        return false;

    if (fractionDigits == 0)
        return *fraction == '\0';

    const size_t fractionLength = std::strlen(fraction);
    if (fractionLength != fractionDigits + 1 || fraction[0] != '.')
        return false;

    for (size_t i = 1; i < fractionLength; ++i)
    {
        if (fraction[i] < '0' || fraction[i] > '9')
            return false;
    }
    return true;
}

bool IsDay(const std::string &value)
{
    struct tm parsedTime = {};
    const char *end = strptime(value.c_str(), "%Y-%m-%d", &parsedTime);
    return end != NULL && *end == '\0';
}

bool IsNumberDay(const std::string &value)
{
    if (value.size() != 8)
        return false;

    for (char character : value)
    {
        if (character < '0' || character > '9')
            return false;
    }
    return true;
}

void CheckSplit(const char *input, const char *delimiter,
                const std::vector<std::string> &expected,
                const char *message)
{
    std::vector<std::string> actual;
    Utils::Split(input, delimiter, actual);
    Check(actual == expected, message);
}

void TestTimeFormatting()
{
    Check(IsTimestamp(Utils::getCurrentTimeSec(), 0),
          "current second timestamp format");
    Check(IsTimestamp(Utils::getCurrentTimeMs(), 3),
          "current millisecond timestamp format");
    Check(IsTimestamp(Utils::getCurrentTimeUs(), 6),
          "current microsecond timestamp format");
    Check(IsTimestamp(Utils::getCurrentTimeNs(), 9),
          "current nanosecond timestamp format");
    Check(IsDay(Utils::getCurrentDay()), "current day format");
    Check(IsNumberDay(Utils::getCurrentNumberDay()),
          "current number day format");

    int todaySeconds = Utils::getCurrentTodaySec();
    Check(todaySeconds >= 0 && todaySeconds < 24 * 3600,
          "current seconds of day range");
}

void TestTimeParsing()
{
    Check(Utils::getTimeStampMs("00:00:00.000") == 0,
          "millisecond timestamp at midnight");
    Check(Utils::getTimeStampMs("01:02:03.004") == 3723004,
          "millisecond timestamp value");
    Check(Utils::getTimeStampMs("00:00:00.1") == 1,
          "millisecond parser preserves suffix integer semantics");
    Check(Utils::getTimeStampUs("12:00:00.123456") == 43200123456L,
          "microsecond timestamp avoids integer overflow");
    Check(Utils::getTimeStampUs("23:59:59.999999") == 86399999999L,
          "microsecond timestamp near end of day");
    Check(Utils::getTimeStampMs("invalid") == -1,
          "invalid millisecond timestamp");
    Check(Utils::getTimeStampUs("invalid") == -1,
          "invalid microsecond timestamp");
    Check(Utils::getTimeStampMs(NULL) == -1,
          "null millisecond timestamp");
    Check(Utils::getTimeStampUs(NULL) == -1,
          "null microsecond timestamp");

    Check(Utils::TimeDiffUs("01:00:00.000000", "01:00:00.000001") == 1,
          "microsecond time difference");
    Check(Utils::TimeDiffUs("23:59:59.900000", "00:00:00.100000") ==
              -86399800000LL,
          "cross-midnight difference preserves existing arithmetic");
    Check(Utils::TimeDiffUs("invalid", "00:00:00.000000") == -1,
          "invalid microsecond time difference");

    struct tm expectedTime = {};
    Check(strptime("2024-01-02 03:04:05", "%Y-%m-%d %H:%M:%S",
                   &expectedTime) != NULL,
          "build expected calendar time");
    time_t expectedEpoch = mktime(&expectedTime);
    Check(Utils::getTimeStamp("2024-01-02 03:04:05") ==
              static_cast<unsigned long>(expectedEpoch),
          "calendar timestamp");
    Check(Utils::getTimeStamp("invalid") == 0,
          "invalid calendar timestamp");
    Check(Utils::getTimeStamp(NULL) == 0,
          "null calendar timestamp");
}

void TestStringHelpers()
{
    std::string right = "ab";
    Utils::RightFill(5, 'x', right);
    Check(right == "abxxx", "right fill");

    Utils::RightFill(5, 'x', right);
    Check(right == "abxxx", "right fill does not truncate");

    Utils::RightFill(2, 'x', right);
    Check(right == "abxxx", "right fill below current width");

    Utils::RightFill(-1, 'x', right);
    Check(right == "abxxx", "right fill negative width");

    std::string left = "ab";
    Utils::LeftFill(5, '0', left);
    Check(left == "000ab", "left fill");

    Utils::LeftFill(5, '0', left);
    Check(left == "000ab", "left fill does not truncate");

    Utils::LeftFill(0, '0', left);
    Check(left == "000ab", "left fill non-positive width");

    Check(Utils::startWith("abc", "ab"), "prefix match");
    Check(!Utils::startWith("abc", "abcd"), "long prefix mismatch");
    Check(Utils::startWith("abc", ""), "empty prefix");
    Check(Utils::endWith("abc", "bc"), "suffix match");
    Check(!Utils::endWith("abc", "abcd"), "long suffix mismatch");
    Check(Utils::endWith("abc", ""), "empty suffix");
    Check(Utils::equalWith("abc", "abc"), "equal strings");
    Check(!Utils::equalWith("abc", "abd"), "different strings");
}

void TestSplit()
{
    CheckSplit("", ",", {}, "empty split input");
    CheckSplit("a", ",", {}, "single character split input");
    CheckSplit(",", ",", {}, "single delimiter split input");
    CheckSplit("a,", ",", {"a", ""}, "trailing empty field");
    CheckSplit(",a", ",", {"a"}, "leading empty field ignored");
    CheckSplit(" a , b ", ",", {"a", "b"}, "trim surrounding spaces");
    CheckSplit("a,,b", ",", {"a", "b"}, "middle empty fields ignored");
    CheckSplit("a  b", ",", {"a  b"}, "internal spaces preserved");
    CheckSplit("a\tb", ",", {"a\tb"}, "tabs preserved");
    CheckSplit("   ,a", ",", {"", "a"}, "whitespace-only field preserved");
    CheckSplit(",,", ",", {""}, "trailing empty field after delimiters");
    CheckSplit(" x ", "", {"x"}, "empty delimiter");
    CheckSplit("a,b c", ", ", {"a", "b", "c"},
               "delimiter acts as a character set");
}

bool WriteFile(const std::string &path, const std::string &content)
{
    std::ofstream stream(path, std::ios::binary);
    stream << content;
    return stream.good();
}

void TestFileHelpers()
{
    char directoryTemplate[] = "/tmp/quantfabric_util_test_XXXXXX";
    char *createdDirectory = mkdtemp(directoryTemplate);
    Check(createdDirectory != NULL, "create temporary test directory");
    if (createdDirectory == NULL)
        return;

    const std::string directory(createdDirectory);
    const std::string fileA = directory + "/a.txt";
    const std::string fileB = directory + "/b.txt";
    const std::string subdirectory = directory + "/subdir";
    const std::string missing = directory + "/missing";

    Utils::CreateDirectory(subdirectory.c_str());
    struct stat subdirectoryStatus = {};
    Check(stat(subdirectory.c_str(), &subdirectoryStatus) == 0 &&
              S_ISDIR(subdirectoryStatus.st_mode),
          "create temporary subdirectory");
    Check(WriteFile(fileA, "a"), "write first temporary file");
    Check(WriteFile(fileB, "b"), "write second temporary file");

    std::vector<std::string> entries;
    Check(Utils::ReadDirectory(directory, entries),
          "read existing directory");
    Check(entries == std::vector<std::string>({"a.txt", "b.txt"}),
          "directory entries sorted and regular files only");

    Check(!Utils::ReadDirectory(missing, entries),
          "missing directory returns false");
    Check(entries.empty(), "missing directory clears output");

    Check(WriteFile(fileA, "one\n\nthree"), "write multiline file");
    std::vector<std::string> lines;
    Check(Utils::ReadFile(fileA, lines), "read multiline file");
    Check(lines == std::vector<std::string>({"one\n", "\n", "three"}),
          "file lines preserve original line endings");

    Check(!Utils::ReadFile(missing, lines), "missing file returns false");
    Check(lines.empty(), "missing file clears output");

    std::remove(fileA.c_str());
    std::remove(fileB.c_str());
    rmdir(subdirectory.c_str());
    rmdir(directory.c_str());
}

void TestCodeConvert()
{
    char gb2312[] = "\xB2\xE2\xCA\xD4";
    char output[64] = {};
    Check(Utils::CodeConvert(gb2312, sizeof(gb2312), output, sizeof(output),
                             "gb2312", "utf-8") == 0,
          "GB2312 to UTF-8 conversion");
    Check(std::strcmp(output, "\xE6\xB5\x8B\xE8\xAF\x95") == 0,
          "converted UTF-8 content");

    char shortInput[] = "AB";
    char shortOutput[2] = {'x', 'x'};
    Check(Utils::CodeConvert(shortInput, sizeof(shortInput), shortOutput,
                             sizeof(shortOutput), "gb2312", "utf-8") == -1,
          "insufficient output buffer returns failure");
    Check(shortOutput[sizeof(shortOutput) - 1] == '\0',
          "truncated output is null terminated");

    char invalidInput[] = {'\xFF', '\0'};
    char invalidOutput[16] = {};
    Check(Utils::CodeConvert(invalidInput, sizeof(invalidInput), invalidOutput,
                             sizeof(invalidOutput), "gb2312", "utf-8") == -1,
          "invalid input sequence returns failure");
    Check(invalidOutput[sizeof(invalidOutput) - 1] == '\0',
          "failed conversion output is null terminated");

    Check(Utils::CodeConvert(gb2312, sizeof(gb2312), output, sizeof(output),
                             "not-a-charset", "utf-8") == -1,
          "invalid source charset returns failure");
    Check(output[0] == '\0',
          "invalid charset clears conversion output");
    Check(Utils::CodeConvert(gb2312, sizeof(gb2312), NULL, 0, "gb2312",
                             "utf-8") == -1,
          "null output buffer returns failure");
}

void TestConcurrentFormatting()
{
    constexpr int kThreadCount = 8;
    constexpr int kIterations = 200;
    std::atomic<bool> valid{true};
    std::vector<std::thread> threads;
    threads.reserve(kThreadCount);

    for (int i = 0; i < kThreadCount; ++i)
    {
        threads.emplace_back([&valid]() {
            for (int iteration = 0; iteration < kIterations; ++iteration)
            {
                std::string seconds = Utils::getCurrentTimeSec();
                std::string milliseconds = Utils::getCurrentTimeMs();
                std::string microseconds = Utils::getCurrentTimeUs();
                std::string nanoseconds = Utils::getCurrentTimeNs();
                std::string day = Utils::getCurrentDay();
                std::string numberDay = Utils::getCurrentNumberDay();

                if (!IsTimestamp(seconds, 0) ||
                    !IsTimestamp(milliseconds, 3) ||
                    !IsTimestamp(microseconds, 6) ||
                    !IsTimestamp(nanoseconds, 9) || !IsDay(day) ||
                    !IsNumberDay(numberDay))
                {
                    valid.store(false, std::memory_order_relaxed);
                    return;
                }
            }
        });
    }

    for (std::thread &thread : threads)
        thread.join();

    Check(valid.load(std::memory_order_relaxed),
          "concurrent timestamp formatting");
    Check(!Utils::ThreadBind(pthread_self(), -1),
          "negative CPU binding rejected");
    Check(!Utils::ThreadBind(pthread_self(), CPU_SETSIZE),
          "out-of-range CPU binding rejected");
}

}

int main()
{
    TestTimeFormatting();
    TestTimeParsing();
    TestStringHelpers();
    TestSplit();
    TestFileHelpers();
    TestCodeConvert();
    TestConcurrentFormatting();

    if (g_failures != 0)
    {
        std::fprintf(stderr, "UtilTest completed with %d failure(s)\n",
                     g_failures);
        return EXIT_FAILURE;
    }

    std::printf("UtilTest passed\n");
    return EXIT_SUCCESS;
}
