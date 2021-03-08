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

    MatrixXld Element::BeeMat(MatrixXld &deriv)
    {
        size_t n_dim = deriv.rows();
        size_t n_shape = deriv.cols();

        size_t bee_rows = n_dim*(n_dim+1)/2;
        size_t bee_cols = n_dim * n_shape;

        MatrixXld bee = MatrixXld::Zero(bee_rows, bee_cols);

        for (size_t j = 0; j < n_shape; j++)
        {
            for (size_t i = 0; i < n_dim; i++)
                bee(i, j * n_dim + i) = deriv(i, j);

            bee(n_dim, j * n_dim + 1) = deriv(0, j);
            bee(n_dim, j * n_dim + 0) = deriv(1, j);
        }
        // for 3d dimension where number of rows in bee matrix is 6
        if (n_dim + 1 < bee_rows)
        {
            for (size_t j = 0; j < n_shape; j++)
            {
                bee(n_dim + 1, j * n_dim + 1) = deriv(2, j);
                bee(n_dim + 1, j * n_dim + 2) = deriv(1, j);
                bee(n_dim + 2, j * n_dim + 0) = deriv(2, j);
                bee(n_dim + 2, j * n_dim + 2) = deriv(0, j);
            }
        }

        return bee;
    }
/*

    MatrixXld Element::Coord()
    {
        size_t n_nodes = m_l_node.size();
        size_t n_dim = m_l_node[0]->GetModel()->GetNumberDims();
        MatrixXld coord(n_dim, n_nodes);
        for (auto node: m_l_node)
            for (size_t i = 0 ; i < n_dim)

    }
*/

    MatrixXld Element::StiffnessMatrix()
    {

    }


}
