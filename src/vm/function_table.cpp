#include "vm/function_table.h"
#include "vm/variable_table.h"

#include "ast/value/signed_int_value.h"
#include "vm/function_table.h"

#include <iostream>

namespace apus {

    // Function class

    Function::Function() {
    }

    Function::Function(const std::string& name) {
        name_ = name;
        return_type_ = nullptr;
    }

    Function::Function(const std::string& name, DataTypePtr return_type) {
        name_ = name;
        return_type_ = return_type;
    }

    Function::Function(const std::string& name, DataTypePtr return_type, list<VariablePtr> arg_list) {
        name_ = name;
        return_type_ = return_type;
        arg_list_ = arg_list;
    }

    Function::~Function() {
    }

    // FunctionTable class

    FunctionTable::FunctionTable() {

    }
    void FunctionTable::Insert(std::string name,
                               std::shared_ptr<Function> function) {
        map_[name] = function;
    }

    std::shared_ptr<Function> FunctionTable::Find(std::string& name) {
        FunctionMap::iterator it = map_.find(name);

        if(it != map_.end()) {
            return it->second;
        }
        return nullptr;
    }

    // Built-in Function

    PrintS64::PrintS64(Context& context) {
        name_ = "printS64";
        return_type_ = context.GetDataTypeTable()->Find(std::string("S64"));

        VariablePtr arg =
                std::make_shared<Variable>(
                        std::string("val"),
                        context.GetDataTypeTable()->Find(S64)
                );

        arg_list_.push_back(arg);
    }

    PrintS64::~PrintS64() {
    }

    std::shared_ptr<Value> PrintS64::Execute(Context & context) {

        VariablePtr var = context.FindVariable("val");

        if (var) {
            ValuePtr value = var->GetValue();

            int64_t int_val = std::dynamic_pointer_cast<SignedIntValue>(value)->getIntValue();
            cout << "[PrintS64]" << int_val << endl;

            return value;
        }

        return nullptr;
    }

}
