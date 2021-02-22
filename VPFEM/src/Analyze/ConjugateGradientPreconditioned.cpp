#include "ConjugateGradientPreconditioned.hpp"

namespace VPFEM {
    void ConjugateGradientPreconditioned::Solve()
    {
       size_t i = 0;
       VectorXld result = VectorXld::Zero(m_total_dof);
       VectorXld residual = GlobalForce();
       VectorXld M = Precondition();
       VectorXld z = M.cwiseProduct(residual);
       VectorXld P = z;
       long double residual_old = residual.transpose() * z;
       for (; i < max_limit*100; i++) // max_limit
       {
           VectorXld Q = VectorXld::Zero(m_total_dof);
           ElementByElement(Q, P);
           long double alpha = residual_old / (P.transpose() * Q);
           result = result + alpha * P;
           residual = residual - alpha * Q;
           z = M.cwiseProduct(residual);

           long double residual_new = z.transpose() * residual;
           if (residual_new < m_tolarance)
               break;
           long double beta = residual_new / residual_old;
           P = z + beta * P;
           residual_old = residual_new;
           //VP_CORE_INFO("iteration:{0}, resedual={1}", i, residual_old);
       }
       if (i == max_limit)
           VP_CORE_ERROR("CGP NOT converged! After {0} iterations.", max_limit);
       else
           VP_CORE_INFO("CGP Converged! After {0} iterations.", i);

       m_deformation = result;
    }

    VectorXld ConjugateGradientPreconditioned::Precondition()
    {
        VectorXld M = VectorXld::Zero(m_total_dof);
        for (auto& ele: m_element)
        {
            VectorXld m = ele->StiffnessMatrix().diagonal().cwiseInverse();
            ele->Assemble(M,m);
        }
        ZeroFixes(M);
        return M;
    }

}
