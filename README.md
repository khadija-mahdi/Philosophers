README.md
# Philosophers :

- ***The Dining Philosopher’s Problem***
    
      The Dining Philosopher's Problem is a classic synchronization problem in
      computer science that illustrates the challenges of coordinating multiple 
      processes that compete for a limited set of resources.
    
          In this problem:
             there are five philosophers sitting around a circular table, each with a plate of spaghetti 
             and a fork on either side of the plate. The philosophers alternate between thinking and eating.
             In order to eat, a philosopher must have both forks. However, there are only five forks, 
              one between each pair of adjacent philosophers.
   
        The challenge is to design a solution in which each philosopher can eat without getting into a deadlock 
        or starvation or a situation where all philosophers are waiting indefinitely for a fork.
    
         -in anther way :
    
         The Dining Philosophers problem is a classic OS problem that’s usually stated in very non-OS terms:
         There are N philosophers sitting around a circular table eating spaghetti and discussing philosophy.
         The problem is that each philosopher needs 2 forks to eat, and there are only N forks, one
        between each 2 philosophers. Design an algorithm that the philosophers can follow that
        insures that none starves as long as each philosopher
    
    -***Deadlock*** : is when all the philosophers hold one fork at the same time and wait for the other fork, waiting forever for an event that never comes. 
    
    -***Starvation :***  literally means death from not being able to eat ***.***
    

   -The operating system uses the concept of  “ Concurrent Programming “ to meet its users expectations.
    If we had to wait for a song to finish to be able to open our browser, or if we had to restart the computer
    to kill a program caught in an infinite loop, we’d die of frustration!*

  *There are three ways to implement concurrency in our programs:  [Process](https://github.com/khadija-mahdi/pipex/blob/master/pipex%20f3f377eedb644f1a805c6f479d7576c0/Process%205489eb2fa3234436838be5c8933e078e.md) , threads,  and multiplexing. Let’s concentrate on threads that we should use in our project .*

## Mandarory :

- **What is a Thread**
    
            In the simplest terms, a thread is a way for a computer program to do multiple things at the same time.
    
      let's say you have a program that needs to download a large file from the internet and also needs to 
      update the user interface to display progress. Without threads, the program would have to wait for 
      the file to finish downloading before it could update the user interface. However, with threads,
      the program could download the file in one thread while updating the user interface in another thread,
      allowing both tasks to be performed simultaneously.
    
        Threads are used in many different types of programs, from simple desktop applications to complex server systems.
        They are a fundamental concept in modern computer programming and are used to improve the performance and 
        responsiveness of software applications.
    
                A thread is a lightweight, independent unit of execution that runs within a process.
                A process is a program that is running on a computer, and it can have one or more threads. 
                Each thread runs concurrently with the other threads in the process, meaning they can execute 
                instructions simultaneously.
    
      Threads can be created and managed by the operating system or by the programming language itself.
    
      Overall, threads are a powerful tool for building complex, concurrent software systems. They allow 
      multiple tasks to be performed simultaneously, improving the performance and responsiveness of the application. 
      However, the use of threads also introduces new challenges, such as resource sharing and synchronization,
      that must be carefully managed to avoid issues such as race conditions and deadlocks.
    
    ***race conditions***  :
    
    In computing, a race condition occurs when two or more processes or programs are trying to access a shared resource (such as memory or a file) at the same time, and the outcome of the program depends on the order in which these processes are executed.
    
    Imagine you have two people trying to withdraw money from the same bank account at the same time. If the bank doesn't have a system in place to prevent multiple withdrawals, both people could potentially withdraw more money than is actually in the account, because the bank's system can't keep track of the account balance properly.
    
    In this example, the problem arises because there is a shared resource (the bank account ) that multiple processes (the two people) are trying to access simultaneously, and the system doesn't have proper safeguards in place to prevent conflicts.
    
    In the world of programming, race conditions can cause all sorts of issues, from security vulnerabilities to crashing programs. That's why programmers spend a lot of time trying to prevent race conditions from happening in their code, by using techniques like locking, synchronization, and atomic operations.
    
    ⛔ **Your program must not have any data races**
    
    ***We have this warning in the subject !!!! . What is the difference between a race condition and a data race?***  
 
   💡 ***A race condition :*** occurs when two or more processes or threads are trying to access a shared resource (such as memory or a file) at the same time, and the outcome of the program depends on the order in which these processes are executed. In other words, a race condition occurs when the behavior of a program depends on the timing of events.
    
    ***-A data race :*** on the other hand, is a specific type of race condition that occurs when two or more threads access a shared variable simultaneously, and at least one of the accesses is a write. In a data race, the final value of the variable depends on the order in which the threads access it, and this can lead to unpredictable behavior.
    
    To put it simply, a data race is a type of race condition that specifically involves shared data being accessed by multiple threads at the same time.
    
   In programming, it's important to avoid both race conditions and data races, as they can lead to bugs, crashes, and security vulnerabilities. Programmers use a variety of techniques to prevent these issues, such as using locks and synchronization primitives to control access to shared resources.
    
    
- ***What is a Mutex?***
    
      a mutex (short for "mutual exclusion") is a technique used to prevent multiple threads (i.e. sequences of
      instructions) from accessing the same resource at the same time.
    
      Imagine you have a group of people trying to use a single bathroom. If there were no rules in place, it's possible 
      that two or more people might try to use the bathroom at the same time, leading to conflicts and chaos. 
      To prevent this, you might establish a rule that only one person can use the bathroom at a time, and others 
      must wait their turn.
      
      A mutex is like that rule - it ensures that only one thread can access a resource (like a piece of memory 
      or a file) at a time, preventing conflicts and errors that can arise from simultaneous access.
    
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




## Bonus :

- ***What is semaphores***
    
    In the simplest terms, semaphores are like traffic signals for processes or threads in a computer program. They help control access to shared resources, like a printer or a file, so that multiple processes don't interfere with each other.
    
    Imagine a single-lane road with a traffic light. When a car wants to cross the road, it first checks the traffic light. If the light is green, the car can proceed. But if the light is red, the car has to wait until it turns green. Once the car has crossed, it signals to the traffic light that it has passed.
    
    Similarly, in a computer program, processes or threads need to check a semaphore before accessing a shared resource. If the semaphore allows access, they can proceed. But if the semaphore indicates that the resource is already in use, they have to wait until it becomes available. Once they're done using the resource, they signal to the semaphore that they are finished, allowing another process or thread to access it.
    
    So, semaphores act as control mechanisms, ensuring that processes or threads take turns using shared resources and avoid conflicts or race conditions.
    
    - *`differences in handling semaphores between processes and threads?`*
        
        
        `the handling of semaphores can differ between processes and threads. Here are some key differences:`
        
        1. `Ownership: In process-based concurrency models, such as those implemented using the fork system call, each process has its own copy of resources, including semaphores. When a process forks, the child process inherits a copy of the parent's semaphore values. Each process can operate on its own set of semaphores independently.`
        
        `On the other hand, in thread-based concurrency models, threads within the same process share the same memory space, including semaphores. Threads can access and manipulate the same set of semaphores directly, without the need for inter-process communication mechanisms.`
        
        1. `Synchronization: Processes typically use semaphores to synchronize activities across different processes. For example, a semaphore can be used to ensure that only one process accesses a shared resource at a time. Processes use functions like sem_init, sem_wait, and sem_post to initialize, wait for, and release semaphores, respectively.`
        
        `Threads, however, can use semaphores for synchronization within the same process. Threads can coordinate their activities, ensuring exclusive access to shared resources. The same functions (sem_init, sem_wait, sem_post) are used by threads to handle semaphores, but the behavior is different because they are operating within the same memory space.`
        
        1. `Resource Sharing: In process-based concurrency, processes typically need to use inter-process communication (IPC) mechanisms, such as shared memory or message passing, to share resources between different processes. Semaphores can be used as part of these IPC mechanisms to coordinate resource access.`
        
        `In thread-based concurrency, threads share the same memory space, so they can access shared resources directly. Semaphores are used to synchronize access to these shared resources, preventing race conditions and ensuring that only one thread accesses the resource at a time.`
        
        <aside>
        💡 It's important to note that the handling of semaphores and concurrency mechanisms may vary depending on the operating system and the libraries used for concurrency in C. The details provided above describe the general differences in handling semaphores between processes and threads in C, but specific implementations may have additional nuances or variations.
        
        </aside>
        
- ***What is the deferent between mutex and semaphore***
    
    Mutexes and Semaphores are both synchronization mechanisms used in concurrent programming to control access to shared resources. However, they differ in several ways:
    
    - A mutex is a binary semaphore, meaning it has only two states: locked and unlocked. A semaphore, on the other hand, can have multiple values.
    - A mutex is used to protect a single resource that can be accessed by only one thread at a time. A semaphore can protect multiple resources or a shared resource that can be accessed by multiple threads at the same time.
    - A mutex is used to enforce mutual exclusion, meaning that only one thread can access the protected resource at a time. A semaphore can be used for various synchronization purposes, including signaling, counting, and mutual exclusion.
    - A mutex can be unlocked only by the thread that locked it. A semaphore can be unlocked by any thread that holds a lock on it.
    - Mutexes are generally faster and simpler to implement than semaphores because they have only two states and are used for a specific purpose. Semaphores are more versatile but can be more complex to use correctly.
    
    Overall, mutexes are a good choice when you need to protect a single resource that can be accessed by only one thread at a time, while semaphores are more appropriate for situations where you need to coordinate access to multiple resources or manage concurrent access to a shared resource.
    
- ***POSIX Semaphores***
    
    POSIX Semaphores are a synchronization primitive used in concurrent programming to control access to shared resources. They are similar to mutexes, but are more versatile because they can have multiple values.
    
    To use POSIX Semaphores in a C program, you need to include the library  **$semaphore.h$**  and link the program with **$-lrt$**.
    
    The basic functions for working with semaphores are:
    
    - ***sem_open() :***
        
        ```c
        sem_t *sem_open(const char *name, int oflag, mode_t mode,
        		unsigned int value);
        ```
        
        > **Description:**
        > 
        
        > ***The sem_open()*** : function in C is used to create or open a named semaphore. It allows processes to share synchronization primitives even if they are not related by inheritance, such as in the case of forked processes.
        > 
        
        > **Parameters:**
        > 
        
        > *name*: The name of the semaphore. This name should start with a slash ("/") and have a maximum length defined by SEM_NAME_MAX.
        > 
        
        > oflag: Flags to specify the behavior of the semaphore. It can be a combination of O_CREAT, O_EXCL, O_RDWR, and O_TRUNC. Use O_CREAT to create a new semaphore if it doesn't exist, and O_EXCL with O_CREAT to ensure the semaphore is created exclusively. O_RDWR allows both reading and writing access to the semaphore. O_TRUNC truncates the size of the semaphore if it already exists.
        > 
        
        > mode: The access permissions for the semaphore, used when creating a new semaphore. It is specified using the same format as the chmod function.
        > 
        
        > value: The initial value to be assigned to the semaphore. This value should be greater than or equal to zero.
        > 
        
        > **Return Value:**
        > 
        
        > If successful, sem_open returns a pointer to the named semaphore (of type sem_t*). This pointer can be used in subsequent semaphore operations.
        > 
        
        > On error, sem_open returns SEM_FAILED (a macro defined in semaphore.h).
        > 
        
        <aside>
        💡
        
        </aside>
        
    - ***sem_close() :***
        
        ```c
        int sem_close(sem_t *sem);
        ```
        
        > **Description:**
        > 
        
        > ***The sem_close():*** function in C is used to close a named semaphore. It releases any system resources associated with the semaphore
        > 
        
        > ***Parameter:***
        > 
        
        > sem: A pointer to the named semaphore (of type sem_t*) that was obtained from a previous call to sem_open.
        > 
        
        > ***Return Value:***
        > 
        
        > If successful, sem_close returns 0.
        > 
        
        > On error, sem_close returns -1, and an error code is set in the errno variable.
        > 
        
    - ***sem_post() :***
        
        ```c
        int sem_post(sem_t *sem);
        ```
        
        > **Description:**
        > 
        
        > **The sem_post():** function in C is used to increment the value of a semaphore. It is typically used to indicate that a resource is available or to signal the completion of a task
        > 
        
        > ***Parameter:***
        > 
        
        > sem: A pointer to the semaphore (of type sem_t*) on which the operation is performed. The semaphore must have been previously initialized using sem_init or obtained from a call to sem_open.
        > 
        
        > ***Return Value:***
        > 
        
        > *If successful, sem_post returns 0.*
        > 
        
        > *On error, sem_post returns -1, and an error code is set in the errno variable.*
        > 
    - ***sem_wait() :***
        
        ```c
        int sem_wait(sem_t *sem);
        ```
        
        > **Description:**
        > 
        
        > **The sem_wait():** function in C is used to decrement the value of a semaphore. It is typically used to request access to a shared resource and to wait if the resource is currently unavailable.
        > 
        
        > ***Parameter:***
        > 
        
        > sem: A pointer to the semaphore (of type sem_t*) on which the operation is performed. The semaphore must have been previously initialized using sem_init or obtained from a call to sem_open.
        > 
        
        > ***Return Value:***
        > 
        
        > If successful, sem_wait returns 0.
        > 
        
        > On error, sem_wait returns -1, and an error code is set in the errno variable.
        > 
    - ***sem_unlink() :***
        
        ```c
        int sem_unlink(const char *name);
        ```
        
        > **Description:**
        > 
        
        > **The sem_unlink():** function in C is used to remove a named semaphore from the system. It allows you to unlink and delete the named semaphore so that it can no longer be accessed by other processes or threads
        > 
        
        > Parameter:
        > 
        
        > name: The name of the semaphore to be unlinked. This should be the same name that was used when creating or opening the semaphore.
        > 
        
        > Return Value:
        > 
        
        > If successful, sem_unlink returns 0.
        > 
        
        > On error, sem_unlink returns -1, and an error code is set in the errno variable.
        > 
    
    - ***how the operating system manages semaphores and CPU scheduling :***
        
        
        *The POSIX Semaphores are managed by the operating system in a similar way as regular semaphores. The operating system keeps track of the current value of each semaphore and the processes or threads that are waiting on it. When a semaphore is posted using the sem_post() function, the operating system increments its value and wakes up one of the waiting processes or threads, allowing it to proceed. When a semaphore is waited on using the sem_wait() function, the operating system decrements its value. If the value is zero, the process or thread is blocked until the semaphore is posted.*
        
        *In addition to the basic semaphore functions, the POSIX Semaphores API also includes functions for creating and opening named semaphores using the sem_open() function, closing named semaphores using the sem_close() function, and unlinking named semaphores using the sem_unlink() function.*
        
        *CPU scheduling with POSIX Semaphores is similar to regular CPU scheduling. The scheduler maintains a list of all the processes or threads that are ready to run, and selects the next one to run based on the scheduling algorithm. Once a process or thread has used up its time slice or has blocked on a semaphore or I/O operation, the scheduler selects the next process or thread to run.*
        
        *Overall, the operating system manages POSIX Semaphores and CPU scheduling in a similar way as regular semaphores and CPU scheduling, but with additional functions for creating and managing named semaphores.*
