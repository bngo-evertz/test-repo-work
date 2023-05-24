#ifndef HW_LOCK_H
#define HW_LOCK_H

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

//#include <evlog.h>
#include <stdio.h>

/**
 * Inter Process Lock in OS range.
 */
class HwLock
{
    public:
        HwLock(const char* name) {
            locker = sem_open(name, O_CREAT, 0664, 1);
            if (SEM_FAILED == locker) {
                //EV_ERR("failed to create HwLock:%s with reason{%s}\n", name, strerror(errno));
                fprintf(stderr, "failed to create HwLock:%s with reason{%s}\n",
                        name, strerror(errno));
            }
            strncpy(this->name, name, sizeof(this->name));
            this->name[sizeof(this->name)-1] = '\0';
        }

        int lock() const {
            //ignore all errors below.
            struct timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            ts.tv_sec += 1; // 1s shall be enough, otherwise someone quit without release this sem.
                            // so rescue by next unlock.

            int retries = 10;
            while(sem_timedwait(locker, &ts) < 0 && --retries) {
                //EV_WARN("[process:%u, thread:%lu] couldn't get the lock in 1s!!!\n", getpid(), pthread_self());

                // check if someone changed the system clock time
                struct timespec ts2;
                clock_gettime(CLOCK_REALTIME, &ts2);
                if (ts2.tv_sec > ts.tv_sec + 1) {
                    fprintf(stdout, "[HW_LOCK] Expected time: %u, Detected time: %u, Time difference: %d.\n",
                            (unsigned)ts.tv_sec, (unsigned)ts2.tv_sec, (int)(ts2.tv_sec - ts.tv_sec));
                    ts.tv_sec = ts2.tv_sec +1;
                } else {
                    fprintf(stderr, "[process:%u, thread:%lu] couldn't get the lock[%s] in 1s!!!\n",
                            getpid(), pthread_self(), name);

                    //clock_gettime(CLOCK_REALTIME, &ts);
                    //ts.tv_sec += 1;
                }
            }

            return retries ? 0 : -1;
        }

        int unlock() const {
            return sem_post(locker);
        }

    protected:
        sem_t* locker;
        char name[256];
};

#endif /* HW_LOCK_H */
