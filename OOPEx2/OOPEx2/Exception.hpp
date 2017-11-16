#pragma once

#include <exception>

struct Exception : public std::exception {
	virtual const char* what() const noexcept override {
		return "Mimo!\n";
	}
};