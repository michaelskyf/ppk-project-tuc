#pragma once

#include <cstddef>
#include <vector>
#include <string>

/**
 * @brief Structure used for reading inputs/writing outputs
 */
struct Input
{
	size_t nodeID;
	bool value;
};

typedef Input Output;
typedef std::vector<Input> InputLine;
typedef std::vector<Output> OutputLine;

/**
 * @brief Parse given file
 *
 * @param[in]	filename	Path to the file containing inputs
 *
 * @return		Vector of input lines
 */
std::vector<InputLine> get_inputs(const std::string& filename);