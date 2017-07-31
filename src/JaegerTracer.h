#ifndef JAEGERTRACER_H
#define JAEGERTRACER_H

#include <phpcpp.h>
#include <iostream>
#include "ITracer.h"
#include "JaegerSpan.h"
#include "IReporter.h"
#include "ISampler.h"
#include "Process.h"

class JaegerTracer : public ITracer
{
private:
    IReporter* _reporter;
    ISampler* _sampler;
    Process* _process;
    std::vector<ISpan*> _spans;
    std::vector<ISpan*> _activeSpans;
    bool _isSampled;
public:
    ~JaegerTracer()
    {
        delete _reporter;
        delete _sampler;
        delete _process;
        for (auto iter : _spans)
            delete iter;
        _spans.clear();
        for (auto iter : _activeSpans)
            delete iter;
        _activeSpans.clear();

        Php::out << "~JaegerTracer" << std::endl;
    }

    JaegerTracer(IReporter* reporter, ISampler* sampler) :
        _reporter{ reporter },
        _sampler{ sampler },
        _isSampled{ false }
    {
        Php::out << "JaegerTracer::JaegerTracer" << std::endl;
    };

    void init(const std::string& serviceName);
    ISpan* startSpan(const std::string& operationName, const Php::Value& options = nullptr) const;
    ISpan* getCurrentSpan() const;
    void finishSpan() const;
    void inject() const;
    void extract() const;
    void flush() const;

    const char* _name() const;
};


#endif /* JAEGERTRACER_H */

