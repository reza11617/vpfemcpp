#pragma once
#include "src/Core.hpp"
#include "src/FiniteElementModel.hpp"
namespace VPFEM {
    class Solver
    {
        static Solver& Get()
        {
            static Solver solver;
            return solver;
        }
        static void  CG(FiniteElementModel fem); // Conjugate gradient Iterative
        static void CGP(FiniteElementModel fem); // Conjugate gradient Preconditioned
        void ZeroFixes(VectorXld& v);
        VectorXld GlobalForce();
        VectorXld ElementByElement(VectorXld& input);

        private:
            Solver();
    };

}
