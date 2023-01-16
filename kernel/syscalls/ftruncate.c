//int ftruncate(int fd, off_t length);

#include <hermit/syscall.h>
#include <hermit/logging.h>
#include <asm/page.h>
#include <asm/uhyve.h>
#include <hermit/minifs.h>

typedef struct {
	int fd;
    off_t length;
} __attribute__((packed)) uhyve_ftruncate_t;

int sys_ftruncate(int fd, off_t length) {
	uhyve_ftruncate_t arg;

	if(minifs_enabled)
		return 0;

	arg.fd = fd;
	arg.length = length;


	uhyve_send(UHYVE_PORT_FTRUNCATE, (unsigned)virt_to_phys((size_t)&arg));

	return arg.length;
}
