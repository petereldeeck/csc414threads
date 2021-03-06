# CSC414Threads

# Using Git and Github

1. Click on clone or download button then click on the right of the link to copy it
1. Open GitHub desktop and log in using your username/password
1. Select File->clone repository
1. Select your github repository and set the local directory
At this point you have a local copy of the files. Working with the files
depends on which IDE you use so it is up to you to import the files into an IDE.
Below i give instructions for Visual Studio C++ 2019 community edition, it is free so
you can save yourself the hassle and use it.

1. Open visual studio and select continue without code (bottom right)
1. Select File->New->Project from existing code. In the project file location select the directory
where you have cloned the github repository.
1. Type a project name then next
1. Project type select console application

Now you can make the necessary changes to the code (see below). When you are done use
github Desktop to commit your work. A commit saves a snapshot of the work you have done 
so far so it doesn't hurt to commit often. When you are satisfied with your work submit
it by  PUSHing the changes back to the server.

# Project

The project is in three parts. Each part has a few questions that you have to answer
and an implementation you have to code. Write the answer in the __place indicated in this file__.

## Part 1
Read the code in example1.cpp. It creates four threads: two to run the function doit
and the other two to run a function object. The four threads run concurrently with two
threads run doit() incrementing/decrementing the global variable _y_ and two threads
run function objects incrementing/decrementing the local variable _x_. From the output
you can see that there is data corruption since both _x_ and _y_ should be 0. To fix
this problem uncomment the line with ``` #define SYNC ```.
### Question
  
We learned that a mutex _m_ is locked with a wait(m), (in C++ it is ``` m.lock() ```) and
unlocked with signal(m) (in C++ it is ``` m.unlock() ```).
How is this done in example.cpp? What is a ``` lock_guard ``` ?. Write your answer here
by editing this file (no more that a few lines)

#### Answer

 Here in example.cpp we used lock_guard instead of lock and unlock. A lock-guard is an item that deals with a mutex object by keeping it blocked all the time.
 The purpose of lock_guard is simply to make locking and unlocking the mutex simpler. For instance, on the off chance that you manually lock/unlock, yet your method tosses an exception some place in the middle, 
it will never come to the unlock statement.Therefore, doing it the manual way you need to ensure that the mutex is constantly unlocked. Then again, the lock_guard object gets destroyed automatically at whatever point we go out of scope of the method

## Part 2

### Question

What is the difference between ``` std::mutex ``` and ``` std::shared_mutex ```?
Write your answer below
#### Answer
A Mutex is a mutually exclusive flag. It goes about as a guard to a piece of code permitting one thread in and blocking access to all others. 
This guarantees the code being controlled may be hit by only one thread at a time. However, The shared_mutex class is a synchronization crude that can be utilized to shield shared
information (data) from being all accessed to by many threads at the same time. Also, a shared_mutex has two degrees of access: 
Shared - many threads can share ownership of the same mutex. 
Exclusive - just one thread can own the mutex.


### Implementation

Implement the readers writers solution we discussed in class. Use **readersWriters.cpp** 
as a start. Do not **remove** any code just **add** synchronization code to fix the access
problem. As you might have guessed you need to use ``` std::shared_mutex ``` here.

## Part 3

### Question

Describe condition variables in C++ and how they used (a few lines)

#### Answer

A condition variable is an item ready to block the thread until notified or demanded to continue. It utilizes a unique_lock (over a mutex) 
to lock the thread when one of its wait methods is called.The thread stays blocked then it will be woken by another thread that calls a notify function (for example: notify all)
 on the equivalent condition_variable object.

### Implementation 

Read the file **waitForOthers.cpp**. We have multiple threads running the **same** code
in function ``` void thread(std::string s) ```. Each thread runs through two parts: 
the first it prints "phase 1" and in the second it prints its name followed by 'done'.
Without synchronization these two phases can be interleaved among all threads as you 
can see by running this program. Use condition variables and mutex to synchronize theses 
threads as follows: no thread can start phase two until all threads have completed phase 1.
In terms of output, since we run 10  threads you must guarantee that there are 10 'phase 1' printouts before any 'done' printout.
The order in which threads print 'phase one' or 'done' does not matter as long as all print
'phase 1' before **any** of them prints 'done'.



