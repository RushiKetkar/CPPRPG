#include "RoundPass.hpp"

RoundPass::RoundPass() : m_roundPassed{ false } { }

bool RoundPass::checkPassed() { return m_roundPassed; }

void RoundPass::roundPassed() { m_roundPassed = true; }

void RoundPass::roundStart() { m_roundPassed = false; }