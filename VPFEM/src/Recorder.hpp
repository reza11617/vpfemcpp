#pragma once

#include "Core.hpp"
#include "src/Geometry/Node.hpp"
#include "src/Element/Element.hpp"
#include "src/Analyze/Result.hpp"

namespace VPFEM {
    const static Eigen::IOFormat CSVFormat(Eigen::FullPrecision, Eigen::DontAlignCols, "", ",", "", "", "", ",");
    class Recorder
    {
        public:
            Recorder(const std::string& file_name)
                : m_file_name(file_name)
            {
            }

            void StartRecording(const std::string& file_path)
            {

                std::filesystem::create_directories(file_path);
                m_file_path_name = file_path + "/" + m_file_name;
                m_file.open(m_file_path_name);
            }

            virtual ~Recorder()
            {
                m_file.close();
            }

            virtual void Print(std::shared_ptr<Result> result) = 0;
        protected:
            inline std::ofstream& GetFile() {return m_file;}
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
                        VP_CORE_ERROR("Recorder could not open results file '{0}'.", m_file_path_name);
                    }
                }
            }
        private:
            const std::string m_file_name;
            std::string m_file_path_name;
            std::ofstream m_file;
    };


    template<typename T>
    class Printer : public Recorder
    {
        public:
            Printer(const std::string& file_name,
                    VectorXld (* func) (std::shared_ptr<T>, std::shared_ptr<Result>),
                    const std::initializer_list<std::shared_ptr<T>> print_list)
                : Recorder(file_name), m_func(func), m_print_list(print_list.begin(), print_list.end())
            {

            }
            void Print(std::shared_ptr<Result> result) override
            {
                for (auto type : m_print_list)
                {
                    VectorXld v = m_func(type, result);
                    Recorder::Print(v);
                }
                GetFile() << "\n";
            }
        private:
            VectorXld (* m_func) (std::shared_ptr<T>, std::shared_ptr<Result>);
            std::vector<std::shared_ptr<T>> m_print_list;
    };
}
