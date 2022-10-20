#pragma once

#include <memory>

#include "type.h"

namespace model {

std::unique_ptr<Type> CreateType(TypeId const type_id, bool const is_null_eq_null);

}  // namespace model
