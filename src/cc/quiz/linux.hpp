#ifndef quiz_linux_hpp
#define quiz_linux_hpp

#include <initializer_list>

#include "quiz.hpp"

namespace study {

  const std::initializer_list<Item> linux {
    { "Describe the Linux process states.",
        R"(
TASK_RUNNING

  Process is either executing on a CPU or waiting to be run.

TASK_INTERRUPTIBLE

  Process is sleeping until some condition becomes true.  A hardware interrupt,
  the release of a resource that the process is waiting for, or receipt of a
  signal are all events that can wake up the process and put it into the
  TASK_RUNNING state.

TASK_UNINTERRUPTIBLE

  Same as TASK_INTERRUPTIBLE except that receipt of a signal does not wake the
  process up.

TASK_STOPPED

  Process is stopped (suspended).  Processes go into this state after receiving
  a SIGSTOP, SIGTSTP, SIGTTIN, or SIGTTOU signal.

TASK_TRACED

  Process execution has been stopped by a debugger.

EXIT_ZOMBIE

  Process has exited but the parent process has yet to call wait4 or waitpid.

EXIT_DEAD

  Final process state.  Process has exited and wait4 or waitpid has been called.
)" },
    { "Describe the TASK_UNINTERRUPTIBLE process state in detail.",
        R"(
Processes are in this state when they are sleeping, waiting for an event such as
a hardware interrupt or a resource to become available for which they are
waiting.  Unlike the TASK_INTERRUPTIBLE state, processes in this state are not
awakened upon delivery of a signal.

This process state is seldom used.  It is only used in situations in which a
process must wait until a given event occurs without being interrupted.  For
instance, this state may be used when a process opens a device file and the
corresponding device driver starts probing for a corresponding hardware device.
The device driver must not be interrupted until the probing is complete, or the
hardware device could be left in an unpredictable state.
)" },
    { "What is /dev/loopN ?",
        R"(
/dev/loop[0..7] are virtual block device which can be used to mount a filesystem
stored in a regular file.
)"},
    { "Name and describe all of the process resource limits.",
        R"(
RLIMIT_AS

  The maximum size of process address space, in bytes.

RLIMIT_CORE

  The maximum core dump file size, in bytes.

RLIMIT_CPU

  The maximum CPU time for the process, in seconds.


)"},
  };

}

#endif // quiz_linux_hpp
