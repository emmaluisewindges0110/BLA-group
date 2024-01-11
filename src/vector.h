#ifndef FILE_VECTOR_H
#define FILE_VECTOR_H

#include <initializer_list>
#include <iostream>

#include "expression.h"

namespace pep::bla {

    template <typename T, typename TDIST = std::integral_constant<size_t,1> >
    class VectorView : public VecExpr<VectorView<T,TDIST>> {
    protected:
        T* data_;
        size_t size_;
        TDIST dist_;
    public:
        VectorView (size_t size, T * data) : data_(data), size_(size) {}

        VectorView (size_t size, TDIST dist, T * data) : data_(data), size_(size), dist_(dist) {}

        template <typename TB>
        VectorView& operator= (const VecExpr<TB>& v2) {
            for (size_t i = 0; i < size_; i++) {
                data_[dist_*i] = v2(i);
            }
            return *this;
        }

        VectorView& operator= (const VectorView& other) {
            for (size_t i = 0; i < size_; i++) {
                data_[dist_*i] = other(i);
            }
            return *this;
        }

        VectorView& operator= (T scal) {
            for (size_t i = 0; i < size_; i++) {
                data_[dist_*i] = scal;
            }
            return *this;
        }

        auto View() const {
            return VectorView(size_, dist_, data_);
        }

        size_t Size() const {
            return size_;
        }

        auto Dist() const {
            return dist_;
        }

        auto Data() {
            return data_;
        }

        T& operator()(size_t i) {
            return data_[dist_*i];
        }

        const T& operator()(size_t i) const {
            return data_[dist_*i];
        }

        auto Range(size_t first, size_t next) const {
            return VectorView(next-first, dist_, data_+first*dist_);
        }

        auto Slice(size_t first, size_t slice) const {
            return VectorView<T,size_t> (size_/slice, dist_*slice, data_+first*dist_);
        }

        VectorView& operator*=(const T value){
            for (size_t i = 0; i < size_; i++) {
                data_[dist_*i] *= value;
            }
            return *this;
        }

        VectorView& operator/=(const T value){
            for (size_t i = 0; i < size_; i++) {
                data_[dist_*i] /= value;
            }
            return *this;
        }

        template <typename TB>
        VectorView& operator+= (const VecExpr<TB>& v2) {
            for (size_t i = 0; i < size_; i++) {
                data_[dist_*i] += v2(i);
            }
            return *this;
        }

        template <typename TB>
        VectorView& operator-= (const VecExpr<TB>& v2) {
            for (size_t i = 0; i < size_; i++) {
                data_[dist_*i] -= v2(i);
            }
            return *this;
        }
    };

    template <typename T>
    class Vector : public VectorView<T> {
        typedef VectorView<T> BASE;
        using BASE::size_;
        using BASE::data_;
    public:
        Vector (size_t size) : VectorView<T> (size, new T[size]) {}

        Vector (const Vector& v) : Vector(v.Size()) {
            *this = v;
        }

        Vector (Vector&& v) : VectorView<T> (0, nullptr) {
            std::swap(size_, v.size_);
            std::swap(data_, v.data_);
        }

        template <typename TB>
        Vector (const VecExpr<TB>& v) : Vector(v.Size()) {
            *this = v;
        }

        Vector(std::initializer_list<T> list) : VectorView<T>(list.size(), new T[list.size()]) {
            size_t cnt = 0;
            for (auto val : list) {
                data_[cnt++] = val;
            }
        }

        ~Vector () { delete [] data_; }

        using BASE::operator=;
        Vector& operator=(const Vector& v2) {
            for (size_t i = 0; i < size_; i++) {
                data_[i] = v2(i);
            }
            return *this;
        }

        Vector& operator= (Vector&& v2) {
            for (size_t i = 0; i < size_; i++) {
                data_[i] = v2(i);
            }
            return *this;
        }
    };


    template <size_t T_SIZE, typename T = double>
    class Vec : public VecExpr<Vec<T_SIZE, T>> {
    protected:
        T data_[T_SIZE];
    public:
        Vec() = default;

        Vec(const Vec& v) {
            for (size_t i = 0; i < T_SIZE; ++i) {
                data_[i] = v(i);
            }
        }

        Vec(Vec&& v) {
            for (size_t i = 0; i < T_SIZE; ++i) {
                data_[i] = v(i);
            }
        }

        template <typename TB>
        Vec(const VectorView<TB>& v) {
            for (size_t i = 0; i < T_SIZE; ++i) {
                data_[i] = v(i);
            }
        }

        template <typename TB>
        Vec(const VecExpr<TB>& v) {
            for (size_t i = 0; i < T_SIZE; ++i) {
                data_[i] = v(i);
            }
        }

        Vec(std::initializer_list<T> list) {
            for (size_t i = 0; i < list.size(); ++i) {
                data_[i] = list.begin()[i];
            }
        }

        Vec(T scal) {
            for (size_t i = 0; i < T_SIZE; ++i) {
                data_[i] = scal;
            }
        }

        template <typename TB>
        Vec& operator= (const VecExpr<TB>& other) {
            for (size_t i = 0; i < T_SIZE; i++) {
                data_[i] = other(i);
            }
            return *this;
        }

        Vec& operator= (const Vec& other) {
            for (size_t i = 0; i < T_SIZE; i++) {
                data_[i] = other(i);
            }
            return *this;
        }

        Vec& operator= (T scal) {
            for (size_t i = 0; i < T_SIZE; i++) {
                data_[i] = scal;
            }
            return *this;
        }

        T& operator()(size_t i) {
            return data_[i];
        }

        const T& operator()(size_t i) const {
            return data_[i];
        }

        auto Upcast() const {
            return *this;
        }

        size_t Size() const {
            return T_SIZE;
        }
    };


    template <typename ...Args>
    std::ostream& operator<< (std::ostream& ost, const VectorView<Args...>& v) {
        if (v.Size() > 0) {
            ost << v(0);
        }
        for (size_t i = 1; i < v.Size(); i++) {
            ost << ", " << v(i);
        }
        return ost;
    }


    template <size_t T_SIZE, typename T>
    std::ostream& operator<< (std::ostream& ost, const Vec<T_SIZE, T>& vec) {
        if constexpr (T_SIZE > 0) {
            ost << vec(0);
        }
        for (size_t i = 1; i < T_SIZE; i++) {
            ost << ", " << vec(i);
        }
        return ost;
    }
}

#endif
