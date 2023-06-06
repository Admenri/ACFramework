
#include "wrapper_utility.h"
#include "struct_class.h"

#include "wrapper_acfclass.h"

#include "include/acf_environment.h"

LPBYTE GetAryElementInf(void* pAryData, LPINT pnElementCount) {
  LPINT pnData = (LPINT)pAryData;
  INT nArys = *pnData++;
  INT nElementCount = 1;
  while (nArys > 0) {
    nElementCount *= *pnData++;
    nArys--;
  }

  if (pnElementCount != NULL) *pnElementCount = nElementCount;
  return (LPBYTE)pnData;
}

void FreeAryElement(void* pAryData)
{
  DWORD AryElementCount = 0;
  LPINT* pArryPtr = (LPINT*)GetAryElementInf(pAryData, (LPINT)AryElementCount);

  for (INT i = 0; i < (INT)AryElementCount; i++) {
    void* pElementData = *pArryPtr;
    if (pElementData) {
      free(pElementData);
      *pArryPtr = NULL;
    }
    pArryPtr++;
  }

  free(pAryData);
}


LPSTR GetEString(const AcfString& str) {
  if (str.empty()) return 0;

  size_t size = str.length() + 1;
  LPSTR pstr = (LPSTR)LocalAlloc(LMEM_ZEROINIT, size);
  memset(pstr, 0, size);

  strcpy(pstr, str.c_str());

  return pstr;
}

DLL_EXPORTS(ObjectAddRef, void)(void* obj, EClassVTable type) {
  if (!obj) return;
  
  switch (type) {
    case EClassVTable::VT_ENVIRONMENT:
      static_cast<AcfEnvironment*>(obj)->AddRef();
      break;
    case EClassVTable::VT_BROWSER:
      static_cast<AcfBrowser*>(obj)->AddRef();
      break;
    case EClassVTable::VT_PROFILE:
      static_cast<AcfProfile*>(obj)->AddRef();
      break;
    case EClassVTable::VT_NEWWINDOWDELEGATE:
      static_cast<AcfNewWindowDelegate*>(obj)->AddRef();
      break;
    case EClassVTable::VT_VALUE:
      static_cast<AcfValue*>(obj)->AddRef();
      break;
    case EClassVTable::VT_BINARY:
      static_cast<AcfBinaryValue*>(obj)->AddRef();
      break;
    case EClassVTable::VT_DICTIONARY:
      static_cast<AcfDictionaryValue*>(obj)->AddRef();
      break;
    case EClassVTable::VT_LIST:
      static_cast<AcfListValue*>(obj)->AddRef();
      break;
    case EClassVTable::VT_COOKIEMANAGER:
      static_cast<AcfCookieManager*>(obj)->AddRef();
      break;
    case EClassVTable::VT_FRAME:
      static_cast<AcfFrame*>(obj)->AddRef();
      break;
    case EClassVTable::VT_AUTHCALLBACK:
      static_cast<AcfLoginDelegate*>(obj)->AddRef();
      break;
    case EClassVTable::VT_MENUCALLBACK:
      static_cast<AcfContextMenuCallback*>(obj)->AddRef();
      break;
    case EClassVTable::VT_MENUPARAMS:
      static_cast<AcfContextMenuParams*>(obj)->AddRef();
      break;
    case EClassVTable::VT_MENUMODEL:
      static_cast<AcfContextMenuModel*>(obj)->AddRef();
      break;
    case EClassVTable::VT_REQUEST:
      static_cast<AcfRequest*>(obj)->AddRef();
      break;
    case EClassVTable::VT_RESPONSE:
      static_cast<AcfResponse*>(obj)->AddRef();
      break;
    case EClassVTable::VT_POSTDATA:
      static_cast<AcfPostData*>(obj)->AddRef();
      break;
    case EClassVTable::VT_POSTDATAELEMENTS:
      static_cast<AcfPostDataElement*>(obj)->AddRef();
      break;
    case EClassVTable::VT_RESPONSECALLBACK:
      static_cast<ACFResourceResponseCallback*>(obj)->AddRef();
      break;
    case EClassVTable::VT_RESPONSEFILTER:
      static_cast<ACFResourceFilter*>(obj)->AddRef();
      break;

    default:
      break;
  }
}

DLL_EXPORTS(ObjectRelease, void)(void* obj, EClassVTable type) {
  if (!obj) return;
  
  switch (type) {
    case EClassVTable::VT_ENVIRONMENT:
      static_cast<AcfEnvironment*>(obj)->Release();
      break;
    case EClassVTable::VT_BROWSER:
      static_cast<AcfBrowser*>(obj)->Release();
      break;
    case EClassVTable::VT_PROFILE:
      static_cast<AcfProfile*>(obj)->Release();
      break;
    case EClassVTable::VT_NEWWINDOWDELEGATE:
      static_cast<AcfNewWindowDelegate*>(obj)->Release();
      break;
    case EClassVTable::VT_VALUE:
      static_cast<AcfValue*>(obj)->Release();
      break;
    case EClassVTable::VT_BINARY:
      static_cast<AcfBinaryValue*>(obj)->Release();
      break;
    case EClassVTable::VT_DICTIONARY:
      static_cast<AcfDictionaryValue*>(obj)->Release();
      break;
    case EClassVTable::VT_LIST:
      static_cast<AcfListValue*>(obj)->Release();
      break;
    case EClassVTable::VT_COOKIEMANAGER:
      static_cast<AcfCookieManager*>(obj)->Release();
      break;
    case EClassVTable::VT_FRAME:
      static_cast<AcfFrame*>(obj)->Release();
      break;
    case EClassVTable::VT_AUTHCALLBACK:
      static_cast<AcfLoginDelegate*>(obj)->Release();
      break;
    case EClassVTable::VT_MENUCALLBACK:
      static_cast<AcfContextMenuCallback*>(obj)->Release();
      break;
    case EClassVTable::VT_MENUPARAMS:
      static_cast<AcfContextMenuParams*>(obj)->Release();
      break;
    case EClassVTable::VT_MENUMODEL:
      static_cast<AcfContextMenuModel*>(obj)->Release();
      break;
    case EClassVTable::VT_REQUEST:
      static_cast<AcfRequest*>(obj)->Release();
      break;
    case EClassVTable::VT_RESPONSE:
      static_cast<AcfResponse*>(obj)->Release();
      break;
    case EClassVTable::VT_POSTDATA:
      static_cast<AcfPostData*>(obj)->Release();
      break;
    case EClassVTable::VT_POSTDATAELEMENTS:
      static_cast<AcfPostDataElement*>(obj)->Release();
      break;
    case EClassVTable::VT_RESPONSECALLBACK:
      static_cast<ACFResourceResponseCallback*>(obj)->Release();
      break;
    case EClassVTable::VT_RESPONSEFILTER:
      static_cast<ACFResourceFilter*>(obj)->Release();
      break;

    default:
      break;
  }
}
