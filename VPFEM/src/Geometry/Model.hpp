#pragma once

#include "src/Core.hpp"
#include "src/Log.hpp"

namespace VPFEM {
    class Model
    {
        private:
            static size_t s_number_of_dofs;
            static size_t s_number_of_dimensions;
        public:
            static void ModelBuilder(size_t nDof, size_t nDim);
            inline static size_t GetNumberDofs() {return s_number_of_dofs;}
            inline static size_t GetNumberDims(){return s_number_of_dimensions;}

    };
}
