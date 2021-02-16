#include "Model.hpp"

namespace VPFEM {
    Model::Model(size_t nDof, size_t nDim)
        :m_number_of_dofs(nDof), m_number_of_dimensions(nDim)
    {
        VP_CORE_INFO("Model Build with {0} Dofs {1} Dims.", nDof, nDim);
    }
}
