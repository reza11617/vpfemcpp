#include "Element.hpp"

namespace VPFEM {
    Element::Element()
    {
    }
    Element::~Element(){}

    size_t Element::TotalElementDof() const
    {
        return m_l_node.size() * m_l_node[0]->GetModel()->GetNumberDofs();
    }

    size_t Element::Local2Global(size_t dof)
    {
        size_t max_node_dof = m_l_node[0]->GetModel()->GetNumberDofs();
        size_t node_number = dof/max_node_dof;
        size_t node_dof = dof % max_node_dof;
        return m_l_node[node_number]->Local2Global(node_dof);
    }

    VectorXld Element::ElementVector(VectorXld& global_vector)
    {
        VectorXld local_vector(TotalElementDof());
        for (size_t i = 0; i < TotalElementDof(); i++)
            local_vector(i) = global_vector(Local2Global(i));
        return local_vector;
    }

    size_t Element::Node2Element(size_t dof, size_t node_number) const
    {
        size_t max_node_dof = m_l_node[0]->GetModel()->GetNumberDofs();
        return max_node_dof * node_number + dof;
    }

    VectorXld Element::ForceVector() const
    {
        VectorXld force = VectorXld::Zero(TotalElementDof());
        for (size_t i = 0; i < m_l_node.size(); i++)
            for (auto& load: m_l_node[i]->GetLoad())
                force(Node2Element(load.GetDof(), i)) = load.GetMagnitude();
        return force;
    }

    void Element::Assemble(VectorXld &Global, VectorXld &local)
    {
        for (size_t i = 0; i < TotalElementDof(); i++)
        {
            Global(Local2Global(i)) += local(i);
        }
    }

    void Element::WriteHeader(std::ofstream &fout) const
    {
        for (auto& node : m_l_node)
        {
            fout << "Node" << "_";
            fout << node->GetNodeNumber() << ",";
        }
    }

    void Element::Write(std::ofstream &fout) const
    {
        fout << m_ele_number << ",";
        for (auto& node : m_l_node)
            fout << node->GetNodeNumber() << ",";

    }

}
