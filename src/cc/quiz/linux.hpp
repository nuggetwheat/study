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
  The maximum size of the process’s virtual memory (address  space)  in  bytes.
  This  limit  affects  calls to brk(2), mmap(2) and mremap(2), which fail with
  the error ENOMEM upon exceeding this limit.  Also automatic  stack  expansion
  will  fail  (and  generate  a  SIGSEGV that kills the process if no alternate
  stack has been made available via sigaltstack(2)).   Since  the  value  is  a
  long,  on  machines with a 32-bit long either this limit is at most 2 GiB, or
  this resource is unlimited.

RLIMIT_CORE
  Maximum size of core file.  When 0 no core dump files are created.  When non-
  zero, larger dumps are truncated to this size.

RLIMIT_CPU
  CPU  time  limit  in seconds.  When the process reaches the soft limit, it is
  sent a SIGXCPU signal.  The default action for this signal  is  to  terminate
  the  process.   However, the signal can be caught, and the handler can return
  control to the main program.  If the process continues to consume  CPU  time,
  it  will  be sent SIGXCPU once per second until the hard limit is reached, at
  which time it is sent  SIGKILL.   (This  latter  point  describes  Linux  2.2
  through 2.6 behavior.  Implementations vary in how they treat processes which
  continue to consume CPU time after reaching the soft limit.  Portable  appli-
  cations  that need to catch this signal should perform an orderly termination
  upon first receipt of SIGXCPU.)

RLIMIT_DATA
  The maximum size of the process’s data segment (initialized data,  uninitial-
  ized  data, and heap).  This limit affects calls to brk(2) and sbrk(2), which
  fail with the error ENOMEM upon encountering the soft limit of this resource.

RLIMIT_FSIZE
  The  maximum size of files that the process may create.  Attempts to extend a
  file beyond this limit result in delivery of a SIGXFSZ signal.   By  default,
  this  signal  terminates  a  process,  but  a  process  can catch this signal
  instead, in which case the relevant system call (e.g., write(2), truncate(2))
  fails with the error EFBIG.

RLIMIT_LOCKS (Early Linux 2.4 only)
  A  limit  on  the  combined number of flock(2) locks and fcntl(2) leases that
  this process may establish.

RLIMIT_MEMLOCK
  The maximum number of bytes of memory that may be locked into RAM.  In effect
  this  limit  is rounded down to the nearest multiple of the system page size.
  This limit affects mlock(2) and mlockall(2) and the mmap(2) MAP_LOCKED opera-
  tion.   Since  Linux  2.6.9 it also affects the shmctl(2) SHM_LOCK operation,
  where it sets a maximum on the total bytes in  shared  memory  segments  (see
  shmget(2))  that  may  be  locked by the real user ID of the calling process.
  The shmctl(2) SHM_LOCK locks are accounted for separately from  the  per-pro-
  cess   memory   locks  established  by  mlock(2),  mlockall(2),  and  mmap(2)
  MAP_LOCKED; a process can lock bytes up to this limit in each  of  these  two
  categories.   In Linux kernels before 2.6.9, this limit controlled the amount
  of memory that could be locked by a privileged process.  Since  Linux  2.6.9,
  no  limits  are  placed on the amount of memory that a privileged process may
  lock, and this limit instead governs the amount of memory  that  an  unprivi-
  leged process may lock.

RLIMIT_MSGQUEUE (Since Linux 2.6.8)
  Specifies  the  limit  on the number of bytes that can be allocated for POSIX
  message queues for the real user ID of the calling process.   This  limit  is
  enforced  for  mq_open(3).   Each  message queue that the user creates counts
  (until it is removed) against this limit according to the formula:

      bytes = attr.mq_maxmsg * sizeof(struct msg_msg *) +
              attr.mq_maxmsg * attr.mq_msgsize

  where attr is the mq_attr structure  specified  as  the  fourth  argument  to
  mq_open(3).

  The  first  addend in the formula, which includes sizeof(struct msg_msg *) (4
  bytes on Linux/i386), ensures that the user cannot create an unlimited number
  of  zero-length messages (such messages nevertheless each consume some system
  memory for bookkeeping overhead).

RLIMIT_NICE (since Linux 2.6.12, but see BUGS below)
  Specifies a ceiling to which the process’s nice value  can  be  raised  using
  setpriority(2)  or  nice(2).  The actual ceiling for the nice value is calcu-
  lated as 20 - rlim_cur.  (This strangeness occurs  because  negative  numbers
  cannot  be specified as resource limit values, since they typically have spe-
  cial meanings.  For example, RLIM_INFINITY typically is the same as -1.)

RLIMIT_NOFILE
  Specifies a value one greater than the maximum file  descriptor  number  that
  can be opened by this process.  Attempts (open(2), pipe(2), dup(2), etc.)  to
  exceed this limit yield the error  EMFILE.   (Historically,  this  limit  was
  named RLIMIT_OFILE on BSD.)

RLIMIT_NPROC
  The  maximum  number of processes (or, more precisely on Linux, threads) that
  can be created for the real user ID of the calling process.  Upon  encounter-
  ing this limit, fork(2) fails with the error EAGAIN.

RLIMIT_RSS
  Specifies  the  limit (in pages) of the process’s resident set (the number of
  virtual pages resident in RAM).  This limit only has effect in Linux 2.4.x, x
  < 30, and there only affects calls to madvise(2) specifying MADV_WILLNEED.

RLIMIT_RTPRIO (Since Linux 2.6.12, but see BUGS)
  Specifies  a  ceiling on the real-time priority that may be set for this pro-
  cess using sched_setscheduler(2) and sched_setparam(2).

RLIMIT_RTTIME (Since Linux 2.6.25)
  Specifies a limit on the amount of CPU time that a process scheduled under  a
  real-time  scheduling  policy  may  consume  without making a blocking system
  call.  For the purpose of this limit, each time a process  makes  a  blocking
  system  call,  the  count of its consumed CPU time is reset to zero.  The CPU
  time count is not reset if the process continues trying to use the CPU but is
  preempted, its time slice expires, or it calls sched_yield(2).

  Upon  reaching  the soft limit, the process is sent a SIGXCPU signal.  If the
  process catches or ignores this signal and continues consuming CPU time, then
  SIGXCPU  will  be generated once each second until the hard limit is reached,
  at which point the process is sent a SIGKILL signal.

  The intended use of this limit is to stop a runaway  real-time  process  from
  locking up the system.

RLIMIT_SIGPENDING (Since Linux 2.6.8)
  Specifies  the limit on the number of signals that may be queued for the real
  user ID of the calling process.  Both  standard  and  real-time  signals  are
  counted  for  the purpose of checking this limit.  However, the limit is only
  enforced for sigqueue(2); it is always possible to use kill(2) to  queue  one
  instance of any of the signals that are not already queued to the process.

RLIMIT_STACK
  The maximum size of the process stack, in bytes.  Upon reaching this limit, a
  SIGSEGV signal is generated.  To handle this signal, a process must employ an
  alternate signal stack (sigaltstack(2)).

  Since  Linux  2.6.23, this limit also determines the amount of space used for
  the process’s command-line arguments and environment variables; for  details,
  see execve(2).
)"},
    { "Describe the typical memory layout of a process.",
        R"(

               ------------------
              |                  |
              |      Kernel      |
              |                  |
  0xC0000000  |------------------|
              |   argv, environ  |
              |------------------|
              |       Stack      |
              | (grows downward) |
  Top of      |                  |
  stack --->  |- - - - - - - - - |
              |        |         |
              |        |         |
              |        v         |
              |                  |
              |  (unallocated)   |
              |                  |
              |        ^         |
              |        |         |
  Program     |        |         |
   break ---> | - - - - - - - - -| 
              |      Heap        |
              |   (grows upward) |
              |------------------|
              |Uninitialized data|
              |      (bss)       |
              |------------------|
              | Initialized data |
              |------------------|
              |                  |
              |      Text        |
              |  (program code)  |
  0x80480000  |------------------|
              |                  |
  0x00000000   ------------------
)"},
    { "Describe the four user IDs associated with a process.",
        R"(

Real
----
This ID identifies the user to which the process belongs.  It is read from the
user's password record in the /etc/passwd file.

Effective
---------
Used to determine the permissions granted to a process when it tries to perform
various operations (i.e. system calls).  For example, these identifiers
determine the permissions granted to a process when it accesses resources such
as files and System V interprocess communication (IPC) objects, which themselves
have associated user and group IDs determining to whom they belong.

Saved Set-user-ID
-----------------
Normally this ID is the same as the effective user ID.  When running a set-UID
program, the saved set-user-ID gets set to the ID of the owner of the executable
file, as does the effective user ID.  However, various system calls allow a
set-user-ID program to switch its effective user ID between the values of the
real user ID and the saved set-user-ID.

File-system
-----------
Nowadays, the file-system user ID is the same as the effective user ID.  It
exists for historical reasons.  In Linux kernel 1.2, one process could send a
signal to another if the effective user ID of the sender matched the real or
effective user ID of the target process.  This affected certain programs such as
the Linux NFS server program, which needed to be able to access files as though
it had the effective IDs of the corresponding client process.  However, if the
NFS server changed its effective user ID, it would be vulnerable to signals from
unprivileged user processes.  To prevent this possibility, the separate
file-system user and group IDs were devised.  By leaving its effective IDs
unchanged, but changing its file-system IDs, the NFS server could masquerade as
another user for the purpose of accessing files without being vulnerable to
signals from user processes.  From kernel 2.0 onward, Linux adopted the
SUSv3-mandated rules regarding permission for sending signals, and these rules
don't involve the effective user ID of the target process.  Thus the file-system
ID feature is no longer strictly necessary, but remains for compatibility with
existing software.

)"},
    { "What's the purpose of the saved set User ID?",
        R"(
When a set-UID program is launched, the effective user ID of the process is set
to the owner of the program file.  This is for situations where a user is to be
given controlled privileged access to some resource, such as the passwd program
allowing the user to modify his or her entry in the /etc/shadow file.  At the
same time the effective user ID is set, this (potentially new) effective user ID
is also saved as what's known as the 'saved set user ID' so that if the
effective user ID is later changed, it can be reverted back to the original
set-UID value.

An unpriviledged process can set its effective user ID to either its real user
ID or the saved set user ID using the seteuid() system call.  For example, let's
say a process whose real, effective, and saved set user IDs are all 1000,
executes a set-UID program owned by root (UID 0).  After the exec, the user IDs
of the process will be as follows:

real=1000
effective=0
saved=0

At this point the effective user ID can be changed back-and-forth between the
real user ID and the saved set user ID.  The rationale behind this design is
that set-UID programs are usually written to give an unprivileded user limited
priviledged access.  Most of the instructions in the set-UID program do not
require privileged access, so the program should mostly run with the effective
user ID equal to the real user ID and only run with the privileged effective
user ID (saved set user ID) when it needs priviledged access.  This reduces the
likelihood that some bug in the program wreaks havoc on the system.

)"},
    { "How can a program determine the amount of CPU time that it has used?",
        R"(
The system call times() can be used to obtain CPU time.  It has the following
prototype:

  clock_t times(struct tms *buf);

On success, times() returns the elapsed (real) time in clock ticks since some
arbitrary point in the past (i.e. program startup) and fills out the tms
argument with the CPU times.  struct tms is defined as follows:

  struct tms {
      clock_t tms_utime;  /* user time */
      clock_t tms_stime;  /* system time */
      clock_t tms_cutime; /* user time of children */
      clock_t tms_cstime; /* system time of children */
  };

The child times are the aggregate time spent by child processes for which wait()
has been called.  The clock_t values are 'clock ticks'.  A call to
sysconf(_SC_CLK_TCK) returns the number of clock ticks per second, which
corresponds to the kernel constant USER_HZ which is usually set to 100.

The return value of times() is unreliable since it can overflow the range of
clock_t.  The reliable way to measure the passage of elapsed time is to use
gettimeofday().

The clock() library function returns an approximation of the CPU time
(user + system) used by the process.  On Linux the returned value does not
include time used by children.  The value returned is measured in units of
CLOCKS_PER_SEC which is usually defined to be 1000000, so the value must be
divided by CLOCKS_PER_SEC to get the total number of seconds.
)"},
    { "Name the system config variables that can be obtained with sysconf().",
        R"(
_SC_ARG_MAX
  The maximum length of the arguments to the exec(3) family of functions.  Must
  not be less than _POSIX_ARG_MAX (4096).

_SC_CHILD_MAX
  The max number of simultaneous processes per user ID.  Must not be less than
  _POSIX_CHILD_MAX (25).

_SC_HOST_NAME_MAX
  Max  length  of  a  hostname,  not  including  the terminating null byte, as
  returned by gethostname(2).  Must not be less than _POSIX_HOST_NAME_MAX (255).

_SC_LOGIN_NAME_MAX
  Maximum length of a login name, including the terminating null byte.  Must not
  be less than _POSIX_LOGIN_NAME_MAX (9).

_SC_CLK_TCK
  The number of clock ticks per second.  The corresponding variable is obsolete.
  It was of course called  CLK_TCK.  (Note:  the macro CLOCKS_PER_SEC does not
  give information: it must equal 1000000.)

_SC_OPEN_MAX
  The maximum number of files that a process can have open at any time.  Must
  not be less than _POSIX_OPEN_MAX (20).

_SC_PAGESIZE
  Size of a page in bytes.  Must not be less than 1.
  (Some systems use PAGE_SIZE instead.)

_SC_RE_DUP_MAX
  The  number  of repeated occurrences of a BRE permitted by regexec(3) and
  regcomp(3).  Must not be less than _POSIX2_RE_DUP_MAX (255).

_SC_STREAM_MAX
  The maximum number of streams that a process can have open at any time.  If
  defined, it has the same value as  the  standard  C macro FOPEN_MAX.  Must not
  be less than _POSIX_STREAM_MAX (8).

SYMLOOP_MAX
  The  maximum  number  of  symbolic links seen in a pathname before resolution
  returns ELOOP.  Must not be less than _POSIX_SYM_LOOP_MAX (8).

_SC_TTY_NAME_MAX
  The maximum length of terminal device name, including the terminating null
  byte.  Must not  be  less  than  _POSIX_TTY_NAME_MAX (9).

_SC_TZNAME_MAX
  The maximum number of bytes in a timezone name.  Must not be less than
  _POSIX_TZNAME_MAX (6).

_SC_VERSION
  Indicates  the  year  and  month the POSIX.1 standard was approved in the
  format YYYYMML; the value 199009L indicates the Sept. 1990 revision.

_SC_LINE_MAX
  The  maximum  length  of  a utility’s input line length, either from standard
  input or from a file.  This includes length for a trailing newline.

_SC_RE_DUP_MAX
  The maximum number of repeated occurrences of a regular expression when the
  interval notation \{m,n\} is used.

POSIX2_VERSION - _SC_2_VERSION
  Indicates the version of the POSIX.2 standard in the format of YYYYMML.

These values also exist, but may not be standard.

_SC_PHYS_PAGES
  The number of pages of physical memory.  Note that it is possible for the
  product of this value and the value of _SC_PAGE_SIZE to overflow.

_SC_AVPHYS_PAGES
    The number of currently available pages of physical memory.

_SC_NPROCESSORS_CONF
    The number of processors configured.

_SC_NPROCESSORS_ONLN
    The number of processors currently online (available).
)"},
    { "Name the system config variables that can be obtained with pathconf() and\n"
        "fpathconf().",
        R"(

_PC_LINK_MAX
  returns  the  maximum  number of links to the file.  If fd or path refer to a
  directory, then the value applies to the whole directory.  The  corresponding
  macro is _POSIX_LINK_MAX.

_PC_MAX_CANON
  returns  the  maximum length of a formatted input line, where fd or path must
  refer to a terminal.  The corresponding macro is _POSIX_MAX_CANON.

_PC_MAX_INPUT
  returns the maximum length of an input line, where fd or path must refer to a
  terminal.  The corresponding macro is _POSIX_MAX_INPUT.

_PC_NAME_MAX
  returns the maximum length of a filename in the directory path or fd that the
  process is allowed to create.  The corresponding macro is _POSIX_NAME_MAX.

_PC_PATH_MAX
  returns the maximum length of a relative pathname when path or fd is the cur-
  rent working directory.  The corresponding macro is _POSIX_PATH_MAX.

_PC_PIPE_BUF
  returns  the  size  of the pipe buffer, where fd must refer to a pipe or FIFO
  and path must refer to a FIFO.  The corresponding macro is _POSIX_PIPE_BUF.

_PC_CHOWN_RESTRICTED
  returns non-zero if the chown(2) call may not be used on this file.  If fd or
  path  refer to a directory, then this applies to all files in that directory.
  The corresponding macro is _POSIX_CHOWN_RESTRICTED.

_PC_NO_TRUNC
  returns non-zero if accessing filenames longer than _POSIX_NAME_MAX generates
  an error.  The corresponding macro is _POSIX_NO_TRUNC.

_PC_VDISABLE
  returns non-zero if special character processing can be disabled, where fd or
  Path must refer to a terminal.
)"},
   { "Describe the superblock object.",
       R"(
This in-memory object stores information concerning a mounted filesystem.  For
disk-based filesystems, this object usually corresponds to a 'filesystem control
block' stored on disk.

The object is of type `struct super_block` which includes the following fields:

struct list_head         <b>s_list</b>  Links to adjacent elements in the list
                                 of super block objects
                                 (pointed to by super_blocks variable)

dev_t                     <b>s_dev</b>  Device identifier

unsigned long       <b>s_blocksize</b>  Block size in bytes.

unsigned long   <b>s_old_blocksize</b>  Block size in bytes as reported by the
                                 underlying block device driver.

unsigned char  <b>s_blocksize_bits</b>  Block size in number of bits.

unsigned char            <b>s_dirt</b>  Modified (dirty) flag.

unsigned long long <b> s_maxbytes </b>  Maximum size of the files.

struct
file_system_type *       <b>s_type</b>  Filesystem type

struct super_operations *  <b>s_op</b>  Superblock methods

struct dquot_operations * <b>dq_op</b>  Disk quota handling methods

struct quotactl_ops *    <b>s_qcop</b>  Disk quota administration methods

struct
export_operations * <b>s_export_op</b>  Export operations used by network fs

unsigned long           <b>s_flags</b>  Mount flags

unsigned long           <b>s_magic</b>  Filesystem magic number

struct dentry *          <b>s_root</b>  Dentry object of the filesystem's root
                                 directory

struct rw_semaphore    <b>s_umount</b>  Semaphore used for unmounting

struct semaphore         <b>s_lock</b>  Superblock semaphore

int                     <b>s_count</b>  Reference counter

int                   <b>s_syncing</b>  Flag indicating that inodes of the
                                 superblock are being synchronized

int              <b>s_need_sync_fs</b>  Flag used when synchronizing the
                                 superblock's mounted filesystem

atomic_t               <b>s_active</b>  Secondary reference counter

void *               <b>s_security</b>  Pointer to superblock security structure

struct xattr_handler ** <b>s_xattr</b>  Pointer to superblock extended attribute
                                 structure

struct list_head       <b>s_inodes</b>  List of all inodes

struct list_head        <b>s_dirty</b>  List of modified inodes

struct list_head           <b>s_io</b>  List of inodes waiting to be written to
                                 disk

struct hlist_head        <b>s_anon</b>  List of anonymous dentries for handling
                                 remote network filesystems

struct list_head        <b>s_files</b>  List of file objects

struct block_device *    <b>s_bdev</b>  Poiner to the block device driver
                                 descriptor

struct list_head    <b>s_instances</b>  Pointers for a list of superblock
                                 objects of a given filesystem type

struct quota_info       <b>s_dquot</b>  Descriptor for disk quota

int                    <b>s_frozen</b>  Flag used when freezing the filesystem
                                 (forcing it to a consistent state)

wait_queue_head_t <b>s_wait_frozen</b>  Wait queue where processes sleep until
                                the filesystem is unfrozen

char[]                     <b>s_id</b>  Name of the block device containing the
                                 superblock

void *                <b>s_fs_info</b>  Pointer to superblock information of a
                                 specific filesystem, usually includes disk
                                 allocation bitmaps

struct
semaphore      <b>m_vfs_rename_sem</b>  Semaphore used by VFS when renaming
                                 files across directories

u32                 <b>s_time_gran</b>  Timestamp's granularity (in nanoseconds)
)"},
   { "Describe the superblock methods.",
       R"(
<b>alloc_inode</b>(sb)
  Allocates pace for an inode object, including the space required for
  filesystem-specific data.

<b>destroy_inode</b>(inode)
  Destroys an inode object, including the filesystem-specific data.

<b>read_inode</b>(inode)
  Fills the fields of the inode object passed as the parameter with the data on
  disk; the i_no field of the inode object identifies the specific filesystem
  inode on the disk to be read

<b>dirty_inode</b>(inode)
  Invoked when the inode is marked as modified (dirty).  Used by filesystems
  such as FeiserFS and Ext3 to update the filesystem journal on disk.

<b>write_inode</b>(inode, flag)
  Updates a filesystem inode wiht the contents of the inode object passed as the
  parameter; the i_ino field of the inode object identifies the specific
  filesystem inode on the disk to be read.

<b>put_inode</b>(inode)
  Invoked when the inode is released -- its reference counter is decreased -- to
  perform filesystem-specific operations.

<b>drop_inode</b>(inode)
  Invoked when the inode is about to be destroyed -- that is, when the last user
  releases the inode; filesystems that implement this method usually make use of
  generic_drop_inode().  This function removes every reference to the inode from
  the VFS data structures and, if the inode no longer appears in any directory,
  invokes the delete_inode() superblock method to delete the inode from the
  filesystem.

<b>delete_inode</b>(inode)
  Invoked when the inode must be destroyed.  Deletes the VFS inode in memory and
  the file data and metadata on disk.

<b>put_super</b>(super)
  Releases the superblock object passed as the parameter (because the
  corresponding filesystem is unmounted).

<b>write_super</b>(super)
  Updates a flesystem superblock with the contents of the object indicated.

<b>sync_fs</b>(sb, wait)
  Invoked when flushing the filesystem to update filesystem-specific data
  structures on disk (used by journaling filesystems).

<b>write_super_lockfs</b>(super)
  Blocks changes to the filesystem and updates the superblock with the contents
  of the object indicated.  This method is invoked when the filesystem is
  frozen, for instance by the Logical Volume Manager (LVM) driver.

<b>unlockfs</b>(super)
  Undoes the block of filesystem updates achieved by the write_super_lockfs()
  superblock method.

<b>statfs</b>(super, buf)
  Returns statistics on a filesystem by filling the buf buffer.

<b>remount_fs</b>(super, flags, data)
  Remounts the filesystem with new options (invoked when a mount option must be
  changed).

<b>clear_inode</b>(inode)
  Invoked when a disk inode is being destroyed to perform filesystem-specific
  operations.

<b>unmount_begin</b>(super)
  Aborts a mount operation because the corresponding unmount operation has been
  started (used only by network filesystems).

<b>show_options</b>(seq_file, vfsmount)
  Used to display filesystem-specific options.

<b>quota_read</b>(super, type, data, size, offset)
  Used by the quota system to read data from the file that specifies the limits
  for this filesystem.

<b>quota_write</b>(super, type, data, size, offset)
  Used by the quota system to write data into the file that specifies the limits
  for this filesystem.
)"},
   { "Explain how the dentry cache works.",
       R"(
A dentry object is an in-memory object that represents a directory in the
filesystem.  There is an associated inode which contains a list of directory
contents (files and subdirectories).

Whenever the kernel needs to reference a directory (e.g. pathname lookup), it
constructs a set of dentry objects for each pathname component of the directory.
This involves reading the inode of each path component from disk and allocating
and populating a struct dentry object.

Since directories are often used repeatedly in the same session (e.g. edit file
and then compile it), the kernel maintains an LRU cache of dentry object.
Dentry objects exist in the kernel in one of four states:

Free - The dentry object contians no valid information and is on a free list
       inside the slab allocator.

Unused - The dentry object is not current used by the kernel.  The d_count usage
         counter is 0, but the d_inode field still points to the associated
         inode and the dentry object contains valid information.

In use - The dentry object is currently used by the kernel.  The d_count usage
         counter is positive and the d_inode field points to the associated
         inode object and the dentry object contains valid information.  The
         dentry object cannot be discarded.

Negative - The inode associated with the dentry does not exist, either because
           the corresponding disk inode has been deleted or because the dentry
           object was created by resolving a pathname of a nonexistent file.
           The d_inode field of the dentry object is NULL, but the object
           remains in the dentry cache so that further lookup operations to the
           same file pathname can be quickly resolved.

The dentry cache is an LRU cache of dentry objects in the In use, Unused, and
Negative states.  The 'unused' entries (i.e. Unused or Negative) are linked
together in a list pointed to by the 'dentry_unused' variable and the d_lru
field of the dentry object point to the adjacent entries.  Whenever a dentry
object is released (i.e. no longer In use), it gets added to the front of the
dentry_unused list.

The dentry struct has a set of associated operations referenced by a
dentry_operations table in the d_op field.  One of the operations is called
d_hash:

  d_hash(dentry, name)

It computes a hash value for the directory (dentry) containing the pathname
component and the pathname component (name).  This hash value is used to insert
and lookup a pathname component in the dentry cache hash table.  The
'dentry_hashtable' variable points to the hash table and the d_hash field of the
dentry object contains pointers to adjacent dentry objects in the same bucket.
)"},
   { "Describe the objects used by the kernel to manage files and filesystems.",
       R"(

The following is a list of filesystem related kernel structures along with some
filesystem specific fields.

task_struct
-----------
This is also known as the process descriptor and one is allocated for each
process (thread) running in the system.
  
  struct nameidata *nameidata; // file system info

  struct fs_struct *fs;        // filesystem information
  
  struct files_struct *files;  // open file information
  
  struct nsproxy *nsproxy;     // namespaces

super_block
-----------
Stores information concerning a mounted filesystem.  For disk-based filesystems,
this object usually corresponds to a 'filesystem control block' stored on disk.

  struct file_system_type *s_type; // Filesystem type

  struct list_head s_inodes;       // List of all inodes

  struct list_head s_dirty;        // List of dirty inodes

  struct list_head s_io;           // List of dirty inodes waiting to be
                                   // written to disk

  struct list_head s_files;        // List of file objects

  struct list_head s_instances;    // Pointer to list of superblock objects of a
                                   // List of file objectsgiven filesystem type

inode
-----
Stores general information about a specific file.  For disk-based filesystems,
this object usually corresponds to a file control block stored on disk.

  struct list_head i_dentry;   // Head of the list of dentry oobjects
                               // referencing this inode

  unsigned int  i_nlink;       // Number of hard links

  loff_t  i_size;              // File length in bytes

  struct super_block *i_sb;    // Pointer to superblock object

  struct file_lock *i_flock;   // Pointer to file lock list

  struct address_space i_data; // address_space object of the file

file
----
Stores information about the interaction between an open file and a process.

  struct dentry *f_dentry;         // dentry object associated with the file

  struct vfsmount *f_vfsmnt;       // Mounted filesystem containing the file

  atomic_ f_count;                 // File object's reference counter

  loff_t f_pos;                    // Current file offset (file pointer)

  struct address_space *f_mapping; // Pointer to the file's address space object

dentry
------
Stores information about the linking of a directory entry (that is, a particular
name of the file) with the corresponding file.

  struct inode *d_inode;      // Inode associated with filename

  struct dentry *d_parent;    // Dentry object of parent directory

  struct qstr d_name;         // Filename

  struct list_head d_lru;     // Pointers for the list of unused dentries

  struct list_head d_child;   // For directories, pointers for the list of
                              // directory dentries in same parent directory

  struct list_head d_subdirs; // For directories, head of list of subdirectory
                              // dentries

  struct list_head d_alias;   // Pointers for the list of dentries associated
                              // with the same inode (alias)

  int d_mounted;              // For directories, counter for the number of
                              // filesystems mounted on this dentry

fs_struct
---------

  
)"}
  };

}

#endif // quiz_linux_hpp
