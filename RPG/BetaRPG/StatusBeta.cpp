#include "Status.hpp"
#include <cassert>

Status::Status(StatusFlags::status_t statusFlag, int counter, int scalar) : m_counter{ counter }, m_scalar{ scalar }, 
m_statusFlag{ statusFlag }, m_statusID{ m_IDGen }
{ 
    assert(m_counter > 0); 
    ++m_IDGen; 
}

Status::~Status() { }

int Status::m_IDGen{ 1 };

const StatusFlags::status_t& Status::getStatus() { return m_statusFlag; }
int Status::getCounter() { return m_counter; }
int Status::getScalar() { return m_scalar; }
int Status::getID() { return m_statusID; }
bool Status::getrelateToItem() { return m_relateToItem; }

Status& Status::reduceCounter()
{
    --m_counter;

    return *this;
}


