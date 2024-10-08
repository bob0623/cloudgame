#pragma once

#include "common/config.h"
#include <vector>
#include <mutex>

class LogQueue {
public:
    LogQueue();
    ~LogQueue();
    
public:
    void    push(const std::string& msg);
    void    pull(int max, std::vector<std::string>& items);
    
private:
    std::mutex* m_pMutex;
    std::vector<std::string>    m_arrMsgs;
};


