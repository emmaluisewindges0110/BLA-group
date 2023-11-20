#ifndef FILE_EXPRESSION_H
#define FILE_EXPRESSION_H


namespace pep::bla
{

    template <typename T>
    class VecExpr {
    public:
        auto Upcast() const {
            return static_cast<const T&> (*this);
        }

        size_t Size() const {
            return Upcast().Size();
        }

        auto operator() (size_t i) const {
            return Upcast()(i);
        }
    };


    template <typename TA, typename TB>
    class SumVecExpr : public VecExpr<SumVecExpr<TA,TB>> {
        TA a_;
        TB b_;
    public:
        SumVecExpr (TA a, TB b) : a_(a), b_(b) {}

        auto operator() (size_t i) const {
            return a_(i) + b_(i);
        }

        size_t Size() const {
            return a_.Size();
        }
    };

    template <typename TA, typename TB>
    auto operator+ (const VecExpr<TA>& a, const VecExpr<TB>& b) {
        return SumVecExpr(a.Upcast(), b.Upcast());
    }

    template <typename TSCAL, typename TV>
    class ScaleVecExpr : public VecExpr<ScaleVecExpr<TSCAL,TV>> {
        TSCAL scal_;
        TV vec_;
    public:
        ScaleVecExpr (TSCAL scal, TV vec) : scal_(scal), vec_(vec) {}

        auto operator() (size_t i) const {
            return scal_*vec_(i);
        }

        size_t Size() const {
            return vec_.Size();
        }
    };

    template <typename T>
    auto operator* (double scal, const VecExpr<T>& v) {
        return ScaleVecExpr(scal, v.Upcast());
    }

    template <typename T>
    std::ostream& operator<< (std::ostream& ost, const VecExpr<T>& v) {
        if (v.Size() > 0) {
            ost << v(0);
        }
        for (size_t i = 1; i < v.Size(); i++) {
            ost << ", " << v(i);
        }
        return ost;
    }

    template <typename T>
    class MatrixExpr {
    public:
        auto Upcast() const {
            return static_cast<const T&> (*this);
        }

        size_t Rows() const {
            return Upcast().Rows();
        }

        size_t Cols() const {
            return Upcast().Cols();
        }

        auto operator() (size_t i, size_t j) const {
            return Upcast()(i, j);
        }
    };


    template <typename TA, typename TB>
    class SumMatrixExpr : public MatrixExpr<SumMatrixExpr<TA, TB>> {
        TA a_;
        TB b_;
    public:
        SumMatrixExpr (TA a, TB b) : a_(a), b_(b) {}

        auto operator() (size_t i, size_t j) const {
            return a_(i, j) + b_(i, j);
        }

        size_t Rows() const {
            return a_.Rows();
        }

        size_t Cols() const {
            return a_.Cols();
        }
    };

    template <typename TA, typename TB>
    auto operator+ (const MatrixExpr<TA>& a, const MatrixExpr<TB>& b) {
        return SumMatrixExpr(a.Upcast(), b.Upcast());
    }


    template <typename TA, typename TB>
    class MatrixMatrixProdExpr : public MatrixExpr<MatrixMatrixProdExpr<TA, TB>> {
        TA a_;
        TB b_;
    public:
        MatrixMatrixProdExpr (TA a, TB b) : a_(a), b_(b) {}

        auto operator() (size_t i, size_t j) const {
            auto row = a_.Row(i);
            auto col = b_.Col(j);

            auto sum = 0;
            for (int k = 0; k < a_.Cols(); ++k) {
                sum += row(k) * col(k);
            }
            return sum;
        }

        size_t Rows() const {
            return a_.Rows();
        }

        size_t Cols() const {
            return b_.Cols();
        }
    };

    template <typename TA, typename TB>
    auto operator* (const MatrixExpr<TA>& a, const MatrixExpr<TB>& b) {
        return MatrixMatrixProdExpr(a.Upcast(), b.Upcast());
    }


    template <typename TA, typename TB>
    class MatrixVectorProdExpr : public VecExpr<MatrixVectorProdExpr<TA, TB>> {
        TA a_;
        TB b_;
    public:
        MatrixVectorProdExpr (TA a, TB b) : a_(a), b_(b) {}

        auto operator() (size_t i) const {
            auto row = a_.Row(i);
            auto col = b_;

            auto sum = 0;
            for (int k = 0; k < a_.Cols(); ++k) {
                sum += row(k) * col(k);
            }
            return sum;
        }
        size_t Size() const {
            return a_.Rows();
        }
    };

    template <typename TA, typename TB>
    auto operator* (const MatrixExpr<TA>& a, const VecExpr<TB>& b) {
        return MatrixVectorProdExpr(a.Upcast(), b.Upcast());
    }

    // Output stream operator for easy printing
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const MatrixExpr<T>& matrix) {
        for (size_t i = 0; i < matrix.Rows(); ++i) {
            if (i > 0) {
                os << "\n";
            }
            for (size_t j = 0; j < matrix.Cols(); ++j) {
                if (j > 0) {
                    os << " ";
                }
                os << matrix(i, j);
            }
        }
        return os;
    }
}

#endif
