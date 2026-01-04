import sys

# https://www.chromium.org/chromium-os/developer-library/reference/linux-constants/syscalls/#x86-32-bit

list_syscalls = [
    "restart_syscall", "exit", "fork",
    "read", "write", "open", "close",
    "waitpid", "creat", "link", "unlink",
    "execve", "chdir", "time", "mknod",
    "chmod", "lchown", "break", "oldstat",
    "lseek", "getpid", "mount", "unmount",
    "setuid", "getuid", "stime", "ptrace",
    "alarm", "oldfstat", "pause", "utime",
    "stty", "gtty", "access", "nice",
    "ftime", "sync", "kill", "rename",
    "mkdir", "rmdir", "dup", "pipe",
    "times", "prof", "brk", "setgid",
    "getgid", "signal", "geteuid", "getegid",
    "acct", "umount2", "lock", "ioctl",
    "fcntl", "mpx", "setpgid", "ulimit",
    "oldolduname", "umask", "chroot", "ustat",
    "dup2", "getppid", "getpgrp", "setsid",
    "sigaction", "sgetmask", "ssetmask", "setreuid",
    "setregid", "sigsuspend", "sigpending", "sethostname",
    "setrlimit", "getrusage", "gettimeofday", "settimeofday",
    "getgroups", "setgroups", "select", "symlink",
    "oldlstat", "readlink", "uselib", "swapon",
    "reboot", "readdir", "mmap", "munmap",
    "truncate", "ftruncate", "fchmod", "fchown",
    "getpriority", "setpriority", "profil", "statsfs",
    "fstatsfs", "ioperm", "socketcall", "syslog",
    "setitimer", "getitimer", "stat", "lstat",
    "fstat", "olduname", "iopl", "vhangup",
    "idle", "vm86old", "wait4", "swapoff",
    "sysinfo", "ipc", "fsync", "sigreturn",
    "clone", "setdomainname", "uname", "modify_ldt",
    "adjtimex", "mprotect", "sigprocmask", "create_module",
    "init_module", "delete_module", "get_kernel_syms", "quotactl",
    "getpgid", "fchdir", "bdflush", "sysfs",
    "personality", "afs_syscall", "setfsuid", "setfsgid",
    "_llseek", "getdents", "_newselect", "flock",
    "msync", "readv", "writev", "getsid",
    "fdatasync", "_sysctl", "mlock", "munlock",
    "mlockall", "munlockall", "sched_setparam", "sched_getparam",
    "sched_setscheduler", "sched_getscheduler",
    "sched_yield", "sched_get_priority_max",
    "sched_get_priority_min", "sched_rr_get_interval", "nanosleep", "mremap",
    "setresuid", "getresuid", "vm86", "query_module",
    "poll", "nfsservctl", "setresgid", "getresgid",
    "prctl", "rt_sigreturn", "rt_sigaction", "rt_sigprocmask",
    "rt_sigpending", "rt_sigtimedwait", "rt_sigqueueinfo", "rt_sigsuspend",
    "pread64", "pwrite64", "chown", "getcwd",
    "capget", "capset", "sigaltstack", "sendfile",
    "getpmsg", "putpmsg", "vfork", "ugetrlimit",
    "mmap2", "truncate64", "ftruncate64", "stat64",
    "fstat64", "lstat64", "lchown32", "getuid32",
    "getgid32", "geteuid32", "getegid32", "setreuid32",
    "setregid32", "getgroups32", "setgroups32", "fchown32",
    "setresuid32", "setresgid32", "getresgid32", "chown32",
    "setuid32", "setgid32", "setfsuid32", "getfsgid32",
    "setfsgid32", "pivot_root", "mincore", "madvise",
    "getdents64", "fcntl64", "pass", "pass",
    "gettid", "readahead", "setxattr", "lsetxattr",
    "getxattr", "lgetxattr", "fgetxattr", "listxattr",
    "flistxattr", "removexattr", "lremovexattr", "fremovexattr",
    "tkill", "sendfile64", "futex", "sched_setaffinity",
    "sched_getaffinity", "set_thread_area", "get_thread_area", "io_setup",
    "io_destroy", "io_getevents", "io_submit", "io_cancel",
    "faadvise64", "pass", "exit_group", "lookup_dcookie",
    "epoll_create", "epool_ctl", "epool_wait", "remap_file_pages",
    "set_tid_address", "timer_create", "timer_settime", "timer_gettime",
    "timer_getoverrun", "timer_delete", "clock_settime", "clock_gettime",
    "clock_gettres", "clock_nanosleep", "statfs64", "fstatfs64",
    "tgkill", "utimes", "fadvise64_64", "vserver",
    "mbind", "get_mempolicy", "set_mempolicy", "mq_open",
    "mq_unlink", "mq_timedsend", "mq_timedreceive", "mq_notify",
    "mq_getsetattr", "kexec_load", "waitid", "pass",
    "add_key", "request_key", "keyctl", "ioprio_set",
    "ioprio_get", "inotify_init", "inotify_add_watch", "inotify_rm_watch",
    "migrate_pages", "openat", "mkdirat", "mknodat",
    "futimesat", "fstatat64", "unlinkat", "renameat",
    "linkat", "symlinkat", "readlinkat", "faccesat",
    "pselect6", "ppol", "unshare", "set_robust_list",
    "get_robust_list", "splice", "sync_file_range", "tee",
    "vmsplice", "move_pages", "getcpu", "epoll_pwait",
    "utimensat", "signalfd", "timerfd_create", "eventfd",
    "fallocate", "timerfd_settime", "timerfd_gettime", "signalfd4",
    "eventfd2", "epoll_create1", "dup3", "pipe2",
    "inotify_init1", "preadv", "pwritev", "rt_tgsigqueueinfo",
    "perf_event_open", "recvmmsg", "fanotify_init", "prlimit64",
    "name_to_handle_at", "open_by_handle_at", "clock_adjtime", "syncfs",
    "sendmmsg", "setns", "process_vm_readv", "process_vm_writev",
    "kcmp", "finit_module", "sched_setattr", "sched_getattr",
    "renameat2", "seccomp", "getrandom", "memfd_create",
    "bpf", "execveat", "socket", "connect",
    "listen", "accept4", "getsockopt", "setsockopt",
    "getsockname", "setsockname", "getpeername", "sendto",
    "sendmsg", "recvfrom", "recvmsg", "shutdown",
    "mlock2", "copy_file_range", "preadv2", "pwritev2",
    "pkey_mprotect", "pkey_alloc", "pkey_free", "statx",
    "arch_prctl", "io_pgetevents", "rseq", "pass",
    "pass", "pass", "pass", "pass",
    "pass", "pass", "semget", "semctl",
    "shmat", "shmdt", "msgget", "msgsnd",
    "msgrcv", "msgctl", "clock_gettime64", "clock_settime64",
    "clock_adjtime64", "clock_getres_time64", "clock_nanosleep_time64",
    "timer_gettime64",
    "timer_settime64", "timerfd_gettime64", "timerfd_settime64",
    "ultimensat_time64",
    "pselect6_time64", "ppoll_time64", "pass", "io_pgetevents_time64",
    "recvmmsg_time64", "mq_timedsend_time64", "mq_timedreceive_time64",
    "semtimedop_time64",
    "rt_sigtimedwait_time64", "futex_time64", "sched_rr_get_interval_time64",
    "pidfd_send_signal", "io_uring_setup", "io_uring_enter",
    "io_uring_register", "open_tree", "move_mount", "fsopen", "fsconfig",
    "fsmount", "fspick", "pidfd_open", "clone3",
    "close_range", "pass", "pass", "faccessat2"
]


syscall_foo = f"""
#include "config.h"
#include "utilities/idt/body_int/syscalls/syscall.h"
#include "utilities/idt/idt.h"
#include "config.h"

#define REAL_TOTAL_INT_CREATED {len(list_syscalls)}

"""


tabellone = """
i32 (*table_syscalls[OS_TOTAL_INTERRUPTS])(struct regs_t *) = {
"""

call_do_int80h = """
O3 i32 do_int80h(struct regs_t *r)
{
    if (r->eax > REAL_TOTAL_INT_CREATED - 1)
        return -ENOSYS;     // invalid no syscall

    return table_syscalls[r->eax](r);
}
"""


def main(argc: int, argv: list) -> int:
    global tabellone, syscall_foo

    for idx, element in enumerate(list_syscalls):
        if element == "pass":
            continue

        element = "sys_" + element
        tabellone += "\n" + f"\t{element},\t//eax = {idx}"
        syscall_foo += f"i32 {element}(struct regs_t* r)" + "\n"
        syscall_foo += "{\n"
        syscall_foo += "\treturn 0;\n"
        syscall_foo += "}\n\n\n"

    tabellone += "\n};\n"
    with open("./src/utilities/idt/body_int/syscalls/syscall.c", "w") as f_out:
        f_out.write(syscall_foo + "\n" + tabellone + "\n" + call_do_int80h)

    return 0


if __name__ == "__main__":
    sys.exit(main(len(sys.argv), sys.argv))
