#include "ElasticBeamColumnElement.hpp"

namespace VPFEM {
    ElasticBeamColumnElement::~ElasticBeamColumnElement(){}

    ElasticBeamColumnElement::ElasticBeamColumnElement(std::shared_ptr<Node> node_i, std::shared_ptr<Node> node_j, double inertia, double area, std::shared_ptr<Material> mat)
        : Element()
    {
    #ifdef DEBUG
        assert(node_i->GetModel()->GetNumberDofs() == 3 && "(ElasticBeamColumnElement needs three DOFs)");
    #endif

        m_l_node.emplace_back(node_i);
        m_l_node.emplace_back(node_j);
        SetMaterial(mat);
        m_inertia = inertia;
        m_area = area;
        m_length = Distance(*node_i, *node_j);
    }
    void ElasticBeamColumnElement::WriteHeader(std::ofstream &fout) const
    {
        fout << "ElementType,";
        Element::WriteHeader(fout);
    }
    void ElasticBeamColumnElement::Write(std::ofstream &fout) const
    {
        fout << "ElasticBeamColumnElement,";
        Element::Write(fout);
    }


    MatrixXld ElasticBeamColumnElement::StiffnessMatrix()
    {
        // TODO add traslation using [T'][k][T] otherwise this is use less
        MatrixXld m = MatrixXld::Zero(TotalElementDof(), TotalElementDof());
        double axial_stiff = material->GetStiffness() * m_area;
        m(0,0) = axial_stiff;
        m(3,0) = -axial_stiff;
        m(0,3) = -axial_stiff;
        m(3,3) = axial_stiff;
        double c =  2.0 * (material->GetStiffness()) * m_inertia/pow(m_length, 3);  // coefficient
        m(1,1) = c * 6;
        m(1,2) = c * 3*m_length;
        m(1,4) = c * -6;
        m(1,5) = c * 3*m_length;
        m(2,1) = c * 3*m_length;
        m(2,2) = c * 2*m_length*m_length;
        m(2,4) = c * -3*m_length;
        m(2,5) = c * m_length*m_length;
        m(4,1) = c * -6;
        m(4,2) = c * -3*m_length;
        m(4,4) = c * 6;
        m(4,5) = c * -3*m_length;
        m(5,1) = c * 3*m_length;
        m(5,2) = c * m_length*m_length;
        m(5,4) = c * -3*m_length;
        m(5,5) = c * 2*m_length*m_length;
        return m;
    }
}
