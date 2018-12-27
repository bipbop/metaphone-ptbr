#include <nan.h>
#include <iostream>

extern "C" {
  #include <metaphone_ptbr.h>
}

using namespace Nan;  // NOLINT(build/namespaces)

NAN_METHOD(metaphone) {
  std::string stringArgument = *v8::String::Utf8Value(info[0]->ToString());

  auto stringArgumentLength = stringArgument.length();
  if (!stringArgumentLength) {
    ThrowError("first argument cannot be empty");
    return;
  }

  wchar_t * stringArgumentEncoded = (wchar_t *)malloc(stringArgumentLength * sizeof(wchar_t));
  std::mbstowcs(stringArgumentEncoded, stringArgument.c_str(), stringArgumentLength);
  char * metaphone = Metaphone_PTBR(stringArgumentEncoded, stringArgumentLength);
  free(stringArgumentEncoded);

  info.GetReturnValue().Set(New(metaphone).ToLocalChecked());
  free(metaphone);
}

NAN_MODULE_INIT(Initialize) {
    NAN_EXPORT(target, metaphone);
}

NODE_MODULE(addon, Initialize);