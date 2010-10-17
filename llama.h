#ifndef _INCLUDED_LLAMA
#define _INCLUDED_LLAMA

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef uint32_t llama_options_t;
typedef uint8_t llama_permissions_t;

#define LLAMA_OPTION_NONE   0x00
#define LLAMA_OPTION_FIXED  0x01
#define LLAMA_OPTION_LOCKED 0x02

#define LLAMA_PERMISSION_NONE  0
#define LLAMA_PERMISSION_READ  0x01
#define LLAMA_PERMISSION_WRITE 0x02
#define LLAMA_PERMISSION_EXEC  0x04

void llama_init(void);
void llama_quit(void);

llama_options_t llama_supported_options();
size_t llama_page_size();

void* llama_allocate(unsigned pageCount, llama_permissions_t permissions,
                     llama_options_t options, void* fixedAddress);
void llama_deallocate(void* base, unsigned pageCount);

bool llama_lock(void* base, unsigned pageCount);
void llama_unlock(void* base, unsigned pageCount);

void llama_set_permissions(void* base, llama_permissions_t permissions);

#ifdef __cplusplus
}
#endif

#endif
