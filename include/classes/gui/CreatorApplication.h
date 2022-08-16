#ifndef CREATORAPPLICATION_H
#define CREATORAPPLICATION_H

#include <Wt/WApplication.h>
#include <memory>
#include <vector>
#include <thread>

#include "../Character.h"

using namespace std;
using namespace Wt;

class CreatorApplication : public WApplication
{
private:
    // Member Variables
    /**
     * @brief Holds the threads that set character values.
     *
     * Holds all the threads that set the character values that aren't accessed later in the creation
     * progress and are only needed once the process is over and the character is displayed.
     */
    vector<thread> _threads;
    /**
     * @brief Stores a pointer to the character object we are gonna change.
     *
     */
    shared_ptr<Character> _character;

    // Member Functions
    int GetNumber(string text);

public:
    // Constructors and Destructors
    /**
     * @brief Disables creation of a Creator Application if the required args aren't supplied.
     *
     */
    CreatorApplication() = delete;
    /**
     * @brief Construct a new Creator Application object with a shared pointer to the character.
     *
     * Creates a new Creator Application object with a shared pointer to the character we will edit
     * in the webapp
     *
     * @param env
     */
    CreatorApplication(const WEnvironment &env, shared_ptr<Character> character);
    /**
     * @brief Joins any remaining threads in \ref CreatorApplication::_threads "_threads" before destruction.
     *
     */
    ~CreatorApplication();
    /**
     * @brief Disables the Creator Application copy constuctor
     *
     * Explicitly deletes the copy constructor of the Creator Application class to ensure threads are kept safe and aren't copied.
     */
    CreatorApplication(const CreatorApplication &) = delete;
    /**
     * @brief Disables the Creator Application copy assignment operator.
     *
     * Explicitly deletes the copy assignement operator of the Creator Application class to ensure threads are kept safe and aren't copied.
     */
    CreatorApplication &operator=(const CreatorApplication &) = delete;
    /**
     * @brief Disables the Creator Application move constuctor
     *
     * Explicitly deletes the move constructor of the Creator Application class to ensure threads are kept safe and aren't copied.
     */
    CreatorApplication(CreatorApplication &&) = delete;
    /**
     * @brief Disables the Creator Application move assignment operator.
     *
     * Explicitly deletes the move assignement operator of the Creator Application class to ensure threads are kept safe and aren't copied.
     */
    CreatorApplication &operator=(CreatorApplication &&) = delete;
};
#endif