/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {
    auto* a = new Article(client, barCode);
    a->setPresent(present);
    a->setDeliverHome(deliverHome);
    return a;
}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {
    if (bags.back().size() != BAG_SIZE && !bags.empty()) {
        bags.back().push(article);
        return;
    }
    stack<Article*> bag;
    bag.push(article);
    bags.push_back(bag);
}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {
	vector<Article*> presents;

	for (auto &bag : bags) {
	    vector<Article*> notPresents = {};
	    while (!bag.empty()) {
	        if (bag.top()->getPresent())
	            presents.push_back(bag.top());
	        else
	            notPresents.push_back(bag.top());
	        bag.pop();
	    }
	    for (auto it = notPresents.rbegin(); it != notPresents.rend(); it++)
	        bag.push(*it);
	    notPresents.clear();
	}

	return presents;
}

