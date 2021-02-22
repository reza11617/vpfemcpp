#pragma once

#include "src/Core.hpp"

namespace VPFEM {
    class Material
    {
        private:
            size_t m_material_number = 0;
        protected:
            Material()
            {}
        public:
            inline void SetMaterialNumber(size_t num) {m_material_number = num;}
            virtual inline double GetStiffness() const = 0;
    };

    class UniaxialMaterial : public Material
    {
        protected:
        UniaxialMaterial()
        {}
    };

    class Elastic : public UniaxialMaterial
    {
        private:
            double m_stiffness;
        public:
            Elastic(double stiffness)
                : m_stiffness(stiffness)
            {}
            inline double GetStiffness() const override {return m_stiffness;}
    };
}
