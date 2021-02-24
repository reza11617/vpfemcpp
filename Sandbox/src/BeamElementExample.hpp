#include <VPFEM>



class BeamElementExample : public VPFEM::FiniteElementModel
{
    private:
        double m_length;
        double m_stiffness;
        double m_inertia = 1.0;
        double m_area = 1.0;
        size_t m_num_ele;
    public:
        BeamElementExample(double length, double stiffness, size_t number_of_elements)
            :m_length(length), m_stiffness(stiffness), m_num_ele(number_of_elements)
        {
            // build model
            // VPFEM::Model::ModelBuilder(nDof, nDim);
            ModelBuilder(3, 2);
            // create nodes
            // PushNode(x, y, z)
            for(size_t i = 0; i <= m_num_ele; i++)
                PushNode((double) i * length/ (double) number_of_elements, 0);
            // Boundary condition
            // Fix({dof_0, dof_1, dof_2, ...})
            node[0]->Fix({1,1,1});
            // Load
            // PointLoad(dof, magnitude)
            node[m_num_ele]->PointLoad(1, 10.0);
            // Define Material
            PushMaterial<VPFEM::Elastic>(m_stiffness);
            // Define Element
            // PushElement<ElementType>(args)
            for (size_t i = 0; i < m_num_ele; i++)
                PushElement<VPFEM::ElasticBeamColumnElement>(node[i], node[i+1], m_inertia, m_area,  material[0]);
            // Record mesh data on a file
            RecorderMesh();
            // Analyse
            analyze->SetTolarance(0.0000001);
            //VPFEM::Recorder::Print("disp.out",analyze->GetDeformation());
            //std::cout << analyze->Deformation(node[m_num_ele], 1) << std::endl;
        }

        ~BeamElementExample()
        {

        }
};
