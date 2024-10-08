#include "logqueue.h"

LogQueue::LogQueue() {
    m_pMutex = new std::mutex();
}

LogQueue::~LogQueue() {
    delete m_pMutex;
}

void    LogQueue::push(const std::string& msg) {
    m_pMutex->lock();
    if( m_arrMsgs.size() <= 10000 ) {
        m_arrMsgs.push_back(msg);
    }
    m_pMutex->unlock();
}

void    LogQueue::pull(int max, std::vector<std::string>& items) {
    if( m_arrMsgs.empty() ) {
        return;
    }
    m_pMutex->lock();
    size_t count = (max>=m_arrMsgs.size())?m_arrMsgs.size():max;
    for( size_t i=0; i<count; i++ ) {
        items.push_back(m_arrMsgs[i]);
    }
    m_arrMsgs.erase(m_arrMsgs.begin(), m_arrMsgs.begin()+count);
    m_pMutex->unlock();
}

