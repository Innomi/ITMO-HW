#pragma once

#include <list>
#include <memory>
#include <string>
#include <utility>
#include "sttm.hpp"

class main_class
{
public:
    main_class();
    main_class(std::list<std::shared_ptr<sttm>> &&);
    main_class(const main_class &) = default;
    main_class(main_class &&) = default;
    main_class& operator=(main_class &&);
    void print(std::string && filename) const;
    
private:
    std::list<std::shared_ptr<sttm>> _sttmseq;
};
