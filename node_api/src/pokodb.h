#pragma once

#include <napi.h>

extern "C" {
#include "../../include/hashmap.h"
}

class Pokodb : public Napi::ObjectWrap<Pokodb> {
  private:
    void *_map;

    static void ThrowNewError(Napi::Env env, const std::string &message);
    static void ThrowTypeError(Napi::Env env, const std::string &message);

  public:
    Pokodb(const Napi::CallbackInfo &info);

    void Insert(const Napi::CallbackInfo &info);
    Napi::Value Get(const Napi::CallbackInfo &info);
    void Delete(const Napi::CallbackInfo &info);
    void Update(const Napi::CallbackInfo &info);
    void Close(const Napi::CallbackInfo &info);

    static Napi::Function GetClass(Napi::Env);
};
