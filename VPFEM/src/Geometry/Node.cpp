#include "Node.hpp"

namespace VPFEM {
    Load::Load(size_t dof, double magnitude)
        : m_dof(dof), m_magnitude(magnitude)
    {}

    Node::Node(double x)
        : m_coord({x})
    {
    }

    Node::Node(double x, double y)
        : m_coord({x, y})
    {
    }

    Node::Node(double x, double y, double z)
        : m_coord({x, y, z})
    {
    }

    Node::Node(const Node& other)
    {
        m_coord = other.m_coord;
        m_list_dof = other.m_list_dof;
        m_load = other.m_load;
        m_node_number = other.m_node_number;
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
            m_coord = other.m_coord;
        }
        return *this;
    }

    Node::Node(Node&& other)
    {
        m_list_dof = other.m_list_dof;
        m_load = other.m_load;
        m_node_number = other.m_node_number;
        m_coord = other.m_coord;
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

            m_coord = other.m_coord;
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
        switch(n1.GetCoord().size())
        {
            case 1:
                return sqrt( (n1.GetCoord()[0] - n2.GetCoord()[0]) * (n1.GetCoord()[0] - n2.GetCoord()[0]));
            case 2:
                return sqrt( (n1.GetCoord()[0] - n2.GetCoord()[0]) * (n1.GetCoord()[0] - n2.GetCoord()[0]) +
                             (n1.GetCoord()[1] - n2.GetCoord()[1]) * (n1.GetCoord()[1] - n2.GetCoord()[1]));
            case 3:
                return sqrt( (n1.GetCoord()[0] - n2.GetCoord()[0]) * (n1.GetCoord()[0] - n2.GetCoord()[0]) +
                             (n1.GetCoord()[1] - n2.GetCoord()[1]) * (n1.GetCoord()[1] - n2.GetCoord()[1]) +
                             (n1.GetCoord()[2] - n2.GetCoord()[2]) * (n1.GetCoord()[2] - n2.GetCoord()[2]));
        }
        return 0;
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
        fout << m_node_number << ",";
        for (auto& c: m_coord)
            fout << c << ",";
        fout << "[";
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
