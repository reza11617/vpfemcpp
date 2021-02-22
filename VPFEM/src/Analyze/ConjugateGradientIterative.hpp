#pragma once
#include "src/Core.hpp"
#include "Analyze.hpp"

namespace VPFEM {
    class ConjugateGradientIterative : public Analyze
    {
        private:
        public:
            virtual void Solve() override;
        protected:
            VectorXld MakeInit();
            void ZeroFixes(VectorXld& v);
            VectorXld GlobalForce();
            void ElementByElement(VectorXld& result, VectorXld& input);
    };
}
