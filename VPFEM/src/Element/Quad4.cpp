#include "Quad4.hpp"

namespace VPFEM {
    Quad4::Quad4(std::shared_ptr<Node> n_1,
                 std::shared_ptr<Node> n_2,
                 std::shared_ptr<Node> n_3,
                 std::shared_ptr<Node> n_4,
                 Nip nip, std::shared_ptr<Material> mat)
    {
        m_l_node = {n_1, n_2, n_2, n_4};
        m_nip = static_cast<size_t>(nip);
        material = mat;
        VP_CORE_INFO("Quad4 created! with nip = {0}", m_nip);
        m_points = IntegrationPoints::IntPt(m_nip, DIM);
        MatrixXld der = ShapeDer(m_points[0], m_points[1]);
        VP_CORE_INFO("der = \n{0}", der);
        MatrixXld coord = Coord();
        MatrixXld jac = der * coord;
        VP_CORE_INFO("jac = \n{0}", jac);
        double det = jac.determinant();
        VP_CORE_INFO("det = \n{0}", det);
        jac = jac.inverse();
        MatrixXld deriv = jac * der;
        VP_CORE_INFO("deriv = \n{0}", deriv);
        MatrixXld bee = Element::BeeMat(deriv);
        VP_CORE_INFO("bee = \n{0}", bee);
        MatrixXld k = m_points[0].weight * m_points[1].weight * det * ((bee.transpose() * material->GetMatMatrix()) * bee);
        VP_CORE_INFO("k = \n{0}", k);
    }

    void Quad4::CreateIntegrationPoints()
    {

    }

    VectorXld Quad4::ShapeFun(GaussPointWeight xi, GaussPointWeight eta)
    {
        VectorXld fun(4);
        fun(0) = .25*(1 - xi.value) * (1 - eta.value);
        fun(1) = .25*(1 - xi.value) * (1 + eta.value);
        fun(2) = .25*(1 + xi.value) * (1 + eta.value);
        fun(3) = .25*(1 + xi.value) * (1 - eta.value);
        return fun;
    }

    MatrixXld Quad4::ShapeDer(GaussPointWeight xi, GaussPointWeight eta)
    {
        MatrixXld der(2,4);
        der(0,0) = 0.25 * (-1+eta.value);
        der(0,1) = 0.25 * (-1-eta.value);
        der(0,2) = 0.25 * (1+eta.value);
        der(0,3) = 0.25 * (1-eta.value);
        der(1,0) = 0.25 * (-1+xi.value);
        der(1,1) = 0.25 * (1-xi.value);
        der(1,2) = 0.25 * (1+xi.value);
        der(1,3) = 0.25 * (-1-xi.value);
        return der;
    }

    MatrixXld Quad4::Coord()
    {
        MatrixXld coord(4,2);
        coord(0,0) = 0.0;
        coord(1,0) = 0.0;
        coord(2,0) = 1.0;
        coord(3,0) = 1.0;
        coord(0,1) = 0.0;
        coord(1,1) = 1.0;
        coord(2,1) = 1.0;
        coord(3,1) = 0.0;
        return coord;
    }

}
