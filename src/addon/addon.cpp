#include "lib.hpp"
#include <iostream>
#include <napi.h>

Napi::Boolean Method(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  if (info.Length() != 1) {
    Napi::Error::New(info.Env(), "Expected exactly one argument").ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  if (!info[0].IsString()) {
    Napi::Error::New(info.Env(), "Expected an string").ThrowAsJavaScriptException();
    return Napi::Boolean::New(env, false);
  }
  return Napi::Boolean::New(env, load(static_cast<std::string>(info[0].As<Napi::String>())));
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "HelloWorld"), Napi::Function::New(env, Method));
  return exports;
}

NODE_API_MODULE(addon, Init)
