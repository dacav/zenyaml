#include "datatypes.h"

#include <iostream> 
#include <cassert>

namespace yayaml
{

    struct ScalarStorage : Node::StorageT<std::string>
    {
        std::string string;

        ScalarStorage(const std::string& s)
            : Node::StorageT<std::string>(Node::StorageType::SCALAR)
            , string(s)
        { }

        std::string& get() override {
            return string;
        }
    };

    Node::Storage::Storage(StorageType t)
        : type(t)
    {
    }

    Node::Node(const std::string& scalar)
        : storage(new ScalarStorage(scalar))
    {
    }

    Node::operator const std::string&() const
    {
        switch (storage->type) {
            case Node::StorageType::SCALAR: {
                ScalarStorage& s = dynamic_cast<ScalarStorage&>(*storage.get());
                return s.get();
            }
            default:
                assert(false);
                return *this;
        }
    }

} // namespace yayaml
