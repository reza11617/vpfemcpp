#pragma once
#include "src/Core.hpp"
#include "src/FiniteElementModel.hpp"
namespace VPFEM {
    class Solver
    {
        public:
            static Solver& Get()
            {
                static Solver solver;
                return solver;
            }

            static void ElasticAnalysis(std::shared_ptr<FiniteElementModel> fem);
            static VectorXld  CG(std::shared_ptr<FiniteElementModel> fem); // Conjugate gradient Iterative
            static VectorXld CGP(std::shared_ptr<FiniteElementModel> fem); // Conjugate gradient Preconditioned
            static void ZeroFixes(VectorXld& v, std::shared_ptr<FiniteElementModel> fem);
            static VectorXld GlobalForce(std::shared_ptr<FiniteElementModel> fem);
            static VectorXld ElementByElement(VectorXld& input, std::shared_ptr<FiniteElementModel> fem);
            static VectorXld Precondition(std::shared_ptr<FiniteElementModel> fem);
            static size_t s_max_limit;

        private:
            Solver();
    };

}
