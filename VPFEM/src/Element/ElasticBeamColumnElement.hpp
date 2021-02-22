#pragma once

#include "src/Core.hpp"
#include "src/Log.hpp"
#include "src/Geometry/Node.hpp"
#include "Element.hpp"

namespace VPFEM {
    class ElasticBeamColumnElement : public Element
    {
        public:
            ElasticBeamColumnElement(std::shared_ptr<Node> node_i, std::shared_ptr<Node> node_j, double inertia, double Area, std::shared_ptr<Material> material);
            ~ElasticBeamColumnElement();

            inline double GetLength() const {return m_length;}
            inline double GetInertia() const {return m_inertia;}
            inline double GetArea() const {return m_area;}

            MatrixXld StiffnessMatrix() override;
            virtual void WriteHeader(std::ofstream& fout) const override;
            virtual void Write(std::ofstream& fout) const override;

        private:
            double m_inertia;
            double m_length;
            double m_area;
    };
}
