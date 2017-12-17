#pragma once
#include "component.h"
#include <vector>

/**
 * Class that holds worker bundle.
 */
class composite : public component {
	std::vector <component*> children_;
public:
	/**
	 * Add new children to this bundle.
	 */
	void add(component *ele) {
		children_.push_back(ele);
	}
	/**
	 * Print out every children in this bundle.
	 * 
	 * This function might call itself and will increase indent if that happens.
	 */
	void traverse(const int indent) override {
		for (auto i = 0; i < indent; i++)
		{
			std::cout << "    ";
		}
		for (auto i = 0; i < children_.size(); i++) {
			children_[i]->traverse(indent + 1);
		}
	}
};
