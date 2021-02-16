#include <VPFEM>

class BeamElementExample : public VPFEM::FiniteElementModel
{
    private:
        double m_length;
        double m_stiffness;
        size_t m_num_ele;
    public:
        BeamElementExample(double length, double stiffness, size_t number_of_elements)
            :m_length(length), m_stiffness(stiffness), m_num_ele(number_of_elements)
        {
            // build model
            // VPFEM::Model::ModelBuilder(nDof, nDim);
            ModelBuilder(2, 2);
            // create nodes
            // PushNode(x, y, z)
            for(size_t i = 0; i <= m_num_ele; i++)
                PushNode((double) i * length/ (double) number_of_elements);
            // Boundary condition
            // Fix({dof_0, dof_1, dof_2, ...})
            node[0]->Fix({1,1});
            // Load
            // PointLoad(dof, magnitude)
            node[m_num_ele]->PointLoad(0, 10.0);
            for (auto& n : node)
                VP_TRACE("{0}", *n);
            // Define Element
            // PushElement<ElementType>(args)
            for (size_t i = 0; i < m_num_ele; i++)
                PushElement<VPFEM::BeamElement>(node[i], node[i+1], m_stiffness);
            for (auto& n : element)
                VP_TRACE("{0}", *n);
            // Analyse
            analyze->SetTolarance(0.0001);
            Run();

        }

        ~BeamElementExample()
        {

        }
};
