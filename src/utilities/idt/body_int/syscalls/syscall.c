
#include "config.h"
#include "utilities/idt/body_int/syscalls/syscall.h"
#include "utilities/idt/idt.h"


#define REAL_TOTAL_INT_CREATED 430


i32 sys_restart_syscall(struct regs_t* r)
{
	return 0;// do_restart_syscall(r);
}


i32 sys_exit(struct regs_t* r)
{
	return 0;// do_exit(r);
}


i32 sys_fork(struct regs_t* r)
{
	return 0;// do_fork(r);
}


i32 sys_read(struct regs_t* r)
{
	return 0;// do_read(r);
}


i32 sys_write(struct regs_t* r)
{
	r->eax = do_write(r->ebx, (void*) r->ecx, r->edx);
	return r->eax;
}


i32 sys_open(struct regs_t* r)
{
	return 0;// do_open(r);
}


i32 sys_close(struct regs_t* r)
{
	return 0;// do_close(r);
}


i32 sys_waitpid(struct regs_t* r)
{
	return 0;// do_waitpid(r);
}


i32 sys_creat(struct regs_t* r)
{
	return 0;// do_creat(r);
}


i32 sys_link(struct regs_t* r)
{
	return 0;// do_link(r);
}


i32 sys_unlink(struct regs_t* r)
{
	return 0;// do_unlink(r);
}


i32 sys_execve(struct regs_t* r)
{
	return 0;// do_execve(r);
}


i32 sys_chdir(struct regs_t* r)
{
	return 0;// do_chdir(r);
}


i32 sys_time(struct regs_t* r)
{
	return 0;// do_time(r);
}


i32 sys_mknod(struct regs_t* r)
{
	return 0;// do_mknod(r);
}


i32 sys_chmod(struct regs_t* r)
{
	return 0;// do_chmod(r);
}


i32 sys_lchown(struct regs_t* r)
{
	return 0;// do_lchown(r);
}


i32 sys_break(struct regs_t* r)
{
	return 0;// do_break(r);
}


i32 sys_oldstat(struct regs_t* r)
{
	return 0;// do_oldstat(r);
}


i32 sys_lseek(struct regs_t* r)
{
	return 0;// do_lseek(r);
}


i32 sys_getpid(struct regs_t* r)
{
	return 0;// do_getpid(r);
}


i32 sys_mount(struct regs_t* r)
{
	return 0;// do_mount(r);
}


i32 sys_unmount(struct regs_t* r)
{
	return 0;// do_unmount(r);
}


i32 sys_setuid(struct regs_t* r)
{
	return 0;// do_setuid(r);
}


i32 sys_getuid(struct regs_t* r)
{
	return 0;// do_getuid(r);
}


i32 sys_stime(struct regs_t* r)
{
	return 0;// do_stime(r);
}


i32 sys_ptrace(struct regs_t* r)
{
	return 0;// do_ptrace(r);
}


i32 sys_alarm(struct regs_t* r)
{
	return 0;// do_alarm(r);
}


i32 sys_oldfstat(struct regs_t* r)
{
	return 0;// do_oldfstat(r);
}


i32 sys_pause(struct regs_t* r)
{
	return 0;// do_pause(r);
}


i32 sys_utime(struct regs_t* r)
{
	return 0;// do_utime(r);
}


i32 sys_stty(struct regs_t* r)
{
	return 0;// do_stty(r);
}


i32 sys_gtty(struct regs_t* r)
{
	return 0;// do_gtty(r);
}


i32 sys_access(struct regs_t* r)
{
	return 0;// do_access(r);
}


i32 sys_nice(struct regs_t* r)
{
	return 0;// do_nice(r);
}


i32 sys_ftime(struct regs_t* r)
{
	return 0;// do_ftime(r);
}


i32 sys_sync(struct regs_t* r)
{
	return 0;// do_sync(r);
}


i32 sys_kill(struct regs_t* r)
{
	return 0;// do_kill(r);
}


i32 sys_rename(struct regs_t* r)
{
	return 0;// do_rename(r);
}


i32 sys_mkdir(struct regs_t* r)
{
	return 0;// do_mkdir(r);
}


i32 sys_rmdir(struct regs_t* r)
{
	return 0;// do_rmdir(r);
}


i32 sys_dup(struct regs_t* r)
{
	return 0;// do_dup(r);
}


i32 sys_pipe(struct regs_t* r)
{
	return 0;// do_pipe(r);
}


i32 sys_times(struct regs_t* r)
{
	return 0;// do_times(r);
}


i32 sys_prof(struct regs_t* r)
{
	return 0;// do_prof(r);
}


i32 sys_brk(struct regs_t* r)
{
	return 0;// do_brk(r);
}


i32 sys_setgid(struct regs_t* r)
{
	return 0;// do_setgid(r);
}


i32 sys_getgid(struct regs_t* r)
{
	return 0;// do_getgid(r);
}


i32 sys_signal(struct regs_t* r)
{
	return 0;// do_signal(r);
}


i32 sys_geteuid(struct regs_t* r)
{
	return 0;// do_geteuid(r);
}


i32 sys_getegid(struct regs_t* r)
{
	return 0;// do_getegid(r);
}


i32 sys_acct(struct regs_t* r)
{
	return 0;// do_acct(r);
}


i32 sys_umount2(struct regs_t* r)
{
	return 0;// do_umount2(r);
}


i32 sys_lock(struct regs_t* r)
{
	return 0;// do_lock(r);
}


i32 sys_ioctl(struct regs_t* r)
{
	return 0;// do_ioctl(r);
}


i32 sys_fcntl(struct regs_t* r)
{
	return 0;// do_fcntl(r);
}


i32 sys_mpx(struct regs_t* r)
{
	return 0;// do_mpx(r);
}


i32 sys_setpgid(struct regs_t* r)
{
	return 0;// do_setpgid(r);
}


i32 sys_ulimit(struct regs_t* r)
{
	return 0;// do_ulimit(r);
}


i32 sys_oldolduname(struct regs_t* r)
{
	return 0;// do_oldolduname(r);
}


i32 sys_umask(struct regs_t* r)
{
	return 0;// do_umask(r);
}


i32 sys_chroot(struct regs_t* r)
{
	return 0;// do_chroot(r);
}


i32 sys_ustat(struct regs_t* r)
{
	return 0;// do_ustat(r);
}


i32 sys_dup2(struct regs_t* r)
{
	return 0;// do_dup2(r);
}


i32 sys_getppid(struct regs_t* r)
{
	return 0;// do_getppid(r);
}


i32 sys_getpgrp(struct regs_t* r)
{
	return 0;// do_getpgrp(r);
}


i32 sys_setsid(struct regs_t* r)
{
	return 0;// do_setsid(r);
}


i32 sys_sigaction(struct regs_t* r)
{
	return 0;// do_sigaction(r);
}


i32 sys_sgetmask(struct regs_t* r)
{
	return 0;// do_sgetmask(r);
}


i32 sys_ssetmask(struct regs_t* r)
{
	return 0;// do_ssetmask(r);
}


i32 sys_setreuid(struct regs_t* r)
{
	return 0;// do_setreuid(r);
}


i32 sys_setregid(struct regs_t* r)
{
	return 0;// do_setregid(r);
}


i32 sys_sigsuspend(struct regs_t* r)
{
	return 0;// do_sigsuspend(r);
}


i32 sys_sigpending(struct regs_t* r)
{
	return 0;// do_sigpending(r);
}


i32 sys_sethostname(struct regs_t* r)
{
	return 0;// do_sethostname(r);
}


i32 sys_setrlimit(struct regs_t* r)
{
	return 0;// do_setrlimit(r);
}


i32 sys_getrusage(struct regs_t* r)
{
	return 0;// do_getrusage(r);
}


i32 sys_gettimeofday(struct regs_t* r)
{
	return 0;// do_gettimeofday(r);
}


i32 sys_settimeofday(struct regs_t* r)
{
	return 0;// do_settimeofday(r);
}


i32 sys_getgroups(struct regs_t* r)
{
	return 0;// do_getgroups(r);
}


i32 sys_setgroups(struct regs_t* r)
{
	return 0;// do_setgroups(r);
}


i32 sys_select(struct regs_t* r)
{
	return 0;// do_select(r);
}


i32 sys_symlink(struct regs_t* r)
{
	return 0;// do_symlink(r);
}


i32 sys_oldlstat(struct regs_t* r)
{
	return 0;// do_oldlstat(r);
}


i32 sys_readlink(struct regs_t* r)
{
	return 0;// do_readlink(r);
}


i32 sys_uselib(struct regs_t* r)
{
	return 0;// do_uselib(r);
}


i32 sys_swapon(struct regs_t* r)
{
	return 0;// do_swapon(r);
}


i32 sys_reboot(struct regs_t* r)
{
	return do_reboot(r);
}


i32 sys_readdir(struct regs_t* r)
{
	return 0;// do_readdir(r);
}


i32 sys_mmap(struct regs_t* r)
{
	return 0;// do_mmap(r);
}


i32 sys_munmap(struct regs_t* r)
{
	return 0;// do_munmap(r);
}


i32 sys_truncate(struct regs_t* r)
{
	return 0;// do_truncate(r);
}


i32 sys_ftruncate(struct regs_t* r)
{
	return 0;// do_ftruncate(r);
}


i32 sys_fchmod(struct regs_t* r)
{
	return 0;// do_fchmod(r);
}


i32 sys_fchown(struct regs_t* r)
{
	return 0;// do_fchown(r);
}


i32 sys_getpriority(struct regs_t* r)
{
	return 0;// do_getpriority(r);
}


i32 sys_setpriority(struct regs_t* r)
{
	return 0;// do_setpriority(r);
}


i32 sys_profil(struct regs_t* r)
{
	return 0;// do_profil(r);
}


i32 sys_statsfs(struct regs_t* r)
{
	return 0;// do_statsfs(r);
}


i32 sys_fstatsfs(struct regs_t* r)
{
	return 0;// do_fstatsfs(r);
}


i32 sys_ioperm(struct regs_t* r)
{
	return 0;// do_ioperm(r);
}


i32 sys_socketcall(struct regs_t* r)
{
	return 0;// do_socketcall(r);
}


i32 sys_syslog(struct regs_t* r)
{
	return 0;// do_syslog(r);
}


i32 sys_setitimer(struct regs_t* r)
{
	return 0;// do_setitimer(r);
}


i32 sys_getitimer(struct regs_t* r)
{
	return 0;// do_getitimer(r);
}


i32 sys_stat(struct regs_t* r)
{
	return 0;// do_stat(r);
}


i32 sys_lstat(struct regs_t* r)
{
	return 0;// do_lstat(r);
}


i32 sys_fstat(struct regs_t* r)
{
	return 0;// do_fstat(r);
}


i32 sys_olduname(struct regs_t* r)
{
	return 0;// do_olduname(r);
}


i32 sys_iopl(struct regs_t* r)
{
	return 0;// do_iopl(r);
}


i32 sys_vhangup(struct regs_t* r)
{
	return 0;// do_vhangup(r);
}


i32 sys_idle(struct regs_t* r)
{
	return 0;// do_idle(r);
}


i32 sys_vm86old(struct regs_t* r)
{
	return 0;// do_vm86old(r);
}


i32 sys_wait4(struct regs_t* r)
{
	return 0;// do_wait4(r);
}


i32 sys_swapoff(struct regs_t* r)
{
	return 0;// do_swapoff(r);
}


i32 sys_sysinfo(struct regs_t* r)
{
	return 0;// do_sysinfo(r);
}


i32 sys_ipc(struct regs_t* r)
{
	return 0;// do_ipc(r);
}


i32 sys_fsync(struct regs_t* r)
{
	return 0;// do_fsync(r);
}


i32 sys_sigreturn(struct regs_t* r)
{
	return 0;// do_sigreturn(r);
}


i32 sys_clone(struct regs_t* r)
{
	return 0;// do_clone(r);
}


i32 sys_setdomainname(struct regs_t* r)
{
	return 0;// do_setdomainname(r);
}


i32 sys_uname(struct regs_t* r)
{
	return 0;// do_uname(r);
}


i32 sys_modify_ldt(struct regs_t* r)
{
	return 0;// do_modify_ldt(r);
}


i32 sys_adjtimex(struct regs_t* r)
{
	return 0;// do_adjtimex(r);
}


i32 sys_mprotect(struct regs_t* r)
{
	return 0;// do_mprotect(r);
}


i32 sys_sigprocmask(struct regs_t* r)
{
	return 0;// do_sigprocmask(r);
}


i32 sys_create_module(struct regs_t* r)
{
	return 0;// do_create_module(r);
}


i32 sys_init_module(struct regs_t* r)
{
	return 0;// do_init_module(r);
}


i32 sys_delete_module(struct regs_t* r)
{
	return 0;// do_delete_module(r);
}


i32 sys_get_kernel_syms(struct regs_t* r)
{
	return 0;// do_get_kernel_syms(r);
}


i32 sys_quotactl(struct regs_t* r)
{
	return 0;// do_quotactl(r);
}


i32 sys_getpgid(struct regs_t* r)
{
	return 0;// do_getpgid(r);
}


i32 sys_fchdir(struct regs_t* r)
{
	return 0;// do_fchdir(r);
}


i32 sys_bdflush(struct regs_t* r)
{
	return 0;// do_bdflush(r);
}


i32 sys_sysfs(struct regs_t* r)
{
	return 0;// do_sysfs(r);
}


i32 sys_personality(struct regs_t* r)
{
	return 0;// do_personality(r);
}


i32 sys_afs_syscall(struct regs_t* r)
{
	return 0;// do_afs_syscall(r);
}


i32 sys_setfsuid(struct regs_t* r)
{
	return 0;// do_setfsuid(r);
}


i32 sys_setfsgid(struct regs_t* r)
{
	return 0;// do_setfsgid(r);
}


i32 sys__llseek(struct regs_t* r)
{
	return 0;// do__llseek(r);
}


i32 sys_getdents(struct regs_t* r)
{
	return 0;// do_getdents(r);
}


i32 sys__newselect(struct regs_t* r)
{
	return 0;// do__newselect(r);
}


i32 sys_flock(struct regs_t* r)
{
	return 0;// do_flock(r);
}


i32 sys_msync(struct regs_t* r)
{
	return 0;// do_msync(r);
}


i32 sys_readv(struct regs_t* r)
{
	return 0;// do_readv(r);
}


i32 sys_writev(struct regs_t* r)
{
	return 0;// do_writev(r);
}


i32 sys_getsid(struct regs_t* r)
{
	return 0;// do_getsid(r);
}


i32 sys_fdatasync(struct regs_t* r)
{
	return 0;// do_fdatasync(r);
}


i32 sys__sysctl(struct regs_t* r)
{
	return 0;// do__sysctl(r);
}


i32 sys_mlock(struct regs_t* r)
{
	return 0;// do_mlock(r);
}


i32 sys_munlock(struct regs_t* r)
{
	return 0;// do_munlock(r);
}


i32 sys_mlockall(struct regs_t* r)
{
	return 0;// do_mlockall(r);
}


i32 sys_munlockall(struct regs_t* r)
{
	return 0;// do_munlockall(r);
}


i32 sys_sched_setparam(struct regs_t* r)
{
	return 0;// do_sched_setparam(r);
}


i32 sys_sched_getparam(struct regs_t* r)
{
	return 0;// do_sched_getparam(r);
}


i32 sys_sched_setscheduler(struct regs_t* r)
{
	return 0;// do_sched_setscheduler(r);
}


i32 sys_sched_getscheduler(struct regs_t* r)
{
	return 0;// do_sched_getscheduler(r);
}


i32 sys_sched_yield(struct regs_t* r)
{
	return 0;// do_sched_yield(r);
}


i32 sys_sched_get_priority_max(struct regs_t* r)
{
	return 0;// do_sched_get_priority_max(r);
}


i32 sys_sched_get_priority_min(struct regs_t* r)
{
	return 0;// do_sched_get_priority_min(r);
}


i32 sys_sched_rr_get_interval(struct regs_t* r)
{
	return 0;// do_sched_rr_get_interval(r);
}


i32 sys_nanosleep(struct regs_t* r)
{
	return 0;// do_nanosleep(r);
}


i32 sys_mremap(struct regs_t* r)
{
	return 0;// do_mremap(r);
}


i32 sys_setresuid(struct regs_t* r)
{
	return 0;// do_setresuid(r);
}


i32 sys_getresuid(struct regs_t* r)
{
	return 0;// do_getresuid(r);
}


i32 sys_vm86(struct regs_t* r)
{
	return 0;// do_vm86(r);
}


i32 sys_query_module(struct regs_t* r)
{
	return 0;// do_query_module(r);
}


i32 sys_poll(struct regs_t* r)
{
	return 0;// do_poll(r);
}


i32 sys_nfsservctl(struct regs_t* r)
{
	return 0;// do_nfsservctl(r);
}


i32 sys_setresgid(struct regs_t* r)
{
	return 0;// do_setresgid(r);
}


i32 sys_getresgid(struct regs_t* r)
{
	return 0;// do_getresgid(r);
}


i32 sys_prctl(struct regs_t* r)
{
	return 0;// do_prctl(r);
}


i32 sys_rt_sigreturn(struct regs_t* r)
{
	return 0;// do_rt_sigreturn(r);
}


i32 sys_rt_sigaction(struct regs_t* r)
{
	return 0;// do_rt_sigaction(r);
}


i32 sys_rt_sigprocmask(struct regs_t* r)
{
	return 0;// do_rt_sigprocmask(r);
}


i32 sys_rt_sigpending(struct regs_t* r)
{
	return 0;// do_rt_sigpending(r);
}


i32 sys_rt_sigtimedwait(struct regs_t* r)
{
	return 0;// do_rt_sigtimedwait(r);
}


i32 sys_rt_sigqueueinfo(struct regs_t* r)
{
	return 0;// do_rt_sigqueueinfo(r);
}


i32 sys_rt_sigsuspend(struct regs_t* r)
{
	return 0;// do_rt_sigsuspend(r);
}


i32 sys_pread64(struct regs_t* r)
{
	return 0;// do_pread64(r);
}


i32 sys_pwrite64(struct regs_t* r)
{
	return 0;// do_pwrite64(r);
}


i32 sys_chown(struct regs_t* r)
{
	return 0;// do_chown(r);
}


i32 sys_getcwd(struct regs_t* r)
{
	return 0;// do_getcwd(r);
}


i32 sys_capget(struct regs_t* r)
{
	return 0;// do_capget(r);
}


i32 sys_capset(struct regs_t* r)
{
	return 0;// do_capset(r);
}


i32 sys_sigaltstack(struct regs_t* r)
{
	return 0;// do_sigaltstack(r);
}


i32 sys_sendfile(struct regs_t* r)
{
	return 0;// do_sendfile(r);
}


i32 sys_getpmsg(struct regs_t* r)
{
	return 0;// do_getpmsg(r);
}


i32 sys_putpmsg(struct regs_t* r)
{
	return 0;// do_putpmsg(r);
}


i32 sys_vfork(struct regs_t* r)
{
	return 0;// do_vfork(r);
}


i32 sys_ugetrlimit(struct regs_t* r)
{
	return 0;// do_ugetrlimit(r);
}


i32 sys_mmap2(struct regs_t* r)
{
	return 0;// do_mmap2(r);
}


i32 sys_truncate64(struct regs_t* r)
{
	return 0;// do_truncate64(r);
}


i32 sys_ftruncate64(struct regs_t* r)
{
	return 0;// do_ftruncate64(r);
}


i32 sys_stat64(struct regs_t* r)
{
	return 0;// do_stat64(r);
}


i32 sys_fstat64(struct regs_t* r)
{
	return 0;// do_fstat64(r);
}


i32 sys_lstat64(struct regs_t* r)
{
	return 0;// do_lstat64(r);
}


i32 sys_lchown32(struct regs_t* r)
{
	return 0;// do_lchown32(r);
}


i32 sys_getuid32(struct regs_t* r)
{
	return 0;// do_getuid32(r);
}


i32 sys_getgid32(struct regs_t* r)
{
	return 0;// do_getgid32(r);
}


i32 sys_geteuid32(struct regs_t* r)
{
	return 0;// do_geteuid32(r);
}


i32 sys_getegid32(struct regs_t* r)
{
	return 0;// do_getegid32(r);
}


i32 sys_setreuid32(struct regs_t* r)
{
	return 0;// do_setreuid32(r);
}


i32 sys_setregid32(struct regs_t* r)
{
	return 0;// do_setregid32(r);
}


i32 sys_getgroups32(struct regs_t* r)
{
	return 0;// do_getgroups32(r);
}


i32 sys_setgroups32(struct regs_t* r)
{
	return 0;// do_setgroups32(r);
}


i32 sys_fchown32(struct regs_t* r)
{
	return 0;// do_fchown32(r);
}


i32 sys_setresuid32(struct regs_t* r)
{
	return 0;// do_setresuid32(r);
}


i32 sys_setresgid32(struct regs_t* r)
{
	return 0;// do_setresgid32(r);
}


i32 sys_getresgid32(struct regs_t* r)
{
	return 0;// do_getresgid32(r);
}


i32 sys_chown32(struct regs_t* r)
{
	return 0;// do_chown32(r);
}


i32 sys_setuid32(struct regs_t* r)
{
	return 0;// do_setuid32(r);
}


i32 sys_setgid32(struct regs_t* r)
{
	return 0;// do_setgid32(r);
}


i32 sys_setfsuid32(struct regs_t* r)
{
	return 0;// do_setfsuid32(r);
}


i32 sys_getfsgid32(struct regs_t* r)
{
	return 0;// do_getfsgid32(r);
}


i32 sys_setfsgid32(struct regs_t* r)
{
	return 0;// do_setfsgid32(r);
}


i32 sys_pivot_root(struct regs_t* r)
{
	return 0;// do_pivot_root(r);
}


i32 sys_mincore(struct regs_t* r)
{
	return 0;// do_mincore(r);
}


i32 sys_madvise(struct regs_t* r)
{
	return 0;// do_madvise(r);
}


i32 sys_getdents64(struct regs_t* r)
{
	return 0;// do_getdents64(r);
}


i32 sys_fcntl64(struct regs_t* r)
{
	return 0;// do_fcntl64(r);
}


i32 sys_gettid(struct regs_t* r)
{
	return 0;// do_gettid(r);
}


i32 sys_readahead(struct regs_t* r)
{
	return 0;// do_readahead(r);
}


i32 sys_setxattr(struct regs_t* r)
{
	return 0;// do_setxattr(r);
}


i32 sys_lsetxattr(struct regs_t* r)
{
	return 0;// do_lsetxattr(r);
}


i32 sys_getxattr(struct regs_t* r)
{
	return 0;// do_getxattr(r);
}


i32 sys_lgetxattr(struct regs_t* r)
{
	return 0;// do_lgetxattr(r);
}


i32 sys_fgetxattr(struct regs_t* r)
{
	return 0;// do_fgetxattr(r);
}


i32 sys_listxattr(struct regs_t* r)
{
	return 0;// do_listxattr(r);
}


i32 sys_flistxattr(struct regs_t* r)
{
	return 0;// do_flistxattr(r);
}


i32 sys_removexattr(struct regs_t* r)
{
	return 0;// do_removexattr(r);
}


i32 sys_lremovexattr(struct regs_t* r)
{
	return 0;// do_lremovexattr(r);
}


i32 sys_fremovexattr(struct regs_t* r)
{
	return 0;// do_fremovexattr(r);
}


i32 sys_tkill(struct regs_t* r)
{
	return 0;// do_tkill(r);
}


i32 sys_sendfile64(struct regs_t* r)
{
	return 0;// do_sendfile64(r);
}


i32 sys_futex(struct regs_t* r)
{
	return 0;// do_futex(r);
}


i32 sys_sched_setaffinity(struct regs_t* r)
{
	return 0;// do_sched_setaffinity(r);
}


i32 sys_sched_getaffinity(struct regs_t* r)
{
	return 0;// do_sched_getaffinity(r);
}


i32 sys_set_thread_area(struct regs_t* r)
{
	return 0;// do_set_thread_area(r);
}


i32 sys_get_thread_area(struct regs_t* r)
{
	return 0;// do_get_thread_area(r);
}


i32 sys_io_setup(struct regs_t* r)
{
	return 0;// do_io_setup(r);
}


i32 sys_io_destroy(struct regs_t* r)
{
	return 0;// do_io_destroy(r);
}


i32 sys_io_getevents(struct regs_t* r)
{
	return 0;// do_io_getevents(r);
}


i32 sys_io_submit(struct regs_t* r)
{
	return 0;// do_io_submit(r);
}


i32 sys_io_cancel(struct regs_t* r)
{
	return 0;// do_io_cancel(r);
}


i32 sys_faadvise64(struct regs_t* r)
{
	return 0;// do_faadvise64(r);
}


i32 sys_exit_group(struct regs_t* r)
{
	return 0;// do_exit_group(r);
}


i32 sys_lookup_dcookie(struct regs_t* r)
{
	return 0;// do_lookup_dcookie(r);
}


i32 sys_epoll_create(struct regs_t* r)
{
	return 0;// do_epoll_create(r);
}


i32 sys_epool_ctl(struct regs_t* r)
{
	return 0;// do_epool_ctl(r);
}


i32 sys_epool_wait(struct regs_t* r)
{
	return 0;// do_epool_wait(r);
}


i32 sys_remap_file_pages(struct regs_t* r)
{
	return 0;// do_remap_file_pages(r);
}


i32 sys_set_tid_address(struct regs_t* r)
{
	return 0;// do_set_tid_address(r);
}


i32 sys_timer_create(struct regs_t* r)
{
	return 0;// do_timer_create(r);
}


i32 sys_timer_settime(struct regs_t* r)
{
	return 0;// do_timer_settime(r);
}


i32 sys_timer_gettime(struct regs_t* r)
{
	return 0;// do_timer_gettime(r);
}


i32 sys_timer_getoverrun(struct regs_t* r)
{
	return 0;// do_timer_getoverrun(r);
}


i32 sys_timer_delete(struct regs_t* r)
{
	return 0;// do_timer_delete(r);
}


i32 sys_clock_settime(struct regs_t* r)
{
	return 0;// do_clock_settime(r);
}


i32 sys_clock_gettime(struct regs_t* r)
{
	return 0;// do_clock_gettime(r);
}


i32 sys_clock_gettres(struct regs_t* r)
{
	return 0;// do_clock_gettres(r);
}


i32 sys_clock_nanosleep(struct regs_t* r)
{
	return 0;// do_clock_nanosleep(r);
}


i32 sys_statfs64(struct regs_t* r)
{
	return 0;// do_statfs64(r);
}


i32 sys_fstatfs64(struct regs_t* r)
{
	return 0;// do_fstatfs64(r);
}


i32 sys_tgkill(struct regs_t* r)
{
	return 0;// do_tgkill(r);
}


i32 sys_utimes(struct regs_t* r)
{
	return 0;// do_utimes(r);
}


i32 sys_fadvise64_64(struct regs_t* r)
{
	return 0;// do_fadvise64_64(r);
}


i32 sys_vserver(struct regs_t* r)
{
	return 0;// do_vserver(r);
}


i32 sys_mbind(struct regs_t* r)
{
	return 0;// do_mbind(r);
}


i32 sys_get_mempolicy(struct regs_t* r)
{
	return 0;// do_get_mempolicy(r);
}


i32 sys_set_mempolicy(struct regs_t* r)
{
	return 0;// do_set_mempolicy(r);
}


i32 sys_mq_open(struct regs_t* r)
{
	return 0;// do_mq_open(r);
}


i32 sys_mq_unlink(struct regs_t* r)
{
	return 0;// do_mq_unlink(r);
}


i32 sys_mq_timedsend(struct regs_t* r)
{
	return 0;// do_mq_timedsend(r);
}


i32 sys_mq_timedreceive(struct regs_t* r)
{
	return 0;// do_mq_timedreceive(r);
}


i32 sys_mq_notify(struct regs_t* r)
{
	return 0;// do_mq_notify(r);
}


i32 sys_mq_getsetattr(struct regs_t* r)
{
	return 0;// do_mq_getsetattr(r);
}


i32 sys_kexec_load(struct regs_t* r)
{
	return 0;// do_kexec_load(r);
}


i32 sys_waitid(struct regs_t* r)
{
	return 0;// do_waitid(r);
}


i32 sys_add_key(struct regs_t* r)
{
	return 0;// do_add_key(r);
}


i32 sys_request_key(struct regs_t* r)
{
	return 0;// do_request_key(r);
}


i32 sys_keyctl(struct regs_t* r)
{
	return 0;// do_keyctl(r);
}


i32 sys_ioprio_set(struct regs_t* r)
{
	return 0;// do_ioprio_set(r);
}


i32 sys_ioprio_get(struct regs_t* r)
{
	return 0;// do_ioprio_get(r);
}


i32 sys_inotify_init(struct regs_t* r)
{
	return 0;// do_inotify_init(r);
}


i32 sys_inotify_add_watch(struct regs_t* r)
{
	return 0;// do_inotify_add_watch(r);
}


i32 sys_inotify_rm_watch(struct regs_t* r)
{
	return 0;// do_inotify_rm_watch(r);
}


i32 sys_migrate_pages(struct regs_t* r)
{
	return 0;// do_migrate_pages(r);
}


i32 sys_openat(struct regs_t* r)
{
	return 0;// do_openat(r);
}


i32 sys_mkdirat(struct regs_t* r)
{
	return 0;// do_mkdirat(r);
}


i32 sys_mknodat(struct regs_t* r)
{
	return 0;// do_mknodat(r);
}


i32 sys_futimesat(struct regs_t* r)
{
	return 0;// do_futimesat(r);
}


i32 sys_fstatat64(struct regs_t* r)
{
	return 0;// do_fstatat64(r);
}


i32 sys_unlinkat(struct regs_t* r)
{
	return 0;// do_unlinkat(r);
}


i32 sys_renameat(struct regs_t* r)
{
	return 0;// do_renameat(r);
}


i32 sys_linkat(struct regs_t* r)
{
	return 0;// do_linkat(r);
}


i32 sys_symlinkat(struct regs_t* r)
{
	return 0;// do_symlinkat(r);
}


i32 sys_readlinkat(struct regs_t* r)
{
	return 0;// do_readlinkat(r);
}


i32 sys_faccesat(struct regs_t* r)
{
	return 0;// do_faccesat(r);
}


i32 sys_pselect6(struct regs_t* r)
{
	return 0;// do_pselect6(r);
}


i32 sys_ppol(struct regs_t* r)
{
	return 0;// do_ppol(r);
}


i32 sys_unshare(struct regs_t* r)
{
	return 0;// do_unshare(r);
}


i32 sys_set_robust_list(struct regs_t* r)
{
	return 0;// do_set_robust_list(r);
}


i32 sys_get_robust_list(struct regs_t* r)
{
	return 0;// do_get_robust_list(r);
}


i32 sys_splice(struct regs_t* r)
{
	return 0;// do_splice(r);
}


i32 sys_sync_file_range(struct regs_t* r)
{
	return 0;// do_sync_file_range(r);
}


i32 sys_tee(struct regs_t* r)
{
	return 0;// do_tee(r);
}


i32 sys_vmsplice(struct regs_t* r)
{
	return 0;// do_vmsplice(r);
}


i32 sys_move_pages(struct regs_t* r)
{
	return 0;// do_move_pages(r);
}


i32 sys_getcpu(struct regs_t* r)
{
	return 0;// do_getcpu(r);
}


i32 sys_epoll_pwait(struct regs_t* r)
{
	return 0;// do_epoll_pwait(r);
}


i32 sys_utimensat(struct regs_t* r)
{
	return 0;// do_utimensat(r);
}


i32 sys_signalfd(struct regs_t* r)
{
	return 0;// do_signalfd(r);
}


i32 sys_timerfd_create(struct regs_t* r)
{
	return 0;// do_timerfd_create(r);
}


i32 sys_eventfd(struct regs_t* r)
{
	return 0;// do_eventfd(r);
}


i32 sys_fallocate(struct regs_t* r)
{
	return 0;// do_fallocate(r);
}


i32 sys_timerfd_settime(struct regs_t* r)
{
	return 0;// do_timerfd_settime(r);
}


i32 sys_timerfd_gettime(struct regs_t* r)
{
	return 0;// do_timerfd_gettime(r);
}


i32 sys_signalfd4(struct regs_t* r)
{
	return 0;// do_signalfd4(r);
}


i32 sys_eventfd2(struct regs_t* r)
{
	return 0;// do_eventfd2(r);
}


i32 sys_epoll_create1(struct regs_t* r)
{
	return 0;// do_epoll_create1(r);
}


i32 sys_dup3(struct regs_t* r)
{
	return 0;// do_dup3(r);
}


i32 sys_pipe2(struct regs_t* r)
{
	return 0;// do_pipe2(r);
}


i32 sys_inotify_init1(struct regs_t* r)
{
	return 0;// do_inotify_init1(r);
}


i32 sys_preadv(struct regs_t* r)
{
	return 0;// do_preadv(r);
}


i32 sys_pwritev(struct regs_t* r)
{
	return 0;// do_pwritev(r);
}


i32 sys_rt_tgsigqueueinfo(struct regs_t* r)
{
	return 0;// do_rt_tgsigqueueinfo(r);
}


i32 sys_perf_event_open(struct regs_t* r)
{
	return 0;// do_perf_event_open(r);
}


i32 sys_recvmmsg(struct regs_t* r)
{
	return 0;// do_recvmmsg(r);
}


i32 sys_fanotify_init(struct regs_t* r)
{
	return 0;// do_fanotify_init(r);
}


i32 sys_prlimit64(struct regs_t* r)
{
	return 0;// do_prlimit64(r);
}


i32 sys_name_to_handle_at(struct regs_t* r)
{
	return 0;// do_name_to_handle_at(r);
}


i32 sys_open_by_handle_at(struct regs_t* r)
{
	return 0;// do_open_by_handle_at(r);
}


i32 sys_clock_adjtime(struct regs_t* r)
{
	return 0;// do_clock_adjtime(r);
}


i32 sys_syncfs(struct regs_t* r)
{
	return 0;// do_syncfs(r);
}


i32 sys_sendmmsg(struct regs_t* r)
{
	return 0;// do_sendmmsg(r);
}


i32 sys_setns(struct regs_t* r)
{
	return 0;// do_setns(r);
}


i32 sys_process_vm_readv(struct regs_t* r)
{
	return 0;// do_process_vm_readv(r);
}


i32 sys_process_vm_writev(struct regs_t* r)
{
	return 0;// do_process_vm_writev(r);
}


i32 sys_kcmp(struct regs_t* r)
{
	return 0;// do_kcmp(r);
}


i32 sys_finit_module(struct regs_t* r)
{
	return 0;// do_finit_module(r);
}


i32 sys_sched_setattr(struct regs_t* r)
{
	return 0;// do_sched_setattr(r);
}


i32 sys_sched_getattr(struct regs_t* r)
{
	return 0;// do_sched_getattr(r);
}


i32 sys_renameat2(struct regs_t* r)
{
	return 0;// do_renameat2(r);
}


i32 sys_seccomp(struct regs_t* r)
{
	return 0;// do_seccomp(r);
}


i32 sys_getrandom(struct regs_t* r)
{
	return 0;// do_getrandom(r);
}


i32 sys_memfd_create(struct regs_t* r)
{
	return 0;// do_memfd_create(r);
}


i32 sys_bpf(struct regs_t* r)
{
	return 0;// do_bpf(r);
}


i32 sys_execveat(struct regs_t* r)
{
	return 0;// do_execveat(r);
}


i32 sys_socket(struct regs_t* r)
{
	return 0;// do_socket(r);
}


i32 sys_connect(struct regs_t* r)
{
	return 0;// do_connect(r);
}


i32 sys_listen(struct regs_t* r)
{
	return 0;// do_listen(r);
}


i32 sys_accept4(struct regs_t* r)
{
	return 0;// do_accept4(r);
}


i32 sys_getsockopt(struct regs_t* r)
{
	return 0;// do_getsockopt(r);
}


i32 sys_setsockopt(struct regs_t* r)
{
	return 0;// do_setsockopt(r);
}


i32 sys_getsockname(struct regs_t* r)
{
	return 0;// do_getsockname(r);
}


i32 sys_setsockname(struct regs_t* r)
{
	return 0;// do_setsockname(r);
}


i32 sys_getpeername(struct regs_t* r)
{
	return 0;// do_getpeername(r);
}


i32 sys_sendto(struct regs_t* r)
{
	return 0;// do_sendto(r);
}


i32 sys_sendmsg(struct regs_t* r)
{
	return 0;// do_sendmsg(r);
}


i32 sys_recvfrom(struct regs_t* r)
{
	return 0;// do_recvfrom(r);
}


i32 sys_recvmsg(struct regs_t* r)
{
	return 0;// do_recvmsg(r);
}


i32 sys_shutdown(struct regs_t* r)
{
	return 0;// do_shutdown(r);
}


i32 sys_mlock2(struct regs_t* r)
{
	return 0;// do_mlock2(r);
}


i32 sys_copy_file_range(struct regs_t* r)
{
	return 0;// do_copy_file_range(r);
}


i32 sys_preadv2(struct regs_t* r)
{
	return 0;// do_preadv2(r);
}


i32 sys_pwritev2(struct regs_t* r)
{
	return 0;// do_pwritev2(r);
}


i32 sys_pkey_mprotect(struct regs_t* r)
{
	return 0;// do_pkey_mprotect(r);
}


i32 sys_pkey_alloc(struct regs_t* r)
{
	return 0;// do_pkey_alloc(r);
}


i32 sys_pkey_free(struct regs_t* r)
{
	return 0;// do_pkey_free(r);
}


i32 sys_statx(struct regs_t* r)
{
	return 0;// do_statx(r);
}


i32 sys_arch_prctl(struct regs_t* r)
{
	return 0;// do_arch_prctl(r);
}


i32 sys_io_pgetevents(struct regs_t* r)
{
	return 0;// do_io_pgetevents(r);
}


i32 sys_rseq(struct regs_t* r)
{
	return 0;// do_rseq(r);
}


i32 sys_semget(struct regs_t* r)
{
	return 0;// do_semget(r);
}


i32 sys_semctl(struct regs_t* r)
{
	return 0;// do_semctl(r);
}


i32 sys_shmat(struct regs_t* r)
{
	return 0;// do_shmat(r);
}


i32 sys_shmdt(struct regs_t* r)
{
	return 0;// do_shmdt(r);
}


i32 sys_msgget(struct regs_t* r)
{
	return 0;// do_msgget(r);
}


i32 sys_msgsnd(struct regs_t* r)
{
	return 0;// do_msgsnd(r);
}


i32 sys_msgrcv(struct regs_t* r)
{
	return 0;// do_msgrcv(r);
}


i32 sys_msgctl(struct regs_t* r)
{
	return 0;// do_msgctl(r);
}


i32 sys_clock_gettime64(struct regs_t* r)
{
	return 0;// do_clock_gettime64(r);
}


i32 sys_clock_settime64(struct regs_t* r)
{
	return 0;// do_clock_settime64(r);
}


i32 sys_clock_adjtime64(struct regs_t* r)
{
	return 0;// do_clock_adjtime64(r);
}


i32 sys_clock_getres_time64(struct regs_t* r)
{
	return 0;// do_clock_getres_time64(r);
}


i32 sys_clock_nanosleep_time64(struct regs_t* r)
{
	return 0;// do_clock_nanosleep_time64(r);
}


i32 sys_timer_gettime64(struct regs_t* r)
{
	return 0;// do_timer_gettime64(r);
}


i32 sys_timer_settime64(struct regs_t* r)
{
	return 0;// do_timer_settime64(r);
}


i32 sys_timerfd_gettime64(struct regs_t* r)
{
	return 0;// do_timerfd_gettime64(r);
}


i32 sys_timerfd_settime64(struct regs_t* r)
{
	return 0;// do_timerfd_settime64(r);
}


i32 sys_ultimensat_time64(struct regs_t* r)
{
	return 0;// do_ultimensat_time64(r);
}


i32 sys_pselect6_time64(struct regs_t* r)
{
	return 0;// do_pselect6_time64(r);
}


i32 sys_ppoll_time64(struct regs_t* r)
{
	return 0;// do_ppoll_time64(r);
}


i32 sys_io_pgetevents_time64(struct regs_t* r)
{
	return 0;// do_io_pgetevents_time64(r);
}


i32 sys_recvmmsg_time64(struct regs_t* r)
{
	return 0;// do_recvmmsg_time64(r);
}


i32 sys_mq_timedsend_time64(struct regs_t* r)
{
	return 0;// do_mq_timedsend_time64(r);
}


i32 sys_mq_timedreceive_time64(struct regs_t* r)
{
	return 0;// do_mq_timedreceive_time64(r);
}


i32 sys_semtimedop_time64(struct regs_t* r)
{
	return 0;// do_semtimedop_time64(r);
}


i32 sys_rt_sigtimedwait_time64(struct regs_t* r)
{
	return 0;// do_rt_sigtimedwait_time64(r);
}


i32 sys_futex_time64(struct regs_t* r)
{
	return 0;// do_futex_time64(r);
}


i32 sys_sched_rr_get_interval_time64(struct regs_t* r)
{
	return 0;// do_sched_rr_get_interval_time64(r);
}


i32 sys_pidfd_send_signal(struct regs_t* r)
{
	return 0;// do_pidfd_send_signal(r);
}


i32 sys_io_uring_setup(struct regs_t* r)
{
	return 0;// do_io_uring_setup(r);
}


i32 sys_io_uring_enter(struct regs_t* r)
{
	return 0;// do_io_uring_enter(r);
}


i32 sys_io_uring_register(struct regs_t* r)
{
	return 0;// do_io_uring_register(r);
}


i32 sys_open_tree(struct regs_t* r)
{
	return 0;// do_open_tree(r);
}


i32 sys_move_mount(struct regs_t* r)
{
	return 0;// do_move_mount(r);
}


i32 sys_fsopen(struct regs_t* r)
{
	return 0;// do_fsopen(r);
}


i32 sys_fsconfig(struct regs_t* r)
{
	return 0;// do_fsconfig(r);
}


i32 sys_fsmount(struct regs_t* r)
{
	return 0;// do_fsmount(r);
}


i32 sys_fspick(struct regs_t* r)
{
	return 0;// do_fspick(r);
}


i32 sys_pidfd_open(struct regs_t* r)
{
	return 0;// do_pidfd_open(r);
}


i32 sys_clone3(struct regs_t* r)
{
	return 0;// do_clone3(r);
}


i32 sys_close_range(struct regs_t* r)
{
	return 0;// do_close_range(r);
}


i32 sys_faccessat2(struct regs_t* r)
{
	return 0;// do_faccessat2(r);
}




i32 (*table_syscalls[OS_TOTAL_INTERRUPTS])(struct regs_t *) = {

	[0] = sys_restart_syscall,
	[1] = sys_exit,
	[2] = sys_fork,
	[3] = sys_read,
	[4] = sys_write,
	[5] = sys_open,
	[6] = sys_close,
	[7] = sys_waitpid,
	[8] = sys_creat,
	[9] = sys_link,
	[10] = sys_unlink,
	[11] = sys_execve,
	[12] = sys_chdir,
	[13] = sys_time,
	[14] = sys_mknod,
	[15] = sys_chmod,
	[16] = sys_lchown,
	[17] = sys_break,
	[18] = sys_oldstat,
	[19] = sys_lseek,
	[20] = sys_getpid,
	[21] = sys_mount,
	[22] = sys_unmount,
	[23] = sys_setuid,
	[24] = sys_getuid,
	[25] = sys_stime,
	[26] = sys_ptrace,
	[27] = sys_alarm,
	[28] = sys_oldfstat,
	[29] = sys_pause,
	[30] = sys_utime,
	[31] = sys_stty,
	[32] = sys_gtty,
	[33] = sys_access,
	[34] = sys_nice,
	[35] = sys_ftime,
	[36] = sys_sync,
	[37] = sys_kill,
	[38] = sys_rename,
	[39] = sys_mkdir,
	[40] = sys_rmdir,
	[41] = sys_dup,
	[42] = sys_pipe,
	[43] = sys_times,
	[44] = sys_prof,
	[45] = sys_brk,
	[46] = sys_setgid,
	[47] = sys_getgid,
	[48] = sys_signal,
	[49] = sys_geteuid,
	[50] = sys_getegid,
	[51] = sys_acct,
	[52] = sys_umount2,
	[53] = sys_lock,
	[54] = sys_ioctl,
	[55] = sys_fcntl,
	[56] = sys_mpx,
	[57] = sys_setpgid,
	[58] = sys_ulimit,
	[59] = sys_oldolduname,
	[60] = sys_umask,
	[61] = sys_chroot,
	[62] = sys_ustat,
	[63] = sys_dup2,
	[64] = sys_getppid,
	[65] = sys_getpgrp,
	[66] = sys_setsid,
	[67] = sys_sigaction,
	[68] = sys_sgetmask,
	[69] = sys_ssetmask,
	[70] = sys_setreuid,
	[71] = sys_setregid,
	[72] = sys_sigsuspend,
	[73] = sys_sigpending,
	[74] = sys_sethostname,
	[75] = sys_setrlimit,
	[76] = sys_getrusage,
	[77] = sys_gettimeofday,
	[78] = sys_settimeofday,
	[79] = sys_getgroups,
	[80] = sys_setgroups,
	[81] = sys_select,
	[82] = sys_symlink,
	[83] = sys_oldlstat,
	[84] = sys_readlink,
	[85] = sys_uselib,
	[86] = sys_swapon,
	[87] = sys_reboot,
	[88] = sys_readdir,
	[89] = sys_mmap,
	[90] = sys_munmap,
	[91] = sys_truncate,
	[92] = sys_ftruncate,
	[93] = sys_fchmod,
	[94] = sys_fchown,
	[95] = sys_getpriority,
	[96] = sys_setpriority,
	[97] = sys_profil,
	[98] = sys_statsfs,
	[99] = sys_fstatsfs,
	[100] = sys_ioperm,
	[101] = sys_socketcall,
	[102] = sys_syslog,
	[103] = sys_setitimer,
	[104] = sys_getitimer,
	[105] = sys_stat,
	[106] = sys_lstat,
	[107] = sys_fstat,
	[108] = sys_olduname,
	[109] = sys_iopl,
	[110] = sys_vhangup,
	[111] = sys_idle,
	[112] = sys_vm86old,
	[113] = sys_wait4,
	[114] = sys_swapoff,
	[115] = sys_sysinfo,
	[116] = sys_ipc,
	[117] = sys_fsync,
	[118] = sys_sigreturn,
	[119] = sys_clone,
	[120] = sys_setdomainname,
	[121] = sys_uname,
	[122] = sys_modify_ldt,
	[123] = sys_adjtimex,
	[124] = sys_mprotect,
	[125] = sys_sigprocmask,
	[126] = sys_create_module,
	[127] = sys_init_module,
	[128] = sys_delete_module,
	[129] = sys_get_kernel_syms,
	[130] = sys_quotactl,
	[131] = sys_getpgid,
	[132] = sys_fchdir,
	[133] = sys_bdflush,
	[134] = sys_sysfs,
	[135] = sys_personality,
	[136] = sys_afs_syscall,
	[137] = sys_setfsuid,
	[138] = sys_setfsgid,
	[139] = sys__llseek,
	[140] = sys_getdents,
	[141] = sys__newselect,
	[142] = sys_flock,
	[143] = sys_msync,
	[144] = sys_readv,
	[145] = sys_writev,
	[146] = sys_getsid,
	[147] = sys_fdatasync,
	[148] = sys__sysctl,
	[149] = sys_mlock,
	[150] = sys_munlock,
	[151] = sys_mlockall,
	[152] = sys_munlockall,
	[153] = sys_sched_setparam,
	[154] = sys_sched_getparam,
	[155] = sys_sched_setscheduler,
	[156] = sys_sched_getscheduler,
	[157] = sys_sched_yield,
	[158] = sys_sched_get_priority_max,
	[159] = sys_sched_get_priority_min,
	[160] = sys_sched_rr_get_interval,
	[161] = sys_nanosleep,
	[162] = sys_mremap,
	[163] = sys_setresuid,
	[164] = sys_getresuid,
	[165] = sys_vm86,
	[166] = sys_query_module,
	[167] = sys_poll,
	[168] = sys_nfsservctl,
	[169] = sys_setresgid,
	[170] = sys_getresgid,
	[171] = sys_prctl,
	[172] = sys_rt_sigreturn,
	[173] = sys_rt_sigaction,
	[174] = sys_rt_sigprocmask,
	[175] = sys_rt_sigpending,
	[176] = sys_rt_sigtimedwait,
	[177] = sys_rt_sigqueueinfo,
	[178] = sys_rt_sigsuspend,
	[179] = sys_pread64,
	[180] = sys_pwrite64,
	[181] = sys_chown,
	[182] = sys_getcwd,
	[183] = sys_capget,
	[184] = sys_capset,
	[185] = sys_sigaltstack,
	[186] = sys_sendfile,
	[187] = sys_getpmsg,
	[188] = sys_putpmsg,
	[189] = sys_vfork,
	[190] = sys_ugetrlimit,
	[191] = sys_mmap2,
	[192] = sys_truncate64,
	[193] = sys_ftruncate64,
	[194] = sys_stat64,
	[195] = sys_fstat64,
	[196] = sys_lstat64,
	[197] = sys_lchown32,
	[198] = sys_getuid32,
	[199] = sys_getgid32,
	[200] = sys_geteuid32,
	[201] = sys_getegid32,
	[202] = sys_setreuid32,
	[203] = sys_setregid32,
	[204] = sys_getgroups32,
	[205] = sys_setgroups32,
	[206] = sys_fchown32,
	[207] = sys_setresuid32,
	[208] = sys_setresgid32,
	[209] = sys_getresgid32,
	[210] = sys_chown32,
	[211] = sys_setuid32,
	[212] = sys_setgid32,
	[213] = sys_setfsuid32,
	[214] = sys_getfsgid32,
	[215] = sys_setfsgid32,
	[216] = sys_pivot_root,
	[217] = sys_mincore,
	[218] = sys_madvise,
	[219] = sys_getdents64,
	[220] = sys_fcntl64,
	[223] = sys_gettid,
	[224] = sys_readahead,
	[225] = sys_setxattr,
	[226] = sys_lsetxattr,
	[227] = sys_getxattr,
	[228] = sys_lgetxattr,
	[229] = sys_fgetxattr,
	[230] = sys_listxattr,
	[231] = sys_flistxattr,
	[232] = sys_removexattr,
	[233] = sys_lremovexattr,
	[234] = sys_fremovexattr,
	[235] = sys_tkill,
	[236] = sys_sendfile64,
	[237] = sys_futex,
	[238] = sys_sched_setaffinity,
	[239] = sys_sched_getaffinity,
	[240] = sys_set_thread_area,
	[241] = sys_get_thread_area,
	[242] = sys_io_setup,
	[243] = sys_io_destroy,
	[244] = sys_io_getevents,
	[245] = sys_io_submit,
	[246] = sys_io_cancel,
	[247] = sys_faadvise64,
	[249] = sys_exit_group,
	[250] = sys_lookup_dcookie,
	[251] = sys_epoll_create,
	[252] = sys_epool_ctl,
	[253] = sys_epool_wait,
	[254] = sys_remap_file_pages,
	[255] = sys_set_tid_address,
	[256] = sys_timer_create,
	[257] = sys_timer_settime,
	[258] = sys_timer_gettime,
	[259] = sys_timer_getoverrun,
	[260] = sys_timer_delete,
	[261] = sys_clock_settime,
	[262] = sys_clock_gettime,
	[263] = sys_clock_gettres,
	[264] = sys_clock_nanosleep,
	[265] = sys_statfs64,
	[266] = sys_fstatfs64,
	[267] = sys_tgkill,
	[268] = sys_utimes,
	[269] = sys_fadvise64_64,
	[270] = sys_vserver,
	[271] = sys_mbind,
	[272] = sys_get_mempolicy,
	[273] = sys_set_mempolicy,
	[274] = sys_mq_open,
	[275] = sys_mq_unlink,
	[276] = sys_mq_timedsend,
	[277] = sys_mq_timedreceive,
	[278] = sys_mq_notify,
	[279] = sys_mq_getsetattr,
	[280] = sys_kexec_load,
	[281] = sys_waitid,
	[283] = sys_add_key,
	[284] = sys_request_key,
	[285] = sys_keyctl,
	[286] = sys_ioprio_set,
	[287] = sys_ioprio_get,
	[288] = sys_inotify_init,
	[289] = sys_inotify_add_watch,
	[290] = sys_inotify_rm_watch,
	[291] = sys_migrate_pages,
	[292] = sys_openat,
	[293] = sys_mkdirat,
	[294] = sys_mknodat,
	[295] = sys_futimesat,
	[296] = sys_fstatat64,
	[297] = sys_unlinkat,
	[298] = sys_renameat,
	[299] = sys_linkat,
	[300] = sys_symlinkat,
	[301] = sys_readlinkat,
	[302] = sys_faccesat,
	[303] = sys_pselect6,
	[304] = sys_ppol,
	[305] = sys_unshare,
	[306] = sys_set_robust_list,
	[307] = sys_get_robust_list,
	[308] = sys_splice,
	[309] = sys_sync_file_range,
	[310] = sys_tee,
	[311] = sys_vmsplice,
	[312] = sys_move_pages,
	[313] = sys_getcpu,
	[314] = sys_epoll_pwait,
	[315] = sys_utimensat,
	[316] = sys_signalfd,
	[317] = sys_timerfd_create,
	[318] = sys_eventfd,
	[319] = sys_fallocate,
	[320] = sys_timerfd_settime,
	[321] = sys_timerfd_gettime,
	[322] = sys_signalfd4,
	[323] = sys_eventfd2,
	[324] = sys_epoll_create1,
	[325] = sys_dup3,
	[326] = sys_pipe2,
	[327] = sys_inotify_init1,
	[328] = sys_preadv,
	[329] = sys_pwritev,
	[330] = sys_rt_tgsigqueueinfo,
	[331] = sys_perf_event_open,
	[332] = sys_recvmmsg,
	[333] = sys_fanotify_init,
	[334] = sys_prlimit64,
	[335] = sys_name_to_handle_at,
	[336] = sys_open_by_handle_at,
	[337] = sys_clock_adjtime,
	[338] = sys_syncfs,
	[339] = sys_sendmmsg,
	[340] = sys_setns,
	[341] = sys_process_vm_readv,
	[342] = sys_process_vm_writev,
	[343] = sys_kcmp,
	[344] = sys_finit_module,
	[345] = sys_sched_setattr,
	[346] = sys_sched_getattr,
	[347] = sys_renameat2,
	[348] = sys_seccomp,
	[349] = sys_getrandom,
	[350] = sys_memfd_create,
	[351] = sys_bpf,
	[352] = sys_execveat,
	[353] = sys_socket,
	[354] = sys_connect,
	[355] = sys_listen,
	[356] = sys_accept4,
	[357] = sys_getsockopt,
	[358] = sys_setsockopt,
	[359] = sys_getsockname,
	[360] = sys_setsockname,
	[361] = sys_getpeername,
	[362] = sys_sendto,
	[363] = sys_sendmsg,
	[364] = sys_recvfrom,
	[365] = sys_recvmsg,
	[366] = sys_shutdown,
	[367] = sys_mlock2,
	[368] = sys_copy_file_range,
	[369] = sys_preadv2,
	[370] = sys_pwritev2,
	[371] = sys_pkey_mprotect,
	[372] = sys_pkey_alloc,
	[373] = sys_pkey_free,
	[374] = sys_statx,
	[375] = sys_arch_prctl,
	[376] = sys_io_pgetevents,
	[377] = sys_rseq,
	[385] = sys_semget,
	[386] = sys_semctl,
	[387] = sys_shmat,
	[388] = sys_shmdt,
	[389] = sys_msgget,
	[390] = sys_msgsnd,
	[391] = sys_msgrcv,
	[392] = sys_msgctl,
	[393] = sys_clock_gettime64,
	[394] = sys_clock_settime64,
	[395] = sys_clock_adjtime64,
	[396] = sys_clock_getres_time64,
	[397] = sys_clock_nanosleep_time64,
	[398] = sys_timer_gettime64,
	[399] = sys_timer_settime64,
	[400] = sys_timerfd_gettime64,
	[401] = sys_timerfd_settime64,
	[402] = sys_ultimensat_time64,
	[403] = sys_pselect6_time64,
	[404] = sys_ppoll_time64,
	[406] = sys_io_pgetevents_time64,
	[407] = sys_recvmmsg_time64,
	[408] = sys_mq_timedsend_time64,
	[409] = sys_mq_timedreceive_time64,
	[410] = sys_semtimedop_time64,
	[411] = sys_rt_sigtimedwait_time64,
	[412] = sys_futex_time64,
	[413] = sys_sched_rr_get_interval_time64,
	[414] = sys_pidfd_send_signal,
	[415] = sys_io_uring_setup,
	[416] = sys_io_uring_enter,
	[417] = sys_io_uring_register,
	[418] = sys_open_tree,
	[419] = sys_move_mount,
	[420] = sys_fsopen,
	[421] = sys_fsconfig,
	[422] = sys_fsmount,
	[423] = sys_fspick,
	[424] = sys_pidfd_open,
	[425] = sys_clone3,
	[426] = sys_close_range,
	[429] = sys_faccessat2,
};


O3 i32 do_int80h(struct regs_t *r)
{
    if (r->eax < 0 || r->eax > REAL_TOTAL_INT_CREATED - 1)
        return -ENOSYS;     // invalid no syscall

    return table_syscalls[r->eax](r);
}
