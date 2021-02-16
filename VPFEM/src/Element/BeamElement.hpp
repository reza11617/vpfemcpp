#pragma once

#include "src/Core.hpp"
#include "src/Log.hpp"
#include "src/Geometry/Node.hpp"
#include "Element.hpp"

namespace VPFEM {
    class BeamElement : public Element
    {
        public:
            BeamElement(std::shared_ptr<Node> node_i, std::shared_ptr<Node> node_j, double stiffness);
            ~BeamElement();

            inline double GetLength() const {return m_length;}
            inline double GetStiffness() const {return m_stiffness;}

            Eigen::MatrixXd StiffnessMatrix() override;
            void Write(std::ostream& os) const;

        private:
            double m_stiffness;
            double m_length;
    };
}
