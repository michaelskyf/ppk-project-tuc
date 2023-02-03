/**
 * @file parser_input.hpp
 *
 * @brief Functions and structures related to parsing the input file
 */

#pragma once

#include <cstddef>
#include <vector>
#include <string>

/**
 * @brief Structure used for reading inputs/writing outputs
 */
struct Input
{
	/// ID of the node
	size_t nodeID;
	/// Binary representation of the state of the node
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