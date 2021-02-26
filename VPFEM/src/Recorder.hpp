#pragma once

#include "Core.hpp"
#include "src/Analyze/Result.hpp"
#include <filesystem>

namespace VPFEM {
    const static Eigen::IOFormat CSVFormat(Eigen::FullPrecision, Eigen::DontAlignCols, "", ",", "", "", "", "\n");
    template <typename T, typename T2>
    class Recorder
    {
        public:

            Recorder(const std::string& file_name, size_t fem_number, T* function, std::shared_ptr<T2> node, std::shared_ptr<Result> results)
                : m_file_name(file_name), m_fem_number(fem_number), m_function(function), m_node(node), m_results(results)
            {
                std::string file_path = "results/model_" + std::to_string(m_fem_number);
                m_file_name = file_path + "/" + m_file_name;
                m_file.open(m_file_name);

            }
            void Print()
            {
                VectorXld v = m_function(m_node, m_results);
                Print(v);
            }

            void Print(VectorXld& vector)
            {
                if (m_file.is_open())
                {
                    m_file << vector.format(CSVFormat);
                }
                else
                {
                    if (Log::GetCoreLogger())
                    {
                        VP_CORE_ERROR("Recorder could not open results file '{0}'.", m_file_name);
                    }
                }
            }
            ~Recorder()
            {
                m_file.close();
            }
        private:
            std::string m_file_name;
            size_t m_fem_number;
            T* m_function;
            std::shared_ptr<Node> m_node;
            std::shared_ptr<Result> m_results;
            std::ofstream m_file;
    };
}
