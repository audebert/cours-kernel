lectures = linux_devices \
	linux_fs \
	linux_kernel_features \
	linux_kernel_history \
	linux_misc \
	linux_mm \
	linux_modules \
	linux_processes \
	linux_sched \
	linux_syscalls

all:
	for lecture in $(lectures); \
	    do \
	    $(MAKE) -C $$lecture; \
	    done
