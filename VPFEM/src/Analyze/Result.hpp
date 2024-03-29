#pragma once

#include "src/Core.hpp"
#include "src/Geometry/Node.hpp"

namespace VPFEM {
    class Result
    {
        protected:
            VectorXld m_deformation;
        public:
            inline VectorXld& GetDeformation() {return m_deformation;}
            inline void SetDeformation(VectorXld v) {m_deformation = v;}
            static VectorXld Deformation(std::shared_ptr<Node> node, std::shared_ptr<Result> results);
    };
}
