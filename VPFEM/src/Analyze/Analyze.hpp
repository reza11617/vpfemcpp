#pragma once

#include "src/Core.hpp"
#include "src/Element/Element.hpp"

namespace VPFEM {
    class Analyze
    {
        public:
            Analyze();
            ~Analyze();
            inline void SetTolarance(double tol) {m_tolarance = tol;}
            inline double GetTolarance() const {return m_tolarance;}
        protected:
            double m_tolarance = 0.0001;
            size_t max_limit = 1000000;
    };
}
