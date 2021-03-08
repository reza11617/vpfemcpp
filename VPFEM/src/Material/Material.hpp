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
            virtual ~Material () {}
            inline void SetMaterialNumber(size_t num) {m_material_number = num;}
            virtual double GetStiffness() const = 0;
            virtual MatrixXld GetMatMatrix() const = 0;
    };

    class UniaxialMaterial : public Material
    {
        public:
            virtual MatrixXld GetMatMatrix() const override {return MatrixXld(0,0);}
        protected:
            UniaxialMaterial() {}
            virtual ~UniaxialMaterial() {}

    };

    class Elastic : public UniaxialMaterial
    {
        private:
            double m_stiffness;
        public:
            Elastic(double stiffness)
                : m_stiffness(stiffness)
            {}
            double GetStiffness() const override {return m_stiffness;}
    };

    class NDMaterial : public Material
    {
        protected:
            NDMaterial() {}
        public:
            virtual double GetStiffness() const override {return 0.0;}
            virtual ~NDMaterial() {}
    };

    class ElasticPlainStress : public NDMaterial
    {
        public:
            ElasticPlainStress(long double stiffness, long double nu)
                : m_stiffness(stiffness), m_nu(nu)
            {}
            MatrixXld GetMatMatrix() const override
            {
                // TODO fix this it should be dependent to the dimentions
                MatrixXld D(3,3);
                long double coeff = m_stiffness / (1.0 - (m_nu*m_nu));
                D(0,0) = coeff * 1.0;
                D(0,1) = coeff * m_nu;
                D(0,2) = coeff * 0.0;
                D(1,0) = coeff * m_nu;
                D(1,1) = coeff * 1.0;
                D(1,2) = coeff * 0.0;
                D(2,0) = coeff * 0.0;
                D(2,1) = coeff * 0.0;
                D(2,2) = coeff * (1.0 - m_nu) / 2.0;
                return D;
            }
        private:
            long double m_stiffness;
            long double m_nu;
    };
}
