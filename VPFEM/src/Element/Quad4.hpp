#pragma once

#include "src/Core.hpp"
#include "Element.hpp"

namespace VPFEM {
    class Quad4 : public Element
    {
        public:
            Quad4(size_t nip);
            void CreateIntegrationPoints();
            VectorXld ShapeFun(GaussPointWeight point);

        private:
            const static size_t DIM = 2;
            size_t m_nip;
            std::vector<GaussPointWeight> m_points;

    };
}
