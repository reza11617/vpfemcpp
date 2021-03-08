#pragma once

#include "Core.hpp"
#include "Log.hpp"
#include "src/Geometry/Model.hpp"
#include "src/Geometry/Node.hpp"
#include "src/Element/Element.hpp"
#include "src/Element/Quad4.hpp"
#include "src/Element/ElasticBeamElement.hpp"
#include "src/Element/ElasticBeamColumnElement.hpp"
#include "src/Material/Material.hpp"
#include "src/Analyze/Analyze.hpp"
#include "src/Analyze/Result.hpp"
#include "src/Recorder.hpp"

namespace VPFEM {
    class FiniteElementModel
    {
        public:
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

            template<typename T>
            void PushRecorder(const std::string& file_name,
                              VectorXld (* func) (std::shared_ptr<T>, std::shared_ptr<Result>),
                              std::initializer_list<std::shared_ptr<T>> list)
            {
                m_recorder.push_back(std::make_shared<Printer<T>>(file_name,
                                                                  func,
                                                                  list));
            }

            FiniteElementModel();
            void ModelBuilder(size_t nDof, size_t nDim);
            static void PrintRecorders(std::shared_ptr<FiniteElementModel> fem);
            virtual ~FiniteElementModel();
            inline std::vector<std::shared_ptr<Node>> GetNode() const {return node;}
            inline std::vector<std::shared_ptr<Element>> GetElement() const {return element;}
            inline std::vector<std::shared_ptr<Material>> GetMaterial() const {return material;}
            inline std::shared_ptr<Analyze> GetAnalyze() const {return analyze;}
            inline size_t GetTotalDof() const {return node.size() * m_model->GetNumberDofs();}
            inline std::shared_ptr<Result> GetResult() const {return result;}
            inline void SetDeformation(VectorXld& def) {result->SetDeformation(def);}
            inline void SetFiniteElementModelNumber(size_t num) {m_finite_element_model_number = num;}
            inline size_t GetFiniteElementModelNumber() const {return m_finite_element_model_number;}
            inline void SetRecorderDir(const std::string& path) {m_recorder_dir = path;}
            inline std::string& GetRecorderDir() {return m_recorder_dir;}
            inline std::vector<std::shared_ptr<Recorder>>& GetRecorder() {return m_recorder;}

        protected:
            std::vector<std::shared_ptr<Node>> node;
            std::vector<std::shared_ptr<Element>> element;
            std::vector<std::shared_ptr<Material>> material;
            std::shared_ptr<Analyze> analyze;
            std::shared_ptr<Result> result;
        private:
            std::shared_ptr<Model> m_model;
            size_t m_total_node_number = 0;
            size_t m_total_element_number = 0;
            size_t m_total_material_number = 0;
            size_t m_finite_element_model_number = 0;
            std::vector<std::shared_ptr<Recorder>> m_recorder;
            std::string m_recorder_dir;
    };

}
