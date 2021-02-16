#include "BeamElement.hpp"

namespace VPFEM {
    BeamElement::~BeamElement(){}

    BeamElement::BeamElement(std::shared_ptr<Node> node_i, std::shared_ptr<Node> node_j, double stiffness)
        : Element()
    {
        m_l_node.emplace_back(node_i);
        m_l_node.emplace_back(node_j);
        m_stiffness = stiffness;
        m_length = Distance(*node_i, *node_j);
    }

    void BeamElement::Write(std::ostream &os) const
    {
        os << " Length = " << m_length;
    }


    Eigen::MatrixXd BeamElement::StiffnessMatrix()
    {
        Eigen::MatrixXd m(TotalElementDof(), TotalElementDof());
        double c =  2.0*m_stiffness/pow(m_length, 3);  // coefficient
        m(0,0) = c * 6;
        m(0,1) = c * 3*m_length;
        m(0,2) = c * -6;
        m(0,3) = c * 3*m_length;
        m(1,0) = c * 3*m_length;
        m(1,1) = c * 2*m_length*m_length;
        m(1,2) = c * -3*m_length;
        m(1,3) = c * m_length*m_length;
        m(2,0) = c * -6;
        m(2,1) = c * -3*m_length;
        m(2,2) = c * 6;
        m(2,3) = c * -3*m_length;
        m(3,0) = c * 3*m_length;
        m(3,1) = c * m_length*m_length;
        m(3,2) = c * -3*m_length;
        m(3,3) = c * 2*m_length*m_length;
        return m;
    }
}
