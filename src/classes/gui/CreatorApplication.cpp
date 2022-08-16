#include "../../../include/classes/gui/CreatorApplication.h"

CreatorApplication::CreatorApplication(const WEnvironment &env, shared_ptr<Character> character) : WApplication(env), _character(character)
{
}

CreatorApplication::~CreatorApplication()
{
    for (auto &&thread : _threads)
    {
        thread.join();
    }
}
