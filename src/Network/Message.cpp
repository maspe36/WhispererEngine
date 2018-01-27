//
// Created by Sam on 1/15/2018.
//

#include "../../include/Network/Message.h"
#include <include/rapidjson/stringbuffer.h>
#include <include/rapidjson/writer.h>
#include <utility>


std::string Message::getMember(std::string key)
{
    std::string message = getValue(false, std::move(key));

    return message;
}

std::string Message::getDataMember(std::string key)
{
    std::string message = getValue(true, std::move(key));

    return message;
}

void Message::loadJSON(std::string json)
{
    document.Parse(json.c_str());
}

void Message::addMember(std::string key, std::string value)
{
    auto& allocator = document.GetAllocator();

    Value valKey(key.c_str(), allocator);
    Value valVal(value.c_str(), allocator);

    document.AddMember(valKey.Move(),
                       valVal.Move(),
                       allocator);
}

void Message::addDataMember(std::string key, std::string value)
{
    auto& allocator = document.GetAllocator();

    Value valKey(key.c_str(), allocator);
    Value valVal(value.c_str(), allocator);

    document[dataKey.c_str()].AddMember(valKey.Move(),
                                        valVal.Move(),
                                        allocator);
}

std::string Message::getJSON()
{
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);

    return buffer.GetString();
}

Message::Message(std::string type)
        : typeKey("type"), dataKey("data")
{
    document.SetObject();

    addMember(typeKey, std::move(type));
    initializeData();
}

Message::Message()
{
    document.SetObject();
    initializeData();
}

Message::~Message()
= default;

void Message::initializeData()
{
    auto& allocator = document.GetAllocator();

    Value data;
    data.SetObject();

    Value valKey(dataKey.c_str(), allocator);

    document.AddMember(valKey, data, allocator);
}

std::string Message::getValue(bool isData, std::string key)
{
    Value* doc;
    if (isData)
    {
        // For some reason using dataKey.c_str() when loading
        // the document from parsed JSON causes it to error out
        doc = &document["data"];
    }
    else
    {
        doc = &document;
    }

    std::string member;

    Value::ConstMemberIterator itr = doc->FindMember(key.c_str());

    if (itr != doc->MemberEnd())
    {
        member = itr->value.GetString();

        if (member.empty())
        {
            throw std::invalid_argument("The key '" + key + "' exists but the value is empty");
        }
    }

    if (member.empty())
    {
        throw std::invalid_argument("The key '" + key + "' doesn't exist on the JSON document");
    }

    return member;
}