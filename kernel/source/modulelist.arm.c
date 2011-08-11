#include "fxe.h"

#define LINK_FAKEMODULE(NAME) \
	extern fxe_runtime_header _header_##NAME; \
	FeOS_ModuleListAdd(&_header_##NAME)

extern fxe_runtime_header _header_FEOSBASE;

static fxe_runtime_header* mListHead = &_header_FEOSBASE;
static fxe_runtime_header* mListTail = &_header_FEOSBASE;
static int nmodules = 1;

void FeOS_ModuleListInit()
{
	LINK_FAKEMODULE(FEOSSTDIO);
	LINK_FAKEMODULE(FEOSPOSIXEMU);
	LINK_FAKEMODULE(FEOSDSAPI);
}

void FeOS_ModuleListAdd(fxe_runtime_header* pModule)
{
	mListTail->next = pModule;
	pModule->next = NULL;
	pModule->prev = mListTail;
	mListTail = pModule;
	nmodules ++;
}

void FeOS_ModuleListRemove(fxe_runtime_header* pModule)
{
	if (pModule->file == -1) return; // thwart attempts at doing evil

	pModule->prev->next = pModule->next;
	if (mListTail == pModule) mListTail = pModule->prev;
	nmodules --;
}

int FeOS_ModuleListCount()
{
	return nmodules;
}

fxe_runtime_header* FeOS_ModuleListFind(const char* name)
{
	fxe_runtime_header* item;
	for (item = mListHead; item != NULL; item = item->next)
		if (stricmp(name, item->name) == 0) return item;
	return NULL;
}

void* FeOS_ModuleFromAddress(void* addr)
{
	word_t addrw = (word_t) addr;

	fxe_runtime_header* item;
	for (item = mListHead; item != NULL; item = item->next)
	{
		if (item->file == -1) continue; // Ignore fake modules

		word_t m_bottom = (word_t) item->hThis;
		word_t m_top = m_bottom + item->size;

		if (addrw >= m_bottom && addrw <= m_top)
			return item->hThis;
	}

	return NULL;
}
