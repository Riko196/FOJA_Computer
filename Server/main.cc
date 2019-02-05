// hello.cc
#include <node.h>
#include "Grammar.h"

namespace demo
{

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::NewStringType;
using v8::Object;
using v8::String;
using v8::Value;

void Execute(const FunctionCallbackInfo<Value> &args)
{
  Isolate *isolate = args.GetIsolate();

  if (args.Length() == 2)
  {
    String::Utf8Value str(isolate, args[0]);
    string grammarString(*str);

    String::Utf8Value req(isolate, args[1]);
    string request(*req);

    Grammar *grammar = new Grammar(grammarString);

    if (request == "reducedNormalForm")
      grammar->toReducedNormalForm();
    else if (request == "epsilonFreeForm")
      grammar->toEpsilonFreeForm();

    string result = grammar->grammarToString();

    delete grammar;
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, result.c_str()));
    return;
  }
  else if (args.Length() == 3)
  {
    String::Utf8Value str1(isolate, args[0]);
    string grammarString1(*str1);
    String::Utf8Value str2(isolate, args[1]);
    string grammarString2(*str2);
    Grammar *grammar1 = new Grammar(grammarString1);
    Grammar *grammar2 = new Grammar(grammarString2);

    string isEquivalent = grammar1->isEquivalent(grammar2);

    delete grammar1;
    delete grammar2;
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, isEquivalent.c_str()));
    return;
  }
  else
  {
    args.GetReturnValue().Set(String::NewFromUtf8(
                                  isolate, "Wrong inputs", NewStringType::kNormal)
                                  .ToLocalChecked());
    return;
  }
}

void Initialize(Local<Object> exports)
{
  NODE_SET_METHOD(exports, "execute", Execute);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

} // namespace demo