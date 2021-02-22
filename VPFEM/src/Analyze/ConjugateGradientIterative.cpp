#include "ConjugateGradientIterative.hpp"

namespace VPFEM {
    void ConjugateGradientIterative::Solve()
    {
       size_t i = 0;
       VectorXld result = VectorXld::Zero(m_total_dof);//MakeInit(); ZeroFixes(result);
       VectorXld residual = GlobalForce();
       VectorXld P = residual;
       long double residual_old = residual.transpose() * residual;
       for (; i < max_limit; i++)
       {
           VectorXld Q = VectorXld::Zero(m_total_dof);
           ElementByElement(Q, P);
           long double alpha = residual_old / (P.transpose() * Q);
           result = result + alpha * P;
           residual = residual - alpha * Q;
           long double residual_new = residual.transpose() * residual;
           if (residual_new < m_tolarance)
               break;
           long double beta = residual_new / residual_old;
           P = residual + beta * P;
           residual_old = residual_new;
           //VP_CORE_INFO("iteration:{0}, resedual={1}", i, residual_old);
       }
       if (i == max_limit)
           VP_CORE_ERROR("CG NOT converged! After {0} iterations.", max_limit);
       else
           VP_CORE_INFO("CG Converged! After {0} iterations.", i);

       m_deformation = result;
    }


    VectorXld ConjugateGradientIterative::MakeInit()
    {
        VectorXld init(m_total_dof);
        for (auto& i: init)
            i = 1.0;
        return init;
    }
    void ConjugateGradientIterative::ZeroFixes(VectorXld& v)
    {
        for (auto& n : m_node)
            n->ZeroFixes(v);
    }

    VectorXld ConjugateGradientIterative::GlobalForce()
    {

        VectorXld F  = VectorXld::Zero(m_total_dof);
        for (auto& ele : m_element)
        {
            VectorXld f = ele->ForceVector();
            ele->Assemble(F, f);
        }
        return F;
    }
    void ConjugateGradientIterative::ElementByElement(VectorXld& result, VectorXld& input)
    {
        for (auto& ele : m_element)
        {
            VectorXld r0 = ele->StiffnessMatrix() * ele->ElementVector(input);
            ele->Assemble(result, r0);
        }
        ZeroFixes(result);
    }
}
