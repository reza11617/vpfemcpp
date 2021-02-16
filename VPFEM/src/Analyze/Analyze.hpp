#pragma once

#include "src/Core.hpp"
#include "src/Element/Element.hpp"

namespace VPFEM {
    struct Analyze
    {
        public:
            Analyze() {};
            inline void SetTolarance(double tol) {m_tolarance = tol;}
            inline void SetTotalDof(size_t num) {m_total_dof = num;}
            inline void SetElement(std::vector<std::shared_ptr<Element>>& ele) {m_element = ele;}
            inline void SetNode(std::vector<std::shared_ptr<Node>>& node) {m_node = node;}

        protected:
            double m_tolarance = 0.0001;
            size_t m_total_number_dof = 0;
            size_t m_total_dof;
            std::vector<std::shared_ptr<Element>> m_element;
            std::vector<std::shared_ptr<Node>> m_node;
    };

    class ConjugateGradientIterative : public Analyze
    {
        private:
            Eigen::VectorXd* Result;
        public:
            void Solve()
            {
                Eigen::VectorXd init = MakeInit(); ZeroFixes(init);
                Eigen::VectorXd R0 = Eigen::VectorXd::Zero(m_total_dof);
                for (auto& ele : m_element)
                {
                    Eigen::VectorXd r0 = ele->ForceVector() - ele->StiffnessMatrix() * ele->ElementVector(init);
                    ele->Assemble(R0, r0);
                }
                VP_CORE_INFO(R0);
            }
        private:
            Eigen::VectorXd MakeInit()
            {
                Eigen::VectorXd init(m_total_dof);
                for (auto& i: init)
                    i = 1.0;
                return init;
            }
            void ZeroFixes(Eigen::VectorXd& v)
            {
                for (auto& n : m_node)
                    n->ZeroFixes(v);
            }
    };

}
