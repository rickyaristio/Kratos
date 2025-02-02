//    |  /           |
//    ' /   __| _` | __|  _ \   __|
//    . \  |   (   | |   (   |\__ `
//   _|\_\_|  \__,_|\__|\___/ ____/
//                   Multi-Physics
//
//  License:         BSD License
//                   Kratos default license: kratos/license.txt
//
//  Main authors:    Suneth Warnakulasuriya
//

#pragma once

// System includes
#include <cmath>
#include <string>
#include <vector>

// Project includes
#include "containers/container_expression/expressions/expression.h"

namespace Kratos {

///@name Kratos Classes
///@{

namespace BinaryOperations
{
    struct Addition       { static inline constexpr double Evaluate(const double V1, const double V2) { return V1 + V2; } };
    struct Substraction   { static inline constexpr double Evaluate(const double V1, const double V2) { return V1 - V2; } };
    struct Multiplication { static inline constexpr double Evaluate(const double V1, const double V2) { return V1 * V2; } };
    struct Division       { static inline constexpr double Evaluate(const double V1, const double V2) { return V1 / V2; } };
    struct Power          { static inline           double Evaluate(const double V1, const double V2) { return std::pow(V1, V2); } };
}


template <class TOperationType>
class KRATOS_API(KRATOS_CORE) BinaryExpression : public Expression {
public:
    ///@name Type definitions
    ///@{

    using IndexType = std::size_t;

    ///@}
    ///@name Life cycle
    ///@{

    BinaryExpression(
        Expression::Pointer pLeft,
        Expression::Pointer pRight);

    ///@}
    ///@name Public operations
    ///@{

    static Expression::Pointer Create(
        Expression::Pointer pLeft,
        Expression::Pointer pRight);

    double Evaluate(
        const IndexType EntityIndex,
        const IndexType EntityDataBeginIndex,
        const IndexType ComponentIndex) const override;

    const std::vector<IndexType> GetShape() const override;

    std::string Info() const override;

    ///@}
protected:
    ///@name Private member variables
    ///@{

    const Expression::Pointer mpLeft;

    const Expression::Pointer mpRight;

    ///@}
};

} // namespace Kratos