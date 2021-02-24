#include "Node.hpp"

namespace VPFEM {
    Load::Load(size_t dof, double magnitude)
        : m_dof(dof), m_magnitude(magnitude)
    {}

    Node::Node(double x)
        : m_x(x)
    {
    }
    Node::Node(double x, double y)
        : m_x(x), m_y(y)
    {
    }
    Node::Node(double x, double y, double z)
        : m_x(x), m_y(y), m_z(z)
    {
    }

    Node::Node(const Node& other)
    {
        m_list_dof = other.m_list_dof;
        m_load = other.m_load;
        m_node_number = other.m_node_number;
        m_x = other.m_x;
        m_y = other.m_y;
        m_z = other.m_z;
    }

    Node& Node::operator=(const Node &other)
    {
        if (this != &other)
        {
            m_list_dof.clear();
            m_load.clear();
            m_list_dof = other.m_list_dof;
            m_load = other.m_load;
            m_node_number = other.m_node_number;
            m_x = other.m_x;
            m_y = other.m_y;
            m_z = other.m_z;
        }
        return *this;
    }

    Node::Node(Node&& other)
    {
        m_list_dof = other.m_list_dof;
        m_load = other.m_load;
        m_node_number = other.m_node_number;
        m_x = other.m_x;
        m_y = other.m_y;
        m_z = other.m_z;
        other.m_list_dof.clear();
        other.m_load.clear();
    }

    Node& Node::operator=(Node &&other)
    {
        if (this != &other)
        {
            m_list_dof.clear();
            m_load.clear();

            m_list_dof = other.m_list_dof;
            m_load = other.m_load;
            m_node_number = other.m_node_number;
            m_x = other.m_x;
            m_y = other.m_y;
            m_z = other.m_z;

            other.m_list_dof.clear();
            other.m_load.clear();
        }
        return *this;
    }

    Node::~Node()
    {
    }

    double Distance(const Node& n1, const Node& n2)
    {
        return sqrt( (n1.GetX() - n2.GetX()) * (n1.GetX() - n2.GetX()) +
                     (n1.GetY() - n2.GetY()) * (n1.GetY() - n2.GetY()) +
                     (n1.GetZ() - n2.GetZ()) * (n1.GetZ() - n2.GetZ()));
    }

    void Node::Fix(std::initializer_list<bool> l_dof)
    {
    #ifdef DEBUG
        assert(l_dof.size() == m_model->GetNumberDofs());
    #endif
        m_list_dof.insert(m_list_dof.end(), l_dof.begin(), l_dof.end());
    }

    void Node::PointLoad(size_t dof, double magnitude)
    {
        m_load.emplace_back(dof, magnitude);
    }

    size_t Node::Local2Global(size_t dof)
    // This function take a local dof and returns a global dof
    {
        return m_node_number*m_model->GetNumberDofs() + dof;
    }

    void Node::ZeroFixes(VectorXld &v)
    // This function zeros the entris of a global vector v
    {
        size_t i = 0;
        for (auto dof : m_list_dof)
        {
            if (dof)
                v(Local2Global(i)) = 0.0;
            i++;
        }
    }

    void Node::WriteHeader(std::ofstream &fout) const
    {
        fout << "Node,x,y,z,fixedDof,load[dof,magnitude]";
    }

    void Node::Write(std::ofstream &fout) const
    {
        fout << m_node_number << "," << m_x << "," << m_y << "," << m_z << ",[";

        for (size_t i = 0; i < m_list_dof.size(); i++)
        {
            if (m_list_dof[i])
                fout << i << ",";
        }
        fout << "],[";
        for (auto& load : m_load)
            fout << "[" <<load.GetDof() << "," << load.GetMagnitude() << "]";
        fout << "]";
    }
}
