
#include "include/acf_environment.h"
#include "include/acf_profile.h"
#include "wrapper_utility.h"

#include <iostream>

extern DWORD acf_cpp_fntable_profile[];
extern DWORD acf_cpp_fntable_environment[];
extern DWORD acf_cpp_fntable_cookiemanager[];

namespace {

BOOL ACF_CALLBACK get_env(AcfProfile* obj, DWORD* retObj) {
  AcfRefPtr<AcfEnvironment> env = obj->GetEnvironment();

  if (env) {
    env->AddRef();
    retObj[1] = (DWORD)env.get();
    retObj[2] = (DWORD)acf_cpp_fntable_environment;
  }

  return !!env.get();
}

bool ACF_CALLBACK is_valid(AcfProfile* obj) { return obj->IsValid(); }

LPSTR ACF_CALLBACK get_path(AcfProfile* obj) {
  return GetEString(obj->GetPath());
}

class CompleteSyncCallback : public AcfCompleteHandler {
 public:
  CompleteSyncCallback(std::atomic<bool>* notify) : notify_(notify) {}
  ~CompleteSyncCallback() {}

 protected:
  void OnComplete(bool success) override { *notify_ = true; }

 private:
  std::atomic<bool>* notify_;
  IMPLEMENT_REFCOUNTING(CompleteSyncCallback);
};

void ACF_CALLBACK set_prefs(AcfProfile* obj, LPCSTR name, AcfValue* value) {
  std::unique_ptr<std::atomic<bool>> notify =
      std::make_unique<std::atomic<bool>>(false);
  obj->SetPreference(name, value, new CompleteSyncCallback(notify.get()));

  while (!*notify) {
    ::Sleep(0);
  }
}

void ACF_CALLBACK remove_browsing_data(AcfProfile* obj,
                                       AcfProfile::RemoveDataType type,
                                       bool no_check) {
  std::unique_ptr<std::atomic<bool>> notify =
      std::make_unique<std::atomic<bool>>(false);
  obj->RemoveBrowsingData(type, no_check,
                          new CompleteSyncCallback(notify.get()));

  while (!*notify) {
    ::Sleep(0);
  }
}

void ACF_CALLBACK get_cookie_manager(AcfProfile* obj, DWORD* retObj) {
  AcfRefPtr<AcfCookieManager> ckm = obj->GetCookieManager();

  if (ckm) {
    ckm->AddRef();
    retObj[1] = (DWORD)ckm.get();
    retObj[2] = (DWORD)acf_cpp_fntable_cookiemanager;
  }
}

}  // namespace

DWORD acf_cpp_fntable_profile[] = {
    (DWORD)is_valid,           (DWORD)get_path,
    (DWORD)set_prefs,          (DWORD)remove_browsing_data,
    (DWORD)get_cookie_manager,
};

namespace {

PACF_COOKIE transfer_cookie_data(AcfRefPtr<AcfCookie> cookie) {
  PACF_COOKIE pCookie = new ACF_COOKIE;

  pCookie->name = GetEString(cookie->GetName());
  pCookie->value = GetEString(cookie->GetValue());
  pCookie->domain = GetEString(cookie->GetDomain());
  pCookie->path = GetEString(cookie->GetPath());

  pCookie->secure = cookie->IsSecure();
  pCookie->httponly = cookie->IsHttponly();

  pCookie->same_site = cookie->GetSameSite();
  pCookie->priority = cookie->GetPriority();

  pCookie->creation = cookie->GetCreation();
  pCookie->expires = cookie->GetExpiry();
  pCookie->last_access = cookie->GetLastAccess();
  pCookie->last_update = cookie->GetLastUpdate();

  return pCookie;
}

AcfRefPtr<AcfCookie> transfer_cookie_data(PACF_COOKIE cookie) {
  AcfRefPtr<AcfCookie> pCookie = AcfEnvironment::CreateCookie();

  if (cookie) {
    if (cookie->name && *cookie->name) {
      pCookie->SetName(cookie->name);
    }
    if (cookie->value && *cookie->value) {
      pCookie->SetValue(cookie->value);
    }
    if (cookie->domain && *cookie->domain) {
      pCookie->SetDomain(cookie->domain);
    }
    if (cookie->path && *cookie->path) {
      pCookie->SetPath(cookie->path);
    }

    pCookie->SetSecure(cookie->secure);
    pCookie->SetHttponly(cookie->httponly);

    pCookie->SetSameSite((AcfCookie::AcfCookieSameSite)cookie->same_site);
    pCookie->SetPriority((AcfCookie::AcfCookiePriority)cookie->priority);

    pCookie->SetCreation(cookie->creation);
    pCookie->SetExpiry(cookie->expires);
    pCookie->SetLastAccess(cookie->last_access);
    pCookie->SetLastUpdate(cookie->last_update);
  }

  return pCookie;
}

class CookieVisitorSync : public AcfCookieVisitor {
 public:
  CookieVisitorSync(std::atomic<bool>* notify) : notify_(notify) {}
  ~CookieVisitorSync() {}

  std::vector<AcfRefPtr<AcfCookie>>& GetResult() { return data_; }

 protected:
  void Visit(AcfRefPtr<AcfCookiesGetter> cookie_getter) override {
    for (size_t i = 0; i < cookie_getter->GetCookiesCount(); i++)
      data_.push_back(cookie_getter->GetCookieAt(i));

    *notify_ = true;
  }

 private:
  std::vector<AcfRefPtr<AcfCookie>> data_;
  std::atomic<bool>* notify_;

  IMPLEMENT_REFCOUNTING(CookieVisitorSync);
};

int ACF_CALLBACK visit_cookies_sync(AcfCookieManager* obj, LPCSTR url,
                                    bool httpOnly, LPVOID* eArray) {
  ISVALIDR(obj, false);

  std::unique_ptr<std::atomic<bool>> notify =
      std::make_unique<std::atomic<bool>>(false);

  AcfRefPtr<CookieVisitorSync> lpHandler = new CookieVisitorSync(notify.get());
  obj->GetCookies(url, httpOnly, lpHandler);

  while (!*notify) {
    ::Sleep(0);
  }

  FreeAryElement(*eArray);
  std::vector<AcfRefPtr<AcfCookie>>& data = lpHandler->GetResult();

  DWORD* pStrs = new DWORD[data.size()];
  for (size_t i = 0; i < data.size(); i++)
    pStrs[i] = (DWORD)transfer_cookie_data(data[i]);

  int nSize = data.size() * sizeof(DWORD);
  LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
  *(LPINT)pAry = 1;
  *(LPINT)(pAry + sizeof(INT)) = data.size();
  memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
  delete[] pStrs;

  *eArray = pAry;

  return lpHandler->GetResult().size();
}

void ACF_CALLBACK set_cookie(AcfCookieManager* obj, LPCSTR url,
                             PACF_COOKIE* ckdata) {
  obj->SetCookie(url, transfer_cookie_data(*ckdata), nullptr);
}

void ACF_CALLBACK delete_cookies(AcfCookieManager* obj, LPCSTR url,
                                 LPCSTR name) {
  obj->DeleteCookies(url, name, nullptr);
}

void ACF_CALLBACK flush_cookies(AcfCookieManager* obj) {
  obj->FlushStore(nullptr);
}

}  // namespace

DWORD acf_cpp_fntable_cookiemanager[] = {
    (DWORD)visit_cookies_sync,
    (DWORD)set_cookie,
    (DWORD)delete_cookies,
    (DWORD)flush_cookies,
};