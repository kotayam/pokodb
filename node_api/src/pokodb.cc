#include "pokodb.h"

using namespace Napi;

Pokodb::Pokodb(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();

    if (info.Length() >= 1) {
        ThrowTypeError(env, "Wrong number of arguments");
        return;
    }

    hashmap *map = NULL;
    if (create_map(&map) < 0) {
        ThrowNewError(env, "Not enough memory");
        return;
    }

    this->_map = map;
}

void Pokodb::Insert(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() != 2) {
        ThrowTypeError(env, "Key and value not provided");
        return;
    }

    if (!info[0].IsString()) {
        ThrowTypeError(env, "Key needs to be string");
        return;
    }

    if (!info[1].IsString()) {
        ThrowTypeError(env, "Value needs to be string");
        return;
    }

    std::string key = info[0].As<Napi::String>().Utf8Value();
    std::string value = info[1].As<Napi::String>().Utf8Value();

    if (hm_insert((char *)key.c_str(), (char *)value.c_str(),
                  (hashmap *)this->_map) < 0) {
        ThrowNewError(env, "Failed to insert");
        return;
    }
}

Napi::Value Pokodb::Get(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1) {
        ThrowTypeError(env, "Key not provided");
        return env.Null();
    }

    if (!info[0].IsString()) {
        ThrowTypeError(env, "Key needs to be string");
        return env.Null();
    }

    std::string key = info[0].As<Napi::String>().Utf8Value();

    char *res = NULL;

    if (hm_get((char *)key.c_str(), &res, (hashmap *)this->_map) < 0) {
        ThrowNewError(env, "Key does not exist");
        return env.Null();
    }

    return Napi::String::New(env, res);
}

void Pokodb::Delete(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1) {
        ThrowTypeError(env, "Key not provided");
        return;
    }

    if (!info[0].IsString()) {
        ThrowTypeError(env, "Key needs to be string");
        return;
    }

    std::string key = info[0].As<Napi::String>().Utf8Value();

    if (hm_delete((char *)key.c_str(), (hashmap *)this->_map) < 0) {
        ThrowNewError(env, "Failed to delete key");
        return;
    }
}

void Pokodb::Update(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() != 2) {
        ThrowTypeError(env, "Key and value not provided");
        return;
    }

    if (!info[0].IsString()) {
        ThrowTypeError(env, "Key needs to be string");
        return;
    }

    if (!info[1].IsString()) {
        ThrowTypeError(env, "Value needs to be string");
        return;
    }

    std::string key = info[0].As<Napi::String>().Utf8Value();
    std::string value = info[0].As<Napi::String>().Utf8Value();

    if (hm_update((char *)key.c_str(), (char *)value.c_str(),
                  (hashmap *)this->_map) < 0) {
        ThrowNewError(env, "Failed to update key");
        return;
    }
}

void Pokodb::Close(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() > 0) {
        ThrowTypeError(env, "Should not have any arguments");
        return;
    }

    free_map((hashmap *)this->_map);
    this->_map = NULL;
}

Napi::Function Pokodb::GetClass(Napi::Env env) {
    return DefineClass(env, "Pokodb",
                       {Pokodb::InstanceMethod("insert", &Pokodb::Insert),
                        Pokodb::InstanceMethod("get", &Pokodb::Get),
                        Pokodb::InstanceMethod("delete", &Pokodb::Delete),
                        Pokodb::InstanceMethod("update", &Pokodb::Update),
                        Pokodb::InstanceMethod("close", &Pokodb::Close)});
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    Napi::String name = Napi::String::New(env, "Pokodb");
    exports.Set(name, Pokodb::GetClass(env));
    return exports;
}

NODE_API_MODULE(addon, Init)

void Pokodb::ThrowNewError(Napi::Env env, const std::string &message) {
    Napi::Error::New(env, message).ThrowAsJavaScriptException();
}

void Pokodb::ThrowTypeError(Napi::Env env, const std::string &message) {
    Napi::TypeError::New(env, message).ThrowAsJavaScriptException();
}
