#pragma once
#include "src/Core.hpp"
#include "ConjugateGradientIterative.hpp"

namespace VPFEM {
    class ConjugateGradientPreconditioned : public ConjugateGradientIterative
    {
        public:
            void Solve() override;
        private:
            VectorXld Precondition();
    };
}
