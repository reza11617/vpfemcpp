#include "FiniteElementModel.hpp"

namespace VPFEM {
    FiniteElementModel::FiniteElementModel()
    {
        result = std::make_shared<Result>();
        analyze = std::make_shared<Analyze>();
    }

    FiniteElementModel::~FiniteElementModel()
    {
    }

    void FiniteElementModel::ModelBuilder(size_t nDof, size_t nDim)
    {
        m_model = std::make_shared<Model>(nDof, nDim);
    }

    void FiniteElementModel::RecorderMesh()
    {
        Recorder::Print("mesh_element.out", element);
        Recorder::Print("mesh_node.out", node);
    }
}
