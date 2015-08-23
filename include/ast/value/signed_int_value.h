#ifndef SIGNED_INT_VALUE_H_
#define SIGNED_INT_VALUE_H_

#include <memory>
#include "value.h"
#include "common/common.h"

namespace apus {

    class SignedIntValue : public Value {
    public:

        static std::shared_ptr<SignedIntValue> Create(TypeSpecifier type, int64_t value);

        virtual ~SignedIntValue() {}

        virtual ValuePtr Copy() const override {
            return SignedIntValue::Create(type_, getIntValue());
        }

        virtual ValuePtr Promote(const ValuePtr another) const override;

        virtual ValuePtr OperateBinary(
                const Expression::Type expression_type,
                const ValuePtr& right) const override;

        virtual ValuePtr OperateUnary(
                const Expression::Type expression_type) const override;

        inline int64_t getIntValue() const {
            return *((int64_t *)value_.get());
        }

    protected:

        SignedIntValue(TypeSpecifier type, int64_t value)
                : Value(type, std::make_shared<int64_t>(value)) {
        }

        SignedIntValue(TypeSpecifier type, std::shared_ptr<void> value_ptr)
                : Value(type, value_ptr) {
        }

    };

}

#endif
