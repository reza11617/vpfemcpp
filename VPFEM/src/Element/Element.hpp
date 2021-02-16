#pragma once

#include "src/Core.hpp"
#include "src/Log.hpp"
#include "src/Geometry/Node.hpp"

namespace VPFEM {
    class Element
    {
        public:
            Element();
            virtual ~Element();
            virtual void Write(std::ostream& os) const = 0;
            virtual Eigen::MatrixXd StiffnessMatrix() = 0;

            inline const std::vector<std::shared_ptr<Node>>& GetListNode() const {return m_l_node;}
            inline size_t GetElementNumber() const {return m_ele_number;}
            inline void SetElementNumber(size_t num) {m_ele_number = num;}

            size_t Local2Global(size_t dof);
            size_t TotalElementDof();
            size_t Node2Element(size_t dof, size_t node_number);
            void Assemble(Eigen::VectorXd& Global, Eigen::VectorXd& local);
            Eigen::VectorXd ElementVector(Eigen::VectorXd& global_vector);
            Eigen::VectorXd ForceVector();
        protected:
            std::vector<std::shared_ptr<Node>> m_l_node;

        private:
            size_t m_ele_number;

        public:
            template<typename OStream>
            friend OStream &operator<<(OStream &os, const Element &c)
            {
                os << "Element(" << c.GetElementNumber() << ") ";
                os << "Nodes={ ";
                for (auto& n : c.GetListNode())
                    os << n->GetNodeNumber() << " ";
                os << "}";
                c.Write(os);
                return os;
            }
    };
}
