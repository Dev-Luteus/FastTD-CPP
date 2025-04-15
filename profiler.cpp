#include "profiler.h"
#include <iostream>

/* Initializing static variables
 */
std::map<std::string, Profiler::ProfileData> Profiler::timingProfile;
FILE* Profiler::outputLog = nullptr;

void Profiler::Init(const char *fileName)
{
    outputLog = fopen(fileName, "w"); // writing mode

    if (!outputLog)
    {
        std::cerr << "Failed to open output file " << fileName << std::endl;
        return;
    }

    fprintf(outputLog, "FastTD-CPP Performance Log\n");
    fprintf(outputLog, "=========================\n\n");
}

// Return current point in time
Profiler::TimePoint Profiler::StartTimer()
{
    return Clock::now();
}

void Profiler::EndTimer(const char* section, TimePoint startTime)
{
    TimePoint endTime = Clock::now();

    /* Here we calculate a duration in milliseconds:
     * - create duration object: double as presentation type (decimals)
     * - subtract endTime by startTime,
     * - .count() extracts the actual numerical value.
     *
     * We can now have durations in milliseconds with decimals, say: 14.321 ms
     */
    double durationMs = std::chrono::duration<double, std::milli>(endTime - startTime).count();

    /* find() - return an iterator to the elemend section, end() if not found
     * So if section is not found, this condition is true
     * We're basically checking if we've seen this section before,
     * If its the first time,
     * or if we've seen it before and need ot update it,
     */
    if (timingProfile.find(section) == timingProfile.end())
    {
        // The first time we've seen this section
        ProfileData data;
        data.totalTimeMs = durationMs;
        data.calls = 1;
        data.minTimeMs = durationMs;
        data.maxTimeMs = durationMs;
        timingProfile[section] = data;
    }
    else
    {
        // Update section
        ProfileData& data = timingProfile[section];
        data.totalTimeMs += durationMs;
        data.calls++;
        data.minTimeMs = std::min(data.minTimeMs, durationMs);
        data.maxTimeMs = std::max(data.maxTimeMs, durationMs);
    }
}

void Profiler::PrintSummary()
{
    if (!outputLog)
    {
        std::cerr << "Profiler outputLog not initialised. Call Profiler::Init() first." << std::endl;
        return;
    }

    fprintf(outputLog, "\n========== TIMING SUMMARY ==========\n");
    fprintf(outputLog, "%-30s | %15s | %6s | %15s | %15s | %15s\n",
            "Section", "Total Time (ms)", "Calls", "Avg Time (ms)", "Min Time (ms)", "Max Time (ms)");
    fprintf(outputLog, "--------------------------------------------------------------------------------------------------\n");

    double grandTotal = 0.0;

    for (const auto& entry : timingProfile)
    {
        const std::string& name = entry.first;
        const ProfileData& data = entry.second;
        double avgTime = data.calls > 0 ? data.totalTimeMs / data.calls : 0.0;

        fprintf(outputLog, "%-30s | %15.2f | %6d | %15.2f | %15.2f | %15.2f\n",
                name.c_str(), data.totalTimeMs, data.calls, avgTime, data.minTimeMs, data.maxTimeMs);

        grandTotal += data.totalTimeMs;
    }

    fprintf(outputLog, "--------------------------------------------------------------------------------------------------\n");
    fprintf(outputLog, "%-30s | %15.2f\n", "TOTAL", grandTotal);

    std::cout << "\nProfiling summary written to log file. Total measured time: "
              << grandTotal << " ms across " << timingProfile.size() << " sections.\n";

    fclose(outputLog);
    outputLog = nullptr;
}