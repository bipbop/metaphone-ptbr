#include <iostream>
#include <nan.h>

extern "C" {
#include <metaphone_ptbr.h>
}

using namespace Nan; // NOLINT(build/namespaces)

NAN_METHOD(metaphone) {
  std::string arg;
  char *metastr;
  char *argCpy;
  wchar_t *argEnc;
  size_t sizeArg;
  size_t sizeArgEnc;
  size_t sizeArgCpy;

  arg = *Utf8String(info[0]->ToString(Nan::GetCurrentContext()).FromMaybe(v8::Local<v8::String>()));
  sizeArg = arg.length();

  sizeArgCpy = ((sizeArg + 1) * sizeof(char));
  argCpy = (char *)malloc(sizeArgCpy);
  bzero(argCpy, sizeArgCpy);

  sizeArgEnc = ((sizeArg + 1) * sizeof(wchar_t));
  argEnc = (wchar_t *)malloc(sizeArgEnc);
  bzero(argEnc, sizeArgEnc);

  strncpy(argCpy, arg.c_str(), sizeArg);
  mbstowcs(argEnc, argCpy, sizeArg);
  free(argCpy);

  metastr = metaphone_ptbr(argEnc, sizeArg);

  auto returnValue = info.GetReturnValue();
  if (metastr != NULL) {
    returnValue.Set(New(metastr).ToLocalChecked());
  } else {
    returnValue.Set(Null());
  }

  free(metastr);
  metastr = NULL;

  free(argEnc);
  argEnc = NULL;
}

NAN_MODULE_INIT(Initialize) { NAN_EXPORT(target, metaphone); }
NODE_MODULE(addon, Initialize);