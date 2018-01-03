//
// Created by Sam on 1/3/2018.
//

#include "../../../include/Game/Core/Exportable.h"
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

Exportable::Exportable()
        : tag(boost::uuids::to_string(boost::uuids::random_generator()()))
{
}

Exportable::~Exportable()
= default;
