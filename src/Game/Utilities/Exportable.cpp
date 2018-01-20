//
// Created by Sam on 1/19/2018.
//

#include "../../../include/Game/Utilities/Exportable.h"
#include "include/rapidjson/writer.h"

void Exportable::buildJSON()
{
}

std::string Exportable::exportJSON()
{
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);

    return buffer.GetString();
}

Exportable::Exportable()
{
    document.SetObject();
}

Value Exportable::getValue(std::string& data)
{
    auto& allocator = document.GetAllocator();

    Value val(kObjectType);
    val.SetString(data.c_str(), static_cast<SizeType>(data.length()), allocator);
    return val;
}

Exportable::~Exportable()
= default;
