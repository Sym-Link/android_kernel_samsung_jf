/*
 * Linux 2.6.32 and later Kernel module for VMware MVP Hypervisor Support
 *
<<<<<<< HEAD
 * Copyright (C) 2010-2012 VMware, Inc. All rights reserved.
=======
 * Copyright (C) 2010-2013 VMware, Inc. All rights reserved.
>>>>>>> cm/cm-11.0
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; see the file COPYING.  If not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#line 5

/**
 *  @file
 *
 *  @brief Contains linux-specific type definitions and function declarations
 */

#ifndef	_COMM_OS_LINUX_H_
#define	_COMM_OS_LINUX_H_

#include <linux/types.h>
#include <linux/version.h>

<<<<<<< HEAD
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,20)
#error "Kernel versions lower than 2.6.20 are not supported"
#endif

=======
>>>>>>> cm/cm-11.0
#include <linux/kernel.h>
#include <linux/workqueue.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>
<<<<<<< HEAD
=======
#include <linux/cpu.h>
>>>>>>> cm/cm-11.0


/*
 * Type definitions.
 */

typedef atomic_t CommOSAtomic;
typedef spinlock_t CommOSSpinlock;
typedef struct mutex CommOSMutex;
typedef wait_queue_head_t CommOSWaitQueue;
typedef struct delayed_work CommOSWork;
typedef void (*CommOSWorkFunc)(CommOSWork *work);
typedef struct list_head CommOSList;
typedef struct module *CommOSModule;


/*
 * Initializers.
 */

#define CommOSSpinlock_Define DEFINE_SPINLOCK


<<<<<<< HEAD
#define COMM_OS_DOLOG(...) printk(KERN_INFO __VA_ARGS__)
=======
#define COMM_OS_DOLOG(...) pr_info(__VA_ARGS__)
>>>>>>> cm/cm-11.0


/**
 *  @brief Logs given arguments in debug builds.
 */

#if defined(COMM_OS_DEBUG)
<<<<<<< HEAD
   #define CommOS_Debug(args) COMM_OS_DOLOG args
=======
   #define CommOS_Debug(args) do { COMM_OS_DOLOG args ; } while (0)
>>>>>>> cm/cm-11.0
#else
   #define CommOS_Debug(args)
#endif


/**
 *  @brief Logs given arguments.
 */

<<<<<<< HEAD
#define CommOS_Log(args) COMM_OS_DOLOG args
=======
#define CommOS_Log(args) do { COMM_OS_DOLOG args ; } while (0)
>>>>>>> cm/cm-11.0


/**
 *  @brief Logs function name and location.
 */

#if defined(COMM_OS_TRACE)
<<<<<<< HEAD
#define TRACE(ptr)                                                       \
   do {                                                                  \
      CommOS_Debug(("%p:%s: at [%s:%d] with arg ptr [0x%p].\n", current, \
      __FUNCTION__, __FILE__, __LINE__, (ptr)));                         \
   } while (0)
=======
#define TRACE(ptr) \
	CommOS_Debug(("%p:%s: at [%s:%d] with arg ptr [0x%p].\n", current, \
		      __func__, __FILE__, __LINE__, (ptr)))
>>>>>>> cm/cm-11.0
#else
#define TRACE(ptr)
#endif


/**
 *  @brief Write atomic variable
 *  @param[in,out] atomic variable to write
 *  @param val new value
 */

static inline void
CommOS_WriteAtomic(CommOSAtomic *atomic,
<<<<<<< HEAD
                   int val)
{
   atomic_set(atomic, val);
=======
		   int val)
{
	atomic_set(atomic, val);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Reads atomic variable
 *  @param atomic variable to read
 *  @return value
 */

static inline int
CommOS_ReadAtomic(CommOSAtomic *atomic)
{
<<<<<<< HEAD
   return atomic_read(atomic);
=======
	return atomic_read(atomic);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Atomically add value to atomic variable, return new value.
 *  @param[in,out] atomic variable
 *  @param val value to add
 *  @return new value
 */

static inline int
CommOS_AddReturnAtomic(CommOSAtomic *atomic,
<<<<<<< HEAD
                       int val)
{
   return atomic_add_return(val, atomic);
=======
		       int val)
{
	return atomic_add_return(val, atomic);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Atomically substract value from atomic variable, return new value.
 *  @param[in,out] atomic variable
 *  @param val value to substract
 *  @return new value
 */

static inline int
CommOS_SubReturnAtomic(CommOSAtomic *atomic,
<<<<<<< HEAD
                       int val)
{
   return atomic_sub_return(val, atomic);
=======
		       int val)
{
	return atomic_sub_return(val, atomic);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Initializes a given lock.
 *  @param[in,out] lock lock to initialize
 */

static inline void
CommOS_SpinlockInit(CommOSSpinlock *lock)
{
<<<<<<< HEAD
   spin_lock_init(lock);
=======
	spin_lock_init(lock);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Locks given lock and disables bottom half processing.
 *  @param[in,out] lock lock to lock
 */

static inline void
CommOS_SpinLockBH(CommOSSpinlock *lock)
{
<<<<<<< HEAD
   spin_lock_bh(lock);
=======
	spin_lock_bh(lock);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Attempts to lock the given lock and disable BH processing.
 *  @param[in,out] lock lock to lock
 *  @return zero if successful, non-zero otherwise
 */

static inline int
CommOS_SpinTrylockBH(CommOSSpinlock *lock)
{
<<<<<<< HEAD
   return !spin_trylock_bh(lock);
=======
	return !spin_trylock_bh(lock);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Unlocks given lock and re-enables BH processing.
 *  @param[in,out] lock lock to unlock
 */

static inline void
CommOS_SpinUnlockBH(CommOSSpinlock *lock)
{
<<<<<<< HEAD
   spin_unlock_bh(lock);
=======
	spin_unlock_bh(lock);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Locks the given lock.
 *  @param[in,out] lock lock to lock
 */

static inline void
CommOS_SpinLock(CommOSSpinlock *lock)
{
<<<<<<< HEAD
   spin_lock(lock);
=======
	spin_lock(lock);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Attempts to lock the given lock.
 *  @param[in,out] lock lock to try-lock
 *  @return zero if successful, non-zero otherwise
 */

static inline int
CommOS_SpinTrylock(CommOSSpinlock *lock)
{
<<<<<<< HEAD
   return !spin_trylock(lock);
=======
	return !spin_trylock(lock);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Unlocks given lock.
 *  @param[in,out] lock lock to unlock
 */

static inline void
CommOS_SpinUnlock(CommOSSpinlock *lock)
{
<<<<<<< HEAD
   spin_unlock(lock);
=======
	spin_unlock(lock);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Initializes given mutex.
 *  @param[in,out] mutex mutex to initialize
 */

static inline void
CommOS_MutexInit(CommOSMutex *mutex)
{
<<<<<<< HEAD
   mutex_init(mutex);
=======
	mutex_init(mutex);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Acquires mutex.
 *  @param[in,out] mutex mutex to lock
 *  @return zero if successful, non-zero otherwise (interrupted)
 */

static inline int
CommOS_MutexLock(CommOSMutex *mutex)
{
<<<<<<< HEAD
   return mutex_lock_interruptible(mutex);
=======
	return mutex_lock_interruptible(mutex);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Acquires mutex in uninterruptible mode.
 *  @param[in,out] mutex mutex to lock
 */

static inline void
CommOS_MutexLockUninterruptible(CommOSMutex *mutex)
{
<<<<<<< HEAD
   mutex_lock(mutex);
=======
	mutex_lock(mutex);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Attempts to acquire given mutex.
 *  @param[in,out] mutex mutex to try-lock
 *  @return zero if successful, non-zero otherwise
 */

static inline int
CommOS_MutexTrylock(CommOSMutex *mutex)
{
<<<<<<< HEAD
   return !mutex_trylock(mutex);
=======
	return !mutex_trylock(mutex);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Releases a given mutex.
 *  @param[in,out] mutex mutex to unlock
 */

static inline void
CommOS_MutexUnlock(CommOSMutex *mutex)
{
<<<<<<< HEAD
   mutex_unlock(mutex);
=======
	mutex_unlock(mutex);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Initializes a wait queue.
 *  @param[in,out] wq workqueue to initialize
 */

static inline void
CommOS_WaitQueueInit(CommOSWaitQueue *wq)
{
<<<<<<< HEAD
   init_waitqueue_head(wq);
=======
	init_waitqueue_head(wq);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Puts the caller on a wait queue until either of the following occurs:
 *      - the condition function (predicate) evaluates to TRUE
 *      - the specified timeout interval elapsed
 *      - a signal is pending
 *  @param[in,out] wq wait queue to put item on
 *  @param cond predicate to test
 *  @param condArg1 argument 1 for cond
 *  @param condArg2 argument 2 for cond
 *  @param[in,out] timeoutMillis timeout interval in milliseconds
 *  @param interruptible enable/disable signal pending check
 *  @return 1 if condition was met
 *          0 if the timeout interval elapsed
 *          <0, if a signal is pending or other error set by condition
 *  @sideeffect timeoutMillis is updated to time remaining
 */

static inline int
CommOS_DoWait(CommOSWaitQueue *wq,
<<<<<<< HEAD
              CommOSWaitConditionFunc cond,
              void *condArg1,
              void *condArg2,
              unsigned long long *timeoutMillis,
              int interruptible)
{
   int rc;
   DEFINE_WAIT(wait);
   long timeout;
#if defined(COMM_OS_LINUX_WAIT_WORKAROUND)
   long tmpTimeout;
   long retTimeout;
   const unsigned int interval = 50;
#endif

   if (!timeoutMillis) {
      return -1;
   }
   if ((rc = cond(condArg1, condArg2)) != 0) {
      return rc;
   }

#if defined(COMM_OS_LINUX_WAIT_WORKAROUND)
   timeout = msecs_to_jiffies(interval < *timeoutMillis ?
                                 interval : (unsigned int)*timeoutMillis);
   retTimeout = msecs_to_jiffies((unsigned int)(*timeoutMillis));

   for (; retTimeout >= 0; ) {
      prepare_to_wait(wq, &wait,
                      (interruptible?TASK_INTERRUPTIBLE:TASK_UNINTERRUPTIBLE));
      if ((rc = cond(condArg1, condArg2))) {
         break;
      }
      if (interruptible && signal_pending(current)) {
         rc = -EINTR;
         break;
      }
      if ((tmpTimeout = schedule_timeout(timeout))) {
         retTimeout -= (timeout - tmpTimeout);
      } else {
         retTimeout -= timeout;
      }
      if (retTimeout < 0) {
         retTimeout = 0;
      }
   }
   finish_wait(wq, &wait);
   if (rc == 0) {
      rc = cond(condArg1, condArg2);
      if (rc && (retTimeout == 0)) {
         retTimeout = 1;
      }
   }
   *timeoutMillis = (unsigned long long)jiffies_to_msecs(retTimeout);
#else // !defined(COMM_OS_LINUX_WAIT_WORKAROUND)
   timeout = msecs_to_jiffies((unsigned int)(*timeoutMillis));

   for (;;) {
      prepare_to_wait(wq, &wait,
                      (interruptible?TASK_INTERRUPTIBLE:TASK_UNINTERRUPTIBLE));
      if ((rc = cond(condArg1, condArg2)) != 0) {
         break;
      }
      if (interruptible && signal_pending(current)) {
         rc = -EINTR;
         break;
      }
      if ((timeout = schedule_timeout(timeout)) == 0) {
         rc = 0;
         break;
      }
   }
   finish_wait(wq, &wait);
   if (rc == 0) {
      rc = cond(condArg1, condArg2);
      if (rc && (timeout == 0)) {
         timeout = 1;
      }
   }
   *timeoutMillis = (unsigned long long)jiffies_to_msecs(timeout);
#endif

   return rc;
=======
	      CommOSWaitConditionFunc cond,
	      void *condArg1,
	      void *condArg2,
	      unsigned long long *timeoutMillis,
	      int interruptible)
{
	int rc;
	DEFINE_WAIT(wait);
	long timeout;
#if defined(COMM_OS_LINUX_WAIT_WORKAROUND)
	long tmpTimeout;
	long retTimeout;
	const unsigned int interval = 50;
#endif

	if (!timeoutMillis)
		return -1;

	rc = cond(condArg1, condArg2);
	if (rc != 0)
		return rc;

#if defined(COMM_OS_LINUX_WAIT_WORKAROUND)
	timeout = msecs_to_jiffies(interval < *timeoutMillis ?
				       interval : (unsigned int)*timeoutMillis);
	retTimeout = msecs_to_jiffies((unsigned int)(*timeoutMillis));

	for (; retTimeout >= 0; ) {
		prepare_to_wait(wq, &wait,
		  (interruptible ? TASK_INTERRUPTIBLE : TASK_UNINTERRUPTIBLE));
		rc = cond(condArg1, condArg2);
		if (rc)
			break;

		if (interruptible && signal_pending(current)) {
			rc = -EINTR;
			break;
		}
		tmpTimeout = schedule_timeout(timeout);
		if (tmpTimeout)
			retTimeout -= (timeout - tmpTimeout);
		else
			retTimeout -= timeout;

		if (retTimeout < 0)
			retTimeout = 0;
	}
	finish_wait(wq, &wait);
	if (rc == 0) {
		rc = cond(condArg1, condArg2);
		if (rc && (retTimeout == 0))
			retTimeout = 1;
	}
	*timeoutMillis = (unsigned long long)jiffies_to_msecs(retTimeout);
#else /* !defined(COMM_OS_LINUX_WAIT_WORKAROUND) */
	timeout = msecs_to_jiffies((unsigned int)(*timeoutMillis));

	for (;;) {
		prepare_to_wait(wq, &wait,
		  (interruptible ? TASK_INTERRUPTIBLE : TASK_UNINTERRUPTIBLE));
		rc = cond(condArg1, condArg2);
		if (rc != 0)
			break;

		if (interruptible && signal_pending(current)) {
			rc = -EINTR;
			break;
		}
		timeout = schedule_timeout(timeout);
		if (timeout == 0) {
			rc = 0;
			break;
		}
	}
	finish_wait(wq, &wait);
	if (rc == 0) {
		rc = cond(condArg1, condArg2);
		if (rc && (timeout == 0))
			timeout = 1;
	}
	*timeoutMillis = (unsigned long long)jiffies_to_msecs(timeout);
#endif

	return rc;
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Puts the caller on a wait queue until either of the following occurs:
 *      - the condition function (predicate) evaluates to TRUE
 *      - the specified timeout interval elapsed
 *      - a signal is pending
 *  @param[in,out] wq wait queue to put item on
 *  @param cond predicate to test
 *  @param condArg1 argument 1 for cond
 *  @param condArg2 argument 2 for cond
 *  @param[in,out] timeoutMillis timeout interval in milliseconds
 *  @return 1 if condition was met
 *          0 if the timeout interval elapsed
 *          <0, if a signal is pending or other error set by condition
 *  @sideeffect timeoutMillis is updated to time remaining
 */

static inline int
CommOS_Wait(CommOSWaitQueue *wq,
<<<<<<< HEAD
            CommOSWaitConditionFunc cond,
            void *condArg1,
            void *condArg2,
            unsigned long long *timeoutMillis)
{
   return CommOS_DoWait(wq, cond, condArg1, condArg2, timeoutMillis, 1);
=======
	    CommOSWaitConditionFunc cond,
	    void *condArg1,
	    void *condArg2,
	    unsigned long long *timeoutMillis)
{
	return CommOS_DoWait(wq, cond, condArg1, condArg2, timeoutMillis, 1);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Puts the caller on a wait queue until either of the following occurs:
 *      - the condition function (predicate) evaluates to TRUE
 *      - the specified timeout interval elapsed
 *  @param[in,out] wq wait queue to put item on
 *  @param cond predicate to test
 *  @param condArg1 argument 1 for cond
 *  @param condArg2 argument 2 for cond
 *  @param[in,out] timeoutMillis timeout interval in milliseconds
 *  @return 1 if condition was met
 *          0 if the timeout interval elapsed
 *          <0, error set by condition
 *  @sideeffect timeoutMillis is updated to time remaining
 */

static inline int
CommOS_WaitUninterruptible(CommOSWaitQueue *wq,
<<<<<<< HEAD
                           CommOSWaitConditionFunc cond,
                           void *condArg1,
                           void *condArg2,
                           unsigned long long *timeoutMillis)
{
   return CommOS_DoWait(wq, cond, condArg1, condArg2, timeoutMillis, 0);
=======
			   CommOSWaitConditionFunc cond,
			   void *condArg1,
			   void *condArg2,
			   unsigned long long *timeoutMillis)
{
	return CommOS_DoWait(wq, cond, condArg1, condArg2, timeoutMillis, 0);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Wakes up task(s) waiting on the given wait queue.
 *  @param[in,out] wq wait queue.
 */

static inline void
CommOS_WakeUp(CommOSWaitQueue *wq)
{
<<<<<<< HEAD
   wake_up(wq);
=======
	wake_up(wq);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Allocates kernel memory of specified size; does not sleep.
 *  @param size size to allocate.
 *  @return Address of allocated memory or NULL if the allocation fails.
 */

static inline void *
CommOS_KmallocNoSleep(unsigned int size)
{
<<<<<<< HEAD
   return kmalloc(size, GFP_ATOMIC);
=======
	return kmalloc(size, GFP_ATOMIC);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Allocates kernel memory of specified size; may sleep.
 *  @param size size to allocate.
 *  @return Address of allocated memory or NULL if the allocation fails.
 */

static inline void *
CommOS_Kmalloc(unsigned int size)
{
<<<<<<< HEAD
   return kmalloc(size, GFP_KERNEL);
=======
	return kmalloc(size, GFP_KERNEL);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Frees previously allocated kernel memory.
 *  @param obj object to free.
 */

static inline void
CommOS_Kfree(void *obj)
{
<<<<<<< HEAD
   if (obj) {
      kfree(obj);
   }
=======
	kfree(obj);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Yields the current cpu to other runnable tasks.
 */

static inline void
CommOS_Yield(void)
{
<<<<<<< HEAD
   cond_resched();
=======
	cond_resched();
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Gets the current time in milliseconds.
 *  @return Current time in milliseconds, with precision of at most one tick.
 */

static inline unsigned long long
CommOS_GetCurrentMillis(void)
{
<<<<<<< HEAD
   return (unsigned long long)jiffies_to_msecs(jiffies);
=======
	return (unsigned long long)jiffies_to_msecs(jiffies);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Initializes given list.
 *  @param list list to initialize.
 */

static inline void
CommOS_ListInit(CommOSList *list)
{
<<<<<<< HEAD
   INIT_LIST_HEAD(list);
=======
	INIT_LIST_HEAD(list);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Tests if list is empty.
 *  @param list list to test.
 *  @return non-zero if empty, zero otherwise.
 */

#define CommOS_ListEmpty(list) list_empty((list))


/**
 *  @brief Adds given element to beginning of list.
 *  @param list list to add to.
 *  @param elem element to add.
 */

#define CommOS_ListAdd(list, elem) list_add((elem), (list))


/**
 *  @brief Adds given element to end of list.
 *  @param list list to add to.
 *  @param elem element to add.
 */

#define CommOS_ListAddTail(list, elem) list_add_tail((elem), (list))


/**
 *  @brief Deletes given element from its list.
 *  @param elem element to delete.
 */

<<<<<<< HEAD
#define CommOS_ListDel(elem)  \
   do {                       \
      list_del((elem));       \
      INIT_LIST_HEAD((elem)); \
   } while (0)
=======
#define CommOS_ListDel(elem)		\
	do {				\
		list_del((elem));	\
		INIT_LIST_HEAD((elem));	\
	} while (0)
>>>>>>> cm/cm-11.0


/**
 *  @brief Iterates over a list.
 *  @param list list to iterate over.
 *  @param[out] item stores next element.
 *  @param itemListFieldName name in the item structure storing the list head.
 */

#define CommOS_ListForEach(list, item, itemListFieldName) \
<<<<<<< HEAD
   list_for_each_entry((item), (list), itemListFieldName)
=======
	list_for_each_entry((item), (list), itemListFieldName)
>>>>>>> cm/cm-11.0


/**
 *  @brief Iterates safely over a list.
 *  @param list list to iterate over.
 *  @param[out] item stores next element. May be deleted in the loop.
 *  @param[out] tmpItem saves iteration element.
 *  @param itemListFieldName name in the item structure storing the list head.
 */

#define CommOS_ListForEachSafe(list, item, tmpItem, itemListFieldName) \
<<<<<<< HEAD
   list_for_each_entry_safe((item), (tmpItem), (list), itemListFieldName)
=======
	list_for_each_entry_safe((item), (tmpItem), (list), itemListFieldName)
>>>>>>> cm/cm-11.0


/**
 *  @brief Combines two lists, adds second list to beginning of first one.
 *  @param list list to add to.
 *  @param list2 list to add.
 */

#define CommOS_ListSplice(list, list2) list_splice((list2), (list))


/**
 *  @brief Combines two lists, adds second list to end of first one.
 *  @param list list to add to.
 *  @param list2 list to add.
 */

#define CommOS_ListSpliceTail(list, list2) list_splice_tail((list2), (list))


/**
 *  @brief Gets current module handle.
 *  @return module handle.
 */

static inline CommOSModule
CommOS_ModuleSelf(void)
{
<<<<<<< HEAD
   return THIS_MODULE;
=======
	return THIS_MODULE;
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Retains module.
 *  @param[in,out] module to retain.
 *  @return zero if successful, non-zero otherwise.
 */

static inline int
CommOS_ModuleGet(CommOSModule module)
{
<<<<<<< HEAD
   int rc = 0;

   if (!module) {
      goto out;
   }
   if (!try_module_get(module)) {
      rc = -1;
   }

out:
   return rc;
=======
	int rc = 0;

	if (!module)
		goto out;

	if (!try_module_get(module))
		rc = -1;

out:
	return rc;
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Releases module.
 *  @param[in,out] module to release.
 */

static inline void
CommOS_ModulePut(CommOSModule module)
{
<<<<<<< HEAD
   if (module) {
      module_put(module);
   }
=======
	if (module)
		module_put(module);
>>>>>>> cm/cm-11.0
}


/**
 *  @brief Inserts r/w memory barrier.
 */

#define CommOS_MemBarrier smp_mb

#endif  /* _COMM_OS_LINUX_H_ */

