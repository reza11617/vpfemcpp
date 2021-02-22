#pragma once

#include "Core.hpp"
#include "Log.hpp"
#include "src/Geometry/Model.hpp"
#include "src/Geometry/Node.hpp"
#include "src/Element/Element.hpp"
#include "src/Element/ElasticBeamElement.hpp"
#include "src/Element/ElasticBeamColumnElement.hpp"
#include "src/Analyze/Analyze.hpp"
#include "src/Analyze/ConjugateGradientIterative.hpp"
#include "src/Analyze/ConjugateGradientPreconditioned.hpp"
#include "src/Material/Material.hpp"
#include "Recorder.hpp"

namespace VPFEM {
    class FiniteElementModel
    {
        public:
            FiniteElementModel();
            void ModelBuilder(size_t nDof, size_t nDim);
            virtual ~FiniteElementModel();
            template<typename ... Ts>
            void PushNode(Ts ... args)
            {
                node.emplace_back(std::make_shared<Node>(args...));
                node.back()->SetNodeNumber(m_total_node_number);
                node.back()->SetModel(m_model);
                m_total_node_number++;
            }
            template<typename T, typename ... Ts>
            void PushElement(Ts ... args)
            {
                element.emplace_back(std::make_shared<T>(args...));
                element.back()->SetElementNumber(m_total_element_number);
                m_total_element_number++;

            }
            template<typename T, typename ... Ts>
            void PushMaterial(Ts ... args)
            {
                material.emplace_back(std::make_shared<T>(args...));
                material.back()->SetMaterialNumber(m_total_material_number);
                m_total_material_number++;

            }
            template <typename T>
            void Analyze(double tol)
            {
                analyze = std::make_unique<T>();
                analyze->SetTolarance(tol);
            }
            void Run();
            void RecorderMesh()
            {
                Recorder::Print("mesh_element.out", element);
                Recorder::Print("mesh_node.out", node);
            }
        protected:
            std::vector<std::shared_ptr<VPFEM::Node>> node;
            std::vector<std::shared_ptr<VPFEM::Element>> element;
            std::vector<std::shared_ptr<VPFEM::Material>> material;
            std::unique_ptr<ConjugateGradientIterative> analyze;
        private:
            std::shared_ptr<Model> m_model;
            size_t m_total_node_number = 0;
            size_t m_total_element_number = 0;
            size_t m_total_material_number = 0;
    };

}
