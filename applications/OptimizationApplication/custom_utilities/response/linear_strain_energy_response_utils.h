//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:         BSD License
//                   license: OptimizationApplication/license.txt
//
//  Main author:     Reza Najian Asl,
//                   Suneth Warnakulasuriya
//

#pragma once

// System includes
#include <variant>
#include <vector>

// Project includes
#include "includes/define.h"
#include "includes/model_part.h"

// Application includes

namespace Kratos
{

///@name Kratos Classes
///@{

class KRATOS_API(OPTIMIZATION_APPLICATION) LinearStrainEnergyResponseUtils
{
public:
    ///@name Type definitions
    ///@{

    using IndexType = std::size_t;

    using GeometryType = ModelPart::ElementType::GeometryType;

    using GradientFieldVariableTypes = std::variant<const Variable<double>*, const Variable<array_1d<double, 3>>*>;

    ///@}
    ///@name Static operations
    ///@{

    static double CalculateValue(ModelPart& rEvaluatedModelPart);

    static void CalculateGradient(
        const std::vector<GradientFieldVariableTypes>& rListOfGradientVariables,
        const std::vector<ModelPart*>& rListOfGradientRequiredModelParts,
        const std::vector<ModelPart*>& rListOfGradientComputedModelParts,
        const double PerturbationSize);

    ///@}
private:
    ///@name Private static operations
    ///@{

    template<class TEntityType>
    static double CalculateEntityStrainEnergy(
        TEntityType& rEntity,
        Matrix& rLHS,
        Vector& rRHS,
        Vector& rX,
        const ProcessInfo& rProcessInfo);

    template<class TEntityType>
    static void CalculateStrainEnergyEntitySemiAnalyticShapeGradient(
        TEntityType& rEntity,
        Vector& rX,
        Vector& rRefRHS,
        Vector& rPerturbedRHS,
        typename TEntityType::Pointer& pThreadLocalEntity,
        ModelPart& rModelPart,
        std::vector<std::string>& rModelPartNames,
        const double Delta,
        const IndexType MaxNodeId,
        const Variable<array_1d<double, 3>>& rOutputGradientVariable);

    static void CalculateStrainEnergySemiAnalyticShapeGradient(
        ModelPart& rModelPart,
        const double Delta,
        const Variable<array_1d<double, 3>>& rOutputGradientVariable);

    static void CalculateStrainEnergyLinearlyDependentPropertyGradient(
        ModelPart& rModelPart,
        const Variable<double>& rPrimalVariable,
        const Variable<double>& rOutputGradientVariable);

    static void CalculateStrainEnergySemiAnalyticPropertyGradient(
        ModelPart& rModelPart,
        const double Delta,
        const Variable<double>& rPrimalVariable,
        const Variable<double>& rOutputGradientVariable);

    ///@}
};

///@}
}