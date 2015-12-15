#ifndef quiz_lock_free_hpp
#define quiz_lock_free_hpp

#include <initializer_list>

#include "quiz.hpp"

namespace study {

  const std::initializer_list<Item> lock_free {
    { "Explain the ABA problem.",
        R"(
Let's say you have a stack implementation with a poiner to the top defined as
follows:

  std::atomic<Obj*> top;

Let's say the 'pop' method is implemented as follows:

  while(1) {
    Obj* ret = top;
    if (!ret)
      return std::nullptr;

    // For simplicity, suppose that we can ensure that this dereference is safe
    // (i.e., that no other thread has popped the stack in the meantime).
    Obj* next = ret->next;

    // If the top node is still ret, then assume no one has changed the stack.
    // (That statement is not always true because of the ABA problem)
    // Atomically replace top with next.
    if (top.compare_exchange_weak(ret, next)) {
      return ret;
    }
    // The stack has changed, try again.
  }

Consider the following sequence:

Stack initially contains top → A → B → C

Thread 1 starts running pop:

 ret = A;
 next = B;

Thread 1 gets interrupted just before the compare_exchange_weak...

  // Thread 2 runs pop:
  ret = A;
  next = B;
  compare_exchange_weak(A, B)  // Success, top = B
  return A;

  // Now the stack is top → B → C

  // Thread 2 runs pop again:
  ret = B;
  next = C;
  compare_exchange_weak(B, C)  // Success, top = C
  return B;

  // Now the stack is top → C

  delete B;

  // Thread 2 now pushes A back onto the stack:
  A->next = C;
  compare_exchange_weak(C, A)  // Success, top = A

  // Now the stack is top → A → C

When Thread 1 resumes:

 compare_exchange_weak(A, B)

This instruction succeeds because it finds top == ret (both are A), so it sets
top to next (which is B).  As B has been deleted the program will access freed
memory when it tries to look the first element on the stack.
)" },
    { "Define lock-free programming.",
        R"(
A program is lock-free if it is algorithmically impossible for it to lock up.

More formally: In an infinite execution, infinitely often some method call finishes.

It doesn't just mean programming without mutexes.  For example, the following
seemingly lock-free attempt to test X for value 0 and set it to 1 can deadlock
if two threads simultaneously call it reapeatedly:

  while (X == 0)
    X = 1 - X;

One important consequence of lock-free programming is that if you suspend a
single thread, it will never prevent other threads from making progress, as a
group, through their own lock-free operations
)" },
    { "Explain what a Compare-And-Swap (CAS) operation is.",
        R"(
A compare-and-swap operation is an atomic operation that allows you to compare
the content of a destination address with an expected value, and if
they're equal, swap the contents of the destination address with a source
value.

The Intel x86 processors implement this with a ‘cmpxchg’ instruction which is
described as follows.

  [lock]  cmpxchg   reg,     reg/dst

    ^       ^        ^          ^
    |       |        |          |

   SMP   mnemonic  source   destination
                   operand   operand

The cmpxchg instruction uses two implicit operands:

- The accumulator register (EAX) is used as both a source and a destination
  operand
- The six status-bits in the EFLAGS register get modified, as a ‘side-effect’
  this instruction, setting ZF to 1 on success.

The instruction logically operates as follows.

  if (EAX == destination) {
    ZF = 1;
    destination = source;
  }
  else {
    ZF = 0;
    EAX = destination;
  }
)"},
  };

}

#endif // quiz_lock_free_hpp
