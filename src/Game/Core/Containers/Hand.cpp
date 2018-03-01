//
// Created by Sam on 3/1/2018.
//

#include "../../../../include/Game/Core/Containers/Hand.h"

json Hand::getJSON()
{
    return Exportable::getJSON();
}

Hand::Hand(std::vector<std::shared_ptr<Card>> cards)
{

}

Hand::~Hand()
= default;
