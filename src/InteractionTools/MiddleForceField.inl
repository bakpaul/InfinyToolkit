/******************************************************************************
*                 SOFA, Simulation Open-Framework Architecture                *
*                    (c) 2006 INRIA, USTL, UJF, CNRS, MGH                     *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#ifndef SOFA_COMPONENT_FORCEFIELD_MiddleForceField_INL
#define SOFA_COMPONENT_FORCEFIELD_MiddleForceField_INL

#include <InteractionTools/MiddleForceField.h>
#include <sofa/helper/vector.h>
#include <sofa/defaulttype/VecTypes.h>
#include <sofa/defaulttype/RigidTypes.h>
#include <sofa/defaulttype/BaseVector.h>

#include <SofaBaseTopology/TopologySubsetData.inl>

namespace sofa
{

namespace component
{

namespace forcefield
{

template<class DataTypes>
MiddleForceField<DataTypes>::MiddleForceField()
    : d_force(initData(&d_force, (Real)1.0, "force", "applied force to all points"))
    , d_pace(initData(&d_pace, (Real)1.0, "pace", "applied force to all points"))
{ 

}


template<class DataTypes>
void MiddleForceField<DataTypes>::doInit()
{
    core::behavior::BaseMechanicalState* state = this->getContext()->getMechanicalState();
    m_bary = Coord(0.0, 0.0, 0.0);

    if (state == nullptr || state->getSize() == 0)
    {
        msg_warning() << "Wrong BaseMechanicalState pointer or buffer size";
        return;
    }

    size_t nbPoints = state->getSize();
    for (size_t i = 0; i < nbPoints; ++i)
    {
        m_bary[0] += state->getPX(i);
        m_bary[1] += state->getPY(i);
        m_bary[2] += state->getPZ(i);
    }

    m_bary /= nbPoints;
}

template<class DataTypes>
void MiddleForceField<DataTypes>::addForce(const core::MechanicalParams* /*mparams*/, DataVecDeriv& f1, const DataVecCoord& p1, const DataVecDeriv&)
{
    sofa::helper::WriteAccessor< core::objectmodel::Data< VecDeriv > > _f1 = f1;
    sofa::helper::ReadAccessor< core::objectmodel::Data< VecCoord > > _p1 = p1;

    Real cT = this->getContext()->getTime();
    
    const Real& pace = d_pace.getValue();
    Real pacePercent = fmod (cT, pace) / pace;
    
    Real factor = 0;
    if (pacePercent < 0.5)
        factor = pacePercent * 2;
    else
        factor = 2 - (pacePercent * 2);

    Real factorForce = d_force.getValue()*factor;

    for (size_t i = 0; i < _p1.size(); ++i)
    {
        Coord dir = m_bary - _p1[i];
        _f1[i] += factorForce * dir;
    }
}

template<class DataTypes>
void MiddleForceField<DataTypes>::addDForce(const core::MechanicalParams* mparams, DataVecDeriv& /* d_df */, const DataVecDeriv& /* d_dx */)
{
    //TODO: remove this line (avoid warning message) ...
    //mparams->setKFactorUsed(true);
}

template<class DataTypes>
void MiddleForceField<DataTypes>::addKToMatrix(defaulttype::BaseMatrix* matrix, SReal kFact, unsigned int& offset)
{
    SOFA_UNUSED(matrix);
    SOFA_UNUSED(kFact);
    SOFA_UNUSED(offset);
}

template<class DataTypes>
SReal MiddleForceField<DataTypes>::getPotentialEnergy(const core::MechanicalParams* /*mparams*/, const DataVecCoord& x) const
{
    SReal e = 0;

    return e;
}


} // namespace forcefield

} // namespace component

} // namespace sofa

#endif // SOFA_COMPONENT_FORCEFIELD_MiddleForceField_INL