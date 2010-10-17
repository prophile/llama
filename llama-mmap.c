#include "llama.h"

void llama_init(void)
{
}

void llama_quit(void)
{
}

llama_options_t llama_supported_options(void)
{
	return LLAMA_OPTION_NONE;
}

size_t llama_page_size(void)
{
	return 0;
}

void* llama_allocate(unsigned pageCount, llama_permissions_t permissions,
                     llama_options_t options, void* fixedAddress)
{
	return NULL;
}

void llama_deallocate(void* base, unsigned pageCount)
{
}

bool llama_lock(void* base, unsigned pageCount)
{
	return false;
}

void llama_unlock(void* base, unsigned pageCount)
{
}

void llama_set_permissions(void* base, unsigned pageCount, llama_permissions_t newPermissions)
{
}
