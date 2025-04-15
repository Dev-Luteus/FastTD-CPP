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
 * __PRETTY_FUNCTION__ returns the full function signature, including the class name.
 */
#define PROFILE_FUNCTION() ProfileScope profiler##__LINE__(__PRETTY_FUNCTION__)

/* When we create a ProfileScope object, its constructor starts the timer.
 * When our scope ends, the object is automatically destroyed.
 * Our deconstruction then stops the timer and logs the duration.
 */

// Component specific macros for organizing our output log
#define PROFILE_GAME(name) ProfileScope profiler##__LINE__("Game::" name)
#define PROFILE_GRID(name) ProfileScope profiler##__LINE__("Grid::" name)
#define PROFILE_ENEMY(name) ProfileScope profiler##__LINE__("Enemy::" name)
#define PROFILE_UI(name) ProfileScope profiler##__LINE__("UI::" name)
#define PROFILE_PATHFIND(name) ProfileScope profiler##__LINE__("PathFind::" name)
#define PROFILE_SPIRE(name) ProfileScope profiler##__LINE__("Spire::" name)
#define PROFILE_CAMERA(name) ProfileScope profiler##__LINE__("Camera::" name)
#define PROFILE_OBSTACLE(name) ProfileScope profiler##__LINE__("Obstacle::" name)

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
