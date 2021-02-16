#include "FiniteElementModel.hpp"

namespace VPFEM {
    FiniteElementModel::FiniteElementModel()
    {
    }

    FiniteElementModel::~FiniteElementModel()
    {
    }

    void FiniteElementModel::ModelBuilder(size_t nDof, size_t nDim)
    {
        m_model = std::make_shared<Model>(nDof, nDim);
        // TODO - make it a way user can chose the type of analysis
        analyze = std::make_unique<ConjugateGradientIterative>();
    }

    void FiniteElementModel::Run()
    {
        analyze->SetTotalDof(node.size() * m_model->GetNumberDofs());
        analyze->SetElement(element);
        analyze->SetNode(node);
        analyze->Solve();
    }
}
