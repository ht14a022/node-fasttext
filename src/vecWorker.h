
#ifndef VEC_WORKER_H
#define VEC_WORKER_H

#include <nan.h>
#include "wrapper.h"

class VecWorker : public Nan::AsyncWorker
{
public:
  VecWorker(Nan::Callback *callback, std::string query, Wrapper *wrapper)
      : Nan::AsyncWorker(callback),
        query_(query),
        wrapper_(wrapper){};

  ~VecWorker(){};

  void Execute();
  void HandleOKCallback();
  void HandleErrorCallback();

private:
  std::string query_;
  Wrapper *wrapper_;
  std::vector<double> resultV_;
};

#endif