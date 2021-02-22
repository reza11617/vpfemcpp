#include "Result.hpp"

namespace VPFEM {
    double Result::Deformation(std::shared_ptr<Node> node, size_t dof)
    // This function takes node number and the dof in that node and returns the deformation of the dof
    {
        return m_deformation(node->Local2Global(dof));
    }
}
