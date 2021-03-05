#pragma once

#include "src/Core.hpp"

namespace VPFEM {
    struct GaussPointWeight
    {
        long double value;
        long double weight;
        GaussPointWeight(long double value, long double weight);
        GaussPointWeight(const GaussPointWeight& other);
        GaussPointWeight(GaussPointWeight&& other);
    };

    class IntegrationPoints
    {
        public:
            static const size_t MAX_INTEGRATION_POINT = 5;
            IntegrationPoints(const IntegrationPoints&) = delete;

            static IntegrationPoints& Get();
            static std::vector<GaussPointWeight> IntPt(size_t nip, size_t dim);
        private:
            std::vector<GaussPointWeight> m_v_ga_pt_wt;
        private:
            IntegrationPoints();
            std::vector<GaussPointWeight> I_IntPt(size_t nip, size_t dim);
            std::vector<GaussPointWeight> I_IntPt(size_t nip);
            void One();
            void Two();
            void Three();
            void Four();
            void Five();
    };
}
