//
// Created by Sam on 3/18/2018.
//

#ifndef WHISPERERENGINE_CONTAINER_H
#define WHISPERERENGINE_CONTAINER_H


#include "Utilities/Exportable.h"

class Card;

class Container
    : public Exportable,
      public std::enable_shared_from_this<Container>
{
public:
    std::vector<std::shared_ptr<Card>> cards;

    json getJSON() override;

    std::shared_ptr<Card> findCard(const std::string& tag);
    int count();
    void shuffle();

    virtual void addCard(const std::shared_ptr<Card>& card);
    void removeCard(const std::shared_ptr<Card>& card);

    explicit Container(const std::vector<std::shared_ptr<Card>>& cards);
    Container();
    virtual ~Container();
};


#endif //WHISPERERENGINE_CONTAINER_H
