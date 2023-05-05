# Philosophers :

- ***The Dining Philosopher’s Problem***
    
    ***The Dining Philosopher's Problem is a classic synchronization problem in computer science that illustrates the challenges of coordinating multiple processes that compete for a limited set of resources.***
    
    ***In this problem, there are five philosophers sitting around a circular table, each with a plate of spaghetti and a fork on either side of the plate. The philosophers alternate between thinking and eating. In order to eat, a philosopher must have both forks. However, there are only five forks, one between each pair of adjacent philosophers.***
    
    ***The challenge is to design a solution in which each philosopher can eat without getting into a deadlock or starvation or a situation where all philosophers are waiting indefinitely for a fork.***
    
    *i**n anther way :*** 
    
    ***The Dining Philosophers problem is a classic OS problem that’s usually stated in very non-OS terms:
    There are N philosophers sitting around a circular table eating spaghetti and discussing philosophy. The problem is that each philosopher needs 2 forks to eat, and there are only N forks, one
    between each 2 philosophers. Design an algorithm that the philosophers can follow that
    insures that none starves as long as each philosopher***
    
    ***Deadlock*** : is when all the philosophers hold one fork at the same time and wait for the other      fork, waiting forever for an event that never comes. 
    
    ***Starvation :***  literally means death from not being able to eat ***.***
    

*The operating system uses the concept of  “ **Concurrent Programming “** to meet its users expectations. If we had to wait for a song to finish to be able to open our browser, or if we had to restart the computer to kill a program caught in an infinite loop, we’d die of frustration!*

*There are three ways to implement concurrency in our programs:  [processes](https://www.notion.so/Process-5489eb2fa3234436838be5c8933e078e) , threads,  and multiplexing. Let’s concentrate on threads that we should use in our project .*

- **What is a Thread**
    
    In the simplest terms, a thread is a way for a computer program to do multiple things at the same time.
    
    let's say you have a program that needs to download a large file from the internet and also needs to update the user interface to display progress. Without threads, the program would have to wait for the file to finish downloading before it could update the user interface. However, with threads, the program could download the file in one thread while updating the user interface in another thread, allowing both tasks to be performed simultaneously.
    
    Threads are used in many different types of programs, from simple desktop applications to complex server systems. They are a fundamental concept in modern computer programming and are used to improve the performance and responsiveness of software applications.
    
    A thread is a lightweight, independent unit of execution that runs within a process. A process is a program that is running on a computer, and it can have one or more threads. Each thread runs concurrently with the other threads in the process, meaning they can execute instructions simultaneously.
    
    Threads can be created and managed by the operating system or by the programming language itself.
    
    Overall, threads are a powerful tool for building complex, concurrent software systems. They allow multiple tasks to be performed simultaneously, improving the performance and responsiveness of the application. However, the use of threads also introduces new challenges, such as resource sharing and synchronization, that must be carefully managed to avoid issues such as race conditions and deadlocks.
    
    ***race conditions  :***
    
    In computing, a race condition occurs when two or more processes or programs are trying to access a shared resource (such as memory or a file) at the same time, and the outcome of the program depends on the order in which these processes are executed.
    
    Imagine you have two people trying to withdraw money from the same bank account at the same time. If the bank doesn't have a system in place to prevent multiple withdrawals, both people could potentially withdraw more money than is actually in the account, because the bank's system can't keep track of the account balance properly.
    
    In this example, the problem arises because there is a shared resource (the bank account ) that multiple processes (the two people) are trying to access simultaneously, and the system doesn't have proper safeguards in place to prevent conflicts.
    
    In the world of programming, race conditions can cause all sorts of issues, from security vulnerabilities to crashing programs. That's why programmers spend a lot of time trying to prevent race conditions from happening in their code, by using techniques like locking, synchronization, and atomic operations.
    
    <aside>
    ⛔ ***Your program must not have any data races.***
    
    </aside>
    
    ***We have this warning in the subject. What is the difference between a race***      
    
                                    ***condition and a data race?”***
    
    <aside>
    💡 ***A race condition*** occurs when two or more processes or threads are trying to access a shared resource (such as memory or a file) at the same time, and the outcome of the program depends on the order in which these processes are executed. In other words, a race condition occurs when the behavior of a program depends on the timing of events.
    
    ***A data race,*** on the other hand, is a specific type of race condition that occurs when two or more threads access a shared variable simultaneously, and at least one of the accesses is a write. In a data race, the final value of the variable depends on the order in which the threads access it, and this can lead to unpredictable behavior.
    
    To put it simply, a data race is a type of race condition that specifically involves shared data being accessed by multiple threads at the same time.
    
    In programming, it's important to avoid both race conditions and data races, as they can lead to bugs, crashes, and security vulnerabilities. Programmers use a variety of techniques to prevent these issues, such as using locks and synchronization primitives to control access to shared resources.
    
    </aside>
    
- ***What is a Mutex?***
    
    a mutex (short for "mutual exclusion") is a technique used to prevent multiple threads (i.e. sequences of instructions) from accessing the same resource at the same time.
    
    Imagine you have a group of people trying to use a single bathroom. If there were no rules in place, it's possible that two or more people might try to use the bathroom at the same time, leading to conflicts and chaos. To prevent this, you might establish a rule that only one person can use the bathroom at a time, and others must wait their turn. A mutex is like that rule - it ensures that only one thread can access a resource (like a piece of memory or a file) at a time, preventing conflicts and errors that can arise from simultaneous access.
    
    For example, suppose two threads in a program both want to write to the same file at the same time. Without a mutex, it's possible that they could both try to write to the file at the same time, causing the data to become corrupted or lost. By using a mutex, only one thread can access the file at a time, ensuring that the data is written correctly.
    
    <aside>
    ✅ Mutexes can help solve problems related to race conditions and data races
    
    Mutexes are a synchronization technique that allows only one thread to access a shared resource at a time. When a thread wants to access a shared resource, it must first acquire a mutex lock. If another thread has already acquired the lock, the requesting thread will wait until the lock is released. Once the thread has finished accessing the resource, it releases the lock so that other threads can access it.
    
    By using mutexes to synchronize access to shared resources, programmers can prevent data races and race conditions that might occur if multiple threads try to access the same resource at the same time.
    
    However, using mutexes effectively can be tricky. If a programmer uses mutexes incorrectly, it can lead to deadlocks, livelocks, and other synchronization problems that can be difficult to debug.
    
    Other synchronization techniques, such as semaphores, condition variables, and atomic operations, can also be used to solve problems related to race conditions and data races. The choice of synchronization technique depends on the specific requirements of the program and the resources being shared.
    
    </aside>
    
- ***POSIX Threads (also known as Pthreads)***
    
    
    *The standard interface in C to manipulate threads is POSIX with its **<pthread.h>** library. It contains around sixty functions to create and join threads, as well as to manage their shared memory. We will only study a fraction of these in this article. In order to compile a program using this library, we can’t forget to link it with `-pthread`:*
    
    ```bash
    gcc -pthread program.c
    ```
    
    - ***The pthread_create()*** :
        
        ```c
        int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                                  void *(*start_routine)(void*), void *arg);
        ```
        
        > **Description:**
        > 
        
        > ***The pthread_create()*** function creates a new thread and starts executing the function pointed to by start_routine, passing it the argument arg. The new thread starts executing as soon as it is created, and runs concurrently with the calling thread.
        > 
        
        > The thread ID of the newly created thread is returned in the variable pointed to by thread. This ID can be used to refer to the thread in other pthreads functions.
        > 
        
        > The attr argument is a pointer to a pthread_attr_t structure that contains attributes for the new thread, such as its stack size and scheduling policy. If this argument is NULL, default attributes are used.
        > 
        
        > The start_routine argument is a pointer to the function that the new thread will execute. This function should have a void* return type and take a void* argument. The argument passed to this function is the value of arg.
        > 
        
        > **Return Value:**
        > 
        
        > On success, pthread_create() returns 0. On failure, it returns an error code indicating the cause of the error.
        > 
        
        > **Errors:**
        > 
        
        > Possible errors returned by pthread_create() include:
        > 
        
        > EAGAIN: The system lacks the resources to create another thread.
        > 
        
        > EINVAL: The value specified in attr is invalid.
        > 
        
        > EPERM: The caller does not have the privilege to set the scheduling policy specified in attr.
        > 
        
    - ***The*** **pthread_detach ():**
        
        ```c
        int pthread_detach(pthread_t thread);
        ```
        
        > **Description:**
        > 
        
        > ***The pthread_detach() :***  function marks the thread specified by the thread argument as detached. Once a thread has been detached, its resources will be automatically released when it terminates, instead of being held for later retrieval by another thread calling pthread_join().
        > 
        
        > **Return Value:**
        > 
        
        > On success, pthread_detach() returns 0. On failure, it returns an error code indicating the cause of the error.
        > 
        
        > **Errors:**
        > 
        
        > Possible errors returned by pthread_detach() include:
        > 
        
        > ESRCH: The specified thread does not exist.
        > 
        
    - ***The pthread_join() :***
        
        ```c
        int pthread_join(pthread_t thread, void **retval);
        ```
        
        > ***Description:***
        > 
        
        > *The pthread_join() function waits for the thread specified by the thread argument to terminate. If the thread has already terminated, pthread_join() returns immediately. When the thread terminates, its exit status can be retrieved using the retval argument.*
        > 
        
        > ***Return Value:***
        > 
        
        > *On success, pthread_join() returns 0. On failure, it returns an error code indicating the cause of the error.*
        > 
        
        > ***Errors:***
        > 
        
        > *Possible errors returned by pthread_join() include:*
        > 
        
        > *ESRCH: The specified thread does not exist.*
        > 
        
        > *EINVAL: The thread is not a joinable thread.*
        > 
        
    - ***The pthread_mutex_init() :***
        
        ```c
        int pthread_mutex_init(pthread_mutex_t *mutex, 
        														const pthread_mutexattr_t *attr);
        ```
        
        > **Description:**
        > 
        
        > The pthread_mutex_init() function initializes a mutex object specified by the mutex argument. The mutex can be used to protect shared resources from concurrent access by multiple threads. The attr argument is a pointer to a pthread_mutexattr_t structure that contains attributes for the mutex, such as its type.
        > 
        
        > **Return Value:**
        > 
        
        > On success, pthread_mutex_init() returns 0. On failure, it returns an error code indicating the cause of the error.
        > 
        
        > **Errors:**
        > 
        
        > Possible errors returned by pthread_mutex_init() include:
        > 
        
        > EINVAL: The value specified in attr is invalid.
        > 
        
        > EAGAIN: The system lacked the resources to create the mutex.
        > 
        
    - ***The pthread_mutex_destroy() :***
        
        ```c
        int pthread_mutex_destroy(pthread_mutex_t *mutex);
        ```
        
        > **Description:**
        > 
        
        > The pthread_mutex_destroy() function destroys a mutex object specified by the mutex argument. The mutex object must be unlocked and not in use by any threads when pthread_mutex_destroy() is called.
        > 
        
        > **Return Value:**
        > 
        
        > On success, pthread_mutex_destroy() returns 0. On failure, it returns an error code indicating the cause of the error.
        > 
        
        > **Errors:**
        > 
        
        > Possible errors returned by pthread_mutex_destroy() include:
        > 
        
        > EINVAL: The mutex is invalid.
        > 
        
        > EBUSY: The mutex is currently locked by a thread.
        > 
        
    - ***The pthread_mutex_lock() :***
        
        ```c
        int pthread_mutex_lock(pthread_mutex_t *mutex);
        ```
        
        > **Description:**
        > 
        
        > The pthread_mutex_lock() function locks a mutex object specified by the mutex argument. If the mutex is already locked by another thread, the calling thread will block until the mutex becomes available.
        > 
        
        > **Return Value:**
        > 
        
        > On success, pthread_mutex_lock() returns 0. On failure, it returns an error code indicating the cause of the error.
        > 
        
        > **Errors:**
        > 
        
        > Possible errors returned by pthread_mutex_lock() include:
        > 
        
        > EINVAL: The mutex is invalid.
        > 
        
        > EAGAIN: The maximum number of recursive locks for the mutex has been exceeded.
        > 
        
        > EDEADLK: The calling thread already owns the mutex.
        > 
        
    - ***The pthread_mutex_unlock() :***
        
        ```c
        int pthread_mutex_unlock(pthread_mutex_t *mutex);
        ```
        
        > **Description:**
        > 
        
        > The pthread_mutex_unlock() function unlocks a mutex object specified by the mutex argument. If the mutex is already unlocked, the behavior is undefined.
        > 
        
        > **Return Value:**
        > 
        
        > On success, pthread_mutex_unlock() returns 0. On failure, it returns an error code indicating the cause of the error.
        > 
        
        > **Errors:**
        > 
        
        > Possible errors returned by pthread_mutex_unlock() include:
        > 
        
        > EINVAL: The mutex is invalid.
        > 
        
        > EPERM: The calling thread does not own the mutex.
        > 
        
    
- ***External functions:***
    - $***`usleep :`***$
        
        ```c
        unsigned int usleep(unsigned int microseconds);
        ```
        
        > **Description:**
        > 
        
        > The **`usleep()`** function is used to suspend the execution of the calling thread for a specified number of microseconds. The argument **`usec`** specifies the number of microseconds to suspend execution.
        > 
        
        > **Return Value:**
        > 
        
        > On success, **`usleep()`** returns 0. On failure, it returns -1 and sets **`errno`** to indicate the cause of the error.
        > 
        
        > **Errors:**
        > 
        
        > Possible errors returned by **`usleep()`** include:
        > 
        
        > **`EINTR`**: The sleep was interrupted by a signal.
        > 
        
        > **`EINVAL`**: The value of **`usec`** is negative.
        > 
        
    - *`gettimeofday :`*
        
        ```c
        int gettimeofday(struct timeval *tv, struct timezone *tz);
        ```
        
        > **Description:**
        > 
        
        > The **`gettimeofday()`** function is used to get the current time of day in seconds and microseconds since the Epoch (00:00:00 UTC, January 1, 1970). The time is returned in the **`tv`** argument, which is a **`struct timeval`** containing two fields: **`tv_sec`** (seconds since the Epoch) and **`tv_usec`** (microseconds within the second). The **`tz`** argument is ignored on most systems and should be set to NULL.
        > 
        
        > **Return Value:**
        > 
        
        > On success, **`gettimeofday()`** returns 0. On failure, it returns -1 and sets **`errno`** to indicate the cause of the error.
        > 
        
        > **Errors:**
        > 
        
        > Possible errors returned by **`gettimeofday()`** include:
        > 
        
        > **`EFAULT`**: The **`tv`** or **`tz`** argument points to an invalid address.
        > 
        
        > **`EINVAL`**: The **`tv`** or **`tz`** argument is NULL.
        >