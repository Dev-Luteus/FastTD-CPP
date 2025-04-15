#ifndef PROFILESCOPE_H
#define PROFILESCOPE_H

#include "profiler.h"

#define PROFILE_INIT(fileName) Profiler::Init(fileName)

/* I'm writing comments here since I'm mostly focused on C# over C++ at this point in time.
 * Create new ProfileScope object named profiler + current line number,

 * ## is the preprocessor concatenation operator:
 * - We're ensuring each profiler object has a unique name dependant on the line of code
 */
#define PROFILE_SCOPE(name) ProfileScope profiler##__LINE__(name)

/* Creates a ProfileScope object with the function name, using __FUNCTION__ (pre-defined macro)
 */
#define PROFILE_FUNCTION() ProfileScope profiler##__LINE__(__FUNCTION__)

/* When we create a ProfileScope object, its constructor starts the timer.
 * When our scope ends, the object is automatically destroyed.
 * Our deconstruction then stops the timer and logs the duration.
 */
class ProfileScope
{
    const char* section;
    Profiler::TimePoint startTime;

public:
    explicit ProfileScope(const char* sectionName) : section(sectionName)
    {
        startTime = Profiler::StartTimer();
    }

    ~ProfileScope()
    {
        Profiler::EndTimer(section, startTime);
    }
};

#endif //PROFILESCOPE_H
