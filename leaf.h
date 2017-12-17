#pragma once
#include "component.h"
#include <iostream>
#include <string>

/**
 * Class that holds worker.
 */
class leaf : public component {
	std::string first_;
	std::string last_;
	std::string role_;
public:
	/**
	 * Constructor.
	 */
	explicit leaf(const std::string first, const std::string last, const std::string role) {
		first_ = first;
		last_ = last;
		role_ = role;
	}
	/**
	 * Print worker in this leaf.
	 */
	void traverse(const int) override {
		std::cout << first_ << " " << last_ << " " << "(" << role_ << ")" << std::endl;
	}
};