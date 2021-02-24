#pragma once

#include "src/Core.hpp"
#include "src/Element/Element.hpp"
#include "Result.hpp"

namespace VPFEM {
    class Analyze : public Result
    {
        public:
            Analyze();
            virtual ~Analyze();
            inline void SetTolarance(double tol) {m_tolarance = tol;}
            inline void SetTotalDof(size_t num) {m_total_dof = num;}
            inline void SetElement(std::vector<std::shared_ptr<Element>>& ele) {m_element = ele;}
            inline void SetNode(std::vector<std::shared_ptr<Node>>& node) {m_node = node;}
            virtual void Solve() = 0;
        protected:
            double m_tolarance = 0.0001;
            size_t max_limit = 1000000;
            size_t m_total_number_dof = 0;
            size_t m_total_dof;
            std::vector<std::shared_ptr<Element>> m_element;
            std::vector<std::shared_ptr<Node>> m_node;
    };
}
