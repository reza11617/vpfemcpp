#pragma once

#include "src/Core.hpp"
#include "src/Log.hpp"
#include "src/Material/Material.hpp"
#include "src/Geometry/Node.hpp"

namespace VPFEM {
    class Element
    {
        public:
            Element();
            virtual ~Element();
            virtual void Write(std::ofstream& fout) const;
            virtual void WriteHeader(std::ofstream& fout) const;
            virtual MatrixXld StiffnessMatrix() = 0;
            inline void SetElementNumber(size_t num) {m_ele_number = num;}
            inline void SetMaterial(std::shared_ptr<Material> mat) {material = mat;}
            inline const std::vector<std::shared_ptr<Node>>& GetListNode() const {return m_l_node;}
            inline size_t GetElementNumber() const {return m_ele_number;}

            size_t Local2Global(size_t dof);
            size_t TotalElementDof() const;
            size_t Node2Element(size_t dof, size_t node_number) const;
            void Assemble(VectorXld& Global, VectorXld& local);
            VectorXld ElementVector(VectorXld& global_vector);
            VectorXld ForceVector() const;
        protected:
            std::vector<std::shared_ptr<Node>> m_l_node;
            std::shared_ptr<Material> material;

        private:
            size_t m_ele_number = 0;
    };
}
