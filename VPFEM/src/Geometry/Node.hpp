#pragma once

#include "src/Core.hpp"
#include "Model.hpp"
#include "src/Log.hpp"

namespace VPFEM {
    class Load
    {
        public:
            Load(size_t dof, double magnitude);
            inline size_t GetDof() const {return m_dof;}
            inline size_t GetMagnitude() const {return m_magnitude;}
            void Write(std::ofstream& fout) const
            {
                fout << m_dof << "," << m_magnitude << ",";
            }
        private:
            size_t m_dof;
            double m_magnitude;
    };


    class Node
    {
        public:
            Node(double x);
            Node(double x, double y);
            Node(double x, double y, double z);
            Node(const Node& other);
            Node(Node&& other);
            Node& operator=(const Node& other);
            Node& operator=(Node&& other);
            void Fix(std::initializer_list<bool> l_dof);
            void PointLoad(size_t dof, double magnitude);
            size_t Local2Global(size_t dof);
            void ZeroFixes(VectorXld& v);
            inline double GetX() const {return m_x;}
            inline double GetY() const {return m_y;}
            inline double GetZ() const {return m_z;}
            inline size_t GetNodeNumber() const {return m_node_number;}
            inline void SetNodeNumber(size_t num) {m_node_number = num;}
            inline void SetModel(std::shared_ptr<Model> m) {m_model = m;}
            inline std::shared_ptr<Model> GetModel() const {return m_model;}
            inline const std::vector<Load>& GetLoad() const {return m_load;}
            inline const std::vector<bool>& GetListFixDofs() const {return m_list_dof;}
            ~Node();
            void WriteHeader(std::ofstream& fout) const;
            void Write(std::ofstream& fout) const;
            friend double Distance(const Node& n1, const Node& n2);
        private:
            size_t m_node_number = -1;
            double m_x = 0.0, m_y = 0.0, m_z = 0.0;
            std::vector<bool> m_list_dof;
            std::vector<Load> m_load;
            std::shared_ptr<Model> m_model;
    };
}
