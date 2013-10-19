//*****************************************************************************
// Copyright 1986-2010 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
// Germany. All rights reserved.
//*****************************************************************************
/// \file       mi/base/lock.h
/// \brief      Locks
///
//*****************************************************************************

#ifndef MI_BASE_LOCK_H
#define MI_BASE_LOCK_H

#include <mi/base/config.h>

#ifndef MI_PLATFORM_WINDOWS
#include <pthread.h>
#else
#include "miwindows.h"
#endif

namespace mi {

namespace base {
    
// On some operating systems the name is different.
#ifndef PTHREAD_MUTEX_ERRORCHECK
#define PTHREAD_MUTEX_ERRORCHECK PTHREAD_MUTEX_ERRORCHECK_NP
#endif

/// Lock class implementing a critical region that only one thread can
/// enter at a time.
class Lock
{

  public:

    /// Constructor.
#ifndef MI_PLATFORM_WINDOWS
    inline Lock() { pthread_mutex_init(&m_mutex,NULL); };
#else
    inline Lock() { InitializeCriticalSection(&m_critical_section); };
#endif

    /// Destructor.
#ifndef MI_PLATFORM_WINDOWS
    inline ~Lock() { pthread_mutex_destroy(&m_mutex); };
#else
    inline ~Lock() { DeleteCriticalSection(&m_critical_section); };
#endif

    /// Utility class to aquire a lock that is released on block exit.
    class Block {

      private:

        /// The mutex associated to this lock.
        Lock *m_mutex;

      public:

        /// Constructor.
        /// \param lock A NULL pointer arg means just create, don't set.
        explicit Block(Lock *lock = 0);

        /// Destructor.
        ~Block();

        /// Set a lock that was constructed using a NULL pointer.
        /// \param lock lock to use
        void set(Lock *lock);

        /// Release lock.
        void release();
    };

protected:

    /// Lock the lock.
#ifndef MI_PLATFORM_WINDOWS
    void lock() { pthread_mutex_lock(&m_mutex); };
#else
    void lock() { EnterCriticalSection(&m_critical_section); };
#endif

    /// Unlock the lock.
#ifndef MI_PLATFORM_WINDOWS
    void unlock() { pthread_mutex_unlock(&m_mutex); };
#else
    void unlock() { LeaveCriticalSection(&m_critical_section); };
#endif

private:
    /// Copying a lock is a fatal error which is not so easy to detect. So make
    /// this non-copyable.
    Lock(Lock const &);

    /// Assigning to a lock is a fatal error which is not so easy to detect. So make
    /// this non-assignable.
    Lock& operator= (Lock const &);

    /// The pthreads mutex implementing the Lock.
#ifndef MI_PLATFORM_WINDOWS
    pthread_mutex_t m_mutex;
#else
    CRITICAL_SECTION m_critical_section;
#endif
};

// The implementation of Lock::Block is the same on all platforms.

// Constructor. The argument is allowed to be 0 so a lock can be created
// without setting it. Using the set() function, the lock can then be set
// in a different scope without losing the benefit of implict unlocks when
// the outer scope is left.
inline Lock::Block::Block(
    Lock *lock)                        // lock this lock
{
    m_mutex = lock;
    if (lock != NULL)
        m_mutex->lock();
}

// Destructor.
inline Lock::Block::~Block()
{
    if (m_mutex)
        m_mutex->unlock();
}

// Set a lock previously created but not set (see constructor).
inline void Lock::Block::set(
     Lock *lock)                // lock this lock
{
    if (m_mutex != NULL)
        m_mutex->unlock();

    m_mutex = lock;
    if (m_mutex != NULL)
        m_mutex->lock();
}

// Release lock.
inline void Lock::Block::release()
{
    m_mutex->unlock();
    m_mutex = 0;
}

}            // namespace base
}            // namespace mi

#endif       // ifdef MI_BASE_LOCK_H
