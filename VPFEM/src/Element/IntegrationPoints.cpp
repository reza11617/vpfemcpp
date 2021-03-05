#include "IntegrationPoints.hpp"

namespace VPFEM {
    GaussPointWeight::GaussPointWeight(long double value, long double weight)
        : value(value), weight(weight)
    {}

    GaussPointWeight::GaussPointWeight(const GaussPointWeight& other)
        : value(other.value), weight(other.weight)
    {}

    GaussPointWeight::GaussPointWeight(GaussPointWeight&& other)
        : value(other.value), weight(other.weight)
    {}

    // Utolity function used in the integraion point class
    size_t SumInteger(size_t i)
    {
        return (i*(i+1))/2;
    }

    size_t IntPow(size_t i, size_t j)
    {
        size_t result = i;
        for (size_t incr = 1; incr < j; incr++)
        {
            result *= i;
        }
        return result;
    }
    // CLASS IntegraionPoints
    IntegrationPoints& IntegrationPoints::Get()
    {
        static IntegrationPoints instance;
        return instance;
    }

    std::vector<GaussPointWeight> IntegrationPoints::IntPt(size_t nip, size_t dim)
    {
        return IntegrationPoints::Get().I_IntPt(nip, dim);
    }

    std::vector<GaussPointWeight> IntegrationPoints::I_IntPt(size_t nip, size_t dim)
    // This function takes nip and dim and return a vector of IntegraionPoints eg: {{xi}_1, {eta}_1, ...}
    {
        std::vector<GaussPointWeight> gp;
        if (dim == 1)
        {
            gp = I_IntPt(nip);
        }
        else
        {
            std::vector<GaussPointWeight> temp = I_IntPt(nip);
            gp.reserve(IntPow(nip, dim)*dim);
            for (size_t i = 0; i < IntPow(nip,dim) ; i++)
            {
                for (size_t k = 0; k < dim; k++)
                {
                    size_t index = ((2-k)/2)*(1-k)*(i%nip) + (k)*(2-k)*(i/(nip))%(nip) + (k/2)*(k-1)*(i/(nip*nip));
                    gp.push_back(temp[index]);
                }
            }
        }
        return gp;
    }

    std::vector<GaussPointWeight> IntegrationPoints::I_IntPt(size_t nip)
    {
        auto first = m_v_ga_pt_wt.begin() + SumInteger(nip-1);
        auto last  = first + nip ;
        std::vector<GaussPointWeight> new_vec(first, last);
        return new_vec;
    }

    IntegrationPoints::IntegrationPoints()
    {
        size_t size = SumInteger(MAX_INTEGRATION_POINT);
        m_v_ga_pt_wt.reserve(size);
        One();
        Two();
        Three();
        Four();
        Five();
    };

    void IntegrationPoints::One()
    {
        m_v_ga_pt_wt.emplace_back(0.0, 2.0);
    }
    void IntegrationPoints::Two()
    {
        const long double p_1 = 1.0/sqrt(3.);
        m_v_ga_pt_wt.emplace_back(-p_1, 1.0);
        m_v_ga_pt_wt.emplace_back(p_1, 1.0);

    }
    void IntegrationPoints::Three()
    {
        const long double p_1 = sqrt(3./5.);
        const long double w_1 = 5.0/9.0;
        const long double w_2 = 8.0/9.0;
        m_v_ga_pt_wt.emplace_back(-p_1, w_1);
        m_v_ga_pt_wt.emplace_back(0., w_2);
        m_v_ga_pt_wt.emplace_back(p_1, w_1);
    }
    void IntegrationPoints::Four()
    {
        const long double p_1 = sqrt((3./7.) - (2./7.) * sqrt(6./5.));
        const long double w_1 = (18.+sqrt(30.0))/36.;
        const long double p_2 = sqrt((3./7.) + (2./7.) * sqrt(6./5.));
        const long double w_2 = (18.-sqrt(30.0))/36.;
        m_v_ga_pt_wt.emplace_back(-p_2, w_2);
        m_v_ga_pt_wt.emplace_back(-p_1, w_1);
        m_v_ga_pt_wt.emplace_back(p_1, w_1);
        m_v_ga_pt_wt.emplace_back(p_2, w_2);
    }
    void IntegrationPoints::Five()
    {
        const long double p_1 = (1./3.) * sqrt(5. - 2. * sqrt(10./7.));
        const long double w_1 = (322. + 13. * sqrt(70.)) / 900.;
        const long double p_2 = (1./3.) * sqrt(5. + 2. * sqrt(10./7.));
        const long double w_2 = (322. - 13. * sqrt(70.)) / 900.;
        m_v_ga_pt_wt.emplace_back(-p_2, w_2);
        m_v_ga_pt_wt.emplace_back(-p_1, w_1);
        m_v_ga_pt_wt.emplace_back(0., (128./225.));
        m_v_ga_pt_wt.emplace_back(p_1, w_1);
        m_v_ga_pt_wt.emplace_back(p_2, w_2);
    }
}
