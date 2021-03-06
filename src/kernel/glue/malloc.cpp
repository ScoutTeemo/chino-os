//
// Chino Glue
//
#include <malloc.h>
#include <string.h>
#include "../memory/MemoryManager.hpp"
#include "../kdebug.hpp"
#ifndef _WIN32
#include <reent.h>
#endif

using namespace Chino::Memory;

#ifndef _WIN32
extern "C"
{
	void* malloc(size_t n)
	{
		auto p = g_MemoryMgr->HeapAlloc(n);
		kassert(p);
		return p;
	}

	void free(void* p)
	{
		g_MemoryMgr->HeapFree(p);
	}

	void* realloc(void* p, size_t n)
	{
		auto np = malloc(n);
		if (p)
		{
			memcpy(np, p, n);
			free(p);
		}

		return np;
	}

	void* calloc(size_t num, size_t size)
	{
		const auto n = num * size;
		auto p = malloc(n);
		if (p)
			memset(p, 0, n);
		return p;
	}

	void* _malloc_r(struct _reent *, size_t n)
	{
		return malloc(n);
	}

	void _free_r(struct _reent *, void* p)
	{
		free(p);
	}

	void* _realloc_r(struct _reent *, void* p, size_t n)
	{
		return realloc(p, n);
	}

	void* _calloc_r(struct _reent *, size_t num, size_t size)
	{
		return calloc(num, size);
	}
}
#endif