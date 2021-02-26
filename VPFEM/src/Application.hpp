#pragma once

#include "Core.hpp"
#include "Log.hpp"
#include "FiniteElementModel.hpp"
#include "src/Analyze/Solver.hpp"

#include <future>

namespace VPFEM {
    class Application
    {
        public:
            Application();
            virtual ~Application();
            void Run();

            template<typename T, typename ... Ts>
            void PushFiniteElementModel(Ts ... args)
            {
                m_v_fem.emplace_back(std::make_shared<T>(args...));
                total_fem_number++;
                m_v_fem.back()->SetFiniteElementModelNumber(total_fem_number);
                FiniteElementModel::CreateRecorderFilePath(total_fem_number);
            }
        private:
            std::vector<std::future<VectorXld>> m_future;
            std::vector<std::shared_ptr<FiniteElementModel>> m_v_fem;
            size_t total_fem_number = 0;
    };

    // To be defined in CLIENT code
    Application* CreateApplication();
}
