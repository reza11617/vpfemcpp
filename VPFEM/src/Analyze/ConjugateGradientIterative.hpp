#pragma once
#include "src/Core.hpp"
#include "Analyze.hpp"

namespace VPFEM {
    class ConjugateGradientIterative : public Analyze
    {
        private:
        public:
            ConjugateGradientIterative(){};
            ~ConjugateGradientIterative(){};
            virtual void Solve() override;
        protected:
            void ZeroFixes(VectorXld& v);
            VectorXld GlobalForce();
            VectorXld ElementByElement(VectorXld& input);
    };
}
