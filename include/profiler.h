#ifndef PROFILER_H
#define PROFILER_H

#include <chrono>
#include <map>

class Profiler
{
    /**
     * std::numeric_limits just provides the maximum possible value for a type, in our case double.
     * We use it as an initial value for our double because: every time we measure time,
     * we can compare our method time versus the maximum time.
     * Since it'll always return a smaller time, its convenient to log this way.
     */
    struct ProfileData
    {
        double totalTimeMs { 0.0 };
        int calls { 0 };
        double minTimeMs { std::numeric_limits<double>::max() };
        double maxTimeMs { 0.0 };
    };

    // Array storing ProfileData objects
    static std::map<std::string, ProfileData> timingProfile;
    static FILE* outputLog;

public:
    /** Here we've defined two type-aliases.
     * std::chrono is c++ highest precision clock.
     * time_point is a specific point in time from a clock. So, when we call something for instance.
     */
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    static void Init(const char* fileName);
    [[nodiscard]] static TimePoint StartTimer();
    static void EndTimer(const char* section, TimePoint startTime);
    static void PrintSummary();
};

#endif //PROFILER_H