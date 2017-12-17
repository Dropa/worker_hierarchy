#pragma once

/**
 * Base class for worker (leaf) and bundle (composite).
 */
class component {
public:
	virtual ~component() = default;
	virtual void traverse(const int) = 0;
};