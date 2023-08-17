#ifndef EXPR_TMPL_HPP
#define EXPR_TMPL_HPP

#include <cstddef>  // size_t

//
// For simplicity, all members are public.
//

/// @brief All Expressions must inherit this.
/// @tparam SubType The actual expression type.
template <class SubType>
struct Expr {
  constexpr const SubType& Self() const noexcept {
    return static_cast<const SubType&>(*this);
  }
};

template <class LhsType, class RhsType>
struct BinaryAddExpr : public Expr<BinaryAddExpr<LhsType, RhsType>> {
  const LhsType& lhs;
  const RhsType& rhs;

  BinaryAddExpr(const LhsType& lhs, const RhsType& rhs) noexcept
      : lhs{lhs}, rhs{rhs} {}

  /// @note Expressions are evaluated lazily on references.
  float operator[](std::size_t i) const { return Evaluate(i); }

  /// @brief Evaluates the expression at position `i`.
  float Evaluate(std::size_t i) const noexcept {
    return lhs.Evaluate(i) + rhs.Evaluate(i);
  }
};

template <class LhsType, class RhsType>
inline BinaryAddExpr<LhsType, RhsType> operator+(const Expr<LhsType>& lhs,
                                                 const Expr<RhsType>& rhs) {
  return {lhs.Self(), rhs.Self()};
}

struct Vec : public Expr<Vec> {
  std::size_t len;
  float* elements;

  Vec() = default;
  Vec(float* elements, std::size_t len) noexcept
      : elements{elements}, len{len} {}

  /// @note Expressions are evaluated lazily on assignments.
  template <class ExprType>
  Vec& operator=(const Expr<ExprType>& src) {
    for (std::size_t i = 0; i < len; ++i) {
      elements[i] = src.Self().Evaluate(i);
    }
    return *this;
  }

  float operator[](std::size_t i) const { return Evaluate(i); }

  float Evaluate(std::size_t i) const noexcept { return elements[i]; }
};

#endif
