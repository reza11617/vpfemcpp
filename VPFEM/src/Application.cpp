#include "Application.hpp"

namespace VPFEM {
    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        typedef Eigen::Triplet<double> T;
        std::vector<T> tripletList;
        tripletList.reserve(2);
        Eigen::SparseVector<double> vec(2);
    }
}

www.csce.ca/apps/pdfs/Paper_ST165_0611020517
