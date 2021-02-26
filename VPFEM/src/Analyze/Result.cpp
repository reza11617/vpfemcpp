#include "Result.hpp"

namespace VPFEM {
    VectorXld Result::Deformation(std::shared_ptr<Node> node, std::shared_ptr<Result> results)
    // This function takes node number and the dof in that node and returns the deformation of the dof
    {
        size_t total_dof = node->GetModel()->GetNumberDofs();
        VectorXld def(total_dof);
        for (size_t i = 0; i < total_dof; i++)
            def(i) = results->GetDeformation()[node->Local2Global(i)];
        return def;
    }
}
