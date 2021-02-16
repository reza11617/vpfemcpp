#pragma once

#include "src/Core.hpp"
#include "src/Log.hpp"

namespace VPFEM {
    class Model
    {
        private:
            size_t m_number_of_dofs = 0;
            size_t m_number_of_dimensions = 0;
        public:
            Model() {};
            Model(size_t nDof, size_t nDim);
            inline size_t GetNumberDofs() const {return m_number_of_dofs;}
            inline size_t GetNumberDims() const {return m_number_of_dimensions;}

    };
}
