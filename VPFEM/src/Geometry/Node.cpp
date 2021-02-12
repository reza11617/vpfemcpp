#include "Node.hpp"

namespace VPFEM {
    int Node::s_total_node = 0;
    Node::Node(double x)
        : m_x(x)
    {
        //--TODO check for each constructor to see if dim is correct
        m_node_number = s_total_node++; // capture the node number and increment the total number of nodes.

    }
    Node::~Node()
    {
    }
    void Node::Fix(std::initializer_list<bool> l_dof)
    {
    #ifdef DEBUG
        assert(l_dof.size() == Model::GetNumberDofs());
    #endif
        m_list_dof.insert(m_list_dof.end(), l_dof.begin(), l_dof.end());
    }
}
