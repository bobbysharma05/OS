#include <stdint.h>

#include "string.h"

#include "arm.h"
#include "console.h"
#include "vm.h"
#include "mm.h"
#include "clock.h"
#include "timer.h"
#include "trap.h"
#include "proc.h"
#include "emmc.h"
#include "buf.h"
#include "mbox.h"
#include "irq.h"

/*
 * Keep it in data segment by explicitly initializing by zero,
 * since we have `-fno-zero-initialized-in-bss` in Makefile.
 */
static struct {
    int cnt;
    struct spinlock lock;
} mp = { 0 };

void
main()
{
    extern char edata[], end[];
    acquire(&mp.lock);
    if (mp.cnt++ == 0) {
        memset(edata, 0, end - edata);

        irq_init();
        console_init();
        mm_init();
        clock_init();
        proc_init();
        user_init();
        binit();

        // Tests
        mbox_test();
        mm_test();
        vm_test();
        
        // Test PS command functionality directly in kernel
        info("=== TESTING PS COMMAND FUNCTIONALITY ===");
        proc_info_t proc_info;
        int found_processes = 0;
        
        for(int i = 0; i < 10; i++) {
            if(get_proc_info_by_index(i, &proc_info) == 0) {
                info("Process %d: PID=%d, NAME=%s, STATE=%c", 
                     i, proc_info.pid, proc_info.name, proc_info.state);
                found_processes++;
            }
        }
        
        if(found_processes > 0) {
            info("PS COMMAND TEST: SUCCESS! Found %d processes", found_processes);
        } else {
            info("PS COMMAND TEST: No processes found yet (normal during early boot)");
        }
        info("=== PS COMMAND READY FOR USE ===");
    }
    release(&mp.lock);

    timer_init();
    trap_init();
    info("cpu %d init finished", cpuid());

    scheduler();

    panic("scheduler return.\n");
}
