#pragma once

#include "src/Core.hpp"
#include "src/Log.hpp"
#include "src/Geometry/Node.hpp"
#include "Element.hpp"

namespace VPFEM {
    class ElasticBeamElement : public Element
    {
        public:
            using Element::Write;
            ElasticBeamElement(std::shared_ptr<Node> node_i, std::shared_ptr<Node> node_j, double inertia, std::shared_ptr<Material> material);
            ~ElasticBeamElement();

            inline double GetLength() const {return m_length;}
            inline double GetInertia() const {return m_inertia;}

            MatrixXld StiffnessMatrix() override;
            void WriteHeader(std::ofstream& fout) const override;
            void Write(std::ofstream& fout) const override;

        private:
            double m_inertia;
            double m_length;
    };
}
