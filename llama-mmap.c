#include "llama.h"
#include "llama-internal.h"
#include <unistd.h>
#include <sys/mman.h>

#ifdef __APPLE__
#define MAP_ANONYMOUS MAP_ANON
#endif

static int permissions_to_prot(llama_permissions_t permissions)
{
	int result = 0;
	if (permissions & LLAMA_PERMISSION_READ)  result |= PROT_READ;
	if (permissions & LLAMA_PERMISSION_WRITE) result |= PROT_WRITE;
	if (permissions & LLAMA_PERMISSION_EXEC)  result |= PROT_EXEC;
	return result;
}

static size_t pageSize = 0;

void llama_init(void)
{
	pageSize = getpagesize();
}

void llama_quit(void)
{
}

llama_options_t llama_supported_options(void)
{
	return LLAMA_OPTION_FIXED | LLAMA_OPTION_LOCK;
}

size_t llama_page_size(void)
{
	return pageSize;
}

void* llama_allocate(unsigned pageCount, llama_permissions_t permissions,
                     llama_options_t options, void* fixedAddress)
{
	return mmap(fixedAddress, pageCount * pageSize,
	            permissions_to_prot(permissions), MAP_ANONYMOUS | MAP_PRIVATE,
	            0, 0);
}

void llama_deallocate(void* base, unsigned pageCount)
{
	munmap(base, pageCount * pageSize);
}

bool llama_lock(void* base, unsigned pageCount)
{
	return mlock(base, pageCount * pageSize) == 0;
}

void llama_unlock(void* base, unsigned pageCount)
{
	munlock(base, pageCount * pageSize);
}

void llama_set_permissions(void* base, unsigned pageCount, llama_permissions_t newPermissions)
{
	mprotect(base, pageCount * pageSize, permissions_to_prot(newPermissions));
}
