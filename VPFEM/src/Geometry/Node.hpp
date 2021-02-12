#pragma once

#include "src/Core.hpp"
#include "Model.hpp"
#include "src/Log.hpp"

namespace VPFEM {
    class Node
    {
        public:
            Node(double x);
            void Fix(std::initializer_list<bool> l_dof);
            inline double GetX() const {return m_x;}
            inline int GetNodeNumber() const {return m_node_number;}
            ~Node();
        private:
            static int s_total_node;
            int m_node_number;
            double m_x, m_y, m_z;
            std::vector<bool> m_list_dof;
    };
}
