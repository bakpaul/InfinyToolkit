/*****************************************************************************
 *            Copyright (C) - InfinyTech3D - All Rights Reserved             *
 *                                                                           *
 * Unauthorized copying of this file, via any medium is strictly prohibited  *
 * Proprietary and confidential.                                             *
 *                                                                           *
 * Written by Erik Pernod <erik.pernod@infinytech3d.com>, October 2019       *
 ****************************************************************************/
#pragma once

#include <InteractionTools/config.h>
#include <SofaHaptics/ForceFeedback.h>
#include <sofa/defaulttype/VecTypes.h>
#include <InteractionTools/AdvanceCarvingManager.h>

namespace sofa
{

namespace component
{

namespace controller
{


/// @brief Null force feedback for haptic feedback device
class SOFA_INTERACTIONTOOLS_API BruteForceFeedback : public sofa::component::controller::ForceFeedback
{
public:
    SOFA_CLASS(BruteForceFeedback,sofa::component::controller::ForceFeedback);
    void init() override;

    void computeForce(SReal x, SReal y, SReal z, SReal u, SReal v, SReal w, SReal q, SReal& fx, SReal& fy, SReal& fz) override;
    void computeWrench(const sofa::defaulttype::SolidTypes<SReal>::Transform &world_H_tool, const sofa::defaulttype::SolidTypes<SReal>::SpatialVector &V_tool_world, sofa::defaulttype::SolidTypes<SReal>::SpatialVector &W_tool_world ) override;

    void setCurrentForce(sofa::defaulttype::Vector3 _force) { currentForce = _force; }

    Data< double > forceCoef; ///< multiply haptic force by this coef.

protected:
    BruteForceFeedback();
protected:
    sofa::component::collision::AdvanceCarvingManager::SPtr m_ACarving;

    sofa::defaulttype::Vector3 currentForce;
};

} // namespace controller

} // namespace component

} // namespace sofa
