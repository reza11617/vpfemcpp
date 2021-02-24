#include "Solver.hpp"

namespace VPFEM
{
    size_t Solver::s_max_limit = 1000000;
    VectorXld Solver::CG(std::shared_ptr<FiniteElementModel> fem)
    {
        VP_PROFILE_FUNCTION();
        size_t i = 0;
        VectorXld result = VectorXld::Zero(fem->GetTotalDof());
        VectorXld residual = GlobalForce(fem);
        VectorXld P = residual;
        long double residual_old = residual.transpose() * residual;
        for (; i < s_max_limit; i++)
        {
            VectorXld Q = ElementByElement(P, fem);
            long double alpha = residual_old / (P.transpose() * Q);
            result = result + alpha * P;
            residual = residual - alpha * Q;
            long double residual_new = residual.transpose() * residual;
            if (residual_new < fem->GetAnalyze()->GetTolarance())
                break;
            long double beta = residual_new / residual_old;
            P = residual + beta * P;
            residual_old = residual_new;
            //VP_CORE_INFO("iteration:{0}, resedual={1}", i, residual_old);
        }
        if (i == s_max_limit)
            VP_CORE_ERROR("CG NOT converged! After {0} iterations.", s_max_limit);
        else
            VP_CORE_INFO("CG Converged! After {0} iterations.", i);

        return result;
    }

    VectorXld Solver::CGP(std::shared_ptr<FiniteElementModel> fem)
    {
        VP_PROFILE_FUNCTION();
        size_t i = 0;
        VectorXld result = VectorXld::Zero(fem->GetTotalDof());
        VectorXld residual = GlobalForce(fem);
        VectorXld M = Precondition(fem);
        VectorXld z = M.cwiseProduct(residual);
        VectorXld P = z;
        long double residual_old = residual.transpose() * z;
        for (; i < s_max_limit*100; i++) // max_limit
        {
            VectorXld Q = ElementByElement(P, fem);
            long double alpha = residual_old / (P.transpose() * Q);
            result = result + alpha * P;
            residual = residual - alpha * Q;
            z = M.cwiseProduct(residual);
            long double residual_new = z.transpose() * residual;
            if (residual_new < fem->GetAnalyze()->GetTolarance())
                break;
            long double beta = residual_new / residual_old;
            P = z + beta * P;
            residual_old = residual_new;
            //VP_CORE_INFO("iteration:{0}, resedual={1}", i, residual_old);
        }
        if (i == s_max_limit)
            VP_CORE_ERROR("CGP NOT converged! After {0} iterations.", s_max_limit);
        else
            VP_CORE_INFO("CGP Converged! After {0} iterations.", i);
        return result;
    }

    void Solver::ZeroFixes(VectorXld& v, std::shared_ptr<FiniteElementModel> fem)
    {
        for (auto& n : fem->GetNode())
            n->ZeroFixes(v);
    }

    VectorXld Solver::GlobalForce(std::shared_ptr<FiniteElementModel> fem)
    {

        VectorXld F  = VectorXld::Zero(fem->GetTotalDof());
        for (auto& ele : fem->GetElement())
        {
            VectorXld f = ele->ForceVector();
            ele->Assemble(F, f);
        }
        return F;
    }
    VectorXld Solver::ElementByElement(VectorXld& input, std::shared_ptr<FiniteElementModel> fem)
    {
        VectorXld Q = VectorXld::Zero(fem->GetTotalDof());
        for (auto& ele : fem->GetElement())
        {
            VectorXld r0 = ele->StiffnessMatrix() * ele->ElementVector(input);
            ele->Assemble(Q, r0);
        }
        ZeroFixes(Q, fem);
        return Q;
    }

    VectorXld Solver::Precondition(std::shared_ptr<FiniteElementModel> fem)
    {
        VectorXld M = VectorXld::Zero(fem->GetTotalDof());
        for (auto& ele: fem->GetElement())
        {
            VectorXld m = ele->StiffnessMatrix().diagonal().cwiseInverse();
            ele->Assemble(M,m);
        }
        ZeroFixes(M, fem);
        return M;
    }
}
