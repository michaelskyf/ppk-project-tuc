#pragma once

#include <cstddef>
#include <vector>
#include <string>

struct Input
{
	size_t nodeID;
	bool value;
};

/**
 * @brief Parsed single line from the input file
 */
typedef std::vector<Input> InputLine;
typedef InputLine OutputLine;

/**
 * @brief Parse given file
 */
std::vector<InputLine> get_inputs(const std::string& filename);