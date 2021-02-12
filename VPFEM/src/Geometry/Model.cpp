#include "Model.hpp"

namespace VPFEM {
    size_t Model::s_number_of_dofs;
    size_t Model::s_number_of_dimensions;

    void Model::ModelBuilder(size_t nDof, size_t nDim)
    {
        Model::s_number_of_dofs = nDof;
        Model::s_number_of_dimensions = nDof;
        VP_CORE_INFO("Model Build with {0} Dofs {1} Dims.", nDof, nDim);
    }
}
