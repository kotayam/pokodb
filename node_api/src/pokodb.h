#pragma once

#include <napi.h>

extern "C" {
  #include "../../include/hashmap.h"
}

class Pokodb : public Napi::ObjectWrap<Pokodb> {
  public:
    Pokodb(const Napi::CallbackInfo &);
    Napi::Value Greet(const Napi::CallbackInfo &);

    static Napi::Function GetClass(Napi::Env);

  private:
    std::string _greeterName;
};
