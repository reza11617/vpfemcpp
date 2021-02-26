#include "FiniteElementModel.hpp"

namespace VPFEM {
    FiniteElementModel::FiniteElementModel()
    {
        result = std::make_shared<Result>();
        analyze = std::make_shared<Analyze>();
    }

    static VectorXld GetDif(size_t i)
    {
        VectorXld v(2);
        v << 2,3;
        return v;
    }
    FiniteElementModel::~FiniteElementModel()
    {
        VectorXld r = result->GetDeformation();
        Recorder recorder("displacement.out",
                          m_finite_element_model_number,
                          Result::Deformation,
                          node.back(),
                          result);
        recorder.Print(r);
        recorder.Print(r);
        recorder.Print();

    }

    void FiniteElementModel::CreateRecorderFilePath(size_t num)
    {
        // creating the file path for results
        std::string file_path = "results/model_" + std::to_string(num);
        std::filesystem::create_directories(file_path);
    }
    void FiniteElementModel::ModelBuilder(size_t nDof, size_t nDim)
    {
        m_model = std::make_shared<Model>(nDof, nDim);
    }

}
