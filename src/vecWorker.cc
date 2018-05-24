

#include <iostream>
#include "vecWorker.h"
#include <v8.h>

void VecWorker::Execute()
{
    try
    {
        wrapper_->loadModel();
        wrapper_->precomputeWordVectors();
        resultV_ = wrapper_->getWordVector(query_);
    }
    catch (std::string errorMessage)
    {
        std::cout << "Exception: " << errorMessage << std::endl;
        SetErrorMessage(errorMessage.c_str());
    }
    catch (const char *str)
    {
        std::cout << "Exception: " << str << std::endl;
        SetErrorMessage(str);
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        SetErrorMessage(e.what());
    }
}

void VecWorker::HandleErrorCallback()
{
    Nan::HandleScope scope;

    v8::Local<v8::Value> argv[] = {
        Nan::Error(ErrorMessage()),
        Nan::Null()};

    callback->Call(2, argv);
}

void VecWorker::HandleOKCallback()
{
    Nan::HandleScope scope;
    v8::Local<v8::Array> result = Nan::New<v8::Array>(resultV_.size());

    for (unsigned int i = 0; i < resultV_.size(); i++)
    {
        result->Set(i, Nan::New<v8::Number>(resultV_[i]));
    }

    v8::Local<v8::Value> argv[] = {
        Nan::Null(),
        result};

    callback->Call(2, argv);
}