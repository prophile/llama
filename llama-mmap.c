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

void llama_init(void)
{
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
	MEMOISE(size_t, getpagesize());
}

void* llama_allocate(unsigned pageCount, llama_permissions_t permissions,
                     llama_options_t options, void* fixedAddress)
{
	return mmap(fixedAddress, pageCount * llama_page_size(),
	            permissions_to_prot(permissions), MAP_ANONYMOUS | MAP_PRIVATE,
	            0, 0);
}

void llama_deallocate(void* base, unsigned pageCount)
{
	munmap(base, pageCount * llama_page_size());
}

bool llama_lock(void* base, unsigned pageCount)
{
	return mlock(base, pageCount) == 0;
}

void llama_unlock(void* base, unsigned pageCount)
{
	munlock(base, pageCount);
}

void llama_set_permissions(void* base, unsigned pageCount, llama_permissions_t newPermissions)
{
}
