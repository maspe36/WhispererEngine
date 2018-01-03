//
// Created by Sam on 1/3/2018.
//

#include "../../../include/Game/Core/Taggable.h"
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

Taggable::Taggable()
        : tag(boost::uuids::to_string(boost::uuids::random_generator()()))
{
}

Taggable::~Taggable()
= default;
