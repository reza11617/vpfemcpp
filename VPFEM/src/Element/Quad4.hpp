#pragma once

#include "src/Core.hpp"
#include "Element.hpp"

namespace VPFEM {
    class Quad4 : public Element
    {
        public:
            enum Nip {ONE=1, Four=2, NINE=3};
        public:
            Quad4(std::shared_ptr<Node> n_1,
                  std::shared_ptr<Node> n_2,
                  std::shared_ptr<Node> n_3,
                  std::shared_ptr<Node> n_4,
                  Nip nip, std::shared_ptr<Material> material);
            void CreateIntegrationPoints();
            VectorXld ShapeFun(GaussPointWeight xi, GaussPointWeight eta);
            MatrixXld ShapeDer(GaussPointWeight xi, GaussPointWeight eta);
            MatrixXld Coord();
            MatrixXld BeeMat(MatrixXld &deriv);
        private:
            size_t m_nip;
            const static size_t DIM = 2;
            std::vector<GaussPointWeight> m_points;

    };
}
