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

    void FiniteElementModel::PrintRecorders(std::shared_ptr<FiniteElementModel> fem)
    {
        VP_PROFILE_FUNCTION();
        for (auto recorder : fem->GetRecorder())
        {
            recorder->StartRecording(fem->GetRecorderDir());
            recorder->Print(fem->GetResult());
        }
    }

}
