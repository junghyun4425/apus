#ifndef FUNCTION_TABLE_H_
#define FUNCTION_TABLE_H_

#include <memory>
#include <string>
#include <map>
#include <list>
#include "vm/data_type_table.h"

#include "ast/value/signed_int_value.h"

namespace apus {

    class DataType;
    class Function;

    typedef std::shared_ptr<Function> FunctionPtr;
    typedef std::shared_ptr<DataType> DataTypePtr;
    typedef std::map<std::string, FunctionPtr> FunctionMap;

    class Function {
    public:
        Function();
        Function(const std::string& name);
        Function(const std::string& name, DataTypePtr return_type);
        Function(const std::string& name, DataTypePtr return_type, list<DataTypePtr> arg_list);
        virtual ~Function();

        virtual std::shared_ptr<Value> Execute() = 0;

    protected:
        std::string name_;
        DataTypePtr return_type_;
        list<DataTypePtr> arg_list_;
    };

    class FunctionTable {
    public:
        FunctionTable(std::shared_ptr<FunctionTable> parent);

        void Insert(std::string name, FunctionPtr function);
        FunctionPtr Find(std::string& name);

        inline std::shared_ptr<FunctionTable> GetParent() { return parent_; }

    private:
        FunctionMap map_;
        std::shared_ptr<FunctionTable> parent_;
    };

}

#endif
