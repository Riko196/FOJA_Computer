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

  set<char> nonterminals;
  set<char> terminals;
  char start = 'A';
  set<pair<string, string>> rules;

  Grammar *grammar = new Grammar(nonterminals, terminals, start, rules);
  string response = grammar->hello();

  args.GetReturnValue().Set(String::NewFromUtf8(
                                isolate, response.c_str(), NewStringType::kNormal)
                                .ToLocalChecked());
}

void Initialize(Local<Object> exports)
{
  NODE_SET_METHOD(exports, "execute", Execute);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

} // namespace demo