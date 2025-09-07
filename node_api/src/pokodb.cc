#include "pokodb.h"

using namespace Napi;

Pokodb::Pokodb(const Napi::CallbackInfo& info) : ObjectWrap(info) {
    Napi::Env env = info.Env();

    if (info.Length() >= 1) {
        ThrowTypeError("Wrong number of arguments");
        return;
    }

    hashmap *map = NULL;
    if (create_map(&map) < 0) {
        ThrowNewError("Not enough memory");
        return;
    }

    this->_map = map;
}


void Pokodb::Insert(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 2) {
        ThrowTypeError(env, "Key and value not provided");
        return; 
    }

    if (!info[0].isString()) {
        ThrowTypeError(env, "Key needs to be string");
        return;
    }

    if (!info[1].isString()) {
        ThrowTypeError(env, "Value needs to be string");
        return;
    }

    Napi::String key = info[0].As<Napi::String>();
    Napi::String value = info[1].As<Napi::String>();

    if (hm_insert(key, value, this->_map) < 0) {
        ThrowNewError(env, "Failed to insert");
        return;
    }
}

Napi::Value Pokodb::Greet(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1) {
        Napi::TypeError::New(env, "Wrong number of arguments")
          .ThrowAsJavaScriptException();
        return env.Null();
    }

    if (!info[0].IsString()) {
        Napi::TypeError::New(env, "You need to introduce yourself to greet")
          .ThrowAsJavaScriptException();
        return env.Null();
    }

    Napi::String name = info[0].As<Napi::String>();

    printf("Hello %s\n", name.Utf8Value().c_str());
    printf("I am %s\n", this->_greeterName.c_str());

    return Napi::String::New(env, this->_greeterName);
}

Napi::Function Pokodb::GetClass(Napi::Env env) {
    return DefineClass(env, "Pokodb", {
        Pokodb::InstanceMethod("greet", &Pokodb::Greet),
    });
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::String name = Napi::String::New(env, "Pokodb");
    exports.Set(name, Pokodb::GetClass(env));
    return exports;
}

NODE_API_MODULE(addon, Init)

void Pokodb::ThrowNewError(Napi::Env env, const std::string& message) {
    Napi::Error::New(env, message).ThrowAsJavaScriptException();
}

void Pokodb::ThrowTypeError(Napi::Env env, const std::string& message) {
    Napi::TypeError::New(env, message).ThrowAsJavaScriptException();
}
