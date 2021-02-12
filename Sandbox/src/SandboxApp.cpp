#include <VPFEM>
#include <vector>
class Sandbox : public VPFEM::Application
{
    private:
        double m_length;
        double m_stiffness;
        size_t m_num_ele;
    public:
        std::vector<VPFEM::Node> node;
    public:
        Sandbox(double length, double stiffness, size_t number_of_elements)
            :m_length(length), m_stiffness(stiffness), m_num_ele(number_of_elements)
        {
            // build model
            // VPFEM::Model::ModelBuilder(nDof, nDim);
            VPFEM::Model::ModelBuilder(2, 2);
            // create nodes
            // Node(x, y, z)
            for(size_t i = 0; i <= number_of_elements; i++)
                node.emplace_back((double) i * length/ (double) number_of_elements);
            // Boundary condition
            // Fix({dof_0, dof_1, dof_2, ...})
            node[0].Fix({1,1});
            // Load
            // PointLoad(dof, magnitude)
            VP_Trace("{0}, {1}",node[1].GetNodeNumber(), node[1].GetX());
        }
        ~Sandbox()
        {

        }
};

VPFEM::Application* VPFEM::CreateApplication()
{
    return new Sandbox(1.0, 1.0, 2);
}
