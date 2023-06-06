#ifndef ACF_E_UTIL_H_
#define ACF_E_UTIL_H_

#include "wrapper_types.h"
#include "include/internal/acf_string.h"
#include "struct_class.h"

#include "include/internal/acf_scoped_refptr.h"

#include <windows.h>

LPBYTE GetAryElementInf(void* pAryData, LPINT pnElementCount);
void FreeAryElement(void* pAryData);

LPSTR GetEString(const AcfString& str);

DLL_EXPORTS(RegisterClass, void)(DWORD** pNewClass, EClassVTable nType);
DLL_EXPORTS(ObjectRelease, void)(void* obj, EClassVTable type);

#endif
