#pragma once

#include "Core.hpp"

namespace VPFEM {
    class Recorder
    {
        public:
            Recorder(const Recorder&) = delete;
            static Recorder& Get()
            {
                static Recorder recorder;
                return recorder;
            }
            template<typename T>
            static void Print(const std::string& file_name, std::vector<T> v)
            {
                // TODO this class is a very bad impelementation of recorder fix this try to make it binary
                std::ofstream file(file_name);
                v[0]->WriteHeader(file); file << "\n";
                for (auto& i : v)
                {
                    i->Write(file);
                    file << "\n";
                }
                file.close();
            }

            static void Print(const std::string& file_name, VectorXld& v)
            {
                std::ofstream file(file_name);
                file << v;
                file.close();
            }

        private:
            Recorder();
    };
}
